#include <wv/core.h>
#include <wv/app/EntryPoint.h>

#include <wv/rendering/Shader.h>
#include <wv/rendering/Texture.h>
#include <wv/rendering/VertexArrayObject.h>
#include <wv/rendering/Camera.h>

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
                // Pos                // Tex Coords
                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
                 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
                -0.5f,  0.5f, 0.0f,   0.0f, 1.0f,
                 0.5f,  0.5f, 0.0f,   1.0f, 1.0f
            };

            unsigned int indices[] = {
                0, 2, 1,
                1, 2, 3
            };

            vao = std::make_unique<VertexArrayObject>();
            vao->BufferVertexData(sizeof(vertices), vertices);
            vao->BufferElementData(ElementBufferAttribType::UINT32, 6, indices);
            vao->SetAttribPointer(0, 3, VertexBufferAttribType::FLOAT32, false, 5 * sizeof(float), 0);
            vao->SetAttribPointer(1, 2, VertexBufferAttribType::FLOAT32, false, 5 * sizeof(float), 3 * sizeof(float));

            camera = std::make_unique<Camera>();
        }

        void Update() override
        {

        }

        void Render() override
        {
            shader->Bind();
            texture->BindTexture(Texture::TEX00);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0, 0.0, -1.0));
            shader->SetMat4("model", model);
            shader->SetMat4("view", camera->GetViewMatrix());
            shader->SetMat4("proj", camera->GetProjectionMatrix());

            vao->Draw();
        }

        std::unique_ptr<VertexArrayObject> vao;
        std::unique_ptr<Camera> camera;
        std::shared_ptr<Shader> shader;
        std::shared_ptr<Texture> texture;
    };
}

WillowVox::App* WillowVox::CreateApp()
{
    return new WVTest::TestApp();
}