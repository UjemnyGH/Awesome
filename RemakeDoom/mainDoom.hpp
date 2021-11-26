#include "../src/Aws_Engine.hpp"
#include "../src/Aws_Types.hpp"

class DoomWindow : public AWS::Window
{
public:
    virtual void mainLoop() override;
    virtual void initialize() override;
};