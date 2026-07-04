#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.h"

int main()
{
    Engine::Init(1080, 720, "Planetarium");
    Engine::Run();
    glfwTerminate();
    return 0;
}
