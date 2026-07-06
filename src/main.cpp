#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <Engine.h>

#include "Sphere/Sphere.h"
#include "Grid/Grid.h"
#include "CelestialBody/CelestialBody.h"

const float CAMERA_RADIUS = 15.0f;
const float GRAVITATIONAL_CONSTANT = 9.8;
const float SIMULATION_SPEED = 0.2;
const unsigned int PANEL_WIDTH = 300;

float yaw = 0.0;
float pitch = 20.0;

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
    glfwMaximizeWindow(window->ID);
    // Initialize ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void) io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->ID, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    window->viewportOffsetLeft = PANEL_WIDTH;
    window->updateViewport();

    std::shared_ptr<Texture> earthTex = std::make_shared<Texture>("res/textures/earth.jpg", GL_TEXTURE_2D, 0, GL_RGB);

    std::cout << "test" << std::endl;
    std::pair<std::vector<Vertex>, std::vector<unsigned int>> gridData = getGridData(1000, 2.0);
    meshes["grid"] = std::make_unique<Mesh>(gridData.first, gridData.second, std::make_unique<BasicMaterial>( std::make_unique<Shader>("res/shaders/grid/vert.glsl", "res/shaders/grid/frag.glsl") ));
    meshes["grid"]->DrawLines = true;
    meshes["grid"]->material->parameter["gridRadius"] = 2000.0f;

    std::pair<std::vector<Vertex>, std::vector<unsigned int>> earthSphereData = getSphereData(1, 24, 24);

    meshes["earth"] = std::make_unique<Mesh>(earthSphereData.first, earthSphereData.second, std::make_unique<BasicMaterial>( std::make_unique<Shader>("res/shaders/vert.glsl", "res/shaders/frag.glsl") ));
    meshes["earth"]->material->parameter["isLightSource"] = false;
    meshes["earth"]->material->parameter["material.albedo"] = glm::vec3(1.0);
    meshes["earth"]->material->parameter["material.useDiffuse"] = true;
    meshes["earth"]->material->parameter["material.diffuse"] = earthTex;
    meshes["earth"]->material->parameter["material.specular"] = glm::vec3(0.5, 0.5, 0.5);
    meshes["earth"]->material->parameter["material.shininess"] = 32.0f;
    meshes["earth"]->position.x = 40.0;

    celestial_bodies.push_back(std::make_unique<CelestialBody>("earth", 1.0, 1.0, glm::vec2(meshes["earth"]->position.x, meshes["earth"]->position.z), glm::vec2(0.0, -20.0)));

    std::pair<std::vector<Vertex>, std::vector<unsigned int>> sunSphereData = getSphereData(5, 48, 48);

    meshes["sun"] = std::make_unique<Mesh>(sunSphereData.first, sunSphereData.second, std::make_unique<BasicMaterial>( std::make_unique<Shader>("res/shaders/vert.glsl", "res/shaders/frag.glsl") ));
    meshes["sun"]->material->parameter["isLightSource"] = true;
    meshes["sun"]->material->parameter["material.albedo"] = glm::vec3(1.0f, 1.0f, 0.0f);
    meshes["sun"]->position.x = 0.0;
    lights["sun"] = std::make_unique<Light>();
    lights["sun"]->ambient = glm::vec3(0.2);
    lights["sun"]->diffuse = glm::vec3(0.2);
    lights["sun"]->specular = glm::vec3(1.0);
    lights["sun"]->constant = 1.0;
    lights["sun"]->linear = 0.0014;
    lights["sun"]->quadratic = 0.000007;

    celestial_bodies.push_back(std::make_unique<CelestialBody>("sun", 50.0, 5.0, glm::vec2(meshes["sun"]->position.x, meshes["sun"]->position.z), glm::vec2(0.0, 0.0)));
}

void Engine::Update(float delta)
{
    window->setTitle("Planetarium | FPS: " + std::to_string(fps));

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    float camX = sin(glm::radians(yaw)) * cos(glm::radians(pitch)) * CAMERA_RADIUS;
    float camY = sin(glm::radians(pitch)) * CAMERA_RADIUS;
    float camZ = cos(glm::radians(yaw)) * cos(glm::radians(pitch)) * CAMERA_RADIUS;

    // Calculate all gravity interactions
    for (int i=0; i<celestial_bodies.size(); i++)
    {
        for (int j=0; j<celestial_bodies.size(); j++)
        {
            if (i==j) continue;

            applyGravity(*celestial_bodies[i], *celestial_bodies[j]);
        }
    }

    // Update physics and grid
    meshes["grid"]->material->parameter["massCount"] = (int) celestial_bodies.size();
    for (int i=0; i<celestial_bodies.size(); i++)
    {
        // Apply gravity
        celestial_bodies[i]->applyVelocity(SIMULATION_SPEED * delta);

        // Adjust grid to new mass parameters
        std::string base = "masses[" + std::to_string(i) + "]";
        meshes["grid"]->material->parameter[(base + ".position").c_str()] = celestial_bodies[i]->position;
        meshes["grid"]->material->parameter[(base + ".intensity").c_str()] = celestial_bodies[i]->mass;
        meshes["grid"]->material->parameter[(base + ".radius").c_str()] = celestial_bodies[i]->radius;

        meshes[celestial_bodies[i]->meshID]->material->parameter["viewPos"] = glm::vec3(camX, camY, camZ) + cameraTarget;
        meshes[celestial_bodies[i]->meshID]->material->parameter["lightCount"] = (int) lights.size();
    }

    // Update lights
    int j=0;
    for (const auto& [key, value] : lights)
    {
        lights[key]->position = meshes[key]->position;

        for (int i=0; i<celestial_bodies.size(); i++)
        {
            std::string light = "lights[" + std::to_string(j) + "]";

            meshes[celestial_bodies[i]->meshID]->material->parameter[(light + ".position").c_str()] = lights[key]->position;
            meshes[celestial_bodies[i]->meshID]->material->parameter[(light + ".ambient").c_str()] = lights[key]->ambient;
            meshes[celestial_bodies[i]->meshID]->material->parameter[(light + ".diffuse").c_str()] = lights[key]->diffuse;
            meshes[celestial_bodies[i]->meshID]->material->parameter[(light + ".specular").c_str()] = lights[key]->specular;
            meshes[celestial_bodies[i]->meshID]->material->parameter[(light + ".constant").c_str()] = lights[key]->constant;
            meshes[celestial_bodies[i]->meshID]->material->parameter[(light + ".linear").c_str()] = lights[key]->linear;
            meshes[celestial_bodies[i]->meshID]->material->parameter[(light + ".quadratic").c_str()] = lights[key]->quadratic;

        }
        j++;
    }

    cameraTarget = meshes["earth"]->position;
    view = glm::lookAt(glm::vec3(camX, camY, camZ) + cameraTarget, cameraTarget, glm::vec3(0.0, 1.0, 0.0));
}

void Engine::UpdateUI(float delta)
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(PANEL_WIDTH, Engine::window->getHeight()));
    ImGui::Begin(
        "Scene",
        nullptr,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse
    );
    ImGui::Text("New window!!");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Engine::End()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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