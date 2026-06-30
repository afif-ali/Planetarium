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
    Engine::Init(800, 800, "Planetarium");
    Engine::Run();
    glfwTerminate();
    return 0;
}

float yaw = 0.0;
float pitch = 0.0;

void Engine::Run()
{   
    std::unique_ptr<Mesh> cube = std::make_unique<Mesh>(vertices, indices, std::make_unique<BasicMaterial>( std::make_unique<Shader>("./res/vert.glsl", "./res/frag.glsl") ));
    cube->material->albedo = glm::vec3(1.0, 0.0, 0.0);
    cube->material->useTexture = true;
    cube->material->texture = std::make_unique<Texture>("wall.jpg", GL_TEXTURE_2D, 0, GL_RGB);

    std::unique_ptr<Mesh> greencube = std::make_unique<Mesh>(vertices, indices, std::make_unique<BasicMaterial>( std::make_unique<Shader>("./res/vert.glsl", "./res/frag.glsl") ));
    greencube->material->albedo = glm::vec3(0.0, 1.0, 0.0);
    greencube->material->useTexture = true;
    greencube->material->texture = std::make_unique<Texture>("wall.jpg", GL_TEXTURE_2D, 0, GL_RGB);

    greencube->position.x = 2.0f;


    glfwSetInputMode(window->ID, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glm::mat4 view = glm::mat4(1.0f);
    
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 cameraDir = glm::normalize(cameraPos - cameraTarget);
    glm::vec3 cameraRight = glm::normalize(glm::cross(worldUp, cameraDir));
    glm::vec3 cameraUp = glm::cross(cameraDir, cameraRight);

    while (window->isOpen())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const float radius = 5.0f;
        float camX = sin(glm::radians(yaw)) * cos(glm::radians(pitch)) * radius;
        float camY = sin(glm::radians(pitch)) * radius;
        float camZ = cos(glm::radians(yaw)) * cos(glm::radians(pitch)) * radius;
        view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        
        cube->material->shader->Use();
        glUniformMatrix4fv(cube->material->shader->Uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(cube->material->shader->Uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));
        greencube->material->shader->Use();
        glUniformMatrix4fv(greencube->material->shader->Uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(greencube->material->shader->Uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        cube->Draw();
        greencube->Draw();


        glfwSwapBuffers(window->ID);
        glfwPollEvents();
    }
}

void Engine::MouseMovement(float xoffset, float yoffset)
{
    yaw -= xoffset * 0.1;

    if (pitch - yoffset * 0.1 > 89)
        pitch = 89;
    else if (pitch - yoffset * 0.1 < -89)
        pitch = -89;
    else
        pitch -= yoffset * 0.1;

}