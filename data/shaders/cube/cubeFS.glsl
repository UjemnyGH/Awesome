#version 430 core

in vec3 ioTex;

out vec4 oCol;

uniform vec4 iCol;
uniform samplerCube tex;

void main()
{
    oCol = texture(tex, ioTex) * iCol;
}