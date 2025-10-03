#include "window.h"

#include "app.h"
#include <iostream>

Window::Window(int width, int height, const char *title)
    : m_ptr(nullptr), m_width(width), m_height(height), m_title(title), m_fullscreen(false)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_ptr = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if(!m_ptr)
        throw std::runtime_error("Failed to create Window");

    glfwMakeContextCurrent(m_ptr);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(m_ptr, (mode->width - width) / 2, (mode->height - height) / 2);

    glfwSwapInterval(0);

    glfwSetWindowUserPointer(m_ptr, this);

    glfwFocusWindow(m_ptr);

    glfwSetWindowCloseCallback(m_ptr, [](GLFWwindow* window) {
        App::getInstance()->close();
    });

    glfwSetFramebufferSizeCallback(m_ptr, [](GLFWwindow* window, int width, int height) {
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
        win->m_width = width;
        win->m_height = height;
        App::getInstance()->resize(width, height);
    });

    glfwSetWindowFocusCallback(m_ptr, [](GLFWwindow* window, int focused) {
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if(focused)
            Input::setCursorMode(CURSOR_DISABLED);
        else
            Input::setCursorMode(CURSOR_NORMAL);

        // recenter the cursor to window center
        glfwSetCursorPos(window, win->getWidth() / 2, win->getHeight() / 2);
    });
}

Window::~Window()
{
    if(m_ptr)
        glfwDestroyWindow(m_ptr);
}

void Window::update()
{
    glfwSwapBuffers(m_ptr);
    glfwPollEvents();
}

void Window::setTitle(const char *title)
{
    m_title = title;
    glfwSetWindowTitle(m_ptr, title);
}

void Window::toggleFullscreen()
{
    m_fullscreen = !m_fullscreen;

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    if(m_fullscreen)
    {
        m_lastWidth = m_width;
        m_lastHeight = m_height;
        glfwSetWindowMonitor(m_ptr, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else
    {
        glfwSetWindowMonitor(m_ptr, nullptr, (mode->width - m_lastWidth) / 2, (mode->height - m_lastHeight) / 2, m_lastWidth, m_lastHeight, mode->refreshRate);
    }
}
