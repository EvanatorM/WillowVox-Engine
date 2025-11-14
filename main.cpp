#include <wv/core.h>
#include <wv/app/EntryPoint.h>

using namespace WillowVox;

const char* WillowVox::appWindowName = "MyApp";
int WillowVox::appDefaultWindowX = 1280;
int WillowVox::appDefaultWindowY = 720;

namespace MyProject
{
    class MyApp : public App
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
    return new MyProject::MyApp();
}