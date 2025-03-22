#pragma once

#include <WillowVox/WillowVoxDefines.h>
#include <WillowVox/ui/UIElement.h>
#include <WillowVox/rendering/Texture.h>
#include <WillowVox/rendering/Window.h>
#include <WillowVox/rendering/Shader.h>
#include <WillowVox/ui/Anchor.h>
#include <WillowVox/ui/components/UIColor.h>
#include <WillowVox/ui/components/UITexture.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <cstdint>

namespace WillowVox
{
	class WILLOWVOX_API UIManager
	{
	public:
		UIManager(Window* window, float virtualPixels);
		~UIManager();

		void Render();
		void AddUIElement(UIElement* element);
		void RemoveUIElement(UIElement* element);

		virtual void DrawImage(UIElement& element, UITexture& tex) = 0;
		virtual void DrawColor(UIElement& element, UIColor& color) = 0;

		const glm::vec2& GetVirtualScreenSize();

		static UIManager* m_uiManager;

	protected:
		Window* _window;
		
		Shader* _imageShader;
		Shader* _colorShader;

		float _virtualPixels;
		glm::vec2 _virtualScreenSize;
		glm::mat4 _ortho;

		std::unordered_map<uint32_t, UIElement*> _uiElements;
		uint32_t _idCounter;
	};
}