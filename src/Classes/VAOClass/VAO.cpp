#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO& VBO, unsigned int layout)
{
    VBO.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind()
{
    glBindVertexArray(ID);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}