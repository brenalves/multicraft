#include "input.h"

bool Input::s_currentKeys[GLFW_KEY_LAST];
bool Input::s_previousKeys[GLFW_KEY_LAST];
bool Input::s_currentMouseButtons[GLFW_MOUSE_BUTTON_LAST];
bool Input::s_previousMouseButtons[GLFW_MOUSE_BUTTON_LAST];

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

        if(i < GLFW_MOUSE_BUTTON_LAST)
        {
            s_previousMouseButtons[i] = s_currentMouseButtons[i];
            s_currentMouseButtons[i] = glfwGetMouseButton(glfwGetCurrentContext(), i) == GLFW_PRESS;
        }
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