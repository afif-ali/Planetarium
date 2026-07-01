#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include "Classes/ShaderClass/Shader.h"

class Texture 
{
public:
    unsigned int ID;
    GLenum type;
    unsigned int slot;

    Texture(const char *image, GLenum texType, unsigned int slot, GLenum format);
    ~Texture();

    void texUnit(Shader& shader, const char* uniform);
    void Bind();
    void Unbind();
};