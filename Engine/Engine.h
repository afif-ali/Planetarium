#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <unordered_map>

#include "Classes/WindowClass/Window.h"
#include "Classes/MeshClass/Mesh.h"
#include "Classes/LightClass/Light.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Engine
{
private:
    inline static float lastX = 0.0f;
    inline static float lastY = 0.0f;
    inline static bool firstMouse = true;
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

public:
    inline static std::unique_ptr<Window> window = nullptr;
    inline static glm::mat4 view = glm::mat4(1.0);
    inline static std::unordered_map<std::string, std::unique_ptr<Mesh>> meshes{};
    inline static std::unordered_map<std::string, std::unique_ptr<Light>> lights{};

    inline static unsigned int fps = 0;

    static void Init(unsigned int height, unsigned int width, const char* title);
    static void Run();
    static void Begin();
    static void Update(float delta);
    static void UpdateUI(float delta);
    static void End();
    static void MouseMovement(float xoffset, float yoffset);
};
