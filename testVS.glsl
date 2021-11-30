#version 430 core

uniform mat4 transform;

layout(location = 0)in vec4 iPos;
layout(location = 2)in vec2 iTex;

out vec4 ioPos;
out vec2 ioTex;

void main()
{
    ioPos = iPos;
    ioTex = iTex;
    gl_Position = transform * (iPos * vec4(2.0, 10.0, 2.0, 1.0));
}