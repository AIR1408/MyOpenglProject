#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "src/renderer/shaderProgram.h"

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
    1.0f, 0.0f, 1.0f,
};

const char* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"    color = vertex_color;"
"    gl_Position = vec4(vertex_position, 1.0);"
"}";

const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main(){"
"   frag_color = vec4(color, 1.0);"
"}";

int err(char* msg) {
    std::cout << *msg;
    system("pause");
    return -1;
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    winSizeX = width, winSizeY = height;
    glViewport(0, 0, winSizeX, winSizeY);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    GLFWwindow* pWindow;

    /* Initialize the library */
    if (!glfwInit())
        return err("Cant init glfw.");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    pWindow = glfwCreateWindow(winSizeX, winSizeY, "MyEngine", NULL, NULL);
    if (!pWindow)
        return err("glfwCreateWindow failed!");

    glfwSetWindowSizeCallback(pWindow, window_size_callback);
    glfwSetKeyCallback(pWindow, key_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
        return err("Cant load glad!");

    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

    //glfwGetFramebufferSize(pWindow, &winSizeX, &winSizeY);
    glViewport(0, 0, winSizeX, winSizeY);

    ShaderProgram* shader = new ShaderProgram(vertex_shader, fragment_shader);


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
        shader->use();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    delete shader;
    glfwTerminate();
    return 0;
}