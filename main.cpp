#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <cmath>
#include <vector>

#include "src/extra/extra.h"
#include "src/renderer/shaderProgram.h"
#include "src/resource_manager/ResourceManager.h"
#include "src/renderer/Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

int winSizeX = 640, winSizeY = 480;

vector<ext::Vertex> vert = {
    ext::Vertex{glm::vec3(-0.5, -0.5, -0.5),   glm::vec3(0.0,  0.0, -1.0),   glm::vec2(0.0,  0.0)},
    ext::Vertex{glm::vec3( 0.5,  0.5, -0.5),   glm::vec3(0.0,  0.0, -1.0),   glm::vec2(1.0,  1.0)},
    ext::Vertex{glm::vec3( 0.5, -0.5, -0.5),   glm::vec3(0.0,  0.0, -1.0),   glm::vec2(1.0,  0.0)},
    ext::Vertex{glm::vec3(-0.5,  0.5, -0.5),   glm::vec3(0.0,  0.0, -1.0),   glm::vec2(0.0,  1.0)},

    ext::Vertex{glm::vec3(-0.5,  0.5, -0.5),   glm::vec3(0.0,  1.0,  0.0),   glm::vec2(0.0,  0.0)},
    ext::Vertex{glm::vec3( 0.5,  0.5,  0.5),   glm::vec3(0.0,  1.0,  0.0),   glm::vec2(1.0,  1.0)},
    ext::Vertex{glm::vec3( 0.5,  0.5, -0.5),   glm::vec3(0.0,  1.0,  0.0),   glm::vec2(1.0,  0.0)},
    ext::Vertex{glm::vec3(-0.5,  0.5,  0.5),   glm::vec3(0.0,  1.0,  0.0),   glm::vec2(0.0,  1.0)},

    ext::Vertex{glm::vec3(0.5, -0.5, -0.5),   glm::vec3(1.0,  0.0,  0.0),   glm::vec2(0.0,  0.0)},
    ext::Vertex{glm::vec3(0.5,  0.5,  0.5),   glm::vec3(1.0,  0.0,  0.0),   glm::vec2(1.0,  1.0)},
    ext::Vertex{glm::vec3(0.5,  0.5, -0.5),   glm::vec3(1.0,  0.0,  0.0),   glm::vec2(1.0,  0.0)},
    ext::Vertex{glm::vec3(0.5, -0.5,  0.5),   glm::vec3(1.0,  0.0,  0.0),   glm::vec2(0.0,  1.0)},
};

vector<GLuint> ind = {
    0, 1, 2, 3, 1, 0,
    4, 5, 6, 7, 5, 4,
    8, 9, 10, 11, 9, 8
};

vector<ext::Vertex> vert2 = {
    ext::Vertex{glm::vec3(0.0, 0.0,  0.0),   glm::vec3(1.0,  1.0,  1.0),   glm::vec2(0.0,  0.0)},
    ext::Vertex{glm::vec3(0.0, 0.1,  0.0),   glm::vec3(1.0,  1.0,  1.0),   glm::vec2(0.0,  0.0)},
    ext::Vertex{glm::vec3(0.0, 0.05,  1.0),   glm::vec3(1.0,  1.0,  1.0),   glm::vec2(0.0,  0.0)},

    ext::Vertex{glm::vec3(0.0, 0.0,  0.0),   glm::vec3(1.0,  1.0,  1.0),   glm::vec2(0.0,  0.0)},
    ext::Vertex{glm::vec3(0.0, 0.1,  0.0),   glm::vec3(1.0,  1.0,  1.0),   glm::vec2(0.0,  0.0)},
    ext::Vertex{glm::vec3(2.0, 0.05,  0.0),   glm::vec3(1.0,  1.0,  1.0),   glm::vec2(0.0,  0.0)},

    ext::Vertex{glm::vec3(0.0, 0.0,  0.0),   glm::vec3(1.0,  1.0,  1.0),   glm::vec2(0.0,  0.0)},
    ext::Vertex{glm::vec3(0.1, 0.0,  0.1),   glm::vec3(1.0,  1.0,  1.0),   glm::vec2(0.0,  0.0)},
    ext::Vertex{glm::vec3(0.05, 3.0,  0.05),   glm::vec3(1.0,  1.0,  1.0),   glm::vec2(0.0,  0.0)},
};

vector<GLuint> ind2 = {
    0, 1, 2,  3, 4, 5,  6, 7, 8
};

string* vertex_shader, * fragment_shader;

bool firstMouse = true;
float
    yaw = 110.0, pitch = -20.0,
    lastX = winSizeX / 2.0, lastY = winSizeY / 2.0,
    deltaTime = 0.0, lastFrame = 0.0, currentFrame = 0.0,
    cameraSpeed;
glm::vec3 cameraPos, cameraFront, cameraUp;
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 0.1f);
glm::vec3 lightPos = glm::vec3(-10.0f, 10.0f, -10.0f);


void window_size_callback(GLFWwindow* window, int width, int height) {
    winSizeX = width, winSizeY = height;
    glViewport(0, 0, winSizeX, winSizeY);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    cameraSpeed = 3.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

int main()
{
    GLFWwindow* pWindow;

    /* Initialize the library */
    if (!glfwInit())
        ext::err("Cant init glfw.");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    pWindow = glfwCreateWindow(winSizeX, winSizeY, "MyEngine", NULL, NULL);
    if (!pWindow)
        ext::err("glfwCreateWindow failed!");

    glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowSizeCallback(pWindow, window_size_callback);
    glfwSetKeyCallback(pWindow, key_callback);
    glfwSetCursorPosCallback(pWindow, mouse_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
        ext::err("Cant load glad!");

    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

    ResourceManager manager;
    vertex_shader = new string, fragment_shader = new string;
    *vertex_shader = manager.loadSource("..\\res\\shaders\\vertex.txt");
    *fragment_shader = manager.loadSource("..\\res\\shaders\\fragment.txt");
    //GLuint* tex = manager.loadTexture("..\\res\\textures\\cobblestone.png");

    {
        ShaderProgram shader(*vertex_shader, *fragment_shader);
        if (!shader.isCompiled()) exit(-1);
        delete vertex_shader, fragment_shader;

        
        Mesh m_obj(vert, ind);
        Mesh m_obj2(vert2, ind2);


        shader.use();
        //shader.setInt("ourTexture", 0);
        
        glm::mat4 cubemodel = glm::mat4(1.0);
        glm::mat4 coord_model = glm::mat4(1.0);
        glm::mat4 light_model = glm::mat4(1.0);

        glm::mat4 view = glm::mat4(1.0);
        glm::mat4 projection = glm::perspective(glm::radians(45.f), float(winSizeX / winSizeY), 0.1f, 100.f);

        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
        cubemodel = glm::scale(cubemodel, glm::vec3(2.0, 2.0, 2.0));
        cubemodel = glm::translate(cubemodel, glm::vec3(-1.0, -1.0, -1.0));

        shader.setVector("lightColor", lightColor);
        shader.setVector("lightPos", lightPos);
        shader.setMatrix("projection", glm::value_ptr(projection));

        cameraPos    = glm::vec3(4.0f, 4.0f,-10.0f);
        cameraUp     = glm::vec3(0.0f, 1.0f, 0.0f);

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glEnable(GL_DEPTH_TEST);
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))
        {

            currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;


            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader.use();



            view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            shader.setMatrix("view", glm::value_ptr(view));


            shader.setMatrix("model", glm::value_ptr(cubemodel));
            m_obj.draw();

            shader.setMatrix("model", glm::value_ptr(coord_model));
            m_obj2.draw();

            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}