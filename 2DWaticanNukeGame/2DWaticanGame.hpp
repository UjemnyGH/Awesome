#pragma once
#include "../src/Aws_Engine.hpp"
#include "../src/Aws_Types.hpp"

class Game : public AWS::Window
{
public: 
    virtual void mainLoop() override;
    virtual void initialize() override;
};

class Player : public AWS::Camera
{

};