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
AWS::Cube sq[10];
AWS::Cube background;
AWS::Square squa;
AWS::Square terrain;
AWS::Square visRepColorValues[4];
//AWS::TextRenderer text;
AWS::Time gtime;

glm::mat4x4 proj;

glm::vec3 right;
glm::vec3 pos;
float lastX = 400, lastY = 300;
bool firstMouse = false;
float yaw, pitch;
float posx, posy, posz;
std::random_device rd;

float color1[4] = {1.0f, 1.0f, 1.0f, 1.0f};

float w = 0.0f;

int main()
{
    window.createWindow(1280, 1080, "Window", NULL);
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

    if(glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS)
    {
        if(color1[0] > 0.0f)
        {
            color1[0] -= 0.01f;
        }
    }
    else if(glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
    {
        if(color1[0] < 1.0f)
        {
            color1[0] += 0.01f;
        }
    }

    if(glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
    {
        if(color1[1] > 0.0f)
        {
            color1[1] -= 0.01f;
        }
    }
    else if(glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
    {
        if(color1[1] < 1.0f)
        {
            color1[1] += 0.01f;
        }
    }

    if(glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS)
    {
        if(color1[2] > 0.0f)
        {
            color1[2] -= 0.01f;
        }
    }
    else if(glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
    {
        if(color1[2] < 1.0f)
        {
            color1[2] += 0.01f;
        }
    }

    if(glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
    {
        if(color1[3] > 0.0f)
        {
            color1[3] -= 0.01f;
        }
    }
    else if(glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
    {
        if(color1[3] < 1.0f)
        {
            color1[3] += 0.01f;
        }
    }

    right = glm::normalize(glm::cross(PC.GetFront(), PC.GetUp()));
}

void Game::initialize()
{
    glfwSetFramebufferSizeCallback(Game::getWindowPointer(), reshape);
    glfwSetCursorPosCallback(Game::getWindowPointer(), mouse);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    for(int i = 0; i < sizeof(sq) / 1128; i++)
        sq[i].create("data/texture/image3.png", AWS::CubeTexturing::texture2D);

    squa.create("data/texture/image3.png", AWS::textureVS, AWS::textureFS);

    terrain.create(AWS::colorVS, AWS::colorFS);

    for(int i = 0; i < sizeof(visRepColorValues) / 384; i++)
        visRepColorValues[i].create("data/texture/image3.png", AWS::textureVS, AWS::textureFS);
}

void Game::mainLoop()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.8f, 0.0f);

    glm::mat4x4 view = glm::lookAt(PC.GetPosition(), PC.GetPosition() + PC.GetFront(), PC.GetUp());

    processInput(Game::getWindowPointer());

    PC.SetPosition(pos.x, pos.y, pos.z);

    squa.SetScale(0.1f, 0.1f, 0.1f);
    squa.SetColor(1.0f, 1.0f, 1.0f, 0.5f);

    w += 5.0f;

    if(w > 360.0f)
    {
        w = 0.0f;
    }

    squa.draw(GL_TRIANGLES, proj, view);

    for(int i = 0; i < sizeof(sq) / 1128; i++)
    {
        sq[i].SetRotation(0.0f, w, w);
        sq[i].SetColor(color1[0], color1[1], color1[2], color1[3]);
        sq[i].SetPosition(0.0f + (float)i * 2.0f, 0.0f, 0.0f);

        sq[i].draw(GL_TRIANGLES, proj, view);
    }

    terrain.SetScale(10.0f, 10.0f, 1.0f);
    terrain.SetColor(0.0f, 0.6f, 0.0f, 1.0f);
    terrain.SetPosition(0.0f, 0.0f, 0.0f);
    terrain.SetRotation(90.0f, 0.0f, 0.0f);
    terrain.draw(GL_TRIANGLES, proj, view);

    visRepColorValues[0].SetColor(1.0f, 0.0f, 0.0f, 1.0f);
    visRepColorValues[1].SetColor(0.0f, 1.0f, 0.0f, 1.0f);
    visRepColorValues[2].SetColor(0.0f, 0.0f, 1.0f, 1.0f);
    visRepColorValues[3].SetColor(0.5f, 0.5f, 0.5f, 1.0f);

    for(int i = 0; i < sizeof(visRepColorValues) / 384; i++)
    {
        visRepColorValues[i].SetScale(0.01f, color1[i] / 5.0f, 0.1f);
        visRepColorValues[i].SetPosition(-1.0f + i * 0.02f, -0.8f, 0.0f);
        visRepColorValues[i].draw(GL_TRIANGLES);
    }
}