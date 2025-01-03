#pragma once

namespace WillowVox
{
    class Texture
    {
    public:
        enum TexSlot
        {
            TEX00,
            TEX01,
            TEX02,
            TEX03,
            TEX04,
            TEX05,
            TEX06,
            TEX07,
            TEX08,
            TEX09,
            TEX10,
            TEX11,
            TEX12,
            TEX13,
            TEX14,
            TEX15,
            TEX16
        };

        Texture(const char* path);
        ~Texture();

        void BindTexture(TexSlot slot);

        int width, height;

    private:
        unsigned int textureId;
    };
}