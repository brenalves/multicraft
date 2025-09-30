#include "world.h"

World* World::s_instance = nullptr;

World::World()
{
    if (!s_instance)
        s_instance = this;
    else
        throw std::runtime_error("Only one instance of World can exist");

    m_player = new Player();

    // load initial chunk
    for(int x = -WORLD_INITIAL_SIZE; x <= WORLD_INITIAL_SIZE; x++)
    {
        for(int z = -WORLD_INITIAL_SIZE; z <= WORLD_INITIAL_SIZE; z++)
        {
            glm::ivec2 chunkPos(x, z);
            m_chunks[chunkPos] = new Chunk(glm::vec3(x * CHUNK_SIZE, 0, z * CHUNK_SIZE));
        }
    }

    // generate chunks meshes
    for (auto& pair : m_chunks)
    {
        pair.second->generateMesh();
    }
}

World::~World()
{
    delete m_player;

    for (auto& pair : m_chunks)
    {
        delete pair.second;
    }
}

void World::update(float deltaTime)
{
    m_player->update(deltaTime);

    std::vector<glm::ivec2> chunkToGenerateMesh;

    for(int x = -RENDER_DISTANCE; x <= RENDER_DISTANCE; x++)
    {
        for(int z = -RENDER_DISTANCE; z <= RENDER_DISTANCE; z++)
        {
            glm::ivec2 chunkPos = glm::ivec2(
                static_cast<int>(std::floor(m_player->getTransform().position.x / CHUNK_SIZE)) + x,
                static_cast<int>(std::floor(m_player->getTransform().position.z / CHUNK_SIZE)) + z
            );

            if (m_chunks.find(chunkPos) == m_chunks.end())
            {
                Chunk* newChunk = new Chunk(glm::vec3(chunkPos.x * CHUNK_SIZE, 0, chunkPos.y * CHUNK_SIZE));
                m_chunks[chunkPos] = newChunk;
                chunkToGenerateMesh.push_back(chunkPos);

                // add neighbors to generate mesh if they exist
                glm::ivec2 neighbors[4] = {
                    glm::ivec2(chunkPos.x + 1, chunkPos.y),
                    glm::ivec2(chunkPos.x - 1, chunkPos.y),
                    glm::ivec2(chunkPos.x, chunkPos.y + 1),
                    glm::ivec2(chunkPos.x, chunkPos.y - 1)
                };

                for (const auto& neighborPos : neighbors)
                {
                    if (m_chunks.find(neighborPos) != m_chunks.end())
                    {
                        chunkToGenerateMesh.push_back(neighborPos);
                    }
                }
            }
        }
    }

    // unload distant chunks
    std::vector<glm::ivec2> chunksToUnload;
    for (const auto& pair : m_chunks)
    {
        glm::ivec2 chunkPos = pair.first;
        float distance = glm::length(glm::vec2(
            chunkPos.x * CHUNK_SIZE + CHUNK_SIZE / 2 - m_player->getTransform().position.x,
            chunkPos.y * CHUNK_SIZE + CHUNK_SIZE / 2 - m_player->getTransform().position.z
        ));

        if (distance > UNLOAD_DISTANCE * CHUNK_SIZE)
        {
            chunksToUnload.push_back(chunkPos);
        }
    }

    for (const auto& pos : chunksToUnload)
    {
        auto it = m_chunks.find(pos);
        if (it != m_chunks.end())
        {
            // add neighbors to generate mesh if they exist
            glm::ivec2 neighbors[4] = {
                glm::ivec2(pos.x + 1, pos.y),
                glm::ivec2(pos.x - 1, pos.y),
                glm::ivec2(pos.x, pos.y + 1),
                glm::ivec2(pos.x, pos.y - 1)
            };
            
            for (const auto& neighborPos : neighbors)
            {
                if (m_chunks.find(neighborPos) != m_chunks.end())
                {
                    chunkToGenerateMesh.push_back(neighborPos);
                }
            }

            delete it->second;
            m_chunks.erase(it);
        }
    }

    for (const auto& pos : chunkToGenerateMesh)
    {
        if (m_chunks.find(pos) != m_chunks.end())
            m_chunks[pos]->generateMesh();
    }
}
