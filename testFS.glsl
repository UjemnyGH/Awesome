#version 430 core

uniform float time;
uniform float deltaTime;
uniform vec3 cameraPosition;

in vec4 ioCol;
in vec4 ioPos;

out vec4 oCol;

void main()
{
    vec3 reflectDir = reflect(cameraPosition, normalize(vec3(1.0, 0.3, 0.7)));

    vec3 result = reflectDir;

    oCol = vec4(result, 1.0);
}