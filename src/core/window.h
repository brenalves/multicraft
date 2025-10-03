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

    inline int getWidth() const { return m_width; }
    inline int getHeight() const { return m_height; }
    inline bool isFullscreen() const { return m_fullscreen; }

    void setTitle(const char* title);
    void toggleFullscreen();

private:
    GLFWwindow* m_ptr;
    int m_width;
    int m_height;
    const char* m_title;
    bool m_fullscreen;
    int m_lastWidth;
    int m_lastHeight;
};