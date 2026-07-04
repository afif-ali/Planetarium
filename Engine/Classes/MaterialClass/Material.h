#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Classes/ShaderClass/Shader.h"
#include "Classes/TextureClass/Texture.h"


class BasicMaterial
{
public:
    std::unique_ptr<Shader> shader = nullptr;

    glm::vec3 albedo = glm::vec3(1.0f, 1.0f, 1.0f);
    std::unique_ptr<Texture> texture = nullptr;
    bool useTexture = false;
    bool glow = false;
    
    BasicMaterial(std::unique_ptr<Shader> shader);
    void Update();
};