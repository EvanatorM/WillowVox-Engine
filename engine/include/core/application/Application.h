#pragma once

#include <thread>

namespace WVEngine
{
    class Application
    {
    public:
        Application();
        ~Application();

        virtual void Run() = 0;

    private:
        std::thread m_renderThread;
        std::thread m_physicsThread;
    };

    Application* CreateApplication();
}