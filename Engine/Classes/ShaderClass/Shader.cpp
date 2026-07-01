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

Shader::Shader(const char* vs_path, const char* fs_path)
{
    std::string vs_code;
    std::string fs_code;
    std::ifstream vs_file;
    std::ifstream fs_file;
    
    vs_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fs_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        vs_file.open(vs_path);
        fs_file.open(fs_path);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vs_file.rdbuf();
        fShaderStream << fs_file.rdbuf();		
        vs_file.close();
        fs_file.close();
        vs_code = vShaderStream.str();
        fs_code = fShaderStream.str();		
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR: Failed to read shader file (VERT: " << vs_path << " FRAG: " << fs_path << ")" << std::endl;
    }
    const char* vs_source = vs_code.c_str();
    const char* fs_source = fs_code.c_str();
    
    unsigned int vertexShader;
    if (CompileVertexShader(vs_source, &vertexShader) == 0)
        std::cout << "SUCCESS: Compiled vertex shader (" << vs_path << ")" << std::endl;
    else
        std::cout << "ERROR: Failed to compile vertex shader (" << vs_path << ") : " << infoLog << std::endl;

    unsigned int fragmentShader;
    if (CompileFragmentShader(fs_source, &fragmentShader) == 0)
        std::cout << "SUCCESS: Compiled fragment shader (" << fs_path << ")" << std::endl;
    else
        std::cout << "ERROR: Failed to compile fragment shader (" << fs_path << ") : " << infoLog << std::endl;
    

    ID = glCreateProgram();

    glAttachShader(ID, fragmentShader);
    glAttachShader(ID, vertexShader);
    glLinkProgram(ID);

    int  success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR: Failed to link shader program (VERT: " << vs_path << " FRAG: " << fs_path << ") : " << infoLog << std::endl << std::endl;
    }
    else
        std::cout << "SUCCESS: Linked shader program (VERT: " << vs_path << " FRAG: " << fs_path << ")" << std::endl << std::endl;

    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}

void Shader::Use()
{
    glUseProgram(ID);
}

int Shader::Uniform(const char *uniform)
{
    return glGetUniformLocation(ID, uniform);
}
