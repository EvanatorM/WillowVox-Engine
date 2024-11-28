#pragma once

#include <WillowVoxEngine/World/Chunk.h>
#include <WillowVoxEngine/World/ChunkData.h>
#include <WillowVoxEngine/Math/ivec3Hash.h>
#include <WillowVoxEngine/Rendering/Camera.h>
#include <WillowVoxEngine/World/TerrainGen.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <queue>
#include <thread>
#include <mutex>

namespace WillowVox
{
    class ChunkManager
    {
    public:
        ~ChunkManager();

        void Start();
        void Update();
        void Render(Camera& camera);

        void SetPlayerObj(Camera* camera);

        int renderDistance = 10;
        int renderHeight = 3;

        // TEMP until asset manager
        Shader* terrainShader;

    private:
        void ChunkThreadUpdate();

        TerrainGen worldGen;

        std::unordered_map<glm::ivec3, Chunk*, ivec3Hash> chunks;
        std::unordered_map<glm::ivec3, ChunkData*, ivec3Hash> chunkData;
        std::queue<glm::ivec3> chunkQueue; // For use only by chunk thread
        
        std::thread chunkThread;
        std::mutex chunkMutex;

        Camera* playerObj;
        int lastPlayerX = -100, lastPlayerY = -100, lastPlayerZ = -100;
        int playerChunkX = -100, playerChunkY = -100, playerChunkZ = -100;

        bool shouldEnd = false;
    };
}