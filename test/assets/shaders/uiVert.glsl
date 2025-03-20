#version 330 core

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inTexCoords;

uniform mat4 projection;
uniform vec2 pos;
uniform vec2 size;

out vec2 TexCoords;

void main()
{
	gl_Position = projection * vec4(inPos.x * size.x + pos.x, inPos.y * size.y + pos.y, 0.0, 1.0);
	TexCoords = inTexCoords;
}