#include "cube.h"

Cube::Cube()
{
    BufferLayout layout;
    layout.push<float>(3, false); // position
    layout.push<float>(2, false); // texCoord
    
    m_mesh = new Mesh(layout);

    const std::vector<float> cubeVertices = {
        // Front face
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
         0.5f,  0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.5f, 0.0f, 1.0f,

        // Back face
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        // Left face
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,

        // Right face
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

        // Top face
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f,

        // Bottom face
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 0.0f
    };

    unsigned int cubeIndices[36];
    for (unsigned int i = 0; i < 36; ++i)
        cubeIndices[i] = i;

    m_mesh->setVertices(cubeVertices.data(), cubeVertices.size() * sizeof(float));
    m_mesh->setIndices(cubeIndices, sizeof(cubeIndices));

    m_material = new Material(ResourceManager::getShader("basic"));
    m_material->setDiffuseMap(&ResourceManager::getTexture("container"));

    m_transform.position = glm::vec3(4.0f, 0.0f, -15.0f);
}

Cube::~Cube()
{
    delete m_mesh;
    delete m_material;
}

void Cube::update(float deltaTime)
{
    m_transform.update();
    m_transform.rotation.z += 25.0f * deltaTime;
}