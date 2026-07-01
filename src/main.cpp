#include <Engine.h>

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

const float CAMERA_RADIUS = 5.0f;

float yaw = 0.0;
float pitch = 0.0;

glm::vec3 cameraTarget;

void Engine::Begin()
{
    meshes["cube"] = std::make_unique<Mesh>(vertices, indices, std::make_unique<BasicMaterial>( std::make_unique<Shader>("res/shaders/vert.glsl", "res/shaders/frag.glsl") ));
    meshes["cube"]->material->albedo = glm::vec3(1.0, 0.0, 0.0);
    meshes["cube"]->material->useTexture = true;
    meshes["cube"]->material->texture = std::make_unique<Texture>("res/textures/wall.jpg", GL_TEXTURE_2D, 0, GL_RGB);

    meshes["greencube"] = std::make_unique<Mesh>(vertices, indices, std::make_unique<BasicMaterial>( std::make_unique<Shader>("res/shaders/vert.glsl", "res/shaders/frag.glsl") ));
    meshes["greencube"]->material->albedo = glm::vec3(0.0, 1.0, 0.0);
    meshes["greencube"]->material->useTexture = true;
    meshes["greencube"]->material->texture = std::make_unique<Texture>("res/textures/wall.jpg", GL_TEXTURE_2D, 0, GL_RGB);

    meshes["greencube"]->position.x = 5.0f;

    cameraTarget = meshes["cube"]->position;
    
    float camX = sin(glm::radians(yaw)) * cos(glm::radians(pitch)) * CAMERA_RADIUS;
    float camY = sin(glm::radians(pitch)) * CAMERA_RADIUS;
    float camZ = cos(glm::radians(yaw)) * cos(glm::radians(pitch)) * CAMERA_RADIUS;
    view = glm::lookAt(glm::vec3(camX, camY, camZ) + cameraTarget, cameraTarget, glm::vec3(0.0, 1.0, 0.0));
}

void Engine::Update(float delta)
{
    window->setTitle("Planetarium: " + std::to_string(delta) + " | FPS: " + std::to_string(fps));
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

    float camX = sin(glm::radians(yaw)) * cos(glm::radians(pitch)) * CAMERA_RADIUS;
    float camY = sin(glm::radians(pitch)) * CAMERA_RADIUS;
    float camZ = cos(glm::radians(yaw)) * cos(glm::radians(pitch)) * CAMERA_RADIUS;
    view = glm::lookAt(glm::vec3(camX, camY, camZ) + cameraTarget, cameraTarget, glm::vec3(0.0, 1.0, 0.0));
}