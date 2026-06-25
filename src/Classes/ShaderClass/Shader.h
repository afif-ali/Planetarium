#pragma once

#include <glad/glad.h>
#include <iostream>

class Shader
{
private:
    unsigned int ID;
    char infoLog[512];

    int CompileVertexShader(const char* source, unsigned int* shader);
    int CompileFragmentShader(const char* source, unsigned int* shader);

public:
    Shader(const char* vs_source, const char* fs_source);

    void Use();
    void Delete();
};