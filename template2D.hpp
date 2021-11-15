#pragma once
#include "src/Aws_Engine.hpp"

class Game : public AWS::Window
{
public:
    virtual void mainLoop() override;
    virtual void initialize() override;
};

class PlayerCamera : public AWS::Camera
{
    
};