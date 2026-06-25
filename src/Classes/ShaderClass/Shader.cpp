#include "Shader.h"


int Shader::CompileVertexShader(const char* source, unsigned int* shader) {
    *shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
    int success;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(*shader, 512, NULL, infoLog);
        return -1;
    }
    return 0;
}

int Shader::CompileFragmentShader(const char* source, unsigned int* shader) {
    *shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
    int success;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(*shader, 512, NULL, infoLog);
        return -1;
    }
    return 0;
}

Shader::Shader(const char* vs_source, const char* fs_source)
{
    unsigned int vertexShader;
    if (CompileVertexShader(vs_source, &vertexShader) == 0)
        std::cout << "SUCCESS" << std::endl;
    else
        std::cout << "ERROR: " << infoLog << std::endl;

    unsigned int fragmentShader;
    if (CompileFragmentShader(fs_source, &fragmentShader) == 0)
        std::cout << "SUCCESS" << std::endl;
    else
        std::cout << "ERROR: " << infoLog << std::endl;
    

    ID = glCreateProgram();

    glAttachShader(ID, fragmentShader);
    glAttachShader(ID, vertexShader);
    glLinkProgram(ID);

    int  success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cerr << "ERROR: " << infoLog << std::endl;
    }
    else
        std::cout << "SUCCESS" << std::endl;

    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
}

void Shader::Use()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}