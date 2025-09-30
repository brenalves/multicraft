#include "window.h"

#include "app.h"

Window::Window(int width, int height, const char *title)
    : m_ptr(nullptr), m_width(width), m_height(height), m_title(title)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_ptr = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if(!m_ptr)
        throw std::runtime_error("Failed to create Window");

    glfwMakeContextCurrent(m_ptr);

    glfwSwapInterval(0);

    glfwFocusWindow(m_ptr);

    glfwSetWindowCloseCallback(m_ptr, [](GLFWwindow* window) {
        App::getInstance()->close();
    });

    glfwSetWindowFocusCallback(m_ptr, [](GLFWwindow* window, int focused) {
        if(focused)
            Input::setCursorMode(CURSOR_DISABLED);
        else
            Input::setCursorMode(CURSOR_NORMAL);
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
