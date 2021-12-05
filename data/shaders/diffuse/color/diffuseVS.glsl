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
    ioPos = vec3(modelTransform * vec3(iPos.xyz));
    ioNorm = mat3(transpose(modelTransform)) * iNorm;

    gl_Position = projectionTransform * viewTransform * vec4(ioPos.xyz, 1.0);
}