#include <WillowVox/ui/OpenGLUIManager.h>
#include <WillowVox/rendering/opengl/OpenGLAPI.h>
#include <WillowVox/core/Logger.h>

namespace WillowVox
{
    OpenGLUIManager::OpenGLUIManager(Window* window, float virtualPixels) : UIManager(window, virtualPixels)
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
    }

    OpenGLUIManager::~OpenGLUIManager()
    {
        delete _imageShader;
        delete _colorShader;
        glDeleteBuffers(1, &_vbo);
        glDeleteBuffers(1, &_ebo);
        glDeleteVertexArrays(1, &_vao);
    }

    void OpenGLUIManager::DrawImage(float xPos, float yPos, Anchor anchor, float xSize, float ySize, Texture* tex)
    {
        glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

        _imageShader->Bind();
        _imageShader->SetVec2("pos", (float)xPos, (float)yPos);
        _imageShader->SetVec2("size", (float)xSize, (float)ySize);
        _imageShader->SetInt("anchor", (int)anchor);

        tex->BindTexture(Texture::TEX00);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void OpenGLUIManager::DrawColor(float xPos, float yPos, Anchor anchor, float xSize, float ySize, glm::vec4 color)
    {
        glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

        _colorShader->Bind();
        _colorShader->SetVec2("pos", (float)xPos, (float)yPos);
        _colorShader->SetVec2("size", (float)xSize, (float)ySize);
        _colorShader->SetVec4("color", color);
        _colorShader->SetInt("anchor", (int)anchor);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}