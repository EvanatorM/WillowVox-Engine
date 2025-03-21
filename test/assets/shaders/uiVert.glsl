#version 330 core

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inTexCoords;

uniform mat4 ortho;
uniform vec2 pos;
uniform vec2 size;
uniform vec2 screenSize;

out vec2 TexCoords;

void main()
{
	vec2 posAdjust = pos + screenSize * 0.5;
	gl_Position = ortho * vec4(inPos.x * size.x + posAdjust.x, inPos.y * size.y + posAdjust.y, 0.0, 1.0);
	TexCoords = inTexCoords;
}