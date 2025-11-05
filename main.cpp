#include <wv/core.h>
#include <wv/app/EntryPoint.h>

#include <wv/rendering/Shader.h>
#include <wv/rendering/Texture.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace WillowVox;

namespace WVTest
{
    class TestApp : public App
    {
        void Start() override
        {
            AssetManager& am = AssetManager::GetInstance();
            shader = am.GetAsset<Shader>("test_shader");
            shader->Bind();

            texture = am.GetAsset<Texture>("test_texture");
            texture->BindTexture(Texture::TEX00);

            float vertices[] = {
                // Pos          // Tex Coords
                -0.5f, -0.5f,   0.0f, 0.0f,
                 0.5f, -0.5f,   1.0f, 0.0f,
                -0.5f,  0.5f,   0.0f, 1.0f,
                 0.5f,  0.5f,   1.0f, 1.0f
            };

            unsigned int indices[] = {
                0, 2, 1,
                1, 2, 3
            };

            // Create and bind VAO
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            // Create and bind VBO
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            // Buffer vertex data into VBO
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // Set attribute pointers
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // Create and bind EBO
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            // Buffer index data into EBO
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        void Update() override
        {

        }

        void Render() override
        {
            shader->Bind();
            texture->BindTexture(Texture::TEX00);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        unsigned int EBO;
        unsigned int VBO;
        unsigned int VAO;
        std::shared_ptr<Shader> shader;
        std::shared_ptr<Texture> texture;
    };
}

WillowVox::App* WillowVox::CreateApp()
{
    return new WVTest::TestApp();
}