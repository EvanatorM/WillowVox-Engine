#include <wv/core.h>
#include <wv/app/EntryPoint.h>

using namespace WillowVox;

namespace WVTest
{
    class TestApp : public App
    {
        void Start() override
        {
            Logger::Log("Test");
            Logger::Warn("Test");
            Logger::Error("Test");
            Logger::EngineLog("Test");
            Logger::EngineWarn("Test");
            Logger::EngineError("Test");
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