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
    material->Update();
    
    model = glm::mat4(1.0f);
    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.x), {1,0,0});
    model = glm::rotate(model, glm::radians(rotation.y), {0,1,0});
    model = glm::rotate(model, glm::radians(rotation.z), {0,0,1});

    model = glm::scale(model, scale);
    glUniformMatrix4fv(material->shader->Uniform("model"), 1, GL_FALSE, glm::value_ptr(model));

    vao.Bind();
    if (DrawLines)
        glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
    else
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    GLint currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
};