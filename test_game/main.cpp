#include <core/application/Application.h>
#include <core/EntryPoint.h>
#include <iostream>

using namespace WVEngine;

class TestApp : public Application
{
    void Run()
    {
        std::cout << "Hello World\n";
    }
};

Application* WVEngine::CreateApplication()
{
    return new TestApp();
}