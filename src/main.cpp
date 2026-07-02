#include <Engine.h>

#include "Sphere/Sphere.h"
#include "CelestialBody/CelestialBody.h"

const float CAMERA_RADIUS = 30.0f;

float yaw = 0.0;
float pitch = 0.0;

glm::vec3 cameraTarget;

std::vector<std::unique_ptr<CelestialBody>> celestial_bodies;


void Engine::Begin()
{
    std::pair<std::vector<Vertex>, std::vector<unsigned int>> earthSphereData = getSphereData(1, 24, 24);

    meshes["earth"] = std::make_unique<Mesh>(earthSphereData.first, earthSphereData.second, std::make_unique<BasicMaterial>( std::make_unique<Shader>("res/shaders/vert.glsl", "res/shaders/frag.glsl") ));
    meshes["earth"]->material->useTexture = true;
    meshes["earth"]->material->texture = std::make_unique<Texture>("res/textures/earth.jpg", GL_TEXTURE_2D, 0, GL_RGB);
    meshes["earth"]->position.x = 0.0;

    celestial_bodies.push_back(std::make_unique<CelestialBody>("earth", 1.0, 1.0, glm::vec2(0.0, 0.0), glm::vec2(1.0, 0.0)));

    cameraTarget = glm::vec3(0.0, 0.0, 0.0);
    
    float camX = sin(glm::radians(yaw)) * cos(glm::radians(pitch)) * CAMERA_RADIUS;
    float camY = sin(glm::radians(pitch)) * CAMERA_RADIUS;
    float camZ = cos(glm::radians(yaw)) * cos(glm::radians(pitch)) * CAMERA_RADIUS;
    view = glm::lookAt(glm::vec3(camX, camY, camZ) + cameraTarget, cameraTarget, glm::vec3(0.0, 1.0, 0.0));
}

void Engine::Update(float delta)
{
    window->setTitle("Planetarium: " + std::to_string(delta) + " | FPS: " + std::to_string(fps));

    for (int i=0; i<celestial_bodies.size(); i++)
    {
        celestial_bodies[i]->applyVelocity(delta);
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

    float camX = sin(glm::radians(yaw)) * cos(glm::radians(pitch)) * CAMERA_RADIUS;
    float camY = sin(glm::radians(pitch)) * CAMERA_RADIUS;
    float camZ = cos(glm::radians(yaw)) * cos(glm::radians(pitch)) * CAMERA_RADIUS;
    view = glm::lookAt(glm::vec3(camX, camY, camZ) + cameraTarget, cameraTarget, glm::vec3(0.0, 1.0, 0.0));
}