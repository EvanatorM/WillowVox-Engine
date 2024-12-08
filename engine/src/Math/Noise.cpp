#include <WillowVoxEngine/Math/Noise.h>

namespace WillowVox
{
    FastNoiseLite Noise::noise;

    void Noise::InitNoise()
    {
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    }

    float Noise::GetValue2D(NoiseSettings& settings, int x, int y)
    {
        return noise.GetNoise((float)x * settings.frequency, (float)y * settings.frequency) * settings.amplitude;
    }

    float Noise::GetValue3D(NoiseSettings& settings, int x, int y, int z)
    {
        return noise.GetNoise((float)x * settings.frequency, (float)y * settings.frequency, float(z) * settings.frequency) * settings.amplitude;
    }
}