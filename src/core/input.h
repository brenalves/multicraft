#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

enum CursorMode
{
    CURSOR_NORMAL = GLFW_CURSOR_NORMAL,
    CURSOR_HIDDEN = GLFW_CURSOR_HIDDEN,
    CURSOR_DISABLED = GLFW_CURSOR_DISABLED
};

class Input
{
public:
    static void initialize();

    static void update();

    static inline bool isKeyPressed(int key) { return s_currentKeys[key] && !s_previousKeys[key]; }
    static inline bool isKeyHeld(int key) { return s_currentKeys[key]; }
    static inline bool isKeyReleased(int key) { return !s_currentKeys[key] && s_previousKeys[key]; }
    static inline bool isMouseButtonPressed(int button) { return s_currentMouseButtons[button] && !s_previousMouseButtons[button]; }
    static inline bool isMouseButtonHeld(int button) { return s_currentMouseButtons[button]; }
    static inline bool isMouseButtonReleased(int button) { return !s_currentMouseButtons[button] && s_previousMouseButtons[button]; }

    static float getMouseX();
    static float getMouseY();

    static inline void setCursorMode(CursorMode mode) { glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, mode); }
    static inline CursorMode getCursorMode() { return static_cast<CursorMode>(glfwGetInputMode(glfwGetCurrentContext(), GLFW_CURSOR)); }

private:
    static bool s_currentKeys[GLFW_KEY_LAST];
    static bool s_previousKeys[GLFW_KEY_LAST];
    static bool s_currentMouseButtons[GLFW_MOUSE_BUTTON_LAST];
    static bool s_previousMouseButtons[GLFW_MOUSE_BUTTON_LAST];
};