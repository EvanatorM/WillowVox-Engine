#include <WillowVoxEngine/World/Chunk.h>
#include <WillowVoxEngine/Rendering/Mesh.h>
#include <WillowVoxEngine/World/WorldGlobals.h>
#include <WillowVoxEngine/Core/Logger.h>

namespace WillowVox
{
    Chunk::Chunk(Shader& shader, glm::ivec3 chunkPos, glm::vec3 worldPos)
        : shader(shader), chunkPos(chunkPos), worldPos(worldPos)
    {
        mr = new MeshRenderer(shader);
    }

    Chunk::~Chunk()
    {
        delete mr;
    }

    void Chunk::SetChunkData(ChunkData* data)
    {
        chunkData = data;
    }

    void Chunk::GenerateChunkMeshData()
    {
        vertices.clear();
        indices.clear();

        uint32_t currentVertex = 0;

        for (char x = 0; x < CHUNK_SIZE; x++)
        {
            for (char z = 0; z < CHUNK_SIZE; z++)
            {
                for (char y = 0; y < CHUNK_SIZE; y++)
                {
                    if (chunkData->GetBlock(x, y, z) == 0)
                        continue;
                    
                    // North
                    {
                        if (z == 0 || chunkData->GetBlock(x, y, z - 1) == 0)
                        {
                            vertices.emplace_back(x + 1, y + 0, z + 0, 0, 0);
                            vertices.emplace_back(x + 0, y + 0, z + 0, 1, 0);
                            vertices.emplace_back(x + 1, y + 1, z + 0, 0, 1);
                            vertices.emplace_back(x + 0, y + 1, z + 0, 1, 1);

                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 3);
                            indices.emplace_back(currentVertex + 1);
                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 2);
                            indices.emplace_back(currentVertex + 3);
                            currentVertex += 4;
                        }
                    }

                    // South
                    {
                        if (z == CHUNK_SIZE - 1 || chunkData->GetBlock(x, y, z + 1) == 0)
                        {
                            vertices.emplace_back(x + 0, y + 0, z + 1, 0, 0);
                            vertices.emplace_back(x + 1, y + 0, z + 1, 1, 0);
                            vertices.emplace_back(x + 0, y + 1, z + 1, 0, 1);
                            vertices.emplace_back(x + 1, y + 1, z + 1, 1, 1);

                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 3);
                            indices.emplace_back(currentVertex + 1);
                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 2);
                            indices.emplace_back(currentVertex + 3);
                            currentVertex += 4;
                        }
                    }

                    // West
                    {
                        if (x == 0 || chunkData->GetBlock(x - 1, y, z) == 0)
                        {
                            vertices.emplace_back(x + 0, y + 0, z + 0, 0, 0);
                            vertices.emplace_back(x + 0, y + 0, z + 1, 1, 0);
                            vertices.emplace_back(x + 0, y + 1, z + 0, 0, 1);
                            vertices.emplace_back(x + 0, y + 1, z + 1, 1, 1);

                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 3);
                            indices.emplace_back(currentVertex + 1);
                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 2);
                            indices.emplace_back(currentVertex + 3);
                            currentVertex += 4;
                        }
                    }

                    // East
                    {
                        if (x == CHUNK_SIZE - 1 || chunkData->GetBlock(x + 1, y, z) == 0)
                        {
                            vertices.emplace_back(x + 1, y + 0, z + 1, 0, 0);
                            vertices.emplace_back(x + 1, y + 0, z + 0, 1, 0);
                            vertices.emplace_back(x + 1, y + 1, z + 1, 0, 1);
                            vertices.emplace_back(x + 1, y + 1, z + 0, 1, 1);

                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 3);
                            indices.emplace_back(currentVertex + 1);
                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 2);
                            indices.emplace_back(currentVertex + 3);
                            currentVertex += 4;
                        }
                    }

                    // Bottom
                    {
                        if (y == 0 || chunkData->GetBlock(x, y - 1, z) == 0)
                        {
                            vertices.emplace_back(x + 1, y + 0, z + 1, 0, 0);
                            vertices.emplace_back(x + 0, y + 0, z + 1, 1, 0);
                            vertices.emplace_back(x + 1, y + 0, z + 0, 0, 1);
                            vertices.emplace_back(x + 0, y + 0, z + 0, 1, 1);

                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 3);
                            indices.emplace_back(currentVertex + 1);
                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 2);
                            indices.emplace_back(currentVertex + 3);
                            currentVertex += 4;
                        }
                    }

                    // Top
                    {
                        if (y == CHUNK_SIZE - 1 || chunkData->GetBlock(x, y + 1, z) == 0)
                        {
                            vertices.emplace_back(x + 0, y + 1, z + 1, 0, 0);
                            vertices.emplace_back(x + 1, y + 1, z + 1, 1, 0);
                            vertices.emplace_back(x + 0, y + 1, z + 0, 0, 1);
                            vertices.emplace_back(x + 1, y + 1, z + 0, 1, 1);

                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 3);
                            indices.emplace_back(currentVertex + 1);
                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 2);
                            indices.emplace_back(currentVertex + 3);
                            currentVertex += 4;
                        }
                    }
                }
            }
        }
    }

    void Chunk::GenerateChunkMesh()
    {
        Mesh<ChunkVertex>* mesh = new Mesh<ChunkVertex>();
        mesh->SetMeshData(vertices, indices);
        mr->SetMesh(mesh, true);

        //vertices.clear();
        //indices.clear();
    }

    void Chunk::Render()
    {
        if (!ready)
        {
            GenerateChunkMesh();
            ready = true;
        }

		shader.SetVec3("model", worldPos);
        mr->Render();
    }
}