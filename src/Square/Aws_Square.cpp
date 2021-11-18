#define GLEW_STATIC
#include <GL/glew.h>
#include "Aws_Square.hpp"

void AWS::Aws_Square::create(const std::string &vertName, const std::string &fragName)
{
    textureOn = false;

    sh.create(vertName, fragName);

    vao.create();
    vao.bind();

    vbo[0].create();
    vbo[0].bind(vertices, sizeof(vertices), 0, 3);

    vbo[1].create();
    vbo[1].bind(sqColor, sizeof(color), 1, 4);

    ebo.create();
    ebo.bind(indices, sizeof(indices));

    vao.unbind();
}

void AWS::Aws_Square::create(const std::string textureName, const std::string &vertName, const std::string &fragName)
{
    textureOn = true;

    sh.create(vertName, fragName);

    vao.create();
    vao.bind();

    vbo[0].create();
    vbo[0].bind(vertices, sizeof(vertices), 0, 3);

    vbo[1].create();
    vbo[1].bind(sqColor, sizeof(color), 1, 4);

    vbo[2].create();
    vbo[2].bind(textureCoords, sizeof(textureCoords), 2, 2);
 
    ebo.create();
    ebo.bind(indices, sizeof(indices));

    tex.create();
    tex.bind({textureName}, GL_REPEAT, GL_TEXTURE_2D);

    sh.bind();

    glUniform1i(glGetUniformLocation(sh.GetID(), "tex"), 0);

    sh.unbind();

    vao.unbind();
}

void AWS::Aws_Square::draw(const unsigned int &drawMode)
{
    sh.bind();
    vao.bind();
    if(textureOn)
    {
        tex.bind();
    }

    glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "camera"), 1, GL_FALSE, glm::value_ptr(glm::mat4x4(1.0)));

    glDrawElements(drawMode, 6, GL_UNSIGNED_INT, NULL);

    sh.unbind();
    vao.unbind();
}

void AWS::Aws_Square::draw(const unsigned int &drawMode, glm::mat4x4 camera)
{
    sh.bind();
    vao.bind();
    if(textureOn)
    {
        tex.bind();
    }

    glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "camera"), 1, GL_FALSE, glm::value_ptr(camera));

    glDrawElements(drawMode, sizeof(vertices) / 4, GL_UNSIGNED_INT, NULL);

    sh.unbind();
    vao.unbind();
}

void AWS::Aws_Square::SetPSR(float px, float py, float pz, float sx, float sy, float sz, float rx, float ry, float rz)
{
    squareTransform.position = vec(px, py, pz);
    squareTransform.scale = vec(sx, sy, sz);
    squareTransform.orientation = vec(rx, ry, rz);

    for(int i = 0; i < 4; i++)
    {
        vertices[i * 3] = ((psrConst[i * 3] * squareTransform.scale.vx) + squareTransform.position.vx);// + cos(glm::degrees(squareTransform.orientation.vy)) * cos(glm::degrees(squareTransform.orientation.vx));
        vertices[i * 3 + 1] = ((psrConst[i * 3 + 1] * squareTransform.scale.vy) + squareTransform.position.vy);// + sin(glm::degrees(squareTransform.orientation.vx));
        vertices[i * 3 + 2] = ((psrConst[i * 3 + 2] * squareTransform.scale.vz) + squareTransform.position.vz);// + sin(glm::degrees(squareTransform.orientation.vy)) * cos(glm::degrees(squareTransform.orientation.vx));
    }

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);
}

void AWS::Aws_Square::SetPosition(float x, float y, float z)
{
    squareTransform.position = vec(x, y, z);

    for(int i = 0; i < 4; i++)
    {
        vertices[i * 3] = ((psrConst[i * 3] * squareTransform.scale.vx) + squareTransform.position.vx);// + cos(glm::degrees(squareTransform.orientation.vy)) * cos(glm::degrees(squareTransform.orientation.vx));
        vertices[i * 3 + 1] = ((psrConst[i * 3 + 1] * squareTransform.scale.vy) + squareTransform.position.vy);// + sin(glm::degrees(squareTransform.orientation.vx));
        vertices[i * 3 + 2] = ((psrConst[i * 3 + 2] * squareTransform.scale.vz) + squareTransform.position.vz);// + sin(glm::degrees(squareTransform.orientation.vy)) * cos(glm::degrees(squareTransform.orientation.vx));
    }

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);
}

void AWS::Aws_Square::SetScale(float x, float y, float z)
{
    squareTransform.scale = vec(x, y, z);

    for(int i = 0; i < 4; i++)
    {
        vertices[i * 3] = ((psrConst[i * 3] * squareTransform.scale.vx) + squareTransform.position.vx);// + cos(glm::degrees(squareTransform.orientation.vy)) * cos(glm::degrees(squareTransform.orientation.vx));
        vertices[i * 3 + 1] = ((psrConst[i * 3 + 1] * squareTransform.scale.vy) + squareTransform.position.vy);// + sin(glm::degrees(squareTransform.orientation.vx));
        vertices[i * 3 + 2] = ((psrConst[i * 3 + 2] * squareTransform.scale.vz) + squareTransform.position.vz);// + sin(glm::degrees(squareTransform.orientation.vy)) * cos(glm::degrees(squareTransform.orientation.vx));
    }

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);
}

void AWS::Aws_Square::SetRotation(float x, float y, float z)
{
    squareTransform.orientation = vec(x, y, z);

    for(int i = 0; i < 4; i++)
    {
        vertices[i * 3] = ((psrConst[i * 3] * squareTransform.scale.vx) + squareTransform.position.vx);// + cos(glm::degrees(squareTransform.orientation.vy)) * cos(glm::degrees(squareTransform.orientation.vx));
        vertices[i * 3 + 1] = ((psrConst[i * 3 + 1] * squareTransform.scale.vy) + squareTransform.position.vy);// + sin(glm::degrees(squareTransform.orientation.vx));
        vertices[i * 3 + 2] = ((psrConst[i * 3 + 2] * squareTransform.scale.vz) + squareTransform.position.vz);// + sin(glm::degrees(squareTransform.orientation.vy)) * cos(glm::degrees(squareTransform.orientation.vx));
    }

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);
}

void AWS::Aws_Square::SetTexture(const std::string textureName, const int wrapping)
{
    vao.bind();

    tex.bind({textureName}, wrapping, GL_TEXTURE_2D);

    vao.unbind();
}

void AWS::Aws_Square::SetColor(const float r, const float g, const float b, const float a)
{
    for(int i = 0; i < 4; i++)
    {
        sqColor[i * 4] = r;
        sqColor[i * 4 + 1] = g;
        sqColor[i * 4 + 2] = b;
        sqColor[i * 4 + 3] = a;
    }

    vbo[1].bind(sqColor, sizeof(sqColor), 1, 4);
}

void AWS::Aws_Square::terminate()
{
    vao.terminate();
    vbo->terminate();
    ebo.terminate();
    tex.terminate();
}