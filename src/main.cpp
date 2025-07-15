#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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

int main()
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

    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
