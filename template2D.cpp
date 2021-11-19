#include "template2D.hpp"

Game window;
AWS::Square ground;
AWS::Square player;
AWS::Square obsticle[3];
AWS::Square gameOver;
AWS::Time gTime;
int id[3] = {0, 0, 0};
float posx[10] = {1.0f};
std::random_device randomPos;

float acceleration = 1.0f;
const float gravity = -1.0f;
float playerYPos = -0.5f;
const float c_playerYPos = -0.7f;
bool playerCanJump = true;
bool gameOv = false;
int score = 0;

int main()
{
    window.createWindow(800, 600, "Game 2D", NULL);

    return 0;
}

void reshape(GLFWwindow* window, int w, int h)
{
    glViewport(0, 0, w, h);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, AWS::SPACE) == GLFW_PRESS && playerCanJump)
    {
        acceleration = -1.0f;
        playerYPos += 0.01f;
        playerCanJump = false;
    }

    if(glfwGetKey(window, AWS::R) == GLFW_PRESS && gameOv)
    {
        gameOv = false;
    }
}

void Game::initialize()
{
    glfwSetFramebufferSizeCallback(Game::getWindowPointer(), reshape);

    ground.create();
    player.create("data/texture/image3.png", AWS::textureVS, AWS::textureFS);
    obsticle->create("data/texture/dvd.png", AWS::textureVS, AWS::textureFS);
    gameOver.create("data/texture/gameOver.png", AWS::textureVS, AWS::textureFS);
}

void Game::mainLoop()
{
    float delta = gTime.GetDeltaTime();

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

    processInput(Game::getWindowPointer());

    ground.SetScale(1.0f, 0.1f, 1.0f);
    ground.SetPosition(0.0f, -0.9f, 0.0f);
    ground.SetColor(0.0f, 0.6f, 0.0f, 1.0f);
    ground.draw(GL_TRIANGLES);

    posx[1] -= 2.0f * delta;
    obsticle->SetPosition(posx[1], -0.7f, 0.0f);

    if(posx[1] < -1.2f)
    {
        posx[1] = 1.2f;
        score++;
    }

    obsticle->SetScale(0.1f, 0.1f, 0.1f);
    obsticle->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    obsticle->draw(GL_TRIANGLES);

    if(playerYPos < c_playerYPos)
    {
        acceleration = 0.0f;
        playerCanJump = true;
    }

    if(playerYPos > -0.3f)
    {
        acceleration = 1.0f;
    }

    playerYPos += gravity * acceleration * delta;

    std::cout << score << std::endl;

    player.SetScale(0.1f, 0.1f, 0.1f);
    player.SetPosition(-0.8f, playerYPos, 0.0f);
    player.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    player.draw(GL_TRIANGLES);

    if(playerYPos < -0.6f && posx[1] < -0.7f && posx[1] > -0.9f)
    {
        gameOv = true;
    }

    if(gameOv)
    {
        gameOver.SetScale(0.5f, 0.2f, 0.2f);
        score = 0;
    }
    else
    {
        gameOver.SetScale(0.0f, 0.0f, 0.0f);
    }

    gameOver.SetColor(0.0f, 0.0f, 0.5f, 1.0f);
    gameOver.draw(GL_TRIANGLES);
}