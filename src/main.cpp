#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"

#include <Engine.h>

#include <cfloat>
#include <algorithm>

#include "Sphere/Sphere.h"
#include "Grid/Grid.h"
#include "CelestialBody/CelestialBody.h"



const float CAMERA_RADIUS = 40.0f;
const float GRAVITATIONAL_CONSTANT = 9.8;
const unsigned int PANEL_WIDTH = 300;
const unsigned int PANEL_HEIGHT = 300;

bool simulating = false;

glm::vec3 cameraTarget;
float yaw = 0.0;
float pitch = 20.0;
float scroll_amount = 0.5;

std::pair<std::vector<Vertex>, std::vector<unsigned int>> sphereData = getSphereData(24, 24, false);

std::vector<std::unique_ptr<CelestialBody>> celestial_bodies;
int bodyID = 0;


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
    window->viewportOffsetRight = PANEL_WIDTH;
    window->updateViewport();

    textures["earth"] = std::make_shared<Texture>("res/textures/earth.jpg", GL_TEXTURE_2D, 0, GL_RGB);
    textures["earth-night"] = std::make_shared<Texture>("res/textures/earth-night.jpg", GL_TEXTURE_2D, 1, GL_RGB);
    textures["sun"] = std::make_shared<Texture>("res/textures/sun.jpg", GL_TEXTURE_2D, 2, GL_RGB);
    textures["moon"] = std::make_shared<Texture>("res/textures/moon.jpg", GL_TEXTURE_2D, 3, GL_RGB);
    textures["mercury"] = std::make_shared<Texture>("res/textures/mercury.jpg", GL_TEXTURE_2D, 4, GL_RGB);
    textures["venus"] = std::make_shared<Texture>("res/textures/venus.jpg", GL_TEXTURE_2D, 5, GL_RGB);
    textures["mars"] = std::make_shared<Texture>("res/textures/mars.jpg", GL_TEXTURE_2D, 6, GL_RGB);
    textures["jupiter"] = std::make_shared<Texture>("res/textures/jupiter.jpg", GL_TEXTURE_2D, 7, GL_RGB);
    textures["saturn"] = std::make_shared<Texture>("res/textures/saturn.jpg", GL_TEXTURE_2D, 8, GL_RGB);
    textures["uranus"] = std::make_shared<Texture>("res/textures/uranus.jpg", GL_TEXTURE_2D, 9, GL_RGB);
    textures["neptune"] = std::make_shared<Texture>("res/textures/neptune.jpg", GL_TEXTURE_2D, 10, GL_RGB);
    textures["ceres"] = std::make_shared<Texture>("res/textures/ceres.jpg", GL_TEXTURE_2D, 11, GL_RGB);
    textures["haumea"] = std::make_shared<Texture>("res/textures/haumea.jpg", GL_TEXTURE_2D, 12, GL_RGB);
    textures["makemake"] = std::make_shared<Texture>("res/textures/makemake.jpg", GL_TEXTURE_2D, 13, GL_RGB);
    textures["eris"] = std::make_shared<Texture>("res/textures/eris.jpg", GL_TEXTURE_2D, 14, GL_RGB);

    std::pair<std::vector<Vertex>, std::vector<unsigned int>> gridData = getGridData(1000, 2.0);
    meshes["grid"] = std::make_unique<Mesh>(gridData.first, gridData.second, std::make_unique<BasicMaterial>( std::make_unique<Shader>("res/shaders/grid/vert.glsl", "res/shaders/grid/frag.glsl") ));
    meshes["grid"]->DrawLines = true;
    meshes["grid"]->material->parameter["gridRadius"] = 2000.0f;

    std::pair<std::vector<Vertex>, std::vector<unsigned int>> skyData = getSphereData(48, 48, true);
    meshes["sky"] = std::make_unique<Mesh>(skyData.first, skyData.second, std::make_unique<BasicMaterial>( std::make_unique<Shader>("res/shaders/sky/vert.glsl", "res/shaders/sky/frag.glsl") ));
    meshes["sky"]->material->parameter["skyTexture"] = std::make_shared<Texture>("res/textures/sky.jpg", GL_TEXTURE_2D, 15, GL_RGB);
}


CelestialBody* selectedBody = nullptr;

void Engine::Update(float delta)
{
    window->setTitle("Planetarium | FPS: " + std::to_string(fps));

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    float cam_radius;
    if (selectedBody == nullptr) cam_radius = 100;
    else cam_radius = selectedBody->radius * glm::mix(2.0f, CAMERA_RADIUS, scroll_amount);
    float camX = sin(glm::radians(yaw)) * cos(glm::radians(pitch)) * cam_radius;
    float camY = sin(glm::radians(pitch)) * cam_radius;
    float camZ = cos(glm::radians(yaw)) * cos(glm::radians(pitch)) * cam_radius;

    // Calculate all gravity interactions
    if (simulating)
    {
        std::vector<int> bodiesToDelete;

        for (int i=0; i<celestial_bodies.size(); i++)
        {
            for (int j=0; j<celestial_bodies.size(); j++)
            {
                if (i==j) continue;

                glm::vec2 dist = celestial_bodies[i]->position - celestial_bodies[j]->position;
                float distanceSquared = glm::dot(dist, dist);
                float radiusSum = celestial_bodies[i]->radius + celestial_bodies[j]->radius;

                if (distanceSquared <= radiusSum * radiusSum)
                {
                    int bigger, smaller;
                    if (celestial_bodies[i]->radius < celestial_bodies[j]->radius) {
                        bigger = j;
                        smaller = i;
                    } else {
                        bigger = i;
                        smaller = j;
                    }
                    bodiesToDelete.push_back(smaller);
                    meshes.erase(celestial_bodies[smaller]->meshID);
                    lights.erase(celestial_bodies[smaller]->meshID);

                    float r1 = celestial_bodies[bigger]->radius;
                    float r2 = celestial_bodies[smaller]->radius;
                    celestial_bodies[bigger]->radius = std::cbrt(r1 * r1 * r1 + r2 * r2 * r2);

                    celestial_bodies[bigger]->mass += celestial_bodies[smaller]->mass;

                    if (selectedBody->meshID == celestial_bodies[smaller]->meshID)
                    {
                        selectedBody = celestial_bodies[bigger].get();
                    }
                }
                else
                {
                    applyGravity(*celestial_bodies[i], *celestial_bodies[j]);
                }
            }
        }

        std::sort(bodiesToDelete.begin(), bodiesToDelete.end());
        bodiesToDelete.erase(std::unique(bodiesToDelete.begin(), bodiesToDelete.end()), bodiesToDelete.end());
        for (auto it = bodiesToDelete.rbegin(); it != bodiesToDelete.rend(); ++it)
        {
            celestial_bodies.erase(celestial_bodies.begin() + *it);
        }
    }

    // Update physics and grid
    meshes["grid"]->material->parameter["massCount"] = (int) celestial_bodies.size();
    for (int i=0; i<celestial_bodies.size(); i++)
    {
        // Apply gravity
        celestial_bodies[i]->applyVelocity(delta * simulating);

        // Adjust grid to new mass parameters
        std::string base = "masses[" + std::to_string(i) + "]";
        meshes["grid"]->material->parameter[(base + ".position").c_str()] = celestial_bodies[i]->position;
        meshes["grid"]->material->parameter[(base + ".intensity").c_str()] = celestial_bodies[i]->mass;
        meshes["grid"]->material->parameter[(base + ".radius").c_str()] = celestial_bodies[i]->radius;
        
        meshes[celestial_bodies[i]->meshID]->material->parameter["radius"] = celestial_bodies[i]->radius;
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

    if (selectedBody == nullptr)
        cameraTarget = glm::vec3(0.0, 0.0, 0.0);
    else
        cameraTarget = glm::vec3(selectedBody->position.x, 0.0, selectedBody->position.y);
    view = glm::lookAt(glm::vec3(camX, camY, camZ) + cameraTarget, cameraTarget, glm::vec3(0.0, 1.0, 0.0));
    meshes["sky"]->position = glm::vec3(camX, camY, camZ) + cameraTarget;

    ImGuiIO& io = ImGui::GetIO();
    if (glfwGetMouseButton(window->ID, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && !io.WantCaptureMouse)
        glfwSetInputMode(window->ID, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        
    else
        glfwSetInputMode(window->ID, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

char bodyName[128] = "";

void Engine::UpdateUI(float delta)
{
    // Scene Panel
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(PANEL_WIDTH, Engine::window->getHeight()));
    ImGui::Begin(
        "Scene",
        nullptr,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse
    );
    if (!simulating)
    {
        if (ImGui::Button("Add Body", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
        {
            strcpy(bodyName, "");
            ImGui::OpenPopup("Create Body");
        }
    }
    if (ImGui::BeginPopupModal("Create Body", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        bool enterPressed = ImGui::InputText("Name", bodyName, IM_ARRAYSIZE(bodyName), ImGuiInputTextFlags_EnterReturnsTrue);

        if (enterPressed || ImGui::Button("Create"))
        {
            std::string id = "body_" + std::to_string(bodyID);
            std::string name = bodyName;

            if (name.empty())
                name = "Body";

            meshes[id] = std::make_unique<Mesh>(
                sphereData.first,
                sphereData.second,
                std::make_unique<BasicMaterial>(
                    std::make_unique<Shader>(
                        "res/shaders/vert.glsl",
                        "res/shaders/frag.glsl"
                    )
                )
            );

            meshes[id]->material->parameter["isLightSource"] = false;
            meshes[id]->material->parameter["material.albedo"] = glm::vec3(1.0);
            meshes[id]->material->parameter["material.useDiffuse"] = false;
            meshes[id]->material->parameter["material.diffuse"] = textures["earth"];
            meshes[id]->material->parameter["material.specular"] = glm::vec3(0.5);
            meshes[id]->material->parameter["material.shininess"] = 32.0f;

            celestial_bodies.push_back(std::make_unique<CelestialBody>(
                name,
                id,
                1.0f,
                1.0f,
                glm::vec2(0.0f),
                glm::vec2(0.0f)
            ));

            bodyID++;
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
    for (const auto& body : celestial_bodies)
    {
        bool selected = (selectedBody == body.get());
        if (ImGui::Selectable(body->name.c_str(), selected))
        {
            selectedBody = body.get();
        }
    }
    ImGui::End();

    // Properties Panel
    ImGui::SetNextWindowPos(ImVec2(Engine::window->getWidth() - PANEL_WIDTH, 0));
    ImGui::SetNextWindowSize(ImVec2(PANEL_WIDTH, Engine::window->getHeight() - PANEL_HEIGHT));
    ImGui::Begin(
        "Properties",
        nullptr,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse
    );
    if (selectedBody)
    {
        ImGui::InputText("Name", &selectedBody->name);
        ImGui::DragFloat("Mass", &selectedBody->mass, 1, 0.1, FLT_MAX);
        selectedBody->mass = std::max(0.1f, selectedBody->mass);
        ImGui::DragFloat("Radius", &selectedBody->radius, 0.1, 0.1, 50.0f);
        selectedBody->radius = std::min(std::max(0.1f, selectedBody->radius), 50.0f);
        ImGui::DragFloat2("Position", &selectedBody->position.x);
        ImGui::DragFloat2("Velocity", &selectedBody->velocity.x);

        auto& isLightSource = std::get<bool>(meshes[selectedBody->meshID.c_str()]->material->parameter["isLightSource"]);
        ImGui::Checkbox("Is Light Source", &isLightSource);
        auto& albedo = std::get<glm::vec3>(meshes[selectedBody->meshID.c_str()]->material->parameter["material.albedo"]);
        ImGui::ColorEdit3("Albedo", &albedo.x);
        if (!isLightSource)
        {
            if (lights.contains(selectedBody->meshID))
                lights.erase(selectedBody->meshID);
            auto& specular = std::get<glm::vec3>(meshes[selectedBody->meshID.c_str()]->material->parameter["material.specular"]);
            ImGui::ColorEdit3("Specular", &specular.x);
            auto& shininess = std::get<float>(meshes[selectedBody->meshID.c_str()]->material->parameter["material.shininess"]);
            ImGui::DragFloat("Shininess", &shininess, 1.0, 4, 64);
            shininess = std::max(4.0f, shininess);
        }
        auto& useDiffuse = std::get<bool>(meshes[selectedBody->meshID.c_str()]->material->parameter["material.useDiffuse"]);
        ImGui::Checkbox("Diffuse Map", &useDiffuse);
        if (useDiffuse)
        {
            auto& diffuse = std::get<std::shared_ptr<Texture>>(meshes[selectedBody->meshID.c_str()]->material->parameter["material.diffuse"]);
            const char* current = "None";
            for (const auto& [name, tex] : textures)
            {
                if (tex == diffuse)
                {
                    current = name.c_str();
                    break;
                }
            }
            if (ImGui::BeginCombo("Texture", current))
            {
                for (const auto& [name, tex] : textures)
                {
                    bool selected = (tex == diffuse);
                    if (ImGui::Selectable(name.c_str(), selected))
                        diffuse = tex;
                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            if (diffuse)
            {
                float previewWidth = ImGui::GetContentRegionAvail().x;
                float previewHeight = previewWidth * ((float)diffuse->height / diffuse->width);

                ImGui::Image((ImTextureID)(intptr_t)diffuse->ID, ImVec2(previewWidth, previewHeight));
            }
        }
        if (isLightSource) {
            if (!lights.contains(selectedBody->meshID))
                lights[selectedBody->meshID] = std::make_unique<Light>();
            lights[selectedBody->meshID]->ambient = albedo * 0.2f;
            lights[selectedBody->meshID]->diffuse = albedo * 0.5f;
            ImGui::ColorEdit3("Specular", &lights[selectedBody->meshID]->specular.x);
            ImGui::DragFloat("Linear", &lights[selectedBody->meshID]->linear, 0.000001, 0.000001, 1.0, "%.6f");
            ImGui::DragFloat("Quadratic", &lights[selectedBody->meshID]->quadratic, 0.000001, 0.000001, 1.0, "%.6f");
        }
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(Engine::window->getWidth() - PANEL_WIDTH, Engine::window->getHeight() - PANEL_HEIGHT));
    ImGui::SetNextWindowSize(ImVec2(PANEL_WIDTH, PANEL_HEIGHT));
    ImGui::Begin(
        "Simulation",
        nullptr,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse
    );
    if (!simulating)
    {
        if (ImGui::Button("Start", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
        {
            simulating = true;
        }
    }
    else
    {   
        if (ImGui::Button("Stop", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
        {
            simulating = false;
        }
    }
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
    ImGuiIO& io = ImGui::GetIO();

    if (io.WantCaptureMouse)
        return;

    if (glfwGetInputMode(window->ID, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
    {
        yaw -= xoffset * 0.1;

        if (pitch - yoffset * 0.1 > 89)
            pitch = 89;
        else if (pitch - yoffset * 0.1 < -89)
            pitch = -89;
        else
            pitch -= yoffset * 0.1;
    }
}

void Engine::MouseScroll(float xoffset, float yoffset)
{
    ImGuiIO& io = ImGui::GetIO();

    if (io.WantCaptureMouse)
        return;

    scroll_amount -= 0.1 * yoffset;
    scroll_amount = glm::clamp(scroll_amount, 0.0f, 1.0f);
}