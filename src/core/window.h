#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdexcept>

class Window
{
public:
    Window(int width, int height, const char* title);
    ~Window();

    void update();

private:
    GLFWwindow* m_ptr;
    int m_width;
    int m_height;
    const char* m_title;
};