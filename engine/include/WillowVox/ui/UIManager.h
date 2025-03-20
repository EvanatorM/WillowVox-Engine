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
		UIManager(Window* window, RenderingAPI* api)
			: _window(window), _api(api) {}

		virtual void DrawImage(float xPos, float yPos, float xSize, float ySize, Texture* tex) = 0;

	protected:
		Window* _window;
		RenderingAPI* _api;
	};
}