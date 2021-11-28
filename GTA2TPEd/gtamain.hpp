#pragma once

#include "../src/Aws_Engine.hpp"
#include "../src/Aws_Types.hpp"

AWS::Time gTime;

class GTAWindow : public AWS::Window
{
public:
    virtual void mainLoop() override;
    virtual void initialize() override;
};