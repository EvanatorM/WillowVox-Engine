#pragma once

#include <WillowVox/WillowVoxDefines.h>
#include <WillowVox/ui/Anchor.h>
#include <WillowVox/ui/components/UIComponent.h>
#include <glm/glm.hpp>
#include <cstdint>
#include <vector>

namespace WillowVox
{
	class WILLOWVOX_API UIElement
	{
	public:
		UIElement(glm::vec2 pos, glm::vec2 size, Anchor anchor);
		~UIElement();

		void Render();
		void AddComponent(UIComponent* component);

		void SetPosition(glm::vec2& pos);
		void SetSize(glm::vec2& size);
		void SetAnchor(Anchor anchor);

		const glm::vec2& GetPosition();
		const glm::vec2& GetSize();
		const Anchor& GetAnchor();

		void SetId(uint32_t id);

		const glm::vec2& GetCalculatedPosition();

	private:
		void CalculatePosition();

		glm::vec2 _position;
		Anchor _anchor;
		glm::vec2 _calculatedPosition;
		glm::vec2 _size;

		uint32_t _id;

		std::vector<UIComponent*> _components;
	};
}