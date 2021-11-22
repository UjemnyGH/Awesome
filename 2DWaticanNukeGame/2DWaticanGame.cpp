#include "2DWaticanGame.hpp"

Game window;
AWS::Square debugImage;

float bombPosX = 0.0f, bombPosY = 0.0f;
float currentBombPosX = 0.0f, currentBombPosY = 0.0f;
int widthWin = 800, heightWin = 600;

void cursorPosCall(GLFWwindow* window, double posX, double posY);
void framebufferCall(GLFWwindow* window, int width, int height);

int main()
{
    window.createWindow(800, 600, "VatiNuke", nullptr);

    return 0;
}

void Game::initialize()
{
    glfwSetCursorPosCallback(Game::getWindowPointer(), cursorPosCall);
    glfwSetFramebufferSizeCallback(Game::getWindowPointer(), framebufferCall);
    
    glfwSwapInterval(1);
    debugImage.create("2DWaticanNukeGame/textures/nuke.png", AWS::textureVS, AWS::textureFS);
}

float angle = 0.0f;

void Game::mainLoop()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    angle += 0.1f;

    if(angle > 360.0f)
    {
        angle = 0.0f;
    }

    if(currentBombPosX < bombPosX)
        currentBombPosX += 0.01f;
    else if(currentBombPosX > bombPosX)
        currentBombPosX -= 0.01f;
    else
    {}

    if(currentBombPosY < bombPosY)
        currentBombPosY += 0.01f;
    else if(currentBombPosY > bombPosY)
        currentBombPosY -= 0.01f;
    else
    {}

    if(currentBombPosX < bombPosX && currentBombPosY < bombPosY)
        debugImage.SetRotation(0.0f, 0.0f, -45.0f);
    else if(currentBombPosX > bombPosX && currentBombPosY > bombPosY)
        debugImage.SetRotation(0.0f, 0.0f, 135.0f);
    else if(currentBombPosX > bombPosX && currentBombPosY < bombPosY)
        debugImage.SetRotation(0.0f, 0.0f, 45.0f);
    else if(currentBombPosX < bombPosX && currentBombPosY > bombPosY)
        debugImage.SetRotation(0.0f, 0.0f, -135.0f);
    else if(currentBombPosX < bombPosX && currentBombPosY == bombPosX)
        debugImage.SetRotation(0.0f, 0.0f, -90.0f);
    else if(currentBombPosX > bombPosX && currentBombPosY == bombPosY)
        debugImage.SetRotation(0.0f, 0.0f, 90.0f);
    else if(currentBombPosX == bombPosX && currentBombPosY < bombPosY)
        debugImage.SetRotation(0.0f, 0.0f, 0.0f);
    else if(currentBombPosX == bombPosX && currentBombPosY > bombPosY)
        debugImage.SetRotation(0.0f, 0.0f, 180.0f);
    else
        debugImage.SetRotation(0.0f, 0.0f, 0.0f);

    debugImage.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    debugImage.SetPosition(currentBombPosX, currentBombPosY, 0.0f);
    debugImage.SetScale(0.02f, 0.1f, 0.1f);

    debugImage.draw(GL_TRIANGLES);
}

void cursorPosCall(GLFWwindow* window, double posX, double posY)
{
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        bombPosX = (posX / widthWin) * 2.0f - 1.0f;
        bombPosY = (-posY / heightWin) * 2.0f + 1.0f;
    }
}

void framebufferCall(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    widthWin = width;
    heightWin = height;
}