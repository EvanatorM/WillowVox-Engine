#include <wv/core.h>
#include <wv/app/EntryPoint.h>

using namespace WillowVox;

namespace WVTest
{
    class TestApp : public App
    {
        void Start() override
        {

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