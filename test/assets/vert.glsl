#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 inTexCoords;

out vec2 TexCoord;

uniform vec3 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * vec4(aPos + model, 1.0);
    TexCoord = inTexCoords;
}