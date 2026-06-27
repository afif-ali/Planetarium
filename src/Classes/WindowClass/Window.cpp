#include "Window.h"


void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(unsigned int width, unsigned int height, const char *title)
{
    ID = glfwCreateWindow(width, height, title, NULL, NULL);
    if (ID == nullptr)
    {
        std::cout << "ERROR: Failed to initialize GLAD!" << std::endl;
        glfwTerminate();
    }

    m_Width = width;
    m_Height = height;
    m_Title = title;

    glfwMakeContextCurrent(ID);
    std::cout << "test" << std::endl;
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR: Failed to initialize GLAD!" << std::endl;
        glfwTerminate();
    }
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glfwSetFramebufferSizeCallback(ID, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);
}

bool Window::isOpen()
{
    return !glfwWindowShouldClose(ID);
}

unsigned int Window::getWidth()
{
    return m_Width;
}

unsigned int Window::getHeight()
{
    return m_Height;
}

const char *Window::getTitle()
{
    return m_Title;
}

void Window::setTitle(const char *title)
{
    glfwSetWindowTitle(ID, title);
    m_Title = title;
}