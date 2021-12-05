#include "template2.hpp"

//

AWS::Camera camera;
AWS::Time gTime;
Window window;

int lastX = 400, lastY = 300;
float yaw, pitch;

int wid = 800, hei = 600;
float mouseX, mouseY;

glm::vec3 pos;
glm::vec3 right;

glm::mat4 proj;

//

const float gravity = 1.0f;
float deltaTime;
float velocity = 0.0f;

AWS::Object object;

int main()
{
    window.createWindow(800, 600, "Window", NULL);

    object.Terminate();

    return 0;
}

void reshape(GLFWwindow* gwindow, int w, int h)
{
    glViewport(0, 0, w, h);

    wid = w;
    hei = h;

    proj = glm::perspectiveFov(70.0f, (float)w, (float)h, 0.001f, 1000.0f);
}

void mouse(GLFWwindow* window, double xpos, double ypos)
{
    mouseX = xpos;
    mouseY = ypos;

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

        camera.SetRotation(yaw, pitch, 0.0f);
    }
}

void processInput(GLFWwindow *window)
{
    const float cameraSpeed = 3.0f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        pos += glm::vec3(camera.GetFront().x, 0.0f, camera.GetFront().z) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        pos -= glm::vec3(camera.GetFront().x, 0.0f, camera.GetFront().z) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        pos += right * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        pos -= right * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        //pos.y += 0.1f * cameraSpeed;
        pos.y += 0.05f;

    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        //pos.y -= 0.1f * cameraSpeed;
        pos.y = 1.0f;
    }
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    right = glm::normalize(glm::cross(camera.GetFront(), camera.GetUp()));
}

void Window::initialize()
{
    glfwSetFramebufferSizeCallback(Window::getWindowPointer(), reshape);
    glfwSetCursorPosCallback(Window::getWindowPointer(), mouse);
    glfwSwapInterval(1);

    object.Create(AWS::ShadeType::solid, "testVS.glsl", "testFS.glsl");
    object.SetObjectData(AWS::LoadMesh("data/models/terrainTest1.obj", true));
}

void Window::mainLoop()
{
    deltaTime = gTime.GetDeltaTime();

    AWS::SetWindowAndMouseParameters(wid, hei, mouseX, mouseY);

    processInput(Window::getWindowPointer());

    glm::mat4x4 view = glm::lookAt(camera.GetPosition(), camera.GetPosition() + camera.GetFront(), camera.GetUp());

    bool ray = AWS::CheckRayVertices(pos.x, pos.y, pos.z, pos.x, pos.y - 1.0f, pos.z, proj, view, object.GetObjectData());

    if(ray)
    {
        velocity = 0.0f;
        printf("Work: %d\n", gTime.GetTime());
    }
    else
    {
        velocity = -1.0f;
    }

    pos.y += gravity * velocity * deltaTime;

    camera.SetPosition(pos.x, pos.y, pos.z);

    object.SetColor(0.0f, 1.0f, 0.0f, 1.0f);
    object.DrawObject(GL_TRIANGLES, proj, view);
}