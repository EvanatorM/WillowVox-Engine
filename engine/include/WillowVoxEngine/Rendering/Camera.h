#pragma once

#include <WillowVoxEngine/World/Component.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace WillowVox
{
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN,
        FORWARD_NO_Y
    };

    class Camera : public Component
    {
    public:
        // Camera attributes
        glm::vec3 position;
        // pitch = x, yaw = y, roll = z
        glm::vec3 direction;
        float fov = 70.0f;

        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 direction = glm::vec3(0, -90.0f, 0));

        // constructor with scalar values
        Camera(float posX, float posY, float posZ, float roll, float pitch, float yaw);

        glm::vec3 Front();
        glm::vec3 Right();
        glm::vec3 Up();

        // returns the view matrix calculated using Euler Angles and the LookAt Matrix
        glm::mat4 GetViewMatrix();

        glm::mat4 GetProjectionMatrix();
    };
}