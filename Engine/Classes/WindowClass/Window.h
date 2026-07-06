#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Window
{
private:
    inline static unsigned int m_Width = 0;
    inline static unsigned int m_Height = 0;
    const char* m_Title;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
    GLFWwindow* ID = nullptr;
    inline static unsigned int viewportOffsetTop = 0;
    inline static unsigned int viewportOffsetLeft = 0;
    inline static unsigned int viewportOffsetBottom = 0;
    inline static unsigned int viewportOffsetRight = 0;

    Window(unsigned int width, unsigned int height, const char* title);
    bool isOpen();

    static void updateViewport();
    unsigned int getWidth();
    unsigned int getHeight();
    const char* getTitle();
    void setTitle(std::string title);
};