#include "Material.h"



BasicMaterial::BasicMaterial(std::unique_ptr<Shader> shader)
{
    this->shader = std::move(shader);
}


void BasicMaterial::Update()
{
    shader->Use();

    int textureUnit = 0;

    for (auto& [name, value] : parameter)
    {
        std::visit([&](auto&& v)
        {
            using T = std::decay_t<decltype(v)>;

            if constexpr (std::is_same_v<T, float>)
            {
                glUniform1f(shader->Uniform(name.c_str()), v);
            }
            else if constexpr (std::is_same_v<T, int>)
            {
                glUniform1i(shader->Uniform(name.c_str()), v);
            }
            else if constexpr (std::is_same_v<T, bool>)
            {
                glUniform1i(shader->Uniform(name.c_str()), v);
            }
            else if constexpr (std::is_same_v<T, glm::vec2>)
            {
                glUniform2fv(shader->Uniform(name.c_str()), 1, &v.x);
            }
            else if constexpr (std::is_same_v<T, glm::vec3>)
            {
                glUniform3fv(shader->Uniform(name.c_str()), 1, &v.x);
            }
            else if constexpr (std::is_same_v<T, glm::vec4>)
            {
                glUniform4fv(shader->Uniform(name.c_str()), 1, &v.x);
            }
            else if constexpr (std::is_same_v<T, std::shared_ptr<Texture>>)
            {
                if (v)
                {
                    v->Bind();
                    v->texUnit(*shader, name.c_str());
                }
            }

        }, value);
    }
}

