#include "gtamain.hpp"
#include "gtaPlayer.hpp"
#include <SFML/Audio.hpp>

const float gravity = 1.0f;
float deltaTime;
float speed = 10.0f;
float real_gravity;
float velocityUpward = 0.0f;
const float jumpHeight = 10.0f;

PlayerUI ui;

GTAWindow window;
Player player;
AWS::Cube testCube[40];
AWS::Square grass;

AWS::Object car;
AWS::CubeCollider carTrigger;
float acceleration = 0.0f;
float right = 0.0f;
glm::vec3 carDir = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 carFront;
glm::vec3 carPos;

AWS::CubeCollider grassCollider;

AWS::CubeCollider playerCollider;
AWS::CollisionHandler playerCollisionHandler;
AWS::CollisionHandler p2layerCollisionHandler;

glm::vec3 playerPos(2.0f, 2.0f, 2.0f);
glm::mat4 proj;
bool inCar = false;

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
    if(!inCar)
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
    else
    {
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            acceleration += 0.01f * deltaTime;
        }
        else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            acceleration -= 0.1f * deltaTime;
        }
        else
        {
            if(acceleration > 0.0f)
                acceleration -= 0.1f;
            else if(acceleration < 0.0f)
                acceleration += 0.1f;
        }

        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            right -= 0.1f * deltaTime;
        }
        else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            right += 0.1f * deltaTime;
        }
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

    car.Create(AWS::ShadeType::shade, AWS::shadeTextureVS, AWS::shadeTextureFS);
    car.SetTexture("GTA2TPEd/data/textures/microcarUV.png");
    car.SetObjectData(AWS::LoadMesh("GTA2TPEd/data/mesh/microcar.obj", true));

    for(int i = 0; i < 40; i++)
    {
        testCube[i].Create(AWS::ShadeType::shade, "GTA2TPEd/data/textures/brickWindow1_lod1.png", GL_TEXTURE_2D, AWS::shadeTextureVS, AWS::shadeTextureFS);
        //testCube[i].Create(AWS::ShadeType::solid, AWS::colorVS, AWS::colorFS);
    }

    grass.Create("GTA2TPEd/data/textures/grass1.png", AWS::textureVS, AWS::textureFS);

    //ui
    ui.crosshair.Create("GTA2TPEd/data/textures/crossHair1.png", AWS::textureVS, AWS::textureFS);
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

        glUseProgram(testCube[i].GetShaderID());

        glUniform3f(glGetUniformLocation(testCube[i].GetShaderID(), "viewPos"), player.playerCamera.GetPosition().x, player.playerCamera.GetPosition().y, player.playerCamera.GetPosition().z);
        glUniform3f(glGetUniformLocation(testCube[i].GetShaderID(), "lig_pos"), 2.0f, 2.0f, 2.0f);
        glUniform3f(glGetUniformLocation(testCube[i].GetShaderID(), "lig_col"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(testCube[i].GetShaderID(), "ambientV"), 0.6f);
        glUniform1f(glGetUniformLocation(testCube[i].GetShaderID(), "specularV"), 0.2f);

        glUseProgram(0);

        testCube[i].DrawCube(GL_TRIANGLES, proj, view);

        playerCollisionHandler.CollisionCheck(playerCollider.GetObjectData(), {grassCollider.GetObjectData(), testCube[i].GetObjectData()}, 0.8f, 1.0f, 0.8f);
    }

    grass.SetColor(0.0f, 0.3f, 0.0f, 1.0f);
    grass.SetScale(500.0f, 500.0f, 1.0f);
    grass.SetRotation(90.0f, 0.0f, 0.0f);
    grass.SetTextureCoordinates(10000.0f, 10000.0f);
    grass.DrawSquare(GL_TRIANGLES, proj, view);

    car.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    car.SetScale(1.0f, 1.0f, 1.0f);

    carDir.x += (cos(acceleration) * cos(right));
    carDir.y += sin(acceleration);
    carDir.z += (sin(acceleration) * cos(right));

    carFront = glm::normalize(carDir);

    carPos.x += carFront.x + (right / acceleration);
    carPos.y = 0.0f;
    carPos.z += carFront.z + acceleration;

    car.SetPosition(carPos.x, carPos.y, carPos.z);
    car.SetRotation(carFront.x, 0.0f, carFront.z);
    carTrigger.SetScale(5.0f, 5.0f, 5.0f);
    carTrigger.SetPosition(carPos.x, carPos.y, carPos.z);

    glUseProgram(car.GetShaderID());

    glUniform3f(glGetUniformLocation(car.GetShaderID(), "viewPos"), player.playerCamera.GetPosition().x, player.playerCamera.GetPosition().y, player.playerCamera.GetPosition().z);
    glUniform3f(glGetUniformLocation(car.GetShaderID(), "lig_pos"), 2.0f, 2.0f, 2.0f);
    glUniform3f(glGetUniformLocation(car.GetShaderID(), "lig_col"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(car.GetShaderID(), "ambientV"), 0.0f);
    glUniform1f(glGetUniformLocation(car.GetShaderID(), "specularV"), 0.3f);

    glUseProgram(0);

    car.DrawObject(GL_TRIANGLES, proj, view);

    if(!inCar && glfwGetKey(GTAWindow::getWindowPointer(), GLFW_KEY_F) == GLFW_PRESS && playerCollisionHandler.CollisionCheck(playerCollider.GetObjectData(), carTrigger.GetObjectData(), 1.0f, 1.0f, 1.0f))
    {
        inCar = true;
    }
    else if(inCar && glfwGetKey(GTAWindow::getWindowPointer(), GLFW_KEY_F) == GLFW_PRESS)
    {
        inCar = false;
    }

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
            velocityUpward -= 0.00001;
            if(velocityUpward >= -2.0f)
            {
                velocityUpward = -2.0f;
            }
        }
    }

    real_gravity = gravity * velocityUpward * deltaTime;

    playerPos.y += real_gravity * jumpHeight;

    if(!inCar)
        player.SetPosition(playerPos.x, playerPos.y, playerPos.z);
    else
        player.SetThirdRotation(carPos.x, carPos.z, 3.0f, deltaTime);


    playerCollisionHandler.CollisionClear();

    //UI
    ui.crosshair.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    ui.crosshair.SetScale(OnePixelX * 64.0f, OnePixelY * 64.0f, 0.05f);

    ui.DrawUI();

    glfwSwapInterval(1);
}