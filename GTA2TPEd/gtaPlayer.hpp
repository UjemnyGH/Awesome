#pragma once

#include "gtamain.hpp"

class Player
{
private:
    AWS::Camera playerCamera;
    glm::vec2 rotation;
    int w, h;
    float sensitivity = 0.15f;

public:
    void initCam( int width, int height)
    {
        w = width;
        h = height;
    }

    void SetPosition(float x, float y, float z)
    {
        playerCamera.SetPosition(x, y, z);
    }

    void SetRotation(float x, float y, float deltaTime)
    {
        float xoff = x - w;
        float yoff = h - y;

        w = x;
        h = y;

        xoff *= sensitivity;
        yoff *= sensitivity;

        rotation.x += xoff;
        rotation.y += yoff;

        if(rotation.y > 89.0f)
            rotation.y = 89.0f;
        if(rotation.y < -89.0f)
            rotation.y = -89.0f;

        playerCamera.SetRotation(rotation.x, rotation.y, 0.0f);
    }

    void SetSens(float sens) { sensitivity = sens; }

    glm::mat4 playerLookAt()
    {
        return glm::lookAt(playerCamera.GetPosition(), playerCamera.GetPosition() + playerCamera.GetFront(), playerCamera.GetUp());
    }

    glm::vec3 front() { return playerCamera.GetFront(); }
    glm::vec3 right() { return glm::normalize(glm::cross(playerCamera.GetFront(), playerCamera.GetUp())); }
};