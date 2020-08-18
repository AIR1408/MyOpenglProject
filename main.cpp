#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "src/extra/extra.h"
#include "src/renderer/shaderProgram.h"
#include "src/resource_manager/ResourceManager.h"
#include "src/renderer/Mesh.h"
#include "src/objects/Camera.h"
#include "src/renderer/Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

int winSizeX = 800, winSizeY = 600;

float del = 1.f / 3.f, dek  = 2.f / 3.f;

vector<ext::Vertex> vert = {
    {{ 1.0, -1.0, -1.0},   {0.0,  0.0, -1.0},   {dek + 0.0, 0.0 + 0.0}},
    {{-1.0,  1.0, -1.0},   {0.0,  0.0, -1.0},   {dek + del, 0.0 + 0.5}},
    {{-1.0, -1.0, -1.0},   {0.0,  0.0, -1.0},   {dek + del, 0.0 + 0.0}},
    {{ 1.0,  1.0, -1.0},   {0.0,  0.0, -1.0},   {dek + 0.0, 0.0 + 0.5}},
                          
    {{ 1.0,  1.0, -1.0},   {0.0,  1.0,  0.0},   {del + 0.0, 0.5 + 0.0}},
    {{-1.0,  1.0,  1.0},   {0.0,  1.0,  0.0},   {del + del, 0.5 + 0.5}},
    {{-1.0,  1.0, -1.0},   {0.0,  1.0,  0.0},   {del + del, 0.5 + 0.0}},
    {{ 1.0,  1.0,  1.0},   {0.0,  1.0,  0.0},   {del + 0.0, 0.5 + 0.5}},
                        
    {{ 1.0, -1.0,  1.0},   {1.0,  0.0,  0.0},   {0.0 + 0.0, 0.5 + 0.0}},
    {{ 1.0,  1.0, -1.0},   {1.0,  0.0,  0.0},   {0.0 + del, 0.5 + 0.5}},
    {{ 1.0, -1.0, -1.0},   {1.0,  0.0,  0.0},   {0.0 + del, 0.5 + 0.0}},
    {{ 1.0,  1.0,  1.0},   {1.0,  0.0,  0.0},   {0.0 + 0.0, 0.5 + 0.5}},
                    
    {{-1.0, -1.0,  1.0},   {0.0,  0.0,  1.0},   {dek + 0.0, 0.5 + 0.0}},
    {{ 1.0,  1.0,  1.0},   {0.0,  0.0,  1.0},   {dek + del, 0.5 + 0.5}},
    {{ 1.0, -1.0,  1.0},   {0.0,  0.0,  1.0},   {dek + del, 0.5 + 0.0}},
    {{-1.0,  1.0,  1.0},   {0.0,  0.0,  1.0},   {dek + 0.0, 0.5 + 0.5}},
                   
    {{-1.0, -1.0, -1.0},   {0.0, -1.0,  0.0},   {del + 0.0, 0.0 + 0.0}},
    {{ 1.0, -1.0,  1.0},   {0.0, -1.0,  0.0},   {del + del, 0.0 + 0.5}},
    {{ 1.0, -1.0, -1.0},   {0.0, -1.0,  0.0},   {del + del, 0.0 + 0.0}},
    {{-1.0, -1.0,  1.0},   {0.0, -1.0,  0.0},   {del + 0.0, 0.0 + 0.5}},
                         
    {{-1.0, -1.0, -1.0},   {-1.0, 0.0,  0.0},   {0.0 + 0.0, 0.0 + 0.0}},
    {{-1.0,  1.0,  1.0},   {-1.0, 0.0,  0.0},   {0.0 + del, 0.0 + 0.5}},
    {{-1.0, -1.0,  1.0},   {-1.0, 0.0,  0.0},   {0.0 + del, 0.0 + 0.0}},
    {{-1.0,  1.0, -1.0},   {-1.0, 0.0,  0.0},   {0.0 + 0.0, 0.0 + 0.5}},
};

vector<ext::Vertex> lightvert = {
    {{ 1.0, -1.0, -1.0},   { 0.0,  0.0,  1.0},   {dek + 0.0, 0.0 + 0.0}},
    {{-1.0,  1.0, -1.0},   { 0.0,  0.0,  1.0},   {dek + del, 0.0 + 0.5}},
    {{-1.0, -1.0, -1.0},   { 0.0,  0.0,  1.0},   {dek + del, 0.0 + 0.0}},
    {{ 1.0,  1.0, -1.0},   { 0.0,  0.0,  1.0},   {dek + 0.0, 0.0 + 0.5}},
                             
    {{ 1.0,  1.0, -1.0},   { 0.0, -1.0,  0.0},   {del + 0.0, 0.5 + 0.0}},
    {{-1.0,  1.0,  1.0},   { 0.0, -1.0,  0.0},   {del + del, 0.5 + 0.5}},
    {{-1.0,  1.0, -1.0},   { 0.0, -1.0,  0.0},   {del + del, 0.5 + 0.0}},
    {{ 1.0,  1.0,  1.0},   { 0.0, -1.0,  0.0},   {del + 0.0, 0.5 + 0.5}},

    {{ 1.0, -1.0,  1.0},   {-1.0,  0.0,  0.0},   {0.0 + 0.0, 0.5 + 0.0}},
    {{ 1.0,  1.0, -1.0},   {-1.0,  0.0,  0.0},   {0.0 + del, 0.5 + 0.5}},
    {{ 1.0, -1.0, -1.0},   {-1.0,  0.0,  0.0},   {0.0 + del, 0.5 + 0.0}},
    {{ 1.0,  1.0,  1.0},   {-1.0,  0.0,  0.0},   {0.0 + 0.0, 0.5 + 0.5}},

    {{-1.0, -1.0,  1.0},   { 0.0,  0.0, -1.0},   {dek + 0.0, 0.5 + 0.0}},
    {{ 1.0,  1.0,  1.0},   { 0.0,  0.0, -1.0},   {dek + del, 0.5 + 0.5}},
    {{ 1.0, -1.0,  1.0},   { 0.0,  0.0, -1.0},   {dek + del, 0.5 + 0.0}},
    {{-1.0,  1.0,  1.0},   { 0.0,  0.0, -1.0},   {dek + 0.0, 0.5 + 0.5}},
                             
    {{-1.0, -1.0, -1.0},   { 0.0,  1.0,  0.0},   {del + 0.0, 0.0 + 0.0}},
    {{ 1.0, -1.0,  1.0},   { 0.0,  1.0,  0.0},   {del + del, 0.0 + 0.5}},
    {{ 1.0, -1.0, -1.0},   { 0.0,  1.0,  0.0},   {del + del, 0.0 + 0.0}},
    {{-1.0, -1.0,  1.0},   { 0.0,  1.0,  0.0},   {del + 0.0, 0.0 + 0.5}},

    {{-1.0, -1.0, -1.0},   { 1.0, 0.0,  0.0},   {0.0 + 0.0, 0.0 + 0.0}},
    {{-1.0,  1.0,  1.0},   { 1.0, 0.0,  0.0},   {0.0 + del, 0.0 + 0.5}},
    {{-1.0, -1.0,  1.0},   { 1.0, 0.0,  0.0},   {0.0 + del, 0.0 + 0.0}},
    {{-1.0,  1.0, -1.0},   { 1.0, 0.0,  0.0},   {0.0 + 0.0, 0.0 + 0.5}},
};

vector<GLuint> ind = {
    0, 1, 2, 3, 1, 0,
    4, 5, 6, 7, 5, 4,
    8, 9, 10, 11, 9, 8,
    12, 13, 14, 15, 13, 12,
    16, 17, 18, 19, 17, 16,
    20, 21, 22, 23, 21, 20
};

vector<ext::Vertex> vert2 = {
    ext::Vertex{glm::vec3(0.0, 0.0,  0.0),   glm::vec3(-1.0,  0.0,  0.0),   glm::vec2( )},
    ext::Vertex{glm::vec3(0.0, 0.1,  0.0),   glm::vec3(-1.0,  0.0,  0.0),   glm::vec2( )},
    ext::Vertex{glm::vec3(0.0, 0.0,  10.),   glm::vec3(-1.0,  0.0,  0.0),   glm::vec2( )},
                                                                                       
    ext::Vertex{glm::vec3(0.0, 0.0,  0.0),   glm::vec3( 0.0,  0.0, -1.0),   glm::vec2( )},
    ext::Vertex{glm::vec3(0.0, 0.1,  0.0),   glm::vec3( 0.0,  0.0, -1.0),   glm::vec2( )},
    ext::Vertex{glm::vec3(3.0, 0.0,  0.0),   glm::vec3( 0.0,  0.0, -1.0),   glm::vec2( )},
                                                                                       
    ext::Vertex{glm::vec3(0.0, 0.0,  0.0),   glm::vec3( 1.0,  0.0,  1.0),   glm::vec2( )},
    ext::Vertex{glm::vec3(0.1, 0.0,  0.1),   glm::vec3( 1.0,  0.0,  1.0),   glm::vec2( )},
    ext::Vertex{glm::vec3(0.0, 1.0,  0.0),   glm::vec3( 1.0,  0.0,  1.0),   glm::vec2( )},
};

vector<GLuint> ind2 = {
    0, 1, 2,  3, 4, 5,  6, 7, 8
};

string* vertex_shader, * fragment_shader;

glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 0.1f);
glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);

glm::vec3 cubePositions[] = {
    glm::vec3(-3.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(10.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  10.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -10.5f)
};

void window_size_callback(GLFWwindow* window, int width, int height) {
    winSizeX = width, winSizeY = height;
    glViewport(0, 0, winSizeX, winSizeY);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
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

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
        ext::err("Cant load glad!");

    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

    ResourceManager manager("..\\res");
    ext::Texture* cubeTex = manager.loadTexture("\\cube.png");
    ext::Texture* lightTex = manager.loadTexture("\\light.png");
    
    vector<ext::Texture> cubeTexVect = { *cubeTex };
    vector<ext::Texture> lightTexVect = { *lightTex };

    {
        auto shader = manager.loadProgram();
        if (!shader.isCompiled()) exit(-1);
        delete vertex_shader, fragment_shader;

        Mesh m_obj[10] = {
            Mesh(vert, ind, cubeTexVect),
            Mesh(vert, ind, cubeTexVect),
            Mesh(vert, ind, cubeTexVect),
            Mesh(vert, ind, cubeTexVect),
            Mesh(vert, ind, cubeTexVect),
            Mesh(vert, ind, cubeTexVect),
            Mesh(vert, ind, cubeTexVect),
            Mesh(vert, ind, cubeTexVect),
            Mesh(vert, ind, cubeTexVect),
            Mesh(vert, ind, cubeTexVect)
        };

        Mesh coords(vert2, ind2, vector<ext::Texture>());
        Mesh lightCube(lightvert, ind, lightTexVect);
        
        shader.use();
        shader.setInt("Texture0", 0);
        
        
        std::vector<ext::OBJECT>* objFile = new std::vector<ext::OBJECT>;
        *objFile = manager.loadObject("\\backpack.obj");

        auto testModel = translateToModel(*objFile);
        delete objFile;


        glm::mat4 coord_model = glm::mat4(1.0);
        glm::mat4 light_model = glm::mat4(1.0);
        glm::mat4 light_model2 = glm::mat4(1.0);
        glm::mat4 modelArr[10];
        testModel->matrix = glm::translate(testModel->matrix, { 1.0, 1.0, 1.0 });
        testModel->matrix = glm::scale(testModel->matrix, { 0.5, 0.5, 0.5 });

        
        for (int i = 0; i < 10; i++)
        {
            modelArr[i] = glm::mat4(1.0f);
            modelArr[i] = glm::translate(modelArr[i], cubePositions[i]);
            float angle = 30.0f * i;
            modelArr[i] = glm::rotate(modelArr[i], glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        }
        

        glm::mat4 projection = glm::perspective(glm::radians(45.f), float(winSizeX / winSizeY), 0.1f, 100.f);

        shader.setVector("lightColor", lightColor);
        shader.setVector("lightPos", lightPos);
        shader.setMatrix("projection", projection);

        Camera mycam(glm::vec3(-9.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0));

        glm::vec3 rotor = glm::vec3(1.0, 0.0, 0.0);
        float ang = 0.01;

        double currentTime = glfwGetTime(), lastTime = currentTime, deltaTime;
        int nbFrames = 0;

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glEnable(GL_DEPTH_TEST);
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))
        {
            rotor.x = cos(ang) * rotor.x - sin(ang) * rotor.z, 
            rotor.z = sin(ang) * rotor.x + cos(ang) * rotor.z;
            lightPos = 10.0f * rotor;
            
            light_model = light_model2;
            light_model = glm::translate(light_model, lightPos);

            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            testModel->Draw(shader);


            shader.setVector("lightPos", lightPos);
            shader.setMatrix("model", light_model);
            lightCube.draw();

            shader.setMatrix("view", mycam.getViewMatrix());
            shader.setVector("viewPos", mycam.getPosition());
            mycam.Update(pWindow);
            
            
            for (int i = 0; i < 10; i++) 
            {
                shader.setMatrix("model", modelArr[i]);
                m_obj[i].draw();
            }

            shader.setMatrix("model", coord_model);
            coords.draw();


            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();

            currentTime = glfwGetTime();
            deltaTime = currentTime - lastTime;
            nbFrames++;
            if (deltaTime >= 1.0)
            {
                glfwSetWindowTitle(pWindow, std::to_string(nbFrames).c_str());
                lastTime = currentTime;
                nbFrames = 0;
            }
        }
    }

    glfwTerminate();
    return 0;
}