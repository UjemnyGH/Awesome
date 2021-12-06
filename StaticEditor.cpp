#include "StaticEditor.hpp"

//

AWS::Time gTime;

EditorWindow editorWindow;
float deltaTime;
int cEditorWidth = 800, cEditorHeight = 600;
float mouseX, mouseY;

AWS::Camera editorView;
glm::vec3 editorViewPosition;
glm::vec3 editorViewRight;
const float editorViewSpeed = 1.0f;
glm::mat4 proj;
glm::mat4 view;
int lastX = 400, lastY = 300;
float editorViewRX, editorViewRY;

bool rightMouseButton = false;

std::ifstream f;

//

//ImGui
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

//Objects
struct EditorObjectData
{
    AWS::Object object;
    std::string objectPath;

    float p[3];
    float s[3];
    float r[3];
    float col[4];
};

EditorObjectData objects[32767];

AWS::Square testSq;

int main()
{
    editorWindow.createWindow(800, 600, "Awesome Static Object Editor", NULL);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    objects->object.Terminate();

    return 0;
}

void processInput(GLFWwindow *window)
{
    float camSpeed = editorViewSpeed * deltaTime;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            editorViewPosition += editorView.GetFront() * camSpeed;
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            editorViewPosition -= editorView.GetFront() * camSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            editorViewPosition -= editorViewRight * camSpeed;
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            editorViewPosition += editorViewRight * camSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            editorViewPosition.y += camSpeed;
        }
        else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        {
            editorViewPosition.y -= camSpeed;
        }
    }

    editorViewRight = glm::normalize(glm::cross(editorView.GetFront(), editorView.GetUp()));
}

void CameraRotation(GLFWwindow *window, double xpos, double ypos)
{
    mouseX = xpos;
    mouseY = ypos;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
    {
        float sensitivity = 0.1f;

        if (rightMouseButton)
            glfwSetCursorPos(window, cEditorWidth / 2.0f, cEditorHeight / 2.0f);

        rightMouseButton = false;

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        float xoff = xpos - lastX;
        float yoff = ypos - lastY;

        lastX = xpos;
        lastY = ypos;

        xoff *= sensitivity;
        yoff *= sensitivity;

        editorViewRX += xoff;
        editorViewRY += -yoff;

        if (editorViewRY > 89.0f)
            editorViewRY = 89.0f;
        if (editorViewRY < -89.0f)
            editorViewRY = -89.0f;

        editorView.SetRotation(editorViewRX, editorViewRY, 0.0f);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        rightMouseButton = true;
    }
}

void framebufferCall(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);

    cEditorWidth = width;
    cEditorHeight = height;

    proj = glm::perspectiveFov(70.0f, (float)width, (float)height, 0.001f, 1000.0f);
}

void EditorWindow::initialize()
{
    glfwSetFramebufferSizeCallback(EditorWindow::getWindowPointer(), framebufferCall);
    glfwSetCursorPosCallback(EditorWindow::getWindowPointer(), CameraRotation);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(EditorWindow::getWindowPointer(), true);
    ImGui_ImplOpenGL3_Init("#version 430 core");

    testSq.Create();
}

void EditorWindow::mainLoop()
{
    deltaTime = gTime.GetDeltaTime();

    view = glm::lookAt(editorView.GetPosition(), editorView.GetPosition() + editorView.GetFront(), editorView.GetUp());

    AWS::SetWindowAndMouseParameters(cEditorWidth, cEditorHeight, mouseX, mouseY);

    processInput(EditorWindow::getWindowPointer());

    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static int objectCounter = 0;
    static int objectNumber = 0;
    static char pathObj[256];
    static char pathTexture[256];
    static bool checkboxToShading;

    ImGui::Begin("Add object");

    //set index of object
    ImGui::InputInt("Object number", &objectNumber);

    //Set pos, scal, rot and color
    ImGui::InputFloat3("Position: ", objects[objectNumber].p);
    ImGui::InputFloat3("Scale: ", objects[objectNumber].s);
    ImGui::InputFloat3("Rotation: ", objects[objectNumber].r);
    ImGui::ColorEdit4("Color: ", objects[objectNumber].col);

    //add object
    if (ImGui::Button("Add object") && objectCounter < 32767 && objects[objectNumber].object.GetObjectData().od_vertices.size() > 1)
    {
        objects[objectNumber].object.Create(AWS::ShadeType::solid, AWS::textureVS, AWS::textureFS);

        objectCounter++;
    }
    else
    {
        objects[objectNumber].object.Terminate();

        objects[objectNumber].object.Create(AWS::ShadeType::solid, AWS::textureVS, AWS::textureFS);
    }

    //set mesh form path
    ImGui::InputText("Path to mesh data", pathObj, 256);

    f.open(std::string(pathObj), std::ios::binary);

    bool setObjectDataFromPath = ImGui::Button("Set mesh");

    if (setObjectDataFromPath && !f.bad() && !f.fail())
    {
        objects[objectNumber].object.SetObjectData(AWS::LoadMesh(std::string(pathObj), true));
    }
    else if (setObjectDataFromPath && f.bad() || f.fail())
    {
        ImGui::SameLine();
        ImGui::Text("Object dont load mesh from path : %s", pathObj);
    }

    f.close();

    //set texture from path
    ImGui::InputText("Path to texture", pathTexture, 256);

    f.open(std::string(pathTexture), std::ios::binary);

    bool setTextureFromPath = ImGui::Button("Set texture");

    if (setTextureFromPath && !f.bad() && !f.fail())
    {
        objects[objectNumber].object.SetTexture(std::string(pathTexture));
    }
    else if (setTextureFromPath && f.bad() || f.fail())
    {
        ImGui::SameLine();
        ImGui::Text("Object dont load texture from path : %s", pathTexture);
    }

    f.close();

    //image view of texture
    ImGui::Image((void*)objects[objectNumber].object.GetTextureID(), ImVec2(100.0f, 100.0f));

    ImGui::Text("Number of objects: %d", objectCounter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::End();

    for(unsigned int i = 0; i < objectCounter + 1; i++)
    {
        objects[i].object.SetPosition(objects[i].p[0], objects[i].p[1], objects[i].p[2]);
        objects[i].object.SetScale(objects[i].s[0], objects[i].s[1], objects[i].s[2]);
        objects[i].object.SetRotation(objects[i].r[0], objects[i].r[1], objects[i].r[2]);
        objects[i].object.SetColor(objects[i].col[0], objects[i].col[1], objects[i].col[2], objects[i].col[3]);
        objects[i].object.DrawObject(GL_TRIANGLES, proj, view);
    }

    editorView.SetPosition(editorViewPosition.x, editorViewPosition.y, editorViewPosition.z);

    testSq.SetColor(0.0f, 0.0f, 0.0f, 1.0f);
    testSq.SetScale(0.5f, 0.5f, 0.5f);
    testSq.DrawSquare(GL_TRIANGLES, proj, view);
    
    //Must render last
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}