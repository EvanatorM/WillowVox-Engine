#pragma once

#include <core/application/Application.h>

extern WVEngine::Application* WVEngine::CreateApplication();

int main(int argc, char** argv)
{
    auto app = WVEngine::CreateApplication();
    app->Run();
    delete app;
}