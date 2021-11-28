#version 430 core

in vec2 ioTex;

out vec4 oCol;

uniform vec4 iCol;
uniform sampler2D tex;

void main()
{
    oCol = texture(tex, ioTex) * iCol;;
}