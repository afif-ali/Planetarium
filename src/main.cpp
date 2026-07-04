#include <Engine.h>

#include "Sphere/Sphere.h"
#include "Grid/Grid.h"
#include "CelestialBody/CelestialBody.h"

const float CAMERA_RADIUS = 30.0f;
const float GRAVITATIONAL_CONSTANT = 9.8;

float yaw = 0.0;
float pitch = 89.0;

glm::vec3 cameraTarget;

std::vector<std::unique_ptr<CelestialBody>> celestial_bodies;

void applyGravity(CelestialBody& a, CelestialBody& b)
{
    float dist_squared = (a.position.x - b.position.x)*(a.position.x - b.position.x) + (a.position.y - b.position.y)*(a.position.y - b.position.y);
    float intensity = GRAVITATIONAL_CONSTANT * a.mass * b.mass / dist_squared;
    float acceleration = intensity / a.mass;
    glm::vec2 direction = glm::normalize(b.position - a.position);
    a.velocity += acceleration * direction;
}


void Engine::Begin()
{
    std::pair<std::vector<Vertex>, std::vector<unsigned int>> gridData = getGridData(500, 2.0);
    meshes["grid"] = std::make_unique<Mesh>(gridData.first, gridData.second, std::make_unique<BasicMaterial>( std::make_unique<Shader>("res/shaders/grid/vert.glsl", "res/shaders/grid/frag.glsl") ));
    meshes["grid"]->DrawLines = true;
    meshes["grid"]->material->shader->Use();
    glUniform1f(meshes["grid"]->material->shader->Uniform("gridRadius"), 1000);

    std::pair<std::vector<Vertex>, std::vector<unsigned int>> earthSphereData = getSphereData(1, 24, 24);

    meshes["earth"] = std::make_unique<Mesh>(earthSphereData.first, earthSphereData.second, std::make_unique<BasicMaterial>( std::make_unique<Shader>("res/shaders/vert.glsl", "res/shaders/frag.glsl") ));
    meshes["earth"]->material->useTexture = true;
    meshes["earth"]->material->texture = std::make_unique<Texture>("res/textures/earth.jpg", GL_TEXTURE_2D, 0, GL_RGB);
    meshes["earth"]->position.x = 40.0;

    celestial_bodies.push_back(std::make_unique<CelestialBody>("earth", 1.0, 1.0, glm::vec2(meshes["earth"]->position.x, meshes["earth"]->position.z), glm::vec2(0.0, -20.0)));

    std::pair<std::vector<Vertex>, std::vector<unsigned int>> marsSphereData = getSphereData(1, 24, 24);

    meshes["mars"] = std::make_unique<Mesh>(marsSphereData.first, marsSphereData.second, std::make_unique<BasicMaterial>( std::make_unique<Shader>("res/shaders/vert.glsl", "res/shaders/frag.glsl") ));
    meshes["mars"]->material->useTexture = true;
    meshes["mars"]->material->texture = std::make_unique<Texture>("res/textures/mars.jpg", GL_TEXTURE_2D, 0, GL_RGB);
    meshes["mars"]->position.x = 30.0;

    celestial_bodies.push_back(std::make_unique<CelestialBody>("mars", 1.0, 1.0, glm::vec2(meshes["mars"]->position.x, meshes["mars"]->position.z), glm::vec2(0.0, -30.0)));

    
    std::pair<std::vector<Vertex>, std::vector<unsigned int>> sunSphereData = getSphereData(5, 48, 48);

    meshes["sun"] = std::make_unique<Mesh>(sunSphereData.first, sunSphereData.second, std::make_unique<BasicMaterial>( std::make_unique<Shader>("res/shaders/vert.glsl", "res/shaders/frag.glsl") ));
    meshes["sun"]->material->albedo = glm::vec3(1.0, 1.0, 0.0);
    meshes["sun"]->material->glow = true;
    meshes["sun"]->position.x = 0.0;

    celestial_bodies.push_back(std::make_unique<CelestialBody>("sun", 50.0, 5.0, glm::vec2(meshes["sun"]->position.x, meshes["sun"]->position.z), glm::vec2(0.0, 0.0)));

}

void Engine::Update(float delta)
{
    window->setTitle("Planetarium: " + std::to_string(delta) + " | FPS: " + std::to_string(fps));

    
    cameraTarget = meshes["mars"]->position;
    float camX = sin(glm::radians(yaw)) * cos(glm::radians(pitch)) * CAMERA_RADIUS;
    float camY = sin(glm::radians(pitch)) * CAMERA_RADIUS;
    float camZ = cos(glm::radians(yaw)) * cos(glm::radians(pitch)) * CAMERA_RADIUS;
    view = glm::lookAt(glm::vec3(camX, camY, camZ) + cameraTarget, cameraTarget, glm::vec3(0.0, 1.0, 0.0));

    for (int i=0; i<celestial_bodies.size(); i++)
    {
        for (int j=0; j<celestial_bodies.size(); j++)
        {
            if (i==j) continue;

            applyGravity(*celestial_bodies[i], *celestial_bodies[j]);

            
        }
    }

    
    meshes["grid"]->material->shader->Use();
    glUniform1i(meshes["grid"]->material->shader->Uniform("massCount"), celestial_bodies.size());
    for (int i=0; i<celestial_bodies.size(); i++)
    {
        celestial_bodies[i]->applyVelocity(delta);

        std::string base = "masses[" + std::to_string(i) + "]";
        glUniform2fv(meshes["grid"]->material->shader->Uniform((base + ".position").c_str()), 1, glm::value_ptr(celestial_bodies[i]->position));
        glUniform1f(meshes["grid"]->material->shader->Uniform((base + ".intensity").c_str()), celestial_bodies[i]->mass);
        glUniform1f(meshes["grid"]->material->shader->Uniform((base + ".radius").c_str()), celestial_bodies[i]->radius);
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