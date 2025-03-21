#include <WillowVox/ui/UIManager.h>
#include <glm/gtc/matrix_transform.hpp>
#include <WillowVox/core/Logger.h>

namespace WillowVox
{
    UIManager::UIManager(Window* window, RenderingAPI* api)
        : _window(window), _api(api) 
    {
        const char* vCode = "";

        const char* fCode = "";

        _colorShader = _api->CreateShader("assets/shaders/uiVert.glsl", "assets/shaders/uiColorFrag.glsl");
        _imageShader = _api->CreateShader("assets/shaders/uiVert.glsl", "assets/shaders/uiTexFrag.glsl");

        float ratio = (float)_window->GetWindowSize().x / (float)_window->GetWindowSize().y;
        _ortho = glm::ortho(0.0f, 1000.0f * ratio, 0.0f, 1000.0f);

        _window->WindowResizeEventDispatcher.RegisterListener([this](WindowResizeEvent& e) {
            float ratio = (float)e.m_newWidth / (float)e.m_newHeight;
            _ortho = glm::ortho(0.0f, 1000.0f * ratio, 0.0f, 1000.0f);
        });
    }
}