#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Engine
{
private:
    Window m_Window;
public:
    Engine()
    {
        m_Window = nullptr;
    }
};