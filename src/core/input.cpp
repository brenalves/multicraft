#include "input.h"

bool Input::s_currentKeys[GLFW_KEY_LAST];
bool Input::s_previousKeys[GLFW_KEY_LAST];

void Input::initialize()
{
    for (int i = 0; i < GLFW_KEY_LAST; i++)
    {
        s_currentKeys[i] = false;
        s_previousKeys[i] = false;
    }

    setCursorMode(CURSOR_DISABLED);
}

void Input::update()
{
    for (int i = 0; i < GLFW_KEY_LAST; i++)
    {
        s_previousKeys[i] = s_currentKeys[i];
        s_currentKeys[i] = glfwGetKey(glfwGetCurrentContext(), i) == GLFW_PRESS;
    }
}

float Input::getMouseX()
{
    double x;
    glfwGetCursorPos(glfwGetCurrentContext(), &x, nullptr);
    return static_cast<float>(x);
}

float Input::getMouseY()
{
    double y;
    glfwGetCursorPos(glfwGetCurrentContext(), nullptr, &y);
    return static_cast<float>(y);
}