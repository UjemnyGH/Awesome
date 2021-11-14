#version 430 core

uniform mat4 camera;

layout(location = 0)in vec4 iPos;
layout(location = 1)in vec4 iCol;

out vec4 ioCol;

void main()
{
    gl_Position = camera * iPos;
    ioCol = iCol;
}