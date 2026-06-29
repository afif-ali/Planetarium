#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "Classes/MeshClass/Mesh.h"
#include "Classes/MaterialClass/Material.h"
#include "Classes/ShaderClass/Shader.h"
#include "Classes/TextureClass/Texture.h"
#include "Classes/EngineClass/Engine.h"


std::vector<Vertex> vertices = {
    {glm::vec3( -0.5f, -0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 0.0f )},
    {glm::vec3(  0.5f,  0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 1.0f )},
    {glm::vec3(  0.5f, -0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 0.0f )},
    {glm::vec3(  0.5f,  0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 1.0f )},
    {glm::vec3( -0.5f,  0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 1.0f )},
    {glm::vec3( -0.5f, -0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 0.0f )},

    {glm::vec3( -0.5f, -0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 0.0f )},
    {glm::vec3(  0.5f, -0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 0.0f )},
    {glm::vec3(  0.5f,  0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 1.0f )},
    {glm::vec3(  0.5f,  0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 1.0f )},
    {glm::vec3( -0.5f,  0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 1.0f )},
    {glm::vec3( -0.5f, -0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 0.0f )},

    {glm::vec3( -0.5f,  0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 0.0f )},
    {glm::vec3( -0.5f,  0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 1.0f )},
    {glm::vec3( -0.5f, -0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 1.0f )},
    {glm::vec3( -0.5f, -0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 1.0f )},
    {glm::vec3( -0.5f, -0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 0.0f )},
    {glm::vec3( -0.5f,  0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 0.0f )},

    {glm::vec3(  0.5f,  0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 0.0f )},
    {glm::vec3(  0.5f,  0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 1.0f )},
    {glm::vec3(  0.5f, -0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 1.0f )},
    {glm::vec3(  0.5f, -0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 1.0f )},
    {glm::vec3(  0.5f, -0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 0.0f )},
    {glm::vec3(  0.5f,  0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 0.0f )},

    {glm::vec3( -0.5f, -0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 1.0f )},
    {glm::vec3(  0.5f, -0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 1.0f )},
    {glm::vec3(  0.5f, -0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 0.0f )},
    {glm::vec3(  0.5f, -0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 0.0f )},
    {glm::vec3( -0.5f, -0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 0.0f )},
    {glm::vec3( -0.5f, -0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 1.0f )},

    {glm::vec3( -0.5f,  0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 1.0f )},
    {glm::vec3(  0.5f,  0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 1.0f )},
    {glm::vec3(  0.5f,  0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 0.0f )},
    {glm::vec3(  0.5f,  0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 1.0f, 0.0f )},
    {glm::vec3( -0.5f,  0.5f,  0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 0.0f )},
    {glm::vec3( -0.5f,  0.5f, -0.5f ),glm::vec3( 1.0f, 1.0f, 1.0f ),glm::vec2( 0.0f, 1.0f )}
};
std::vector<unsigned int> indices = {
    0, 1, 2,
    3, 4, 5,

    6, 7, 8,
    9, 10, 11,

    12, 13, 14,
    15, 16, 17,

    18, 19, 20,
    21, 22, 23,

    24, 25, 26,
    27, 28, 29,

    30, 31, 32,
    33, 34, 35
};

int main()
{
    Engine engine;
    engine.Init(800, 800, "Planetarium");
    engine.Run();

    return 0;
}

void Engine::Run()
{   
    Mesh cube(vertices, indices, std::make_unique<BasicMaterial>( std::make_unique<Shader>("./res/vert.glsl", "./res/frag.glsl") ));
    cube.material->albedo = glm::vec3(1.0, 0.0, 0.0);
    cube.material->useTexture = true;
    cube.material->texture = std::make_unique<Texture>("wall.jpg", GL_TEXTURE_2D, 0, GL_RGB);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    
    while (window->isOpen())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        
        cube.material->shader->Use();
        glUniformMatrix4fv(cube.material->shader->Uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(cube.material->shader->Uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(cube.material->shader->Uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));

        cube.Draw();

        glfwSwapBuffers(window->ID);
        glfwPollEvents();
    }
}