#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace AWS
{
    class Aws_Window
    {
    private:
        GLFWwindow* window;
    
    public:
        /**
         * @brief Main window loop
         * 
         */
        virtual void mainLoop() {}
        
        /**
         * @brief Window initialize
         * 
         */
        virtual void initialize() {}

        /**
         * @brief Create a Window object
         * 
         * @param width - window width
         * @param height - window height
         * @param title - window title
         * @param fullscreen - window fullscreen, NULL to windowed
         */
        void createWindow(int width, int height, std::string title, GLFWmonitor* fullscreen);

        /**
         * @brief Get the Window Pointer object
         * 
         * @return GLFWwindow* 
         */
        GLFWwindow* getWindowPointer() { return window; }
    };

    void Aws_Window::createWindow(int width, int height, std::string title, GLFWmonitor* fullscreen)
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

    typedef Aws_Window Window;
}