#include <WillowVox/rendering/opengl/OpenGLWindow.h>
#include <WillowVox/core/Logger.h>
#include <WillowVox/input/opengl/OpenGLKey.h>

namespace WillowVox
{
	OpenGLWindow::OpenGLWindow(int width, int height, const char* title)
	{
		// Vars
		_width = width;
		_height = height;

		// Create window
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLAPI::OPENGL_VERSION_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLAPI::OPENGL_VERSION_MINOR);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		glfwMakeContextCurrent(_window);

		// Init GLAD
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			Logger::EngineError("Failed to initialize GLAD\n");
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Callbacks
		glfwSetWindowUserPointer(_window, static_cast<void*>(this));

		glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
			auto self = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));

			self->_width = width;
			self->_height = height;

			glViewport(0, 0, width, height);

			// Resize framebuffer texture and depth texture
			glBindTexture(GL_TEXTURE_2D, self->_framebufferTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, self->_width, self->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glBindTexture(GL_TEXTURE_2D, self->_depthTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, self->_width, self->_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

			WindowResizeEvent e(width, height);
			self->WindowResizeEventDispatcher.Dispatch(e);
		});

		glfwSetScrollCallback(_window, [](GLFWwindow* window, double xoffset, double yoffset) {
			auto self = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));

			MouseScrollEvent e(xoffset, yoffset);
			self->MouseScrollEventDispatcher.Dispatch(e);
		});

		glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xpos, double ypos) {
			auto self = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));

			MouseMoveEvent e(xpos - self->_lastMouseX, ypos - self->_lastMouseY);
			self->_lastMouseX = xpos;
			self->_lastMouseY = ypos;
			self->MouseMoveEventDispatcher.Dispatch(e);
		});

		glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) {
            auto self = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
            if (action == GLFW_PRESS)
            {
                MouseClickEvent e(button);
                self->MouseClickEventDispatcher.Dispatch(e);
            }
            else
            {
                MouseReleaseEvent e(button);
                self->MouseReleaseEventDispatcher.Dispatch(e);
            }
        });

		glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			auto self = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
            
            if (action == GLFW_PRESS)
            {
                KeyPressEvent e((Key)openGLtoKey[key]);
                self->KeyPressEventDispatcher.Dispatch(e);
            }
            else if (action == GLFW_RELEASE)
            {
                KeyReleaseEvent e((Key)openGLtoKey[key]);
                self->KeyReleaseEventDispatcher.Dispatch(e);
            }
		});

		// Post-processing
		glGenFramebuffers(1, &_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

		glGenTextures(1, &_framebufferTexture);
		glBindTexture(GL_TEXTURE_2D, _framebufferTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _framebufferTexture, 0);

		glGenTextures(1, &_depthTexture);
		glBindTexture(GL_TEXTURE_2D, _depthTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthTexture, 0);

		auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
			Logger::EngineError("Framebuffer error: %s", fboStatus);

		float rectangleVertices[] =
		{
			// Coords     // TexCoords
			1.0f, -1.0f,  1.0f, 0.0f,
		   -1.0f, -1.0f,  0.0f, 0.0f,
		   -1.0f,  1.0f,  0.0f, 1.0f,

			1.0f,  1.0f,  1.0f, 1.0f,
			1.0f, -1.0f,  1.0f, 0.0f,
		   -1.0f,  1.0f,  0.0f, 1.0f
		};

		glGenVertexArrays(1, &_postProcessVAO);
		glGenBuffers(1, &_postProcessVBO);
		glBindVertexArray(_postProcessVAO);
		glBindBuffer(GL_ARRAY_BUFFER, _postProcessVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

		const char* vCode = "#version 330 core\n"
			"layout(location = 0) in vec2 inPos;"
			"layout(location = 1) in vec2 inTexCoords;"
			"out vec2 TexCoords;"
			"void main()"
			"{"
			"gl_Position = vec4(inPos.x, inPos.y, 0.0, 1.0);"
			"TexCoords = inTexCoords;"
			"}";

		const char* fCode = "#version 330 core\n"
			"out vec4 FragColor;"
			"in vec2 TexCoords;"
			"uniform sampler2D screenTexture;"
			"uniform sampler2D depthTexture;"
			"void main()"
			"{"
			"vec4 color = texture(screenTexture, TexCoords);"
			"FragColor = color;"
			"}";

		_postProcessShader = RenderingAPI::m_renderingAPI->CreateShaderFromString(vCode, fCode);
		_postProcessShader->Bind();
		_postProcessShader->SetInt("screenTexture", 0);
		_postProcessShader->SetInt("depthTexture", 1);
	}
	OpenGLWindow::~OpenGLWindow()
	{
		glfwDestroyWindow(_window);

		WindowCloseEventDispatcher.Dispatch(*(new WindowCloseEvent()));
	}

	void OpenGLWindow::FrameStart()
	{
		glEnable(GL_DEPTH_TEST);

		// If there are no post processing shaders, don't bind the framebuffer
		if (_postProcessingShaders.size() > 0)
			glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
		else
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLWindow::PostProcessingStart()
	{
		// If there are no post processing shaders, skip
		if (_postProcessingShaders.size() == 0)
			return;

		glBindVertexArray(_postProcessVAO);
		glDisable(GL_DEPTH_TEST);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _framebufferTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _depthTexture);

		for (int i = 0; i < _postProcessingShaders.size(); i++)
		{
			if (!_postProcessingShaders[i]->enabled)
				continue;

			auto s = _postProcessingShaders[i]->shader;
			s->Bind();
			s->SetInt("screenTexture", 0);
			s->SetInt("depthTexture", 1);

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}

	void OpenGLWindow::PostProcessingEnd()
	{
		// If there are no post processing shaders, skip
		if (_postProcessingShaders.size() == 0)
			return;

		_postProcessShader->Bind();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindVertexArray(_postProcessVAO);
		glBindBuffer(GL_ARRAY_BUFFER, _postProcessVBO);
		glDisable(GL_DEPTH_TEST);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _framebufferTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _depthTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void OpenGLWindow::UIStart()
	{
        RenderingAPI::m_renderingAPI->SetCullFace(false);
        RenderingAPI::m_renderingAPI->SetDepthTest(false);
		RenderingAPI::m_renderingAPI->SetBlending(true);
	}

	void OpenGLWindow::UIEnd()
	{
		RenderingAPI::m_renderingAPI->SetCullFace(true);
        RenderingAPI::m_renderingAPI->SetDepthTest(true);
		RenderingAPI::m_renderingAPI->SetBlending(false);
	}

	void OpenGLWindow::FrameEnd()
	{
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	void OpenGLWindow::CloseWindow()
	{
		glfwSetWindowShouldClose(_window, true);
	}

	void OpenGLWindow::SetBackgroundColor(glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLWindow::SetBackgroundColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void OpenGLWindow::SetMouseDisabled(bool state)
	{
		if (state)
		{
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			if (glfwRawMouseMotionSupported())
				glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}
		else
		{
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			if (glfwRawMouseMotionSupported())
				glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
		}
	}

	void OpenGLWindow::ToggleMouseDisabled()
	{
		switch (glfwGetInputMode(_window, GLFW_CURSOR))
		{
		case GLFW_CURSOR_DISABLED:
			SetMouseDisabled(false);
			break;
		case GLFW_CURSOR_NORMAL:
			SetMouseDisabled(true);
			break;
		}
	}

	bool OpenGLWindow::ShouldClose()
	{
		return glfwWindowShouldClose(_window);
	}

	glm::ivec2 OpenGLWindow::GetWindowSize()
	{
		int x, y;
		glfwGetWindowSize(_window, &x, &y);
		return { x, y };
	}

	bool OpenGLWindow::KeyDown(Key key)
	{
		return glfwGetKey(_window, keyToOpenGL[key]) == GLFW_PRESS;
	}

	bool OpenGLWindow::MouseButtonDown(int button)
	{
		return glfwGetMouseButton(_window, button) == GLFW_PRESS;
	}

	glm::vec2 OpenGLWindow::GetMousePos()
	{
		double x, y;
		glfwGetCursorPos(_window, &x, &y);
		return glm::vec2((float)x, (float)y);
	}

	bool OpenGLWindow::MouseDisabled()
	{
		return glfwGetInputMode(_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
	}
}