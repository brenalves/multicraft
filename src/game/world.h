#pragma once

#include <glm/glm.hpp>
#include <stdexcept>
#include <unordered_map>
#include <queue>

#include "chunk.h"
#include "player.h"

#define WORLD_INITIAL_SIZE 5
#define RENDER_DISTANCE 8
#define UNLOAD_DISTANCE 16
#define MAX_CHUNKS_PER_FRAME 1

struct IVec2Hash {
    std::size_t operator()(const glm::ivec2& v) const noexcept {
        std::size_t h1 = std::hash<int>{}(v.x);
        std::size_t h2 = std::hash<int>{}(v.y);
        return h1 ^ (h2 << 1); // Combine hashes
    }
};

class World
{
public:
    World();
    ~World();

    void update(float deltaTime);
    void onWindowResize(int width, int height);

    bool breakBlock(int x, int y, int z);
    bool placeBlock(int x, int y, int z, BlockType type);

    Chunk* getChunk(glm::ivec2 position);

    inline std::unordered_map<glm::ivec2, Chunk*, IVec2Hash>& getChunks() { return m_chunks; }
    inline Player& getPlayer() { return *m_player; }

    static inline World* getInstance() { return s_instance; }

private:
    void updateChunks();

private:
    std::unordered_map<glm::ivec2, Chunk*, IVec2Hash> m_chunks;
    std::queue<glm::ivec2> m_chunksToGenerate;

    Player* m_player;
    
    static World* s_instance;
};