#include "chunk.h"

#include "world.h"

Chunk::Chunk(glm::vec3 position)
    : m_material(ResourceManager::getShader("chunk"))
{
    m_transform.position = position;

    for (int x = 0; x < CHUNK_SIZE; ++x)
    {
        for (int y = 0; y < CHUNK_SIZE; ++y)
        {
            for (int z = 0; z < CHUNK_SIZE; ++z)
            {
                // if(y == 0)
                //     m_blocks[x][y][z] = BLOCK_BEDROCK;
                // else if (y == 2)
                //     m_blocks[x][y][z] = BLOCK_DIAMOND;
                // else if (y < 5)
                //     m_blocks[x][y][z] = BLOCK_STONE;
                // else if (y == 5)
                //     m_blocks[x][y][z] = BLOCK_DIRT;
                // else if (y == 6)
                //     m_blocks[x][y][z] = BLOCK_GRASS;
                // else
                //     m_blocks[x][y][z] = BLOCK_AIR;

                // apply sine wave pattern
                float height = (std::sin((x + position.x) * 0.3f) + std::cos((z + position.z) * 0.3f)) * 2.0f + 8.0f;
                if (y < height - 1)
                    m_blocks[x][y][z] = BLOCK_DIRT;
                else if (y < height)
                    m_blocks[x][y][z] = BLOCK_GRASS;
                else if (y == 0)
                    m_blocks[x][y][z] = BLOCK_BEDROCK;
                else
                    m_blocks[x][y][z] = BLOCK_AIR;
            }
        }
    }

    BufferLayout layout;
    layout.push<float>(3, false); // position
    layout.push<float>(2, false); // uv

    m_mesh = new Mesh(layout);
    m_material.setDiffuseMap(&ResourceManager::getTexture("atlas"));
}

Chunk::~Chunk()
{
    delete m_mesh;
}

BlockType Chunk::getBlock(int x, int y, int z)
{
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_SIZE || z < 0 || z >= CHUNK_SIZE)
        return BLOCK_AIR;

    return m_blocks[x][y][z];
}

void Chunk::generateMesh()
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                if (m_blocks[x][y][z] == BLOCK_AIR)
                    continue;

                bool facesVisible[6] = {false};

                facesVisible[0] = verifyVisibility(x, y + 1, z); // Top
                facesVisible[1] = verifyVisibility(x, y - 1, z); // Bottom
                facesVisible[2] = verifyVisibility(x - 1, y, z); // Left
                facesVisible[3] = verifyVisibility(x + 1, y, z); // Right
                facesVisible[4] = verifyVisibility(x, y, z - 1); // Front
                facesVisible[5] = verifyVisibility(x, y, z + 1); // Back

                for (int i = 0; i < 6; i++)
                {
                    if (!facesVisible[i])
                        continue;

                    float vx = static_cast<float>(x);
                    float vy = static_cast<float>(y);
                    float vz = static_cast<float>(z);

                    glm::vec2 uv = getUV(m_blocks[x][y][z], i);

                    // Calculate per-face UV corners
                    float u0 = uv.x;
                    float v0 = uv.y;
                    float u1 = uv.x + TILE_SIZE / static_cast<float>(ATLAS_SIZE);
                    float v1 = uv.y + TILE_SIZE / static_cast<float>(ATLAS_SIZE);

                    switch (i)
                    {
                    case 0: // Top (+Y)
                        vertices.insert(vertices.end(), {
                            vx,     vy + 1, vz,     u0, v0, // bottom-left
                            vx + 1, vy + 1, vz,     u1, v0, // bottom-right
                            vx + 1, vy + 1, vz + 1, u1, v1, // top-right
                            vx,     vy + 1, vz + 1, u0, v1  // top-left
                        });
                        break;
                    case 1: // Bottom (-Y)
                        vertices.insert(vertices.end(), {
                            vx,     vy, vz,     u0, v1, // top-left
                            vx + 1, vy, vz,     u1, v1, // top-right
                            vx + 1, vy, vz + 1, u1, v0, // bottom-right
                            vx,     vy, vz + 1, u0, v0  // bottom-left
                        });
                        break;
                    case 2: // Left (-X)
                        vertices.insert(vertices.end(), {
                            vx, vy,     vz,     u0, v0, // top-right
                            vx, vy + 1, vz,     u0, v1, // bottom-right
                            vx, vy + 1, vz + 1, u1, v1, // bottom-left
                            vx, vy,     vz + 1, u1, v0  // top-left
                        });
                        break;
                    case 3: // Right (+X)
                        vertices.insert(vertices.end(), {
                            vx + 1, vy,     vz,     u0, v0, // top-left
                            vx + 1, vy + 1, vz,     u0, v1, // bottom-left
                            vx + 1, vy + 1, vz + 1, u1, v1, // bottom-right
                            vx + 1, vy,     vz + 1, u1, v0  // top-right
                        });
                        break;
                    case 4: // Front (-Z)
                        vertices.insert(vertices.end(), {
                            vx,     vy,     vz,     u0, v0, // top-right
                            vx + 1, vy,     vz,     u1, v0, // top-left
                            vx + 1, vy + 1, vz,     u1, v1, // bottom-left
                            vx,     vy + 1, vz,     u0, v1  // bottom-right
                        });
                        break;
                    case 5: // Back (+Z)
                        vertices.insert(vertices.end(), {
                            vx,     vy,     vz + 1, u0, v0, // top-left
                            vx + 1, vy,     vz + 1, u1, v0, // top-right
                            vx + 1, vy + 1, vz + 1, u1, v1, // bottom-right
                            vx,     vy + 1, vz + 1, u0, v1  // bottom-left
                        });
                        break;
                    }

                    unsigned int startIndex = static_cast<unsigned int>(vertices.size() / 5) - 4;
                    indices.insert(indices.end(), {startIndex, startIndex + 1, startIndex + 2,
                                                   startIndex, startIndex + 2, startIndex + 3});
                }
            }
        }
    }

    m_mesh->setVertices(vertices.data(), vertices.size() * sizeof(float));
    m_mesh->setIndices(indices.data(), indices.size() * sizeof(unsigned int));
}

bool Chunk::verifyVisibility(int x, int y, int z)
{
    // Check bounds and internal visibility
    bool localVisibility = getBlock(x, y, z) == BLOCK_AIR;

    // Check neighboring chunks for edge blocks
    bool neighborVisibility = false;

    if(x > 0 && x < CHUNK_SIZE && z > 0 && z < CHUNK_SIZE)
        neighborVisibility = true;
    else
    {
        auto neighbor = World::getInstance()->getChunk(glm::ivec2(
            m_transform.position.x / CHUNK_SIZE + (x < 0 ? -1 : (x >= CHUNK_SIZE ? 1 : 0)),
            m_transform.position.z / CHUNK_SIZE + (z < 0 ? -1 : (z >= CHUNK_SIZE ? 1 : 0))
        ));

        if(neighbor)
            neighborVisibility = neighbor->getBlock((x + CHUNK_SIZE) % CHUNK_SIZE, y, (z + CHUNK_SIZE) % CHUNK_SIZE) == BLOCK_AIR;
        else
            neighborVisibility = true; // If neighbor chunk doesn't exist, consider it visible
    }

    return localVisibility && neighborVisibility;
}

glm::vec2 Chunk::getUV(BlockType type, int face)
{
    int tileX = 0;
    int tileY = 0;

    switch (type)
    {
    case BLOCK_GRASS:
        if (face == 0) // Top
        {
            tileX = 0;
            tileY = 0;
        }
        else if (face == 1) // Bottom
        {
            tileX = 2;
            tileY = 0;
        }
        else // Sides
        {
            tileX = 1;
            tileY = 0;
        }
        break;
    case BLOCK_DIRT:
        tileX = 2;
        tileY = 0;
        break;
    case BLOCK_STONE:
        tileX = 3;
        tileY = 0;
        break;
    case BLOCK_DIAMOND:
        tileX = 4;
        tileY = 0;
        break;
    case BLOCK_BEDROCK:
        tileX = 5; // Default texture
        tileY = 0;
        break;
    }

    float u = (tileX * TILE_SIZE) / static_cast<float>(ATLAS_SIZE);
    float v = (tileY * TILE_SIZE) / static_cast<float>(ATLAS_SIZE);

    return glm::vec2(u, v);
}
