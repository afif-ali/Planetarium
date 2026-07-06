#version 460 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Color;
in vec3 Normal;
in vec2 TexCoord;

struct Material {
    vec3 albedo;
    bool useDiffuse;
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};


uniform Material material;

uniform vec3 viewPos;
uniform bool isLightSource;

#define MAX_LIGHTS 8
uniform int lightCount;
uniform Light lights[MAX_LIGHTS];



void main()
{
    vec3 result;
    vec3 objectColor;
    if (material.useDiffuse)
        objectColor = vec3(texture(material.diffuse, TexCoord)) * material.albedo;
    else
        objectColor = material.albedo;

    if (!isLightSource)
    {
        for (int i =0; i<lightCount; i++)
        {
            // Ambient light
            vec3 ambient = lights[i].ambient * objectColor;

            // Diffuse light
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(lights[i].position - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = lights[i].diffuse * (diff * objectColor);

            // Specular light
            vec3 viewDir = normalize(viewPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
            vec3 specular = lights[i].specular * (spec * material.specular);

            float dist = length(lights[i].position - FragPos);
            float attenuation = 1.0 / (lights[i].constant + lights[i].linear*dist + lights[i].quadratic*dist*dist);

            result += attenuation * (ambient + diffuse + specular);
        }
    }
    else result = objectColor;
    FragColor = vec4(result, 1.0f);
}