#include "Engine.h"


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
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    lastX = width / 2;
    lastY = height / 2;

    glfwSetCursorPosCallback(window->ID, mouse_callback);
}

void Engine::Run()
{
    Engine::Begin();
    
    //glfwSwapInterval(1);

    float lastFrame = 0.0f;

    float fpsTimer = 0.0f;
    int frameCount = 0;

    while (window->isOpen())
    {
        float currentFrame = glfwGetTime();
        float delta = currentFrame - lastFrame;
        
        lastFrame = currentFrame;

        float deltaMs = delta * 1000.0f;
        fpsTimer += delta;
        frameCount++;

        if (fpsTimer >= 1.0f)
        {
            fps = frameCount;

            fpsTimer -= 1.0f;
            frameCount = 0;
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        Engine::Update(delta);

        glm::mat4 projection = glm::perspective(glm::radians(60.0f), ((float) Engine::window->getWidth() - Engine::window->viewportOffsetLeft - Engine::window->viewportOffsetRight) / (Engine::window->getHeight() - Engine::window->viewportOffsetBottom - Engine::window->viewportOffsetTop), 0.1f, 1000.0f);
        for (const auto& [key, mesh] : meshes) {
            mesh->material->shader->Use();
            glUniformMatrix4fv(mesh->material->shader->Uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(mesh->material->shader->Uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
            mesh->Draw();
        }

        Engine::UpdateUI(delta);

        glfwSwapBuffers(window->ID);
        glfwPollEvents();
    }
    Engine::End();
}