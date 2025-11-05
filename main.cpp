#include <wv/core.h>
#include <wv/app/EntryPoint.h>

#include <wv/rendering/Shader.h>
#include <wv/rendering/Texture.h>
#include <wv/rendering/VertexArrayObject.h>

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

            vao = std::make_unique<VertexArrayObject>();
            vao->BufferVertexData(sizeof(vertices), vertices);
            vao->BufferElementData(ElementBufferAttribType::UINT32, 6, indices);
            vao->SetAttribPointer(0, 2, VertexBufferAttribType::FLOAT32, false, 4 * sizeof(float), 0);
            vao->SetAttribPointer(1, 2, VertexBufferAttribType::FLOAT32, false, 4 * sizeof(float), 2 * sizeof(float));
        }

        void Update() override
        {

        }

        void Render() override
        {
            shader->Bind();
            texture->BindTexture(Texture::TEX00);
            vao->Draw();
        }

        std::unique_ptr<VertexArrayObject> vao;
        std::shared_ptr<Shader> shader;
        std::shared_ptr<Texture> texture;
    };
}

WillowVox::App* WillowVox::CreateApp()
{
    return new WVTest::TestApp();
}