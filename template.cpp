#define GLEW_STATIC
#include "template.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "src/stb_image/stb_image.h"

Game window;
PlayerCam PC;
AWS::Cube sq;
AWS::Cube background;
AWS::Square squa;
AWS::Time gtime;
glm::mat4x4 proj;

glm::vec3 right;
glm::vec3 pos;
float lastX = 400, lastY = 300;
bool firstMouse = false;
float yaw, pitch;
float posx, posy, posz;

/**
 * @brief 
 * 
 * @return int 
 */
int main()
{
    window.createWindow(1280, 1080, "Window", NULL);
}

void reshape(GLFWwindow* gwindow, int w, int h)
{
    glViewport(0, 0, w, h);

    proj = glm::perspectiveFov(70.0f, (float)w, (float)h, 0.001f, 1000.0f);
}

void mouse(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; 

        lastX = xpos;
        lastY = ypos;
        firstMouse = false;

        float sensitivity = 0.15f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;
    }

    PC.SetRotation(yaw, pitch, 0.0f);
}

void processInput(GLFWwindow *window)
{
    const float cameraSpeed = 3.0f * gtime.GetDeltaTime(); // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        pos += PC.GetFront() * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        pos -= PC.GetFront() * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        pos += right * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        pos -= right * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        pos.y += 0.1f * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        pos.y -= 0.1f * cameraSpeed;
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        firstMouse = true;
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    right = glm::normalize(glm::cross(PC.GetFront(), PC.GetUp()));
}

void Game::initialize()
{
    glfwSetFramebufferSizeCallback(Game::getWindowPointer(), reshape);
    glfwSetCursorPosCallback(Game::getWindowPointer(), mouse);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    sq.create(AWS::cubeVS, AWS::cubeFS, "data/texture/image3.png");
    squa.create(AWS::textureVS, AWS::textureFS, "data/texture/image3.png");
    background.create(AWS::colorVS, AWS::colorFS);
}

void Game::mainLoop()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glm::mat4x4 view = glm::lookAt(PC.GetPosition(), PC.GetPosition() + PC.GetFront(), PC.GetUp());

    processInput(Game::getWindowPointer());

    PC.SetPosition(pos.x, pos.y, pos.z);

    sq.SetColor(1.0f, 1.0f, 1.0f, 0.1f);

    sq.draw(GL_TRIANGLES, proj * glm::mat4x4(1.0) * view);

    squa.SetPosition(2.0f, 0.0f, 0.0f);
    squa.SetScale(1.0f, 1.0f, 1.0f);
    squa.SetColor(1.0f, 1.0f, 1.0f);
    squa.draw(GL_TRIANGLES, proj * glm::mat4x4(1.0) * view);

    glDepthFunc(GL_LEQUAL);
    background.SetPosition(PC.GetPosition().x, PC.GetPosition().y, PC.GetPosition().z);
    background.SetScale(50.0f, 50.0f, 50.0f);
    background.SetColor(0.0f, 0.0f, 0.6f, 1.0f);

    background.draw(GL_TRIANGLES, proj * glm::mat4x4(1.0) * view);
}