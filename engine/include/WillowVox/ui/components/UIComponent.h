#pragma once

#include <WillowVox/WillowVoxDefines.h>
#include <WillowVox/ui/Anchor.h>
#include <glm/glm.hpp>
#include <cstdint>

namespace WillowVox
{
	class WILLOWVOX_API UIComponent
	{
	public:
		void Render(UIElement* element);
	};
}