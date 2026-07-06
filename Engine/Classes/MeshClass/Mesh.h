#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "Classes/VAOClass/VAO.h"
#include "Classes/VBOClass/VBO.h"
#include "Classes/EBOClass/EBO.h"
#include "Classes/MaterialClass/Material.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 uv;
};

class Mesh
{
private:
    VAO vao;
    std::unique_ptr<VBO> vbo;
    std::unique_ptr<EBO> ebo;
    glm::mat4 model = glm::mat4(1.0f);

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::unique_ptr<BasicMaterial> material;

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

    bool DrawLines = false;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::unique_ptr<BasicMaterial> material);
    void Draw();
};
