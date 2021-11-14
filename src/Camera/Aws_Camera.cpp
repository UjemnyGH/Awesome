#include "Aws_Camera.hpp"

void AWS::Aws_Camera::SetPosition(float x, float y, float z)
{
    cameraPos.x = x;
    cameraPos.y = y;
    cameraPos.z = z;
}

void AWS::Aws_Camera::SetRotation(float x, float y, float z)
{
    camDirection.x = cos(glm::radians(x)) * cos(glm::radians(y));
    camDirection.y = sin(glm::radians(y));
    camDirection.z = sin(glm::radians(x)) * cos(glm::radians(y));
    cameraFront = glm::normalize(camDirection);
}