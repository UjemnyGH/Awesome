#version 430 core

out vec4 oCol;

uniform vec4 iCol;

void main()
{
    oCol = iCol;
}