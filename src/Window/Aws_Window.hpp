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

    typedef Aws_Window Window;
}