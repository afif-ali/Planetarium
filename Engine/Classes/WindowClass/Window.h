#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Window
{
private:
    unsigned int m_Width;
    unsigned int m_Height;
    const char* m_Title;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
    GLFWwindow* ID = nullptr;

    Window(unsigned int width, unsigned int height, const char* title);
    bool isOpen();

    unsigned int getWidth();
    unsigned int getHeight();
    const char* getTitle();
    void setTitle(std::string title);
};