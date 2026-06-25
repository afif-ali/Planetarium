#pragma once


#include <glad/glad.h>
#include "Classes/VBOClass/VBO.h"

class VAO
{
public:
    unsigned int ID;

    VAO();
    ~VAO();

    void LinkVBO(VBO& VBO, unsigned int layout);

    void Bind();
    void Unbind();
};