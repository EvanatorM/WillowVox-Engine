#pragma once

#include <WillowVox/WillowVoxDefines.h>
#include <WillowVox/ui/elements/UIElement.h>
#include <WillowVox/rendering/Texture.h>
#include <WillowVox/rendering/Window.h>
#include <WillowVox/rendering/RenderingAPI.h>
#include <unordered_map>
#include <cstdint>

namespace WillowVox
{
	class WILLOWVOX_API UIManager
	{
	public:
		UIManager(Window* window, RenderingAPI* api);

		virtual void DrawImage(float xPos, float yPos, float xSize, float ySize, Texture* tex) = 0;
		virtual void DrawColor(float xPos, float yPos, float xSize, float ySize, glm::vec4 color) = 0;

	protected:
		Window* _window;
		RenderingAPI* _api;
		
		Shader* _imageShader;
		Shader* _colorShader;
	};
}