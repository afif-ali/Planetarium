#include "Grid.h"

std::pair<std::vector<Vertex>, std::vector<unsigned int>> getGridData(int gridSize, float spacing)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    int count = gridSize * 2 + 1;

    for (int z = 0; z < count; z++)
    {
        for (int x = 0; x < count; x++)
        {
            vertices.push_back({
                glm::vec3(
                    (x - gridSize) * spacing,
                    0.0f,
                    (z - gridSize) * spacing
                )
            });
        }
    }

    for (int z = 0; z < count; z++)
    {
        for (int x = 0; x < count - 1; x++)
        {
            unsigned int i0 = z * count + x;
            unsigned int i1 = i0 + 1;

            indices.push_back(i0);
            indices.push_back(i1);
        }
    }

    for (int z = 0; z < count - 1; z++)
    {
        for (int x = 0; x < count; x++)
        {
            unsigned int i0 = z * count + x;
            unsigned int i1 = i0 + count;

            indices.push_back(i0);
            indices.push_back(i1);
        }
    }

    return { vertices, indices };
}