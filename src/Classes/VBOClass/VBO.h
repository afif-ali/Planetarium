#pragma once

#include <glad/glad.h>

class VBO
{
public:
    unsigned int ID;

    VBO(float* vertices, GLsizeiptr size);
    ~VBO();

    void Bind();
    void Unbind();
};