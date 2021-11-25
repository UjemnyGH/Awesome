#include "src/Aws_Engine.hpp"
#include "src/Aws_Types.hpp"

class Window : public AWS::Window
{
public:
    virtual void mainLoop() override;
    virtual void initialize() override;
};

AWS::Cube *sq = new AWS::Cube;
AWS::Cube sq2;

AWS::Time gTime;
float lastCubeRecall = 0.0f;

AWS::Camera playerCam;
glm::mat4 projection;

glm::vec3 player;
glm::vec3 right;
float playerRX = 0.0f, playerRY = 0.0f;
const float playerSpeed = 1.0f;
const float csprintSpeed = 2.0f;
float sprint = 1.0f;
bool firstMouseButtonClick = false;

const float sensitivity = 0.1f;
int lastX = 400, lastY = 300;

Window window;

int Wwidth = 800, Wheight = 600;

int main()
{
    window.createWindow(1280, 1080, "Window", nullptr);

    return 0;
}

void processInput(GLFWwindow* window)
{
    float camSpeed = playerSpeed * gTime.GetDeltaTime() * sprint;

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        player += playerCam.GetFront() * camSpeed;
    }
    else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        player -= playerCam.GetFront() * camSpeed;
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        player -= right * camSpeed;
    }
    else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        player += right * camSpeed;
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        player.y += camSpeed;
    }
    else if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        player.y -= camSpeed;
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        sprint = csprintSpeed;
    }
    else
    {
        sprint = 1.0f;
    }

    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if(lastCubeRecall + 1.0f < gTime.GetTime())
        {
            sq->terminate();

            delete sq;

            sq = new AWS::Cube;

            sq->create(AWS::ShadeType::solid, "testVS.glsl", "testFS.glsl");

            lastCubeRecall = gTime.GetTime();
        }
    }

    right = glm::normalize(glm::cross(playerCam.GetFront(), playerCam.GetUp()));
}

void CameraRotation(GLFWwindow* window, double xpos, double ypos)
{
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        if(firstMouseButtonClick)
            glfwSetCursorPos(window, Wwidth / 2.0f, Wheight / 2.0f);

        firstMouseButtonClick = false;

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        float xoff = xpos - lastX;
        float yoff = ypos - lastY;

        lastX = xpos;
        lastY = ypos;

        xoff *= sensitivity;
        yoff *= sensitivity;

        playerRX += xoff;
        playerRY += -yoff;

        if(playerRY > 89.0f)
            playerRY = 89.0f;
        if(playerRY < -89.0f)
            playerRY = -89.0f;
        
        playerCam.SetRotation(playerRX, playerRY, 0.0f);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        firstMouseButtonClick = true;
    }
}

void framebufferCall(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    Wwidth = width;
    Wheight = height;

    projection = glm::perspectiveFov(70.0f, (float)width, (float)height, 0.001f, 100.0f);
}

void Window::initialize()
{
    glfwSetFramebufferSizeCallback(Window::getWindowPointer(), framebufferCall);
    glfwSetCursorPosCallback(Window::getWindowPointer(), CameraRotation);

    sq->create(AWS::ShadeType::solid, AWS::colorVS, AWS::colorFS);
    sq2.create(AWS::ShadeType::solid);
}

void Window::mainLoop()
{
    glm::mat4 view = glm::lookAt(playerCam.GetPosition(), playerCam.GetPosition() + playerCam.GetFront(), playerCam.GetUp());

    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

    processInput(Window::getWindowPointer());

    playerCam.SetPosition(player.x, player.y, player.z);

    sq->SetColor(0.0f, 1.0f, 1.0f, 1.0f);

    glUseProgram(sq->GetShaderID());

    glUniform1f(glGetUniformLocation(sq->GetShaderID(), "time"), gTime.GetTime());
    glUniform1f(glGetUniformLocation(sq->GetShaderID(), "deltaTime"), gTime.GetDeltaTime());
    glUniform3f(glGetUniformLocation(sq->GetShaderID(), "cameraPosition"), playerCam.GetPosition().x, playerCam.GetPosition().y, playerCam.GetPosition().z);

    glUseProgram(0);

    sq->draw(GL_TRIANGLES, projection, view);

    sq2.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    sq2.SetScale(0.5f, 0.5f, 0.5f);
    sq2.SetPosition(3.0f, 0.0f, 0.0f);
    sq2.draw(GL_TRIANGLES, projection, view);
}