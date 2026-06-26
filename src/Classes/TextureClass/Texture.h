#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include "Classes/ShaderClass/Shader.h"

class Texture 
{
public:
    unsigned int ID;
    GLenum type;

    Texture(const char *image, GLenum texType, unsigned int slot, GLenum format);
    ~Texture();

    void texUnit(Shader shader, const char* uniform, unsigned int unit);
    void Bind();
    void Unbind();
};