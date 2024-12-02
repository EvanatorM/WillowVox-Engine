#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in int  aTop;

out vec2 TexCoord;

uniform float texMultiplier;

uniform vec3 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

const int aFrames = 32;
const float animationTime = 5;
const int texNum = 16;
void main()
{
    vec3 pos = aPos;
    if (aTop == 1)
    {
        pos.y -= .1;
        pos.y += (sin(pos.x * 3.1415926535 / 2 + time) + sin(pos.z * 3.1415926535 / 2 + time * 1.5)) * .05;
    }
    gl_Position = projection * view * vec4(pos + model, 1.0);

    vec2 currentTex = aTexCoords;
    currentTex.x += mod(floor(mod(time / animationTime, 1) * aFrames), texNum);
    currentTex.y += floor(floor(mod(time / animationTime, 1) * aFrames) / texNum);
    TexCoord = currentTex * texMultiplier;
}