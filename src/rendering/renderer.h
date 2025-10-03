#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "components/material.h"
#include "components/mesh.h"
#include "components/transform.h"
#include "components/camera.h"
#include "core/resourcemanager.h"

enum class DrawMode
{
    FILL = GL_FILL,
    LINE = GL_LINE,
    POINT = GL_POINT
};

class Renderer
{
public:
    static void initialize();
    static void shutdown();

    static void clear();

    static void setCamera(Camera& camera, Transform& cameraTransform);

    static void drawRay(const glm::vec3& start, const glm::vec3& direction, float length, const glm::vec3& color, float lineWidth = 1.0f);
    static void drawChunk(const glm::vec3& position, Mesh& mesh);

    static void setDrawMode(DrawMode mode) { glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(mode)); }

private:
    static glm::mat4 m_currentProjectionMatrix;
    static glm::mat4 m_currentViewMatrix;
};