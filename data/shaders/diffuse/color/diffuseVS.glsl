#version 430 core

layout(location = 0)in vec3 iPos;
layout(location = 3)in vec3 iNorm;

out vec3 ioPos;
out vec3 ioNorm;

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main()
{
    gl_Position = projectionTransform * viewTransform * modelTransform * vec4(iPos, 1.0);

    ioPos = vec3(modelTransform * vec4(iPos, 1.0));
    ioNorm = iNorm;
}