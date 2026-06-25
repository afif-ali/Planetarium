#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Classes/VAOClass/VAO.h"
#include "Classes/VBOClass/VBO.h"
#include "Classes/EBOClass/EBO.h"
#include "Classes/ShaderClass/Shader.h"

float vertices[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    if (!glfwInit())
    {
        std::cout << "ERROR: Failed to initialize GLFW!" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Planetarium", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "ERROR: Failed to open window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR: Failed to initialize GLAD!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    {
        Shader shader("./res/vert.glsl", "./res/frag.glsl");
        
        VAO vao;
        vao.Bind();

        VBO vbo(vertices, sizeof(vertices));
        EBO ebo(indices, sizeof(indices));

        vao.LinkVBO(vbo, 0);
        vao.Unbind();
        vbo.Unbind();
        ebo.Unbind();
    
        
        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            
            shader.Use();
            vao.Bind();
            glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}