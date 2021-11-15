#pragma once

#include <chrono>
#include <iostream>
#include <ctime>
#include <GLFW/glfw3.h>

namespace AWS
{
    class Aws_Time
    {
    private:
        float lastFrame, currentFrame;

    public:
        /**
         * @brief Get the Time object
         * 
         * @return float 
         */
        float GetTime() { return glfwGetTime(); }
        
        /**
         * @brief Get the Delta Time object. USE ONE DELTA IN ALL PROGRAM!!!!!!!!!
         * 
         * @return float 
         */
        float GetDeltaTime() { lastFrame = currentFrame; currentFrame = glfwGetTime(); return currentFrame - lastFrame; }
    };

    typedef Aws_Time Time;

} // namespace AWS
