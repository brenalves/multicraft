#include "camera.h"

Camera::Camera()
{
    fieldOfView = 60.0f;
    aspectRatio = 4.0f / 3.0f;
    nearClipPlane = 0.1f;
    farClipPlane = 1000.0f;
}

glm::mat4 Camera::getProjectionMatrix()
{
    return glm::perspective(glm::radians(fieldOfView), aspectRatio, nearClipPlane, farClipPlane);
}
