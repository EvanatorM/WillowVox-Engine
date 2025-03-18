#include <WillowVox/core/Application.h>

#include <WillowVox/rendering/RenderingAPI.h>
#include <WillowVox/rendering/Window.h>
#include <WillowVox/resources/Blocks.h>
#include <WillowVox/WillowVox.h>
#include <iostream>

namespace WillowVox
{
	Application::Application()
	{
		Logger::EngineLog("Using WillowVox Engine %s", ENGINE_VERSION);
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		// Init rendering API and window
		_renderingAPI = RenderingAPI::GetRenderingAPI();
		_window = _renderingAPI->CreateWindow(_defaultWindowWidth, _defaultWindowHeight, _applicationName);

		// Load assets and resources
		LoadAssets();
		Blocks::RegisterBlock({ 0, 0, Block::TRANSPARENT, "Air" }); // Define air (empty block)
		RegisterBlocks();

		// Pre-game loop start logic
		Start(); // Must define world in client
		m_world->Start();

		// Game loop
		while (!_window->ShouldClose())
		{
			// Calculate deltaTime
			float currentFrame = _renderingAPI->GetTime();
			m_deltaTime = currentFrame - _lastFrame;
			_lastFrame = currentFrame;

			_window->FrameStart();

			// Client-defined update and render logic
			Update();
			m_world->Update();
			Render();
			m_world->Render();

			// Post processing
			if (_postProcessingEnabled)
			{
				ConfigurePostProcessing();
				_window->PostProcessingStart();
			}
			_window->PostProcessingEnd();

			// UI
			if (_renderUI)
			{
				_window->UIStart();
				RenderUI();
				_window->UIEnd();
			}

			_window->FrameEnd();
		}
	}
}