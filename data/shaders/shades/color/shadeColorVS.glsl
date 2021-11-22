/*#version 430 core

uniform mat4 projectionTransform;
uniform mat4 viewTransform;
uniform mat4 modelTransform;

layout(location = 0)in vec3 iPos;
layout(location = 3)in vec3 iNor;

out vec3 ioCol;
out vec3 ioNor;

void main()
{
    ioCol = vec3(modelTransform * vec4(iPos, 1.0));
    ioNor = mat3(transpose(inverse(modelTransform))) * iNor;
    
    gl_Position = projectionTransform * viewTransform * ioCol;
}*/

#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 3) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 projectionTransform;
uniform mat4 viewTransform;
uniform mat4 modelTransform;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}