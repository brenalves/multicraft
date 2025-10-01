#pragma once

#include "components/transform.h"
#include "components/mesh.h"
#include "components/material.h"
#include "core/resourcemanager.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 256
#define CHUNK_SIZE_Z 16
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
    inline void setBlock(int x, int y, int z, BlockType type) { m_blocks[x][y][z] = type; }

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

    BlockType m_blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];
};