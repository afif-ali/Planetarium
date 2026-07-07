#include "Window.h"


void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    m_Width = width;
    m_Height = height;
    updateViewport();
}

Window::Window(unsigned int width, unsigned int height, const char *title)
{
    ID = glfwCreateWindow(width, height, title, NULL, NULL);
    if (ID == nullptr)
    {
        std::cout << "ERROR: Failed to initialize GLAD!" << std::endl;
        glfwTerminate();
    }

    int icon_w, icon_h, icon_c;

    icon.pixels = stbi_load("res/app.png", &icon_w, &icon_h, &icon_c, 4);

    if (icon.pixels)
    {
        icon.width = icon_w;
        icon.height = icon_h;

        glfwSetWindowIcon(ID, 1, &icon);

        stbi_image_free(icon.pixels);
    }

    m_Width = width;
    m_Height = height;
    m_Title = title;

    glfwMakeContextCurrent(ID);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR: Failed to initialize GLAD!" << std::endl;
        glfwTerminate();
    }
    updateViewport();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glfwSetFramebufferSizeCallback(ID, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);
}

bool Window::isOpen()
{
    return !glfwWindowShouldClose(ID);
}

void Window::updateViewport()
{
    glViewport(viewportOffsetLeft, viewportOffsetBottom, m_Width - viewportOffsetLeft - viewportOffsetRight, m_Height - viewportOffsetBottom - viewportOffsetTop); 
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

void Window::setTitle(std::string title)
{
    glfwSetWindowTitle(ID, title.c_str());
    m_Title = title.c_str();
}