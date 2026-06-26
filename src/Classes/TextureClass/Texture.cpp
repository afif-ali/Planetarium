#include "Texture.h"

Texture::Texture(const char *image, GLenum texType, unsigned int slot, GLenum format)
{
    type = texType;
    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(texType, ID);
    
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(image, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(texType, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(texType);
    }
    else
        std::cout << "Failed to load texture" << std::endl;
    stbi_image_free(data);
    glBindTexture(texType, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}

void Texture::texUnit(Shader shader, const char *uniform, unsigned int unit)
{
    unsigned int tex_uniform = glGetUniformLocation(shader.ID, uniform);
    shader.Use();
    glUniform1i(tex_uniform, unit);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
