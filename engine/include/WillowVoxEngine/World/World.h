#pragma once

#include <WillowVoxEngine/Rendering/MeshRenderer.h>
#include <WillowVoxEngine/World/Chunk.h>
#include <WillowVoxEngine/World/GameObject.h>
#include <WillowVoxEngine/Rendering/Shader.h>
#include <WillowVoxEngine/Rendering/Camera.h>
#include <vector>

namespace WillowVox
{
    class World
    {
    public:
        ~World();

        void Start();
        void Update();
        void Render();

        void AddMeshRenderer(MeshRenderer* mr);
        void AddGameObject(GameObject* gameObject);

        Camera* mainCamera;

    private:
        std::vector<GameObject*> gameObjects;
        std::vector<MeshRenderer*> meshRenderers;
        // vvv Test code vvv
        Chunk* chunk;
        Shader* chunkShader;
    };
}