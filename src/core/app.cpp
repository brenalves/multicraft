#include "app.h"

#include "game/world.h"

App *App::s_instance = nullptr;

App::App()
{
    if (!s_instance)
        s_instance = this;
    else
        throw std::runtime_error("Only one instance of App can exist");

    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW library");

    m_window = new Window(800, 600, "Multicraft");

    Renderer::initialize();
    ResourceManager::initialize();
    Input::initialize();

    ResourceManager::loadShader("basic", "assets/shaders/vs.glsl", "assets/shaders/fs.glsl");
    ResourceManager::loadShader("chunk", "assets/shaders/chunk.vert", "assets/shaders/chunk.frag");
    ResourceManager::loadShader("ray", "assets/shaders/ray.vert", "assets/shaders/ray.frag");

    auto &atlas = ResourceManager::loadTexture("atlas", "assets/textures/atlas.png");
    atlas.setFilterMode(GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
    ResourceManager::loadTexture("container", "assets/textures/box.jpg");

    m_running = true;
}

App::~App()
{
    ResourceManager::shutdown();
    Renderer::shutdown();

    delete m_window;

    glfwTerminate();
}

void App::run()
{
    World world;

    Input::setCursorMode(CURSOR_NORMAL);

    double lastTime = glfwGetTime();

    while (m_running)
    {
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        // update window title with fps every 1s
        static double fpsTimer = 0.0;
        fpsTimer += deltaTime;
        if (fpsTimer >= 1.0)
        {
            m_window->setTitle(("Multicraft - FPS: " + std::to_string(static_cast<int>(1.0f / deltaTime))).c_str());
            fpsTimer = 0.0;
        }

        Input::update();

        // update here
        if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
            close();

        if (Input::isKeyPressed(GLFW_KEY_F3))
            Input::setCursorMode(Input::getCursorMode() == CURSOR_DISABLED ? CURSOR_NORMAL : CURSOR_DISABLED);

        if (Input::isKeyPressed(GLFW_KEY_1))
            Renderer::setDrawMode(DrawMode::FILL);
        if (Input::isKeyPressed(GLFW_KEY_2))
            Renderer::setDrawMode(DrawMode::LINE);

        world.update(deltaTime);

        Renderer::clear();

        // render here
        auto &player = world.getPlayer();
        Renderer::setCamera(player.getCamera(), player.getTransform());

        auto &chunks = world.getChunks();
        for (auto &pair : chunks)
        {
            glm::vec3 position = glm::vec3(pair.first.x * CHUNK_SIZE_X, 0.0f, pair.first.y * CHUNK_SIZE_Z);
            Renderer::drawChunk(position, pair.second->getMesh());
        }

        m_window->update();
    }
}

void App::close()
{
    m_running = false;
}
