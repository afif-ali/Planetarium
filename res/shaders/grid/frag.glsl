#version 330 core
out vec4 FragColor;

in vec3 Color;
in vec2 TexCoord;

uniform vec3 u_albedo;
uniform sampler2D u_texture;
uniform bool u_useTexture;

void main()
{
    if (u_useTexture)
    {
        FragColor = vec4(texture(u_texture, TexCoord).rgb * u_albedo, 1.0);  
    }
    else
    {
        FragColor = vec4(u_albedo, 1.0f);  
    }
}