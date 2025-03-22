#include <WillowVox/rendering/opengl/OpenGLAPI.h>

#include <WillowVox/rendering/opengl/OpenGLWindow.h>
#include <WillowVox/rendering/opengl/OpenGLShader.h>
#include <WillowVox/rendering/opengl/OpenGLMesh.h>
#include <WillowVox/rendering/opengl/OpenGLTexture.h>
#include <WillowVox/ui/OpenGLUIManager.h>
#include <WillowVox/core/Logger.h>

namespace WillowVox
{
	OpenGLAPI::OpenGLAPI()
	{
		Logger::EngineLog("Using OpenGL Rendering Version %d.%d", OPENGL_VERSION_MAJOR, OPENGL_VERSION_MINOR);

		glfwInit();
	}

	OpenGLAPI::~OpenGLAPI()
	{
		glfwTerminate();
	}

    // Rendering objects
	Window* OpenGLAPI::CreateWindow(int width, int height, const char* title)
	{
		auto w = new OpenGLWindow(width, height, title);

		const char* vCode = "#version 330 core\n"
			"layout(location = 0) in vec3 aPos;"
			"void main()"
			"{"
			"gl_Position = vec4(aPos, 1.0);"
			"}";

		const char* fCode = "#version 330 core\n"
			"out vec4 FragColor;"
			"uniform vec4 color;"
			"void main()"
			"{"
			"FragColor = color;"
			"}";

		_debugShader = CreateShaderFromString(vCode, fCode);

		glCullFace(GL_BACK);
		glFrontFace(GL_CW);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return w;
	}

	Shader* OpenGLAPI::CreateShader(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		return new OpenGLShader(vertexShaderPath, fragmentShaderPath);
	}

	Shader* OpenGLAPI::CreateShaderFromString(const char* vertexShaderCode, const char* fragmentShaderCode)
	{
		return new OpenGLShader(vertexShaderCode, fragmentShaderCode, true);
	}

	Mesh* OpenGLAPI::CreateMesh()
	{
		return new OpenGLMesh();
	}

	Texture* OpenGLAPI::CreateTexture(const char* path)
	{
		return new OpenGLTexture(path);
	}

	UIManager* OpenGLAPI::CreateUIManager(Window* window, float virtualPixels)
	{
		return new OpenGLUIManager(window, virtualPixels);
	}

    // Vertex attributes
	void OpenGLAPI::SetVertexAttrib1f(int id, uint32_t size, std::size_t offset)
	{
		glVertexAttribPointer(id, 1, GL_FLOAT, GL_FALSE, size, (void*)offset);
		glEnableVertexAttribArray(id);
	}

	void OpenGLAPI::SetVertexAttrib2f(int id, uint32_t size, std::size_t offset)
	{
		glVertexAttribPointer(id, 2, GL_FLOAT, GL_FALSE, size, (void*)offset);
		glEnableVertexAttribArray(id);
	}

	void OpenGLAPI::SetVertexAttrib3f(int id, uint32_t size, std::size_t offset)
	{
		glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, size, (void*)offset);
		glEnableVertexAttribArray(id);
	}

	void OpenGLAPI::SetVertexAttrib1b(int id, uint32_t size, std::size_t offset)
	{
		glVertexAttribIPointer(id, 1, GL_BYTE, size, (void*)offset);
		glEnableVertexAttribArray(id);
	}

	void OpenGLAPI::SetVertexAttrib2b(int id, uint32_t size, std::size_t offset)
	{
		glVertexAttribPointer(id, 2, GL_BYTE, GL_FALSE, size, (void*)offset);
		glEnableVertexAttribArray(id);
	}

	void OpenGLAPI::SetVertexAttrib3b(int id, uint32_t size, std::size_t offset)
	{
		glVertexAttribPointer(id, 3, GL_BYTE, GL_FALSE, size, (void*)offset);
		glEnableVertexAttribArray(id);
	}

    // Getters
	double OpenGLAPI::GetTime()
	{
		return glfwGetTime();
	}

    // Setters
	void OpenGLAPI::SetCullFace(bool cullFaces)
	{
		if (cullFaces)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
	}

	void OpenGLAPI::SetDepthTest(bool enabled)
	{
		if (enabled)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}

	void OpenGLAPI::SetBlending(bool enabled)
	{
		if (enabled)
			glEnable(GL_BLEND);
		else
			glDisable(GL_BLEND);
	}

	void OpenGLAPI::SetInvertRenderMode(bool enabled)
	{
		if (enabled)
		{
			glLogicOp(GL_INVERT);
			glEnable(GL_COLOR_LOGIC_OP);
		}
		else
			glDisable(GL_COLOR_LOGIC_OP);
	}

	void OpenGLAPI::SetRenderingMode(RenderMode mode) 
	{
		switch (mode)
		{
		case RenderMode::Fill:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case RenderMode::Wireframe:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		}
	}

	void OpenGLAPI::SetLineWidth(float width) 
	{
		glLineWidth(width);
	}

	void OpenGLAPI::SetVsync(bool enabled)
	{
		glfwSwapInterval(enabled ? 1 : 0);
	}

    // Raw (mostly debug) rendering
	void OpenGLAPI::RenderTriangles(glm::vec3* vertices, int vertexCount, glm::vec4 color)
	{
		unsigned int VAO;
		unsigned int VBO;

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(glm::vec3), vertices, GL_STREAM_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		_debugShader->Bind();
		_debugShader->SetVec4("color", color.x, color.y, color.z, color.w);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}