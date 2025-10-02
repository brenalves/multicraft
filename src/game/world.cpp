#include "world.h"

World *World::s_instance = nullptr;

World::World()
{
    if (!s_instance)
        s_instance = this;
    else
        throw std::runtime_error("Only one instance of World can exist");

    m_player = new Player();
}

World::~World()
{
    delete m_player;

    for (auto &pair : m_chunks)
    {
        delete pair.second;
    }
}

void World::update(float deltaTime)
{
    m_player->update(deltaTime);

    updateChunks();
}

Chunk *World::getChunk(glm::ivec2 position)
{
    if (m_chunks.find(position) != m_chunks.end())
        return m_chunks[position];
    return nullptr;
}

void World::updateChunks()
{
    // verify new chunks to load around player based on RENDER_DISTANCE
    for (int x = -RENDER_DISTANCE; x <= RENDER_DISTANCE; x++)
    {
        for (int z = -RENDER_DISTANCE; z <= RENDER_DISTANCE; z++)
        {
            glm::ivec2 chunkPos = glm::ivec2(
                static_cast<int>(std::floor(m_player->getTransform().position.x / CHUNK_SIZE_X)) + x,
                static_cast<int>(std::floor(m_player->getTransform().position.z / CHUNK_SIZE_Z)) + z);

            // if chunk already exists, skip
            if (m_chunks.find(chunkPos) != m_chunks.end())
                continue;

            Chunk *newChunk = new Chunk(chunkPos);
            m_chunks[chunkPos] = newChunk;
            m_chunksToGenerate.push(chunkPos);

            // add neighbors to generate/regenerate mesh if they exist
            glm::ivec2 neighbors[4] = {
                glm::ivec2(chunkPos.x + 1, chunkPos.y),
                glm::ivec2(chunkPos.x - 1, chunkPos.y),
                glm::ivec2(chunkPos.x, chunkPos.y + 1),
                glm::ivec2(chunkPos.x, chunkPos.y - 1)};

            // verify if neighbor chunk exists and is not being unloaded, add it to the list to regenerate mesh
            for (const auto &neighborPos : neighbors)
            {
                if (m_chunks.find(neighborPos) == m_chunks.end())
                    continue;

                m_chunksToGenerate.push(neighborPos);
            }
        }
    }

    // verify chunks to unload and load new chunks around player
    std::vector<glm::ivec2> chunksToUnload;

    for (const auto &pair : m_chunks)
    {
        glm::ivec2 chunkPos = pair.first;
        float distance = glm::length(glm::vec2(
            chunkPos.x * CHUNK_SIZE_X + CHUNK_SIZE_X / 2 - m_player->getTransform().position.x,
            chunkPos.y * CHUNK_SIZE_Z + CHUNK_SIZE_Z / 2 - m_player->getTransform().position.z));

        // if chunk is beyond UNLOAD_DISTANCE, mark it for unloading
        if (distance > UNLOAD_DISTANCE * CHUNK_SIZE_X)
            chunksToUnload.push_back(chunkPos);
    }

    // Remove each chunk and add its neighbors to the mesh regeneration list
    for (const auto &chunkPos : chunksToUnload)
    {
        // add neighbors to generate mesh if they exist
        glm::ivec2 neighbors[4] = {
            glm::ivec2(chunkPos.x + 1, chunkPos.y),
            glm::ivec2(chunkPos.x - 1, chunkPos.y),
            glm::ivec2(chunkPos.x, chunkPos.y + 1),
            glm::ivec2(chunkPos.x, chunkPos.y - 1)};

        // verify if neighbor chunks exist and if they are not being unloaded, add them to the list to regenerate mesh
        for (const auto &neighborPos : neighbors)
        {
            if (m_chunks.find(neighborPos) == m_chunks.end())
                continue;

            m_chunksToGenerate.push(neighborPos);
        }

        delete m_chunks[chunkPos];
        m_chunks.erase(chunkPos);
    }

    // regenerate meshes for chunks that need it removing from the list
    int chunksProcessed = 0;
    while (!m_chunksToGenerate.empty() && chunksProcessed < MAX_CHUNKS_PER_FRAME)
    {
        glm::ivec2 chunkPos = m_chunksToGenerate.front();
        m_chunksToGenerate.pop();

        if (m_chunks.find(chunkPos) == m_chunks.end())
            continue;

        m_chunks[chunkPos]->generateMesh();
        chunksProcessed++;
    }
}
