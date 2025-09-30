#version 330 core

in vec2 vTexCoord;

uniform sampler2D uAtlas;

out vec4 oColor;

void main()
{
    oColor = texture(uAtlas, vTexCoord);
}