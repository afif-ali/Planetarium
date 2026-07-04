#include "Material.h"


BasicMaterial::BasicMaterial(std::unique_ptr<Shader> shader)
{
    this->shader = std::move(shader);
}

void BasicMaterial::Update()
{
    shader->Use();
    glUniform3f(shader->Uniform("u_albedo"), albedo.x, albedo.y, albedo.z);
    if (useTexture)
    {
        texture->texUnit(*shader, "u_texture");
        texture->Bind();
    }
    glUniform1i(shader->Uniform("u_useTexture"), useTexture);
    glUniform1i(shader->Uniform("glow"), glow);
}