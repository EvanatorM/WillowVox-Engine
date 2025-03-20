#include <WillowVox/ui/OpenGLUIManager.h>
#include <WillowVox/rendering/opengl/OpenGLAPI.h>
#include <WillowVox/core/Logger.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace WillowVox
{
    OpenGLUIManager::OpenGLUIManager(Window* window, RenderingAPI* api) : UIManager(window, api)
    {
        glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glGenBuffers(1, &_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

        float vertices[] = {
            0, 0,  0, 0,
            1, 0,  1, 0,
            0, 1,  0, 1,
            1, 1,  1, 1
        };

        unsigned int indices[] = {
            0, 1, 2,
            1, 3, 2
        };

		glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

        const char* vCode = "";

        const char* fCode = "";

        _uiShader = _api->CreateShader("assets/shaders/uiVert.glsl", "assets/shaders/uiFrag.glsl");
    }

    OpenGLUIManager::~OpenGLUIManager()
    {
        delete _uiShader;
        glDeleteBuffers(1, &_vbo);
        glDeleteBuffers(1, &_ebo);
        glDeleteVertexArrays(1, &_vao);
    }

    void OpenGLUIManager::DrawImage(float xPos, float yPos, float xSize, float ySize, Texture* tex)
    {
        _api->SetCullFace(false);
        _api->SetDepthTest(false);

        glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

        _uiShader->Bind();
        glm::mat4 ortho = glm::ortho(0.0f, (float)_window->GetWindowSize().x, 0.0f, (float)_window->GetWindowSize().y);
        _uiShader->SetMat4("projection", ortho);
        _uiShader->SetVec2("pos", (float)xPos, (float)yPos);
        _uiShader->SetVec2("size", (float)xSize, (float)ySize);

        tex->BindTexture(Texture::TEX00);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        _api->SetCullFace(true);
        _api->SetDepthTest(true);
    }
}