#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

#include "Classes/WindowClass/Window.h"


class Engine
{
private:
    static float lastX;
    static float lastY;
    static bool firstMouse;

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

public:
    static std::unique_ptr<Window> window;

    static void Init(unsigned int height, unsigned int width, const char* title);
    static void Run();
    static void MouseMovement(float xoffset, float yoffset);
};
