#version 430 core

uniform mat4 camera;

layout(location = 0)in vec4 iPos;
layout(location = 2)in vec3 iTex;

out vec3 ioTex;

void main()
{
    gl_Position = camera * iPos;
    ioTex = iTex;
}