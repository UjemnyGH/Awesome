#define GLEW_STATIC
#include "template.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "src/stb_image/stb_image.h"

Game window;
AWS::Square sq;
AWS::Time gtime;

float x, y;
bool xt[2];

/**
 * @brief 
 * 
 * @return int 
 */
int main()
{
    window.createWindow(1280, 1080, "Window", NULL);
}

bool Get(float value, float val2, int oo)
{
    if(value > 1.0f - val2)
    {
        xt[oo] = false;
    }
    else if(value < -1.0f + val2)
    {
        xt[oo] = true;
    }

    return xt[oo];
}

void Game::initialize()
{
    sq.create(AWS::textureVS, AWS::textureFS, "data/texture/dvd.png");
}

void Game::mainLoop()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    if(Get(x, 0.15f, 0))
    {
        x += 0.01f;
    }
    else
    {
        x -= 0.01f;
    }

    if(Get(y, 0.1f, 1))
    {
        y += 0.01f;
    }
    else
    {
        y -= 0.01f;
    }
    
    sq.SetScale(0.15f, 0.1f, 0.5f);
    sq.SetPosition(x, y, 0.0f);
    sq.SetColor(x, y, -(x + y) / 2.0f);

    sq.draw(GL_TRIANGLES);
}