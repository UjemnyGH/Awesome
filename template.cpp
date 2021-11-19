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
AWS::Cube background;
AWS::Square squa;
AWS::Square terrain;
//AWS::TextRenderer text;
AWS::Time gtime;

AWS::Shader sh;
AWS::VAO vao;
AWS::VBO vbo[3];
AWS::EBO ebo;
AWS::Texture tex;

float position[3 * 5] = {
    0.0f + 3.0f, 0.5f, 0.0f,
    0.5f + 3.0f, -0.5f, 0.5f,
    -0.5f + 3.0f, -0.5f, 0.5f,
    0.5f + 3.0f, -0.5f, -0.5f,
    -0.5f + 3.0f, -0.5f, -0.5f
};

unsigned int indices[] = {
    0, 2, 3,
    0, 2, 4,
    0, 1, 2,
    0, 1, 4,
    0, 1, 3,
    0, 3, 4,
    1, 2, 3,
    2, 3, 4
};

float texture[] = {
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    0.0f, 0.0f
};

float color[] = {
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f
};

glm::mat4x4 proj;

glm::vec3 right;
glm::vec3 pos;
float lastX = 400, lastY = 300;
bool firstMouse = false;
float yaw, pitch;
float posx, posy, posz;
std::random_device rd;

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

    sq.create("data/texture/image3.png", AWS::CubeTexturing::texture2D);
    squa.create("data/texture/image3.png", AWS::textureVS, AWS::textureFS);
    terrain.create();

    sh.create(AWS::textureVS, AWS::textureFS);

    vao.create();
    vao.bind();

    vbo->create();

    vbo[0].bind(position, sizeof(position), 0, 3);
    vbo[1].bind(color, sizeof(color), 1, 3);
    vbo[2].bind(texture, sizeof(texture), 2, 2);

    tex.create();
    tex.bind({"data/texture/obama.png"}, GL_REPEAT, GL_TEXTURE_2D);

    ebo.create();
    ebo.bind(indices, sizeof(indices));

    sh.bind();

    glUniform1f(glGetUniformLocation(sh.GetID(), "tex"), 0);

    sh.unbind();

    vao.unbind();
    //text.create();
}

float w = 0.0f;

void Game::mainLoop()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.8f, 0.0f);

    glm::mat4x4 view = glm::lookAt(PC.GetPosition(), PC.GetPosition() + PC.GetFront(), PC.GetUp());

    processInput(Game::getWindowPointer());

    PC.SetPosition(pos.x, pos.y, pos.z);

    /*text.Text("Hello world");
    text.SetScale(0.1f, 0.1f, 0.1f);
    text.SetPosition(0.6f, 0.0f, 0.0f);
    text.draw();*/

    squa.SetScale(0.01f, 0.01f, 0.01f);
    squa.SetColor(1.0f, 1.0f, 1.0f, 0.5f);

    w += 0.5f;

    if(w > 360.0f)
    {
        w = 0.0f;
    }

    squa.draw(GL_TRIANGLES);

    sq.SetColor(1.0f, 1.0f, 0.0f, 1.0f);
    sq.SetPosition(0.0f, 0.0f, 0.0f);
    sq.SetRotation(w, w, 0.0f);
    sq.draw(GL_TRIANGLES, proj * view);

    terrain.SetScale(10.0f, 10.0f, 1.0f);
    terrain.SetColor(0.0f, 0.6f, 0.0f, 1.0f);
    terrain.draw(GL_TRIANGLES, proj * view);

    vao.bind();
    sh.bind();
    tex.bind();

    glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "camera"), 1, GL_FALSE, glm::value_ptr(proj * glm::mat4x4(1.0) * view));

    glDrawElements(GL_TRIANGLES, sizeof(position) / 2, GL_UNSIGNED_INT, NULL);

    vao.unbind();
    sh.unbind();
}