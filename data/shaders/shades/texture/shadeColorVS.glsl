#version 430 core

uniform mat4 projectionTransform;
uniform mat4 viewTransform;
uniform mat4 modelTransform;

layout(location = 0)in vec4 iPos;
layout(location = 2)in vec2 iTex;
layout(location = 3)in vec3 iNorm;

out vec3 ioPos;
out vec2 ioTex;
out vec3 ioNorm;

void main()
{
    ioPos = vec3(iPos.xyz);
    ioTex = iTex;
    ioNorm = mat3(transpose(inverse(modelTransform))) * iNorm;

    gl_Position = projectionTransform * viewTransform * modelTransform * iPos;
}