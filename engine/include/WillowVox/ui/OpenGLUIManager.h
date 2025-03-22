#pragma once

#include <WillowVox/ui/UIManager.h>
#include <WillowVox/rendering/Shader.h>

namespace WillowVox
{
    class WILLOWVOX_API OpenGLUIManager : public UIManager
    {
    public:
        OpenGLUIManager(Window* window, float virtualPixels);
        ~OpenGLUIManager();

        void DrawImage(UIElement& element, UITexture& tex) override;
		void DrawColor(UIElement& element, UIColor& color) override;

    private:
        unsigned int _vao;
		unsigned int _vbo;
		unsigned int _ebo;
    };
}