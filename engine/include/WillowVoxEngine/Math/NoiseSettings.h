#pragma once

namespace WillowVox
{
    struct NoiseSettings
    {
        NoiseSettings(float frequency, float amplitude)
            : frequency(frequency), amplitude(amplitude) {}

        float frequency;
        float amplitude;
    };
}