#version 330 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec2 iTexCoord;

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

out vec2 vTexCoord;

void main()
{
    gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(iPosition, 1.0);
    vTexCoord = iTexCoord;
}