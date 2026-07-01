#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.h"

int main()
{
    Engine::Init(800, 800, "Planetarium");
    Engine::Run();
    glfwTerminate();
    return 0;
}
