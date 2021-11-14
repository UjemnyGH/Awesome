#version 430 core

in vec4 ioCol;
in vec3 ioTex;

out vec4 oCol;

uniform samplerCube tex;

void main()
{
    oCol = texture(tex, ioTex) * ioCol;
}