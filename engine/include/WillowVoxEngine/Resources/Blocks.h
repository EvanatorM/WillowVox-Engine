#pragma once

#include <WillowVoxEngine/Resources/Block.h>
#include <unordered_map>
#include <vector>

namespace WillowVox
{
    class Blocks
    {
    public:
        static void RegisterBlock(Block block);

        static Block& GetBlock(const char* name);
        static Block& GetBlock(uint16_t id);

        static std::vector<Block> blocks;
        static std::unordered_map<const char*, uint16_t> blockNames;
    };
}