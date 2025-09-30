#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Camera
{
    Camera();

    glm::mat4 getProjectionMatrix();

    float fieldOfView;
    float aspectRatio;
    float nearClipPlane;
    float farClipPlane;
};