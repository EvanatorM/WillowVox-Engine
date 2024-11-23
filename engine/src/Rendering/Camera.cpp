#include <WillowVoxEngine/Rendering/Camera.h>

#include <glad/glad.h>

namespace WillowVox
{
    Camera::Camera(glm::vec3 position, glm::vec3 direction) : position(position), direction(direction) {}

    // constructor with scalar values
    Camera::Camera(float posX, float posY, float posZ, float roll, float pitch, float yaw)
    {
        position = glm::vec3(posX, posY, posZ);
        direction = glm::vec3(roll, pitch, yaw);
    }
    
    glm::vec3 Camera::Front()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(direction.z)) * cos(glm::radians(direction.y));
        front.y = sin(glm::radians(direction.y));
        front.z = sin(glm::radians(direction.z)) * cos(glm::radians(direction.y));
        return glm::normalize(front);
    }

    glm::vec3 Camera::Right()
    {
        return glm::normalize(glm::cross(Front(), glm::vec3(0, 1, 0)));
    }

    glm::vec3 Camera::Up()
    {
        return glm::normalize(glm::cross(Right(), Front()));
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 Camera::GetViewMatrix()
    {
        return glm::lookAt(position, position + Front(), Up());
    }

    glm::mat4 Camera::GetProjectionMatrix()
    {
        return glm::perspective(glm::radians(fov), 600.0f / 400.0f, 0.1f, 1000.0f);
    }
}