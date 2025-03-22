#pragma once

#include <WillowVox/WillowVoxDefines.h>
#include <WillowVox/ui/elements/UIElement.h>
#include <WillowVox/rendering/Texture.h>
#include <WillowVox/rendering/Window.h>
#include <WillowVox/rendering/Shader.h>
#include <glm/glm.hpp>

namespace WillowVox
{
	class WILLOWVOX_API UIManager
	{
	public:
		enum Anchor
		{
			TOP_LEFT,
			TOP_CENTER,
			TOP_RIGHT,
			BOTTOM_LEFT,
			BOTTOM_CENTER,
			BOTTOM_RIGHT,
			LEFT_CENTER,
			RIGHT_CENTER,
			CENTER
		};

		UIManager(Window* window, float virtualPixels);

		virtual void DrawImage(float xPos, float yPos, Anchor anchor, float xSize, float ySize, Texture* tex) = 0;
		virtual void DrawColor(float xPos, float yPos, Anchor anchor, float xSize, float ySize, glm::vec4 color) = 0;

	protected:
		Window* _window;
		
		Shader* _imageShader;
		Shader* _colorShader;

		float _virtualPixels;
		glm::mat4 _ortho;
	};
}