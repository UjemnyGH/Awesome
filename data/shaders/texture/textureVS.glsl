#version 430 core

uniform mat4 transform;

layout(location = 0)in vec4 iPos;
layout(location = 2)in vec2 iTex;

out vec2 ioTex;

void main()
{
    gl_Position = transform * iPos;
    ioTex = iTex;
}