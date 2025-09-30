#include "quad.h"

Quad::Quad()
{
    BufferLayout layout;
    layout.push<float>(3, false); // position
    layout.push<float>(2, false); // texCoord

    m_mesh = new Mesh(layout);

    float vertices[] = {
        // positions        // texCoords
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    m_mesh->setVertices(vertices, sizeof(vertices));
    m_mesh->setIndices(indices, sizeof(indices));

    m_material = new Material(ResourceManager::getShader("basic"));
    m_material->setDiffuseMap(&ResourceManager::getTexture("container"));

    m_transform.position = glm::vec3(0.0f, 0.0f, -8.0f);
}

Quad::~Quad()
{
    delete m_mesh;
    delete m_material;
}

void Quad::update(float deltaTime)
{
    m_transform.update();
    m_transform.rotation.z += 25.0f * deltaTime;
}
