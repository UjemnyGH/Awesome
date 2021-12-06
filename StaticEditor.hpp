#pragma once

#include "src/Aws_Engine.hpp"
#include "src/Aws_Types.hpp"

#include "src/imgui/imgui.h"
#include "src/imgui/imgui_impl_glfw.h"
#include "src/imgui/imgui_impl_opengl3.h"

class EditorWindow : public AWS::Window
{
public:
    virtual void initialize() override;
    virtual void mainLoop() override;
};