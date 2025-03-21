#include <WillowVox/ui/UIManager.h>

namespace WillowVox
{
    UIManager::UIManager(Window* window, RenderingAPI* api)
        : _window(window), _api(api) 
    {
        const char* vCode = "";

        const char* fCode = "";
        
        _colorShader = _api->CreateShader("assets/shaders/uiVert.glsl", "assets/shaders/uiColorFrag.glsl");
        _imageShader = _api->CreateShader("assets/shaders/uiVert.glsl", "assets/shaders/uiTexFrag.glsl");
    }
}