#include <wv/core.h>
#include <wv/app/EntryPoint.h>

using namespace WillowVox;

namespace TestProject
{
    class TestApp : public App
    {
        void Start() override
        {
            Logger::Log("Start");
        }

        void Update() override
        {
            Logger::Log("Update");
        }
    };
}

WillowVox::App* WillowVox::CreateApp()
{
    return new TestProject::TestApp();
}