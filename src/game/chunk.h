#pragma once

#include "components/transform.h"
#include "components/mesh.h"
#include "components/material.h"
#include "core/resourcemanager.h"

#define CHUNK_SIZE 16
#define ATLAS_SIZE 256
#define TILE_SIZE 16

enum BlockType
{
    BLOCK_AIR = 0,
    BLOCK_GRASS,
    BLOCK_DIRT,
    BLOCK_STONE,
    BLOCK_DIAMOND,
    BLOCK_BEDROCK
};

class Chunk
{
public:
    Chunk(glm::vec3 position);
    ~Chunk();

    void generateMesh();

    BlockType getBlock(int x, int y, int z);

    inline Transform& getTransform() { return m_transform; }
    inline Mesh& getMesh() { return *m_mesh; }
    inline Material& getMaterial() { return m_material; }

private:
    bool verifyVisibility(int x, int y, int z);
    glm::vec2 getUV(BlockType type, int face);

private:
    Transform m_transform;
    Mesh* m_mesh;
    Material m_material;

    BlockType m_blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
};