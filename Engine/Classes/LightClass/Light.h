#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Light
{
public:
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular = glm::vec3(1.0);

    float constant = 1.0f;
    float linear = 0.0014;
    float quadratic = 0.000007;
};
