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
    glm::vec2 uv;
};

class Mesh
{
private:
    VAO vao;
    std::unique_ptr<VBO> vbo;
    std::unique_ptr<EBO> ebo;
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::unique_ptr<BasicMaterial> material;


    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::unique_ptr<BasicMaterial> material);
    void Draw();
};
