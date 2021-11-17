#pragma once

#include "../src/Aws_Engine.hpp"

class Window : public AWS::Window
{
    virtual void initialize() override;
    virtual void mainLoop() override;
};

class Camera : public AWS::Camera
{

};