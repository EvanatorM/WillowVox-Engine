#include <wv/core.h>
#include <wv/app/EntryPoint.h>

#include <wv/rendering/Shader.h>

using namespace WillowVox;

namespace WVTest
{
    class TestApp : public App
    {
        void Start() override
        {
            AssetManager& am = AssetManager::GetInstance();
            std::shared_ptr<Shader> shader = am.GetAsset<Shader>("test_shader");
            shader->Bind();
        }

        void Update() override
        {

        }
    };
}

WillowVox::App* WillowVox::CreateApp()
{
    return new WVTest::TestApp();
}