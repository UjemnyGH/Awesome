#define GLEW_STATIC
#include "template.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "src/stb_image/stb_image.h"
#include <future>
#include <thread>
#include <random>

Game window;
PlayerCam PC;
AWS::Cube sq;
AWS::Cube sq2;
AWS::Time gtime;

glm::mat4x4 proj;

glm::vec3 right;
glm::vec3 pos;

float lastX = 400, lastY = 300;
float yaw, pitch;
bool firstMouse = false;

int main()
{
    window.createWindow(1280, 1080, "Window", NULL);

    sq.terminate();

    return 0;
}

void reshape(GLFWwindow* gwindow, int w, int h)
{
    glViewport(0, 0, w, h);

    proj = glm::perspectiveFov(70.0f, (float)w, (float)h, 0.001f, 100.0f);
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

    sq.create(AWS::ShadeType::shade, AWS::shadeColorVS, AWS::shadeColorFS);
    sq2.create(AWS::ShadeType::solid, AWS::colorVS, AWS::colorFS);
}

void Game::mainLoop()
{
    glClearColor(0.0f, 0.0f, 0.8f, 0.0f);

    glm::mat4x4 view = glm::lookAt(PC.GetPosition(), PC.GetPosition() + PC.GetFront(), PC.GetUp());

    processInput(Game::getWindowPointer());

    PC.SetPosition(pos.x, pos.y, pos.z);

    sq.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    sq.SetCameraPosition(PC.GetPosition().x, PC.GetPosition().y, PC.GetPosition().z);
    sq.SetLightPosition(2.0f, 2.0f, 2.0f);
    sq.SetLightColor(1.0f, 1.0f, 1.0f);
    sq.SetAmbientSpecular(0.1f, 0.5f);
    sq.SetPSR(0.0f, 0.0f, 10.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
    sq.draw(GL_TRIANGLES, proj, view);

    sq2.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    sq2.SetScale(1.0f, 1.0f, 1.0f);
    sq2.draw(GL_TRIANGLES, proj, view);
}