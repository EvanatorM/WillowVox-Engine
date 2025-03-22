#include <WillowVox/WillowVoxDefines.h>
#include <WillowVox/ui/components/UIComponent.h>
#include <glm/glm.hpp>

namespace WillowVox
{
    class WILLOWVOX_API UIColor : public UIComponent
    {
    public:
        UIColor(glm::vec4 color)
            : m_color(color) {}

        glm::vec4 m_color;
    }
}