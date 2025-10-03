#pragma once

#include "window.h"
#include "input.h"
#include "rendering/renderer.h"
#include "resourcemanager.h"

class App
{
public:
    App();
    ~App();

    void run();
    void close();
    void resize(int width, int height);

    inline Window& getWindow() { return *m_window; }

    static inline App* getInstance() { return s_instance; }

private:
    static App* s_instance;

    Window* m_window;

    bool m_running;
};