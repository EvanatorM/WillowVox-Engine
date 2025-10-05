#include <wv/core.h>
#include <wv/app/EntryPoint.h>

using namespace WillowVox;

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