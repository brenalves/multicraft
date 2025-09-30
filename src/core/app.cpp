#include "app.h"

#include "game/player.h"
#include "game/quad.h"
#include "game/cube.h"
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
 
    auto& atlas = ResourceManager::loadTexture("atlas", "assets/textures/atlas.png");
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
    Player player;
    Quad quad;
    Cube cube;
    World world;

    double lastTime = glfwGetTime();
    
    while (m_running)
    {
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        Input::update();
        
        // update here
        if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
            close();

        if(Input::isKeyPressed(GLFW_KEY_F3))
            Input::setCursorMode(Input::getCursorMode() == CURSOR_DISABLED ? CURSOR_NORMAL : CURSOR_DISABLED);

        if(Input::isKeyPressed(GLFW_KEY_1))
            Renderer::setDrawMode(DrawMode::FILL);
        if(Input::isKeyPressed(GLFW_KEY_2))
            Renderer::setDrawMode(DrawMode::LINE);

        quad.update(deltaTime);
        player.update(deltaTime);
        cube.update(deltaTime);
        world.update(deltaTime);

        Renderer::clear();

        // render here
        Renderer::setCamera(player.getCamera(), player.getTransform());

        Renderer::draw(quad.getTransform(), quad.getMaterial(), quad.getMesh());
        Renderer::draw(cube.getTransform(), cube.getMaterial(), cube.getMesh());

        auto& chunk = world.getChunk();
        Renderer::drawChunk(chunk.getTransform(), chunk.getMesh());

        m_window->update();
    }
}

void App::close()
{
    m_running = false;
}
