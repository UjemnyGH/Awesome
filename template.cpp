#define GLEW_STATIC
#include "template.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "src/stb_image/stb_image.h"

Game window;
AWS::Square sq;
AWS::Time gtime;

int main()
{
    window.createWindow(800, 600, "Window", NULL);
}

void Game::initialize()
{
    sq.create(AWS::textureVS, AWS::textureFS, "data/texture/imageTest.png");
}

void Game::mainLoop()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 0.0f, 0.0f);

    sq.SetPosition(0.1f, 0.2f, 0.0f);
    sq.SetScale(0.8f, 0.5f, 0.5f);

    sq.draw(GL_TRIANGLES);
}