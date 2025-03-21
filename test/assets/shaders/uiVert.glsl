#version 330 core

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inTexCoords;

uniform mat4 ortho;
uniform vec2 pos;
uniform vec2 size;
uniform vec2 screenSize;
uniform int anchor;

out vec2 TexCoords;

void main()
{
	vec2 posAdjust;
	switch (anchor)
	{
		case 0: // Top left
			posAdjust = pos + vec2(0, screenSize.y);
			break;
		case 1: // Top center
			posAdjust = pos + vec2(screenSize.x * 0.5, screenSize.y);
			break;
		case 2: // Top right
			posAdjust = pos + vec2(screenSize.x, screenSize.y);
			break;
		case 3: // Bottom left
			posAdjust = pos + vec2(0, 0);
			break;
		case 4: // Bottom center
			posAdjust = pos + vec2(screenSize.x * 0.5, 0);
			break;
		case 5: // Bottom right
			posAdjust = pos + vec2(screenSize.x, 0);
			break;
		case 6: // Left center
			posAdjust = pos + vec2(0, screenSize.y * 0.5);
			break;
		case 7: // Right center
			posAdjust = pos + vec2(screenSize.x, screenSize.y * 0.5);
			break;
		default: // Center
			posAdjust = pos + screenSize * 0.5;

	}
	gl_Position = ortho * vec4(inPos.x * size.x + posAdjust.x, inPos.y * size.y + posAdjust.y, 0.0, 1.0);
	TexCoords = inTexCoords;
}