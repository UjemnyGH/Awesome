#version 430 core

uniform mat4 transform;

layout(location = 0)in vec4 iPos;
layout(location = 2)in vec2 iTex;
layout(location = 3)in vec3 iNorm;

out vec3 ioPos;
out vec2 ioTex;
out vec3 ioNorm;

void main()
{
    ioPos = vec3(iPos.xyz);
    ioTex = iTex;
    ioNorm = iNorm;

    gl_Position = transform * iPos;
}