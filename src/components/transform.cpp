#include "transform.h"

Transform::Transform()
{
    position = glm::vec3(0.0f);
    rotation = glm::vec3(0.0f);
    scale = glm::vec3(1.0f);

    forward = glm::vec3(0.0f, 0.0f, -1.0f);
    right = glm::vec3(1.0, 0.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Transform::update()
{
    forward.x = cos(glm::radians(rotation.y - 90.0f)) * cos(glm::radians(rotation.x));
    forward.y = sin(glm::radians(rotation.x));
    forward.z = sin(glm::radians(rotation.y - 90.0f)) * cos(glm::radians(rotation.x));
    forward = glm::normalize(forward);

    right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, forward));
}

glm::mat4 Transform::getModelMatrix()
{
    glm::mat4 matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, position);
    matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::scale(matrix, scale);
    return matrix;
}
