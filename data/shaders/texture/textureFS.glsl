#version 430 core

in vec4 ioCol;
in vec2 ioTex;

out vec4 oCol;

uniform sampler2D tex;

void main()
{
    oCol = texture(tex, ioTex);
}