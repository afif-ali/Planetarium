#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.h"

int main()
{
    Engine::Init(1920, 1080, "Planetarium");
    Engine::Run();
    glfwTerminate();
    return 0;
}
