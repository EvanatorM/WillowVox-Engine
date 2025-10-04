#include <glm/glm.hpp>
#include <core.h>
#include <iostream>

int main() 
{
    glm::vec2 a(1, 2);
    WillowVox::Logger::Log("Hello, WillowVox Engine! %f %f", a.x, a.y);
}