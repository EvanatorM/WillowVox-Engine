#include <WillowVox/ui/UIElement.h>
#include <WillowVox/ui/UIManager.h>

namespace WillowVox
{
    UIElement::UIElement(glm::vec2 pos, glm::vec2 size, Anchor anchor)
        : _position(pos), _size(size), _anchor(anchor)
    {
        CalculatePosition();
    }

    UIElement::~UIElement()
    {
        for (int i = 0; i < _components.size(); i++)
        {
            delete _components[i];
        }
    }

    void UIElement::Render()
    {
        for (int i = 0; i < _components.size(); i++)
        {
            _components[i]->Render(this);
        }
    }

    void UIElement::AddComponent(UIComponent* component)
    {
        _components.push_back(component);
    }

    void UIElement::SetPosition(glm::vec2& pos)
    {
        _position = pos;
        CalculatePosition();
    }

    void UIElement::SetSize(glm::vec2& size)
    {
        _size = size;
    }

    void UIElement::SetAnchor(Anchor anchor)
    {
        _anchor = anchor;
        CalculatePosition();
    }

    const glm::vec2& UIElement::GetPosition()
    {
        return _position;
    }

    const glm::vec2& UIElement::GetSize()
    {
        return _size;
    }

    const Anchor& UIElement::GetAnchor()
    {
        return _anchor;
    }

    void UIElement::SetId(uint32_t id)
    {
        _id = id;
    }

    const glm::vec2& UIElement::GetCalculatedPosition()
    {
        return _calculatedPosition;
    }

    void UIElement::CalculatePosition()
    {
        glm::vec2 screenSize = UIManager::m_uiManager->GetVirtualScreenSize();

        switch (_anchor)
        {
            case 0: // Top left
                _calculatedPosition = _position + glm::vec2(0, screenSize.y);
                break;
            case 1: // Top center
                _calculatedPosition = _position + glm::vec2(screenSize.x * 0.5f, screenSize.y);
                break;
            case 2: // Top right
                _calculatedPosition = _position + glm::vec2(screenSize.x, screenSize.y);
                break;
            case 3: // Bottom left
                _calculatedPosition = _position + glm::vec2(0, 0);
                break;
            case 4: // Bottom center
                _calculatedPosition = _position + glm::vec2(screenSize.x * 0.5f, 0);
                break;
            case 5: // Bottom right
                _calculatedPosition = _position + glm::vec2(screenSize.x, 0);
                break;
            case 6: // Left center
                _calculatedPosition = _position + glm::vec2(0, screenSize.y * 0.5f);
                break;
            case 7: // Right center
                _calculatedPosition = _position + glm::vec2(screenSize.x, screenSize.y * 0.5f);
                break;
            default: // Center
                _calculatedPosition = _position + glm::vec2(screenSize.x * 0.5f, screenSize.y * 0.5f);

        }
    }
}