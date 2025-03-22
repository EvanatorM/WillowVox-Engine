#include <WillowVox/ui/UIManager.h>
#include <glm/gtc/matrix_transform.hpp>
#include <WillowVox/core/Logger.h>
#include <WillowVox/rendering/RenderingAPI.h>

namespace WillowVox
{
    UIManager::UIManager(Window* window, float virtualPixels)
        : _window(window), _virtualPixels(virtualPixels)
    {
        const char* vCode = "";

        const char* fCode = "";

        RenderingAPI& api = *RenderingAPI::m_renderingAPI;
        _colorShader = api.CreateShader("assets/shaders/uiVert.glsl", "assets/shaders/uiColorFrag.glsl");
        _imageShader = api.CreateShader("assets/shaders/uiVert.glsl", "assets/shaders/uiTexFrag.glsl");

        float ratio = (float)_window->GetWindowSize().x / (float)_window->GetWindowSize().y;
        _ortho = glm::ortho(0.0f, _virtualPixels * ratio, 0.0f, _virtualPixels);
        _imageShader->Bind();
        _imageShader->SetMat4("ortho", _ortho);
        _imageShader->SetVec2("screenSize", { _virtualPixels * ratio, _virtualPixels});
        _colorShader->Bind();
        _colorShader->SetMat4("ortho", _ortho);
        _colorShader->SetVec2("screenSize", { _virtualPixels * ratio, _virtualPixels});

        _window->WindowResizeEventDispatcher.RegisterListener([this](WindowResizeEvent& e) {
            float ratio = (float)e.m_newWidth / (float)e.m_newHeight;
            _ortho = glm::ortho(0.0f, _virtualPixels * ratio, 0.0f, _virtualPixels);
            _imageShader->Bind();
            _imageShader->SetMat4("ortho", _ortho);
            _imageShader->SetVec2("screenSize", { _virtualPixels * ratio, _virtualPixels});
            _colorShader->Bind();
            _colorShader->SetMat4("ortho", _ortho);
            _colorShader->SetVec2("screenSize", { _virtualPixels * ratio, _virtualPixels});
        });
    }
}