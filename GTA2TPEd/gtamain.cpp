#include "gtamain.hpp"
#include "gtaPlayer.hpp"
#include <SFML/Audio.hpp>

const float gravity = 4.0f;
float deltaTime;
float speed = 10.0f;
float real_gravity;
float velocityUpward = 0.0f;

PlayerUI ui;

GTAWindow window;
Player player;
AWS::Cube testCube[40];
AWS::Square grass;
AWS::CubeCollider grassCollider;
AWS::CubeCollider playerCollider;
AWS::CollisionHandler playerCollisionHandler;
AWS::CollisionHandler p2layerCollisionHandler;

glm::vec3 playerPos(2.0f, 2.0f, 2.0f);
glm::mat4 proj;

int wid = 400, hei = 300;
bool veloc = true;
bool spacePress = false;

float OnePixelX = 1.0f/800;
float OnePixelY = 1.0f/600;

sf::SoundBuffer katyusha;
sf::Sound katyusaSound;

int main()
{
    window.createWindow(800, 600, "Grand Technics Arrangment - 2TP Edition", NULL);

    return 0;
}

void reshape(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    wid = width;
    hei = height;

    player.initCam(wid, hei);

    OnePixelX = 1.0f / width;
    OnePixelY = 1.0f / height;

    proj = glm::perspectiveFov(70.0f, (float)width, (float)height, 0.01f, 1000.0f);
}

void proccesInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        playerPos += glm::vec3(player.front().x, 0.0f, player.front().z) * speed * deltaTime;
    }
    else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        playerPos -= glm::vec3(player.front().x, 0.0f, player.front().z) * speed * deltaTime;
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        playerPos -= player.right() * speed * deltaTime;
    }
    else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        playerPos += player.right() * speed * deltaTime;
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spacePress)
    {
        velocityUpward = 2.0f;
        playerPos.y += 0.1f;
        spacePress = true;
    }

    if(glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else if(glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        playerPos.y = 3.0f;
    }
}

void mouse(GLFWwindow* window, double xm, double ym)
{
    player.SetRotation(xm, ym, deltaTime);
}

void GTAWindow::initialize()
{
    glfwSetFramebufferSizeCallback(GTAWindow::getWindowPointer(), reshape);
    glfwSetCursorPosCallback(GTAWindow::getWindowPointer(), mouse);

    for(int i = 0; i < 40; i++)
    {
        testCube[i].Create(AWS::ShadeType::solid, "../GTA2TPEd/data/textures/brickWindow1_lod1.png", GL_TEXTURE_2D, AWS::textureVS, AWS::textureFS);
        //testCube[i].Create(AWS::ShadeType::solid, AWS::colorVS, AWS::colorFS);
    }

    grass.Create("../GTA2TPEd/data/textures/grass1.png", AWS::textureVS, AWS::textureFS);

    //ui
    ui.crosshair.Create("../GTA2TPEd/data/textures/crossHair1.png", AWS::textureVS, AWS::textureFS);
}

void GTAWindow::mainLoop()
{
    glClearColor(0.0f, 0.0f, 0.7f, 1.0f);

    glm::mat4 view = player.playerLookAt();

    deltaTime = gTime.GetDeltaTime();

    proccesInput(GTAWindow::getWindowPointer());

    grassCollider.SetRotation(0.0f, -0.05f, 0.0f);
    grassCollider.SetScale(500.0f, 0.1f, 500.0f);
    playerCollider.SetPosition(playerPos.x, playerPos.y - 0.1f, playerPos.z);

    for(int i = 0; i < 40; i++)
    {   
        testCube[i].SetColor(cos((float)i / 40.0f), sin((float)i / 40.0f), 1.0f, 1.0f);
        testCube[i].SetScale(5.0f, 20.0f * sin((float)i / 40.0f), 5.0f);

        if(i % 2 == 0)
        {
            testCube[i].SetPosition(-15.0f, 0.0f + (20.0f * sin((float)i / 40.0f)), i * 12.0f);
        }
        else
        {
            testCube[i].SetPosition(15.0f, 0.0f + (20.0f * sin((float)i / 40.0f)), i * 12.0f);
        }

        testCube[i].SetTextureCoordinates(5.0f, 5.0f);

        testCube[i].DrawCube(GL_TRIANGLES, proj, view);

        playerCollisionHandler.CollisionCheck(playerCollider.GetObjectData(), {grassCollider.GetObjectData(), testCube[i].GetObjectData()});
    }

    grass.SetColor(0.0f, 0.3f, 0.0f, 1.0f);
    grass.SetScale(500.0f, 500.0f, 1.0f);
    grass.SetRotation(90.0f, 0.0f, 0.0f);
    grass.SetTextureCoordinates(10000.0f, 10000.0f);
    grass.DrawSquare(GL_TRIANGLES, proj, view);

    for(int i = 0; i < playerCollisionHandler.isColliding.size(); i++)
    {
        if(playerCollisionHandler.isColliding[i])
        {
            if(!spacePress)
                velocityUpward = 0.0f;
            else
                velocityUpward = 2.0f;

            spacePress = false;

            break;
        }
        else
        {
            velocityUpward -= 0.000001f;
            if(velocityUpward >= -1.0f)
            {
                velocityUpward = -1.0f;
            }
        }
    }

    real_gravity = gravity *velocityUpward * deltaTime;

    playerPos.y += real_gravity;

    player.SetPosition(playerPos.x, playerPos.y, playerPos.z);

    playerCollisionHandler.CollisionClear();

    //UI
    ui.crosshair.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    ui.crosshair.SetScale(OnePixelX * 64.0f, OnePixelY * 64.0f, 0.05f);

    ui.DrawUI();

    glfwSwapInterval(1);
}