#include <WillowVoxEngine/World/TerrainGen.h>

#include <WillowVoxEngine/Core/Logger.h>
#include <WillowVoxEngine/Math/Noise.h>

namespace WillowVox
{
    uint16_t TerrainGen::GetBlock(int x, int y, int z)
    {
        float noise = Noise::GetValue2D(noiseSettings, x, z);
        int block = (int)roundf(noise);

        if (y <= block)
            return 1;
        else if (y < 0)
            return 3;
        else if (y == block + 1)
            return 2;
        else
            return 0;
    }
}