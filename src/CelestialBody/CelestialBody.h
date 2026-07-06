#pragma once

#include "Engine.h"

class CelestialBody
{
public:
    std::string name;
    std::string meshID;
    float mass;
    float radius;
    glm::vec2 position;
    glm::vec2 velocity;

    CelestialBody(std::string name, std::string meshID, float mass, float radius, glm::vec2 start_position, glm::vec2 initial_velocity);

    void applyVelocity(float delta);
};