#pragma once


#include <glad/glad.h>
#include "Classes/VBOClass/VBO.h"

class VAO
{
public:
    unsigned int ID;

    VAO();
    ~VAO();

    void LinkAttribute(VBO& VBO, unsigned int layout, unsigned int numComponents, GLenum type, GLsizeiptr stride, void* offset);

    void Bind();
    void Unbind();
};