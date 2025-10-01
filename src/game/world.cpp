#include "world.h"

World* World::s_instance = nullptr;

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

    for (auto& pair : m_chunks)
    {
        delete pair.second;
    }
}

void World::update(float deltaTime)
{
    m_player->update(deltaTime);

    updateChunks();
}

void World::breakBlock(const glm::ivec3 &blockPos)
{
    Chunk *chunk = getChunk(glm::ivec2(blockPos.x / CHUNK_SIZE_X, blockPos.z / CHUNK_SIZE_Z));
    if (!chunk)
        return;

    glm::ivec3 localPos = glm::ivec3(
        (blockPos.x % CHUNK_SIZE_X + CHUNK_SIZE_X) % CHUNK_SIZE_X,
        blockPos.y,
        (blockPos.z % CHUNK_SIZE_Z + CHUNK_SIZE_Z) % CHUNK_SIZE_Z
    );

    if (localPos.y < 0 || localPos.y >= CHUNK_SIZE_Y)
        return;
    
    if (chunk->getBlock(localPos.x, localPos.y, localPos.z) == BLOCK_AIR)
        return;

    // set block to air
    chunk->setBlock(localPos.x, localPos.y, localPos.z, BLOCK_AIR);
    // mark chunk for mesh regeneration
    m_chunksToGenerateMesh[glm::ivec2(blockPos.x / CHUNK_SIZE_X, blockPos.z / CHUNK_SIZE_Z)] = chunk;
}

void World::updateChunks()
{
    // load new chunks around player based on RENDER_DISTANCE
    for(int x = -RENDER_DISTANCE; x <= RENDER_DISTANCE; x++)
    {
        for(int z = -RENDER_DISTANCE; z <= RENDER_DISTANCE; z++)
        {
            glm::ivec2 chunkPos = glm::ivec2(
                static_cast<int>(std::floor(m_player->getTransform().position.x / CHUNK_SIZE_X)) + x,
                static_cast<int>(std::floor(m_player->getTransform().position.z / CHUNK_SIZE_Z)) + z
            );

            // if chunk already exists, skip
            if(m_chunks.find(chunkPos) != m_chunks.end())
                continue;

            Chunk* newChunk = new Chunk(glm::vec3(chunkPos.x * CHUNK_SIZE_X, 0, chunkPos.y * CHUNK_SIZE_Z));
            m_chunks[chunkPos] = newChunk;
            m_chunksToGenerateMesh[chunkPos] = newChunk;

            // add neighbors to generate/regenerate mesh if they exist
            glm::ivec2 neighbors[4] = {
                glm::ivec2(chunkPos.x + 1, chunkPos.y),
                glm::ivec2(chunkPos.x - 1, chunkPos.y),
                glm::ivec2(chunkPos.x, chunkPos.y + 1),
                glm::ivec2(chunkPos.x, chunkPos.y - 1)
            };

            // verify if neighbor chunks exist and add them to the list to regenerate mesh
            for (const auto& neighborPos : neighbors)
            {
                if(m_chunks.find(neighborPos) == m_chunks.end())
                    continue;

                // the unordered_map will handle duplicates
                m_chunksToGenerateMesh[neighborPos] = m_chunks[neighborPos];
            }
        }
    }

    // unload distant chunks
    std::unordered_map<glm::ivec2, Chunk*, IVec2Hash> chunksToUnload;
    for (const auto& pair : m_chunks)
    {
        glm::ivec2 chunkPos = pair.first;
        float distance = glm::length(glm::vec2(
            chunkPos.x * CHUNK_SIZE_X + CHUNK_SIZE_X / 2 - m_player->getTransform().position.x,
            chunkPos.y * CHUNK_SIZE_Z + CHUNK_SIZE_Z / 2 - m_player->getTransform().position.z
        ));

        // if chunk is beyond UNLOAD_DISTANCE, mark it for unloading
        if (distance > UNLOAD_DISTANCE * CHUNK_SIZE_X)
            chunksToUnload[chunkPos] = pair.second;
    }

    // Remove each chunk and add its neighbors to the mesh regeneration list
    for(const auto& pair : chunksToUnload)
    {
        glm::ivec2 pos = pair.first;
        Chunk* chunk = pair.second;

        // add neighbors to generate mesh if they exist
        glm::ivec2 neighbors[4] = {
            glm::ivec2(pos.x + 1, pos.y),
            glm::ivec2(pos.x - 1, pos.y),
            glm::ivec2(pos.x, pos.y + 1),
            glm::ivec2(pos.x, pos.y - 1)
        };
        
        // verify if neighbor chunks exist and if they are not being unloaded, add them to the list to regenerate mesh
        for (const auto& neighborPos : neighbors)
        {
            if (m_chunks.find(neighborPos) == m_chunks.end())
                continue;

            if(chunksToUnload.find(neighborPos) != chunksToUnload.end())
                continue;

            m_chunksToGenerateMesh[neighborPos] = m_chunks[neighborPos];
        }

        delete chunk;
        m_chunks.erase(pos);
    }

    // regenerate meshes for chunks that need it removing from the list
    int chunksProcessed = 0;
    for(auto it = m_chunksToGenerateMesh.begin(); it != m_chunksToGenerateMesh.end(); )
    {
        if(chunksProcessed >= MAX_CHUNKS_PER_FRAME)
            break;
        it->second->generateMesh();
        it = m_chunksToGenerateMesh.erase(it);
        chunksProcessed++;
    }

}
