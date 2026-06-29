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
