#include "Aws_Window.hpp"

void AWS::Aws_Window::createWindow(int width, int height, std::string title, GLFWmonitor* fullscreen)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), fullscreen, NULL);

    if(!window)
    {
        std::cout << "Window couldn`t created\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        std::cout << "GLEW couldn`t initialized\n";
        glfwTerminate();
    }

    if(!GLEW_VERSION_4_3)
    {
        std::cout << "OpenGL wrong version\n";
        glfwTerminate();
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    initialize();

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainLoop();

        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}