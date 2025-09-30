#pragma once

#include "components/transform.h"
#include "components/camera.h"
#include "core/input.h"

class Player
{
public:
    Player();

    void update(float deltaTime);

    inline Transform& getTransform() { return m_transform; }
    inline Camera& getCamera() { return m_camera; }

private:
    Transform m_transform;
    Camera m_camera;

    float m_speed;
    float m_sensitivity;
    float m_lastX, m_lastY;
};