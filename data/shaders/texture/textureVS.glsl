#version 430 core

layout(location = 0)in vec4 iPos;
layout(location = 1)in vec4 iCol;
layout(location = 2)in vec2 iTex;

out vec2 ioTex;
out vec4 ioCol;

void main()
{
    gl_Position = iPos;
    ioCol = iCol;
    ioTex = iTex;
}