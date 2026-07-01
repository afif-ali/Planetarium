#include <Engine.h>



const float CAMERA_RADIUS = 5.0f;

float yaw = 0.0;
float pitch = 0.0;

glm::vec3 cameraTarget;

std::pair<std::vector<Vertex>, std::vector<unsigned int>> getSphereData(float radius, int sub_vertical, int sub_horizontal)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (int i=0; i<sub_vertical+1; i++)
    {
        float y = radius * sin(glm::radians(-90 + (180.0/sub_vertical) * i));
        float layer_radius = radius * cos(glm::radians(-90 + (180.0/sub_vertical) * i));

        for (int j=0; j<sub_horizontal+1; j++)
        { 
            float z = layer_radius * sin(glm::radians((360.0/sub_horizontal) * j));
            float x = layer_radius * cos(glm::radians((360.0/sub_horizontal) * j));

            float u = -1*(float)j / sub_horizontal +1;
            float v = (float)i / sub_vertical;

            vertices.push_back({glm::vec3(x,y,z),glm::vec3(1.0,1.0,1.0),glm::vec2(u,v)});
        }
    }

    for (int i=0; i<sub_vertical; i++)
    {
        for (int j=0; j<sub_horizontal; j++)
        {
            indices.push_back((j+0) + (i+0)*(sub_horizontal+1));
            indices.push_back((j+0) + (i+1)*(sub_horizontal+1));
            indices.push_back((j+1) + (i+1)*(sub_horizontal+1));
            
            indices.push_back((j+1) + (i+0)*(sub_horizontal+1));
            indices.push_back((j+0) + (i+0)*(sub_horizontal+1));
            indices.push_back((j+1) + (i+1)*(sub_horizontal+1));
        }
    }

    return {vertices, indices};
}

void Engine::Begin()
{
    std::pair<std::vector<Vertex>, std::vector<unsigned int>> sphereData = getSphereData(2, 24, 24);


    meshes["sphere"] = std::make_unique<Mesh>(sphereData.first, sphereData.second, std::make_unique<BasicMaterial>( std::make_unique<Shader>("res/shaders/vert.glsl", "res/shaders/frag.glsl") ));
    meshes["sphere"]->material->useTexture = true;
    meshes["sphere"]->material->texture = std::make_unique<Texture>("res/textures/earth.jpg", GL_TEXTURE_2D, 0, GL_RGB);
    meshes["sphere"]->position.x = 2.0;

    cameraTarget = meshes["sphere"]->position;
    
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