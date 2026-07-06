#include "Sphere.h"

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

            vertices.push_back({glm::vec3(x,y,z),glm::vec3(1.0,1.0,1.0),glm::normalize(glm::vec3(x,y,z)),glm::vec2(u,v)});
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