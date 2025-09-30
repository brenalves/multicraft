#include "world.h"

World::World()
{
    m_chunk = new Chunk(glm::vec3(0.0));
}

World::~World()
{
    delete m_chunk;
}

void World::update(float deltaTime)
{
}
