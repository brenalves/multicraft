#include "renderer.h"

glm::mat4 Renderer::m_currentProjectionMatrix = glm::mat4(1.0f);
glm::mat4 Renderer::m_currentViewMatrix = glm::mat4(1.0f);

void Renderer::initialize()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD library");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
    setDrawMode(DrawMode::FILL);
}

void Renderer::shutdown()
{
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setCamera(Camera& camera, Transform& cameraTransform)
{
    m_currentProjectionMatrix = camera.getProjectionMatrix();
    m_currentViewMatrix = glm::lookAt(cameraTransform.position, cameraTransform.position + cameraTransform.forward, cameraTransform.up);
}

void Renderer::draw(Transform& transform, Material &material, Mesh &mesh)
{
    auto& shader = material.getShader();
    shader.bind();
    mesh.bind();

    shader.setUniformMat4("uProjectionMatrix", glm::value_ptr(m_currentProjectionMatrix));
    shader.setUniformMat4("uViewMatrix", glm::value_ptr(m_currentViewMatrix));
    shader.setUniformMat4("uModelMatrix", glm::value_ptr(transform.getModelMatrix()));

    if(material.getDiffuseMap())
        material.getDiffuseMap()->bind(0);
    if(material.getSpecularMap())
        material.getSpecularMap()->bind(1);

    shader.setUniform1i("uMaterial.diffuse", 0);
    shader.setUniform1i("uMaterial.specular", 1);
    shader.setUniform1f("uMaterial.shininess", material.getShininess());

    glDrawElements(GL_TRIANGLES, mesh.getIB().getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::drawChunk(const glm::vec3& position, Mesh &mesh)
{
    static Shader& shader = ResourceManager::getShader("chunk");
    shader.bind();
    mesh.bind();

    shader.setUniformMat4("uProjectionMatrix", glm::value_ptr(m_currentProjectionMatrix));
    shader.setUniformMat4("uViewMatrix", glm::value_ptr(m_currentViewMatrix));

    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

    shader.setUniformMat4("uModelMatrix", glm::value_ptr(model));

    ResourceManager::getTexture("atlas").bind(0);
    shader.setUniform1i("uAtlas", 0);

    glDrawElements(GL_TRIANGLES, mesh.getIB().getCount(), GL_UNSIGNED_INT, nullptr);
}
