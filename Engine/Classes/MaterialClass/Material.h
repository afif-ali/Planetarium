#pragma once


#include <memory>
#include <variant>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Classes/ShaderClass/Shader.h"
#include "Classes/TextureClass/Texture.h"

using MaterialParameter = std::variant<
    float,
    int,
    bool,
    glm::vec2,
    glm::vec3,
    glm::vec4,
    std::shared_ptr<Texture>
>;


class BasicMaterial
{
public:
    std::unique_ptr<Shader> shader = nullptr;
    std::unordered_map<std::string, MaterialParameter> parameter;
    
    BasicMaterial(std::unique_ptr<Shader> shader);
    void Update();
};