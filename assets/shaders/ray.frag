#version 330 core

uniform vec3 uColor;

out vec4 oColor;

void main()
{
    oColor = vec4(uColor, 1.0);
}