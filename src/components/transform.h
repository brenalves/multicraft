#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Transform
{
    Transform();

    void update();
    
    glm::mat4 getModelMatrix();

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;
};