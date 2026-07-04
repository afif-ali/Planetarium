#version 330 core
out vec4 FragColor;

in vec3 Color;
in vec2 TexCoord;

uniform vec3 u_albedo;
uniform sampler2D u_texture;
uniform bool u_useTexture;
uniform bool glow;

void main()
{
    vec3 color;
    if (glow)
    {
        color = u_albedo * 10000;
    }
    else 
    {
        color = u_albedo;
    }

    if (u_useTexture)
    {
        FragColor = vec4(texture(u_texture, TexCoord).rgb * color, 1.0);  
    }
    else
    {
        FragColor = vec4(color, 1.0f);  
    }
}