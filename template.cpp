#define GLEW_STATIC
#include "template.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "src/stb_image/stb_image.h"
#include <future>
#include <thread>
#include <random>
#include <sstream>
#define SFML_STATIC
//#include <SFML/Audio.hpp>

Game window;
PlayerCam PC;
AWS::Cube sq;
AWS::Cube sq3;
AWS::Square sq2;
AWS::Time gtime;
AWS::Object object;

glm::mat4x4 proj;

glm::vec3 right;
glm::vec3 pos;

float lastX = 400, lastY = 300;
float yaw, pitch;

//sf::SoundBuffer buffer;
//sf::Sound sound;

int main()
{
    /*if(!buffer.loadFromFile("data/audio/GTA_III.wav"))
    {
        printf("LOad error");
    }

    sound.setBuffer(buffer);

    sound.setLoop(true);
    sound.setVolume(70.0f);
    sound.play();*/

    window.createWindow(1280, 1080, "Window", NULL);

    sq.Terminate();

    return 0;
}

void reshape(GLFWwindow* gwindow, int w, int h)
{
    glViewport(0, 0, w, h);

    proj = glm::perspectiveFov(70.0f, (float)w, (float)h, 0.001f, 1000.0f);
}

void mouse(GLFWwindow* window, double xpos, double ypos)
{
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; 

        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.15f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        PC.SetRotation(yaw, pitch, 0.0f);
    }
}

void processInput(GLFWwindow *window)
{
    const float cameraSpeed = 3.0f * gtime.GetDeltaTime();

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

    sq.Create(AWS::ShadeType::solid, "data/texture/awesome.png", GL_TEXTURE_2D, AWS::textureVS, AWS::textureFS);
    sq2.Create("data/texture/awesome.png", AWS::textureVS, AWS::textureFS);
    sq3.Create(AWS::ShadeType::solid);
    object.Create();
    object.SetObjectData(AWS::LoadMesh("data/models/cubeAndBallobj.obj"));
}

float w = 0.0f;

void Game::mainLoop()
{
    processInput(Game::getWindowPointer());

    glm::mat4x4 view = glm::lookAt(PC.GetPosition(), PC.GetPosition() + PC.GetFront(), PC.GetUp());

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    PC.SetPosition(pos.x, pos.y, pos.z);

    sq.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
    sq.SetPosition(5.0f, 5.0f, 5.0f);
    sq.DrawCube(GL_TRIANGLES, proj, view);

    w += 1.0f;

    if(w > 360.0f)
    {
        w = 0.0f;
    } 

    sq2.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    sq2.SetScale(0.05f, 0.1f, 0.1f);
    sq2.SetPosition(-0.8f, -0.8f, 0.0f);
    sq2.SetRotation(w, w, w);
    sq2.DrawSquare(GL_TRIANGLES);

    sq3.SetPosition(PC.GetPosition().x, PC.GetPosition().y, PC.GetPosition().z);
    sq3.SetScale(100.0f, 100.0f, 100.0f);
    sq3.SetColor(tan(PC.GetPosition().x), sin(PC.GetPosition().y), cos(PC.GetPosition().z), 1.0f);
    sq3.DrawCube(GL_TRIANGLES, proj, view);

    object.SetPosition(0.0f, 0.0f, 0.0f);
    object.SetScale(1.0f, 1.0f, 1.0f);
    object.SetColor(w / 360.0f, w / 360.0f, w / 360.0f, 1.0f);
    object.DrawObject(GL_TRIANGLES, proj, view);
}