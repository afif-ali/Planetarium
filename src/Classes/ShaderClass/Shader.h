#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
    unsigned int ID;
    char infoLog[512];


    int CompileVertexShader(const char* source, unsigned int* shader);
    int CompileFragmentShader(const char* source, unsigned int* shader);

public:
    Shader(const char* vs_path, const char* fs_path);
    ~Shader();

    void Use();
};