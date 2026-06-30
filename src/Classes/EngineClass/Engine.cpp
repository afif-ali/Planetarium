#include "Engine.h"

bool Engine::firstMouse = true;
float Engine::lastX = 0.0f;
float Engine::lastY = 0.0f;
std::unique_ptr<Window> Engine::window = nullptr;

void Engine::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    MouseMovement(xoffset, yoffset);
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

    lastX = width / 2;
    lastY = height / 2;

    glfwSetCursorPosCallback(window->ID, mouse_callback);
}
