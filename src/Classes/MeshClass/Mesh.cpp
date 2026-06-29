#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::unique_ptr<BasicMaterial> material)
{
    this->vertices = vertices;
    this->indices = indices;
    this->material = std::move(material);

    vao.Bind();
    
    vbo = std::make_unique<VBO>(this->vertices.data(), this->vertices.size() * sizeof(Vertex));
    ebo = std::make_unique<EBO>(this->indices.data(), this->indices.size() * sizeof(unsigned int));
    
    vao.LinkAttribute(*vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
    vao.LinkAttribute(*vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));
    vao.LinkAttribute(*vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    
    vao.Unbind();
    vbo->Unbind();
    ebo->Unbind();
}
void Mesh::Draw()
{
    material->shader->Use();
    material->Update();
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
};