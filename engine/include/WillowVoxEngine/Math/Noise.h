#pragma once

#include <FastNoiseLite.h>
#include <WillowVoxEngine/Math/NoiseSettings.h>

namespace WillowVox
{
    class Noise
    {
    public:
        static FastNoiseLite noise;

        static void InitNoise();

        static float GetValue2D(NoiseSettings& settings, int x, int y);

        static float GetValue3D(NoiseSettings& settings, int x, int y, int z);
    };
}