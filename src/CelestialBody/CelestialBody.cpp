#include "CelestialBody.h"


CelestialBody::CelestialBody(std::string name, std::string meshID, float mass, float radius, glm::vec2 start_position, glm::vec2 initial_velocity)
{
    this->name = name;
    this->meshID = meshID;
    this->mass = mass;
    this->radius = radius;
    this->position = start_position;
    this->velocity = initial_velocity;
}

void CelestialBody::applyVelocity(float delta)
{
    position += velocity * delta;
    Engine::meshes[meshID]->position = glm::vec3(position.x, 0, position.y);
}