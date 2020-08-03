#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "src/extra/extra.h"
#include "src/renderer/shaderProgram.h"
#include "src/resource_manager/ResourceManager.h"

using namespace std;

int winSizeX = 640, winSizeY = 480;

GLfloat points[] = {
     0.0,  0.5,  0.0,
     0.5, -0.5,  0.0,
    -0.5, -0.5,  0.0,
    -1.0,  0.5,  0.0
};

GLuint index[] = {
    0, 1, 2,
    2, 3, 0
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    5.0f, 5.0f, 1.0f
};

string vertex_shader;

string fragment_shader;

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

    glfwSetWindowSizeCallback(pWindow, window_size_callback);
    glfwSetKeyCallback(pWindow, key_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
        ext::err("Cant load glad!");

    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

    ResourceManager rManager;

    vertex_shader = rManager.getSource("..\\res\\shaders\\vertex.txt");
    fragment_shader = rManager.getSource("..\\res\\shaders\\fragment.txt");

    ShaderProgram shader(vertex_shader, fragment_shader);


    GLuint ebo, vao, points_vbo, colors_vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &ebo);
    glGenBuffers(1, &points_vbo);
    glGenBuffers(1, &colors_vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    glBindVertexArray(0);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        shader.draw();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}