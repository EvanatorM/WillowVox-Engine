#pragma once

#include <WillowVoxEngine/WillowVox.h>
#include <PlayerController.h>

class TestWorld : public WillowVox::World
{
public:
    TestWorld()
    {
        WillowVox::GameObject* player = new WillowVox::GameObject();
        mainCamera = new WillowVox::Camera();
        player->AddComponent(mainCamera);
        PlayerController* p = new PlayerController(mainCamera);
        player->AddComponent(p);
        AddGameObject(player);

        WillowVox::NoiseSettings* noise = new WillowVox::NoiseSettings(1.05f, 10.0f);
        WillowVox::TerrainGen* worldGen = new WillowVox::TerrainGen(*noise);
        chunkManager.SetWorldGen(worldGen);
    }
};