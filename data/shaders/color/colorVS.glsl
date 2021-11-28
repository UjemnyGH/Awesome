#version 430 core

uniform mat4 transform;

layout(location = 0)in vec4 iPos;

void main()
{
    gl_Position = transform * iPos;
}