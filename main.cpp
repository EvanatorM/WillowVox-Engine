#include <wv/core.h>
#include <wv/app/EntryPoint.h>

#include <wv/rendering/Shader.h>
#include <wv/rendering/Texture.h>
#include <wv/rendering/VertexArrayObject.h>
#include <wv/rendering/Camera.h>
#include <wv/input/Input.h>

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
                // Pos                 // Tex Coords
                -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,   1.0f, 1.0f,

                 0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,

                 0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,

                -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,

                -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,

                 0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,   1.0f, 1.0f
            };

            unsigned int indices[] = {
                0, 2, 1,
                1, 2, 3,

                4, 6, 5,
                5, 6, 7,

                8, 10, 9,
                9, 10, 11,

                12, 14, 13,
                13, 14, 15,

                16, 18, 17,
                17, 18, 19,

                20, 22, 21,
                21, 22, 23
            };

            vao = std::make_unique<VertexArrayObject>();
            vao->BufferVertexData(sizeof(vertices), vertices);
            vao->BufferElementData(ElementBufferAttribType::UINT32, 36, indices);
            vao->SetAttribPointer(0, 3, VertexBufferAttribType::FLOAT32, false, 5 * sizeof(float), 0);
            vao->SetAttribPointer(1, 2, VertexBufferAttribType::FLOAT32, false, 5 * sizeof(float), 3 * sizeof(float));

            camera = std::make_unique<Camera>();

            Input::SetMouseMode(MouseMode::DISABLED);
        }

        void Update() override
        {
            if (Input::GetKeyDown(Key::SPACE))
                Logger::Log("Space Pressed");
            if (Input::GetKeyUp(Key::SPACE))
                Logger::Log("Space Released");

            if (Input::GetMouseButtonDown(0))
                Logger::Log("Left Mouse Pressed");
            if (Input::GetMouseButtonUp(0))
                Logger::Log("Left Mouse Released");

            if (Input::GetKeyDown(Key::ESC))
            {
                m_mouseDisabled = !m_mouseDisabled;
                if (m_mouseDisabled)
                    Input::SetMouseMode(MouseMode::DISABLED);
                else
                    Input::SetMouseMode(MouseMode::NORMAL);
            }

            if (m_mouseDisabled)
            {
                if (Input::GetKey(Key::W))
                    camera->m_position += camera->Front() * m_speed * m_deltaTime;
                if (Input::GetKey(Key::S))
                    camera->m_position -= camera->Front() * m_speed * m_deltaTime;
                if (Input::GetKey(Key::A))
                    camera->m_position -= camera->Right() * m_speed * m_deltaTime;
                if (Input::GetKey(Key::D))
                    camera->m_position += camera->Right() * m_speed * m_deltaTime;
                if (Input::GetKey(Key::E))
                    camera->m_position += camera->Up() * m_speed * m_deltaTime;
                if (Input::GetKey(Key::Q))
                    camera->m_position -= camera->Up() * m_speed * m_deltaTime;

                m_speed += Input::GetMouseScrollDelta().y;
                if (m_speed < 0.0f)
                    m_speed = 0;
                else if (m_speed > 20.0f)
                    m_speed = 20;

                auto mouseMove = Input::GetMouseDelta();
                camera->m_direction.y += mouseMove.x * m_sensitivity;
                camera->m_direction.x -= mouseMove.y * m_sensitivity;

                if (camera->m_direction.x > 89.0f)
                    camera->m_direction.x = 89.0f;
                if (camera->m_direction.x < -89.0f)
                    camera->m_direction.x = -89.0f;
            }
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

        float m_speed = 5.0f;
        float m_sensitivity = 0.7f;
        bool m_mouseDisabled = true;
    };
}

WillowVox::App* WillowVox::CreateApp()
{
    return new WVTest::TestApp();
}