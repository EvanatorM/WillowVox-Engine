#pragma once

#include <WillowVox/ui/UIManager.h>
#include <WillowVox/rendering/Shader.h>

namespace WillowVox
{
    class WILLOWVOX_API OpenGLUIManager : public UIManager
    {
    public:
        OpenGLUIManager(Window* window, RenderingAPI* api);
        ~OpenGLUIManager();

        void DrawImage(float xPos, float yPos, float xSize, float ySize, Texture* tex) override;
		void DrawColor(float xPos, float yPos, float xSize, float ySize, glm::vec4 color) override;

    private:
        unsigned int _vao;
		unsigned int _vbo;
		unsigned int _ebo;
    };
}