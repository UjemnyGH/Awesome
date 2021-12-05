#include "template2.hpp"

//

AWS::Camera camera;
AWS::Time gTime;
Window window;

int lastX = 400, lastY = 300;
float yaw, pitch;

glm::vec3 pos;
glm::vec3 right;

glm::mat4 proj;

//

AWS::Cube cube;
AWS::Cube background;
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

        camera.SetRotation(yaw, pitch, 0.0f);
    }
}

void processInput(GLFWwindow *window)
{
    const float cameraSpeed = 3.0f * gTime.GetDeltaTime();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        pos += camera.GetFront() * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        pos -= camera.GetFront() * cameraSpeed;
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

    right = glm::normalize(glm::cross(camera.GetFront(), camera.GetUp()));
}

AWS::ObjectData ob = AWS::LoadMesh("data/models/car1.obj", true);

void Window::initialize()
{
    glfwSetFramebufferSizeCallback(Window::getWindowPointer(), reshape);
    glfwSetCursorPosCallback(Window::getWindowPointer(), mouse);
    glfwSwapInterval(1);

    cube.Create(AWS::ShadeType::solid, "data/texture/awesome.png", GL_TEXTURE_2D, AWS::textureVS, AWS::textureFS);
    background.Create(AWS::ShadeType::solid);
    object.Create(AWS::ShadeType::solid, AWS::textureVS, AWS::textureFS);
    object.SetObjectData(ob);
    object.SetTexture("data/texture/car1.png");

    for(int i = 0; i < ob.od_vertices.size() / 3; i++)
    {
        std::cout << "Vertices " << ob.od_vertices[i * 3] << ' ' << ob.od_vertices[i * 3 + 1] << ' ' << ob.od_vertices[i * 3 + 2] << "\t\t" << i << std::endl;
        if(!ob.arrayOn)
            std::cout << ob.od_indices[i * 3] << ' ' << ob.od_indices[i * 3 + 1] << ' ' << ob.od_indices[i * 3 + 2] << std::endl;
    }
}

void Window::mainLoop()
{
    processInput(Window::getWindowPointer());

    glm::mat4x4 view = glm::lookAt(camera.GetPosition(), camera.GetPosition() + camera.GetFront(), camera.GetUp());

    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    camera.SetPosition(pos.x, pos.y, pos.z);

    glUseProgram(object.GetShaderID());

    glUniform3f(glGetUniformLocation(object.GetShaderID(), "view_Pos"), pos.x, pos.y, pos.z);
    glUniform3f(glGetUniformLocation(object.GetShaderID(), "lig_pos"), 1.0f, 2.0f, 0.0f);
    glUniform3f(glGetUniformLocation(object.GetShaderID(), "lig_col"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(object.GetShaderID(), "ambientV"), 0.1f);
    glUniform1f(glGetUniformLocation(object.GetShaderID(), "specularV"), 0.5f);

    glUseProgram(0);

    object.DrawObject(GL_TRIANGLES, proj, view);

    cube.SetPosition(2.0f, 2.0f, 4.0);
    cube.DrawCube(GL_TRIANGLES, proj, view);

    background.SetScale(100.0f, 100.0f, 100.0f);
    background.SetPosition(pos.x, pos.y, pos.z);
    background.SetColor(0.0f, 0.0f, 0.3f, 1.0);
    background.DrawCube(GL_TRIANGLES, proj, view);
}