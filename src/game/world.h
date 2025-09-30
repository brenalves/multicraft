#pragma once

#include <glm/glm.hpp>
#include <stdexcept>
#include <unordered_map>

#include "chunk.h"
#include "player.h"

#define WORLD_INITIAL_SIZE 5
#define RENDER_DISTANCE 4
#define UNLOAD_DISTANCE 6

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

    inline Chunk* getChunk(const glm::ivec2& position) { return m_chunks.find(position) != m_chunks.end() ? m_chunks[position] : nullptr; }
    inline std::unordered_map<glm::ivec2, Chunk*, IVec2Hash>& getChunks() { return m_chunks; }
    inline Player& getPlayer() { return *m_player; }

    static inline World* getInstance() { return s_instance; }

private:
    std::unordered_map<glm::ivec2, Chunk*, IVec2Hash> m_chunks;

    Player* m_player;
    
    static World* s_instance;
};