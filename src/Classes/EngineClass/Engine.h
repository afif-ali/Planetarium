#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

#include "Classes/WindowClass/Window.h"


class Engine
{
public:
    std::unique_ptr<Window> window;

    ~Engine();

    void Init(unsigned int height, unsigned int width, const char* title);
    void Run();
};

Engine::~Engine()
{
    glfwTerminate();
}

void Engine::Init(unsigned int height, unsigned int width, const char *title)
{
    if (!glfwInit())
    {
        std::cout << "ERROR: Failed to initialize GLFW!" << std::endl;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = std::make_unique<Window>(height, width, title);
}
