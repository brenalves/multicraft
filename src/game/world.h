#pragma once

#include "chunk.h"

class World
{
public:
    World();
    ~World();

    void update(float deltaTime);

    inline Chunk& getChunk() { return *m_chunk; }

private:
    Chunk* m_chunk;
};