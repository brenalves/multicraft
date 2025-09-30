#pragma once

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

    static float getMouseX();
    static float getMouseY();

    static inline void setCursorMode(CursorMode mode) { glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, mode); }
    static inline CursorMode getCursorMode() { return static_cast<CursorMode>(glfwGetInputMode(glfwGetCurrentContext(), GLFW_CURSOR)); }

private:
    static bool s_currentKeys[GLFW_KEY_LAST];
    static bool s_previousKeys[GLFW_KEY_LAST];
    
};