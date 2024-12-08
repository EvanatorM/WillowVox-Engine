#pragma once

#include <WillowVoxEngine/World/WorldGen.h>
#include <WillowVoxEngine/Math/NoiseSettings.h>

namespace WillowVox
{
    class TerrainGen : public WorldGen
    {
    public:
        TerrainGen(NoiseSettings& noiseSettings)
            : noiseSettings(noiseSettings) {}

        uint16_t GetBlock(int x, int y, int z) override;

        NoiseSettings& noiseSettings;
    };
}