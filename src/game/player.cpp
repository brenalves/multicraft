#include "player.h"

#include "world.h"

Player::Player()
{
    m_speed = 25.0f;
    m_lastX = 400.0f; // assuming initial window width / 2
    m_lastY = 300.0f; // assuming initial window height / 2
    m_sensitivity = 0.1f;
}

void Player::update(float deltaTime)
{
    m_transform.update();

    glm::vec3 front = m_transform.forward;
    front.y = 0.0f; // lock y movement for horizontal movement
    front = glm::normalize(front);

    glm::vec3 moveDirection(0.0f);
    if (Input::isKeyHeld(GLFW_KEY_W))
        moveDirection += front;
    if (Input::isKeyHeld(GLFW_KEY_S))
        moveDirection += -front;
    if (Input::isKeyHeld(GLFW_KEY_A))
        moveDirection += -m_transform.right;
    if (Input::isKeyHeld(GLFW_KEY_D))
        moveDirection += m_transform.right;
    if (Input::isKeyHeld(GLFW_KEY_SPACE))
        moveDirection.y += 1.0f;
    if (Input::isKeyHeld(GLFW_KEY_LEFT_SHIFT))
        moveDirection.y -= 1.0f;

    if (glm::length(moveDirection) > 0.0f)
        moveDirection = glm::normalize(moveDirection);

    m_transform.position += moveDirection * m_speed * deltaTime;

    if (Input::getCursorMode() == CURSOR_DISABLED)
    {
        float mouseX = Input::getMouseX();
        float mouseY = Input::getMouseY();

        float offsetX = mouseX - m_lastX;
        float offsetY = m_lastY - mouseY;

        m_lastX = mouseX;
        m_lastY = mouseY;

        m_transform.rotation.y += offsetX * m_sensitivity;
        m_transform.rotation.x += offsetY * m_sensitivity;

        if (m_transform.rotation.x > 89.0f)
            m_transform.rotation.x = 89.0f;
        if (m_transform.rotation.x < -89.0f)
            m_transform.rotation.x = -89.0f;

        if(Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            // break block
            for(int i = 1; i < 6; i++)
            {
                glm::vec3 checkPos = m_transform.position + m_transform.forward * static_cast<float>(i);
                World::getInstance()->breakBlock(glm::ivec3(std::floor(checkPos.x), std::floor(checkPos.y), std::floor(checkPos.z)));
            }
        }
    }
}
