#include <WillowVoxEngine/World/ChunkManager.h>
#include <WillowVoxEngine/World/WorldGlobals.h>
#include <WillowVoxEngine/Core/Logger.h>

namespace WillowVox
{
    ChunkManager* ChunkManager::instance = nullptr;

    ChunkManager::~ChunkManager()
    {
        
    }

    void ChunkManager::Start()
    {
        instance = this;

        chunkThread = std::thread(&ChunkManager::ChunkThreadUpdate, this);
    }

    void ChunkManager::Update()
    {
        playerChunkX = playerObj->position.x < 0 ? floor(playerObj->position.x / CHUNK_SIZE) : playerObj->position.x / CHUNK_SIZE;
        playerChunkY = playerObj->position.y < 0 ? floor(playerObj->position.y / CHUNK_SIZE) : playerObj->position.y / CHUNK_SIZE;
        playerChunkZ = playerObj->position.z < 0 ? floor(playerObj->position.z / CHUNK_SIZE) : playerObj->position.z / CHUNK_SIZE;
    }

    void ChunkManager::ChunkThreadUpdate()
    {
        while (!shouldEnd)
        {
            chunkMutex.lock();
            for (auto it = chunks.begin(); it != chunks.end();)
            {
                if (!(*it->second).ready)
                {
                    ++it;
                    continue;
                }

                int chunkX = (*it->second).chunkPos.x;
                int chunkY = (*it->second).chunkPos.y;
                int chunkZ = (*it->second).chunkPos.z;
                if (abs(chunkX - playerChunkX) > renderDistance ||
                    abs(chunkY - playerChunkY) > renderDistance ||
                    abs(chunkZ - playerChunkZ) > renderDistance)
                {
                    delete it->second;
                    it = chunks.erase(it);
                }
                else
                    ++it;
            }
            chunkMutex.unlock();
            for (auto it = chunkData.begin(); it != chunkData.end(); )
            {
                glm::ivec3 pos = it->first;

                if (chunks.find(pos) == chunks.end() &&
                    chunks.find({ pos.x + 1, pos.y, pos.z }) == chunks.end() &&
                    chunks.find({ pos.x - 1, pos.y, pos.z }) == chunks.end() &&
                    chunks.find({ pos.x, pos.y + 1, pos.z }) == chunks.end() &&
                    chunks.find({ pos.x, pos.y - 1, pos.z }) == chunks.end() &&
                    chunks.find({ pos.x, pos.y, pos.z + 1 }) == chunks.end() &&
                    chunks.find({ pos.x, pos.y, pos.z - 1 }) == chunks.end())
                {
                    delete it->second;
                    it = chunkData.erase(it);
                }
                else
                    ++it;
            }
            //chunkMutex.unlock();

            // Check if player moved to new chunk
            if (playerChunkX != lastPlayerX || playerChunkY != lastPlayerY || playerChunkZ != lastPlayerZ)
            {
                // Player moved chunks, start new chunk queue
                lastPlayerX = playerChunkX;
                lastPlayerY = playerChunkY;
                lastPlayerZ = playerChunkZ;

                chunkQueue = {};
                // Add current chunk
                chunkQueue.push({ playerChunkX, playerChunkY, playerChunkZ });

                for (int r = 0; r < renderDistance; r++)
                {
                    // Add middle chunks
                    for (int y = 0; y < renderHeight; y++)
                    {
                        chunkQueue.push({ playerChunkX,     playerChunkY + y, playerChunkZ + r });
                        chunkQueue.push({ playerChunkX + r, playerChunkY + y, playerChunkZ     });
                        chunkQueue.push({ playerChunkX,     playerChunkY + y, playerChunkZ - r });
                        chunkQueue.push({ playerChunkX - r, playerChunkY + y, playerChunkZ     });

                        if (y > 0)
                        {
                            chunkQueue.push({ playerChunkX,     playerChunkY - y, playerChunkZ + r });
                            chunkQueue.push({ playerChunkX + r, playerChunkY - y, playerChunkZ     });
                            chunkQueue.push({ playerChunkX,     playerChunkY - y, playerChunkZ - r });
                            chunkQueue.push({ playerChunkX - r, playerChunkY - y, playerChunkZ     });
                        }
                    }

                    // Add edges
                    for (int e = 1; e < r; e++)
                    {
                        for (int y = 0; y <= renderHeight; y++)
                        {
                            chunkQueue.push({ playerChunkX + e, playerChunkY + y, playerChunkZ + r });
                            chunkQueue.push({ playerChunkX - e, playerChunkY + y, playerChunkZ + r });

                            chunkQueue.push({ playerChunkX + r, playerChunkY + y, playerChunkZ + e });
                            chunkQueue.push({ playerChunkX + r, playerChunkY + y, playerChunkZ - e });

                            chunkQueue.push({ playerChunkX + e, playerChunkY + y, playerChunkZ - r });
                            chunkQueue.push({ playerChunkX - e, playerChunkY + y, playerChunkZ - r });

                            chunkQueue.push({ playerChunkX - r, playerChunkY + y, playerChunkZ + e });
                            chunkQueue.push({ playerChunkX - r, playerChunkY + y, playerChunkZ - e });

                            if (y > 0)
                            {
                                chunkQueue.push({ playerChunkX + e, playerChunkY - y, playerChunkZ + r });
                                chunkQueue.push({ playerChunkX - e, playerChunkY - y, playerChunkZ + r });

                                chunkQueue.push({ playerChunkX + r, playerChunkY - y, playerChunkZ + e });
                                chunkQueue.push({ playerChunkX + r, playerChunkY - y, playerChunkZ - e });

                                chunkQueue.push({ playerChunkX + e, playerChunkY - y, playerChunkZ - r });
                                chunkQueue.push({ playerChunkX - e, playerChunkY - y, playerChunkZ - r });

                                chunkQueue.push({ playerChunkX - r, playerChunkY - y, playerChunkZ + e });
                                chunkQueue.push({ playerChunkX - r, playerChunkY - y, playerChunkZ - e });
                            }
                        }
                    }

                    // Add corners
                    for (int y = 0; y <= renderHeight; y++)
                    {
                        chunkQueue.push({ playerChunkX + r, playerChunkY + y, playerChunkZ + r });
                        chunkQueue.push({ playerChunkX + r, playerChunkY + y, playerChunkZ - r });
                        chunkQueue.push({ playerChunkX - r, playerChunkY + y, playerChunkZ + r });
                        chunkQueue.push({ playerChunkX - r, playerChunkY + y, playerChunkZ - r });

                        if (y > 0)
                        {
                            chunkQueue.push({ playerChunkX + r, playerChunkY - y, playerChunkZ + r });
                            chunkQueue.push({ playerChunkX + r, playerChunkY - y, playerChunkZ - r });
                            chunkQueue.push({ playerChunkX - r, playerChunkY - y, playerChunkZ + r });
                            chunkQueue.push({ playerChunkX - r, playerChunkY - y, playerChunkZ - r });
                        }
                    }
                }
            }
            else if (!chunkQueue.empty())
            {
                // Generate next chunk in queue
                glm::ivec3 chunkPos = chunkQueue.front();
                
                // If exists, skip
                chunkMutex.lock();
                if (chunks.find(chunkPos) != chunks.end())
                {
                    chunkMutex.unlock();
                    chunkQueue.pop();
                    continue;
                }
                chunkMutex.unlock();

                // Create chunk object
                Chunk* chunk = new Chunk(*solidShader, *fluidShader, *billboardShader, chunkPos, chunkPos * CHUNK_SIZE);

                // Set chunk data
                {
                    chunkMutex.lock();
                    if (chunkData.find(chunkPos) == chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        chunkMutex.unlock();

                        ChunkData* data = new ChunkData();
                        data->offset = chunkPos * CHUNK_SIZE;
                        worldGen->GenerateChunkData(*data);

                        // Set chunk's chunk data
                        chunk->chunkData = data;

                        // Add new chunk data to chunk data map
                        chunkMutex.lock();
                        chunkData[chunkPos] = data;
                        chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->chunkData = chunkData.at(chunkPos);
                        chunkMutex.unlock();
                    }
                }

                // Set north chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x, chunkPos.y, chunkPos.z - 1);
                    chunkMutex.lock();
                    if (chunkData.find(checkPos) == chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        chunkMutex.unlock();
                        
                        ChunkData* data = new ChunkData();
                        data->offset = checkPos * CHUNK_SIZE;
                        worldGen->GenerateChunkData(*data);

                        // Set chunk's chunk data
                        chunk->northData = data;

                        // Add new chunk data to chunk data map
                        chunkMutex.lock();
                        chunkData[checkPos] = data;
                        chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->northData = chunkData.at(checkPos);
                        chunkMutex.unlock();
                    }
                }

                // Set south chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x, chunkPos.y, chunkPos.z + 1);
                    chunkMutex.lock();
                    if (chunkData.find(checkPos) == chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        chunkMutex.unlock();
                        
                        ChunkData* data = new ChunkData();
                        data->offset = checkPos * CHUNK_SIZE;
                        worldGen->GenerateChunkData(*data);

                        // Set chunk's chunk data
                        chunk->southData = data;

                        // Add new chunk data to chunk data map
                        chunkMutex.lock();
                        chunkData[checkPos] = data;
                        chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->southData = chunkData.at(checkPos);
                        chunkMutex.unlock();
                    }
                }

                // Set east chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x + 1, chunkPos.y, chunkPos.z);
                    chunkMutex.lock();
                    if (chunkData.find(checkPos) == chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        chunkMutex.unlock();
                        
                        ChunkData* data = new ChunkData();
                        data->offset = checkPos * CHUNK_SIZE;
                        worldGen->GenerateChunkData(*data);

                        // Set chunk's chunk data
                        chunk->eastData = data;

                        // Add new chunk data to chunk data map
                        chunkMutex.lock();
                        chunkData[checkPos] = data;
                        chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->eastData = chunkData.at(checkPos);
                        chunkMutex.unlock();
                    }
                }

                // Set west chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x - 1, chunkPos.y, chunkPos.z);
                    chunkMutex.lock();
                    if (chunkData.find(checkPos) == chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        chunkMutex.unlock();
                        
                        ChunkData* data = new ChunkData();
                        data->offset = checkPos * CHUNK_SIZE;
                        worldGen->GenerateChunkData(*data);

                        // Set chunk's chunk data
                        chunk->westData = data;

                        // Add new chunk data to chunk data map
                        chunkMutex.lock();
                        chunkData[checkPos] = data;
                        chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->westData = chunkData.at(checkPos);
                        chunkMutex.unlock();
                    }
                }

                // Set top chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x, chunkPos.y + 1, chunkPos.z);
                    chunkMutex.lock();
                    if (chunkData.find(checkPos) == chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        chunkMutex.unlock();
                        
                        ChunkData* data = new ChunkData();
                        data->offset = checkPos * CHUNK_SIZE;
                        worldGen->GenerateChunkData(*data);

                        // Set chunk's chunk data
                        chunk->upData = data;

                        // Add new chunk data to chunk data map
                        chunkMutex.lock();
                        chunkData[checkPos] = data;
                        chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->upData = chunkData.at(checkPos);
                        chunkMutex.unlock();
                    }
                }

                // Set down chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x, chunkPos.y - 1, chunkPos.z);
                    chunkMutex.lock();
                    if (chunkData.find(checkPos) == chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        chunkMutex.unlock();
                        
                        ChunkData* data = new ChunkData();
                        data->offset = checkPos * CHUNK_SIZE;
                        worldGen->GenerateChunkData(*data);

                        // Set chunk's chunk data
                        chunk->downData = data;

                        // Add new chunk data to chunk data map
                        chunkMutex.lock();
                        chunkData[checkPos] = data;
                        chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->downData = chunkData.at(checkPos);
                        chunkMutex.unlock();
                    }
                }

                // Generate chunk mesh
                chunk->GenerateChunkMeshData();

                // Add chunk to chunk map
                chunkMutex.lock();
                chunks[chunkPos] = chunk;
                chunkMutex.unlock();
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }

    void ChunkManager::Render(Camera& camera)
    {
        glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = camera.GetProjectionMatrix();
		solidShader->Use();
		solidShader->SetMat4("view", view);
		solidShader->SetMat4("projection", projection);

		fluidShader->Use();
		fluidShader->SetMat4("view", view);
		fluidShader->SetMat4("projection", projection);

		billboardShader->Use();
		billboardShader->SetMat4("view", view);
		billboardShader->SetMat4("projection", projection);

        chunkMutex.lock();
        for (auto it = chunks.begin(); it != chunks.end();)
        {
            (*it->second).RenderSolid();
            ++it;
        }
        for (auto it = chunks.begin(); it != chunks.end();)
        {
            (*it->second).RenderTransparent();
            ++it;
        }
        chunkMutex.unlock();
    }

    Chunk* ChunkManager::GetChunk(int x, int y, int z)
    {
        chunkMutex.lock();
        Chunk* c;
        if (chunks.find(glm::ivec3(x, y, z)) == chunks.end())
            c = nullptr;
        else
            c = chunks.at(glm::ivec3(x, y, z));

        chunkMutex.unlock();
        return c;
    }

    Chunk* ChunkManager::GetChunk(glm::ivec3 pos)
    {
        chunkMutex.lock();
        Chunk* c;
        if (chunks.find(pos) == chunks.end())
            c = nullptr;
        else
            c = chunks.at(pos);

        chunkMutex.unlock();
        return c;
    }

    void ChunkManager::SetPlayerObj(Camera* camera)
    {
        playerObj = camera;
    }
}