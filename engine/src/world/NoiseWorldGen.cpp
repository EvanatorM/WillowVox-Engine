#include <WillowVox/world/NoiseWorldGen.h>

#include <WillowVox/core/Logger.h>
#include <WillowVox/math/Noise.h>

namespace WillowVox
{
    uint16_t NoiseWorldGen::GetBlock(int x, int y, int z)
    {
        float noise = Noise::GetValue2D(m_noiseSettings, x, z);
        int block = (int)roundf(noise);
        
        if (y <= block)
            return 1;
        else if (y < m_waterLevel)
            return 3;
        else if (y == block + 1)
            return 2;
        else
            return 0;
    }
}