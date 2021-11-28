#version 430 core

uniform mat4 transform;

layout(location = 0)in vec4 iPos;
layout(location = 1)in vec4 iCol;
//layout(location = 3)in vec3 iNor;

out vec4 ioCol;
out vec4 ioPos;
out vec4 ioNor;

void main()
{
    ioNor = mat4(transpose(inversesqrt(transform)));
    ioPos = transform * iPos;
    gl_Position = transform * iPos;

    ioCol = iCol;
}