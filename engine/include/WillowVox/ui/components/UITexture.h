#include <WillowVox/WillowVoxDefines.h>
#include <WillowVox/ui/components/UIComponent.h>
#include <WillowVox/rendering/Texture.h>
#include <glm/glm.hpp>

namespace WillowVox
{
    class WILLOWVOX_API UITexture : public UIComponent
    {
    public:
        UITexture(Texture* tex)
            : m_tex(tex) {}

        Texture* m_tex;
    }
}