#include "game.hpp"

#define TREES 16

Camera playerCam;
Window window;
AWS::Time gTime;

AWS::BatchRenderer treesBatch;
AWS::Square ground;
AWS::Square player;
AWS::Square trees[TREES];
std::random_device rd1;

double scr = 1.0;

float playerX = 0.0f, playerY = 0.0f;
float plX, plY;
float speed = 0.5f;

float delta = 0.0f;

const float grassWidth = 128.0f, grassHeight = 128.0f;
float treePosX[TREES], treePosY[TREES];
bool treeReplace = true;

glm::mat4x4 projection;

void reshape(GLFWwindow* window, int w, int h);
void processInput(GLFWwindow* window);

int main()
{
    window.createWindow(1280, 1080, "2dPlanetaryGame", NULL);

    ground.terminate();
    player.terminate();
    treesBatch.terminate();
    glfwTerminate();

    return 0;
}

void Window::initialize()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetFramebufferSizeCallback(Window::getWindowPointer(), reshape);

    ground.create("data/texture/image3.png", AWS::textureVS, AWS::textureFS);
    player.create("data/texture/image3.png", AWS::textureVS, AWS::textureFS);
    treesBatch.create();
}

void Window::mainLoop()
{
    glm::mat4x4 view = glm::lookAt(playerCam.GetPosition(), playerCam.GetPosition() + playerCam.GetFront(), playerCam.GetUp());

    delta = gTime.GetDeltaTime();

    processInput(Window::getWindowPointer());

    ground.SetScale(grassWidth, grassHeight, 0.0f);
    ground.SetColor(0.0f, 0.3f, 0.0f, 1.0f);
    ground.draw(GL_TRIANGLES, projection * glm::mat4x4(1.0) * view);

    scr += 0.001f;

    if(scr > 3.6f)
    {
        scr = 0.0f;
    }

    player.SetScale(0.5f, 0.5f, 0.5f);
    player.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    player.draw(GL_TRIANGLES);

    if(treeReplace)
    {
        for(int i = 0; i < TREES; i++)
        {
            treePosX[i] = playerCam.GetPosition().x + sin((rd1() % 100) / 100.0f) - 0.5f;
            treePosY[i] = playerCam.GetPosition().y + cos((rd1() % 100) / 100.0f) * 2.0f - 1.5f;
        }

        treeReplace = false;
    }

    for(int i = 0; i < TREES; i++)
    {
        trees[i].SetPosition(treePosX[i], treePosY[i], 0.0f);
        trees[i].SetScale(0.05f, 0.05f, 0.0f);
        trees[i].SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    }

    treesBatch.drawBROSquare(AWS::ShaderType::textureShader, {
        trees[0],
        trees[1],
        trees[2],
        trees[3],
        trees[4],
        trees[5],
        trees[6],
        trees[7],
        trees[8],
        trees[9],
        trees[10],
        trees[11],
        trees[12],
        trees[13],
        trees[14],
        trees[15]
    }, projection * glm::mat4x4(1.0) * view);
} 

void reshape(GLFWwindow* window, int w, int h)
{
    glViewport(0, 0, w, h);

    projection = glm::perspectiveFov(70.0f, (float)w, (float)h, 0.001f, 10.0f);
}

void processInput(GLFWwindow* window)
{
    plX = playerX;
    plY = playerY;

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        playerY += speed * delta;
    }
    else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        playerY -= speed * delta;
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        playerX -= speed * delta;
    }
    else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        playerX += speed * delta;
    }

    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        treeReplace = true;
    }

    playerCam.SetPosition(playerX, playerY, 1.0f);
}