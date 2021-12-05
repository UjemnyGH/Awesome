#pragma once

#include "src/Aws_Engine.hpp"
#include "src/Aws_Types.hpp"

class Window : public AWS::Window
{
public:
    virtual void mainLoop() override;
    virtual void initialize() override;
};