#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:

char infoLog[512];

int CompileVertexShader(const char* source, unsigned int* shader);
int CompileFragmentShader(const char* source, unsigned int* shader);

public:
    unsigned int ID;
    Shader(const char* vs_path, const char* fs_path);
    ~Shader();

    void Use();
    int Uniform(const char* uniform);
};