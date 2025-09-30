#version 330 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

in vec2 vTexCoord;

uniform Material uMaterial;

out vec4 oColor;

void main()
{
    oColor = texture(uMaterial.diffuse, vTexCoord);
}