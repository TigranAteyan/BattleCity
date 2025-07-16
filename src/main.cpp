#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Renderer/ShaderProgram.h"
#include "Resources/ResourcManeger.h"

GLfloat point[] = 
{
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

GLfloat colors[] =
{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,  
};

int windowSize_X = 640;
int windowSize_Y = 480;

void glfwWindowSizeCallBack(GLFWwindow* window, int width, int height)
{
    windowSize_X = width;
    windowSize_Y = height;
    glViewport(0, 0, windowSize_X, windowSize_Y);
}

void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(int argv, char** argc)
{
    if (!glfwInit())
    {
        std::cerr << "glfwInit failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(windowSize_X, windowSize_Y, "Battle City", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Can't load GLAD!" << std::endl;
        return -1;
    }

    glfwSetWindowSizeCallback(window, glfwWindowSizeCallBack);
    glfwSetKeyCallback(window, glfwKeyCallBack);

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

    {
        ResourceManager resourceManager(argc[0]);
        auto defaultShaderProgram = resourceManager.loadShaders("Default", "res/shader/vertex.txt", "res/shader/fragment.txt");

        if (!defaultShaderProgram)
        {
        std::cerr << "Can't create shader program: Defalut" << std::endl;
        return -1;
        }

        GLuint pointers_vbo = 0;
        glGenBuffers(1, &pointers_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, pointers_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, pointers_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            defaultShaderProgram->use();
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
