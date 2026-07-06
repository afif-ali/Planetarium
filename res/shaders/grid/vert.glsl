#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;

out vec3 Color;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

#define MAX_MASSES 128

struct Mass {
    vec2 position;
    float intensity;
    float radius;
};

uniform int massCount;
uniform Mass masses[MAX_MASSES];
uniform float gridRadius;

float flamm(float r, float rs)
{
    return 2.0 * sqrt(rs*(r-rs));
}

float dist(vec2 a, vec2 b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

void main()
{
    float height = 0;
    for (int i=0; i<massCount; i++)
    {
        float rs = masses[i].radius;

        float d1 = dist(vec2(-gridRadius, -gridRadius), masses[i].position);
        float d2 = dist(vec2( gridRadius, -gridRadius), masses[i].position);
        float d3 = dist(vec2(-gridRadius,  gridRadius), masses[i].position);
        float d4 = dist(vec2( gridRadius,  gridRadius), masses[i].position);
        float edgeDistance = max(max(d1,d2),max(d3,d4));
        edgeDistance = max(edgeDistance, rs);

        float r = dist(aPos.xz, masses[i].position);
        r = max(r,rs);


        float h = flamm(r, rs) - flamm(edgeDistance, rs);
        height += (h * masses[i].intensity * 0.01) / (1.5 * r);
    }

    gl_Position = projection * view * model * vec4(aPos.x, height, aPos.z, 1.0);
    Color = aColor;
    TexCoord = aTexCoord;
}