#version 430 core

uniform mat4 transform;

layout(location = 0)in vec4 iPos;
layout(location = 1)in vec4 iCol;

out vec4 ioCol;
out vec4 ioPos;
//out vec4 ioNor;

void main()
{
    gl_Position = transform * iPos;

    ioPos = transform * iPos;

    ioCol = iCol;
}