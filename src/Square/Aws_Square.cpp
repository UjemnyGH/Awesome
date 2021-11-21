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
    vbo[1].bind(sqColor, sizeof(sqColor), 1, 4);

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
    vbo[1].bind(sqColor, sizeof(sqColor), 1, 4);

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

    glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(transform));

    glDrawElements(drawMode, 6, GL_UNSIGNED_INT, NULL);

    sh.unbind();
    vao.unbind();
}

void AWS::Aws_Square::draw(const unsigned int &drawMode, glm::mat4x4 projection, glm::mat4x4 view)
{
    sh.bind();
    vao.bind();
    if(textureOn)
    {
        tex.bind();
    }

    glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(projection * view * transform));

    glDrawElements(drawMode, sizeof(vertices) / 4, GL_UNSIGNED_INT, NULL);

    sh.unbind();
    vao.unbind();
}

void AWS::Aws_Square::SetPSR(float px, float py, float pz, float sx, float sy, float sz, float rx, float ry, float rz)
{
    psr[0][0] = px;
    psr[0][1] = py;
    psr[0][2] = pz;
    psr[1][0] = sx;
    psr[1][1] = sy;
    psr[1][2] = sz;
    psr[2][0] = rx;
    psr[2][1] = ry;
    psr[2][2] = rz;

    transform = glm::translate(glm::mat4(1.0), glm::vec3(psr[0][0], psr[0][1], psr[0][2]));
    transform = glm::rotate(transform, glm::radians(psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(psr[1][0], psr[1][1], psr[1][2]));
    
    /*squareTransform.position = vec(px, py, pz);
    squareTransform.scale = vec(sx, sy, sz);
    squareTransform.orientation = vec(rx, ry, rz);

    for(int i = 0; i < 4; i++)
    {
        vertices[i * 3] = ((psrConst[i * 3] * squareTransform.scale.vx) + squareTransform.position.vx);// + cos(glm::degrees(squareTransform.orientation.vy)) * cos(glm::degrees(squareTransform.orientation.vx));
        vertices[i * 3 + 1] = ((psrConst[i * 3 + 1] * squareTransform.scale.vy) + squareTransform.position.vy);// + sin(glm::degrees(squareTransform.orientation.vx));
        vertices[i * 3 + 2] = ((psrConst[i * 3 + 2] * squareTransform.scale.vz) + squareTransform.position.vz);// + sin(glm::degrees(squareTransform.orientation.vy)) * cos(glm::degrees(squareTransform.orientation.vx));
    }

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);*/
}

void AWS::Aws_Square::SetPosition(float x, float y, float z)
{
    psr[0][0] = x;
    psr[0][1] = y;
    psr[0][2] = z;

    transform = glm::translate(glm::mat4(1.0), glm::vec3(psr[0][0], psr[0][1], psr[0][2]));
    transform = glm::rotate(transform, glm::radians(psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(psr[1][0], psr[1][1], psr[1][2]));

    /*squareTransform.position = vec(x, y, z);

    for(int i = 0; i < 4; i++)
    {
        vertices[i * 3] = ((psrConst[i * 3] * squareTransform.scale.vx) + squareTransform.position.vx);// + cos(glm::degrees(squareTransform.orientation.vy)) * cos(glm::degrees(squareTransform.orientation.vx));
        vertices[i * 3 + 1] = ((psrConst[i * 3 + 1] * squareTransform.scale.vy) + squareTransform.position.vy);// + sin(glm::degrees(squareTransform.orientation.vx));
        vertices[i * 3 + 2] = ((psrConst[i * 3 + 2] * squareTransform.scale.vz) + squareTransform.position.vz);// + sin(glm::degrees(squareTransform.orientation.vy)) * cos(glm::degrees(squareTransform.orientation.vx));
    }

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);*/
}

void AWS::Aws_Square::SetScale(float x, float y, float z)
{
    psr[1][0] = x;
    psr[1][1] = y;
    psr[1][2] = z;

    transform = glm::translate(glm::mat4(1.0), glm::vec3(psr[0][0], psr[0][1], psr[0][2]));
    transform = glm::rotate(transform, glm::radians(psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(psr[1][0], psr[1][1], psr[1][2]));

    /*squareTransform.scale = vec(x, y, z);

    for(int i = 0; i < 4; i++)
    {
        vertices[i * 3] = ((psrConst[i * 3] * squareTransform.scale.vx) + squareTransform.position.vx);// + cos(glm::degrees(squareTransform.orientation.vy)) * cos(glm::degrees(squareTransform.orientation.vx));
        vertices[i * 3 + 1] = ((psrConst[i * 3 + 1] * squareTransform.scale.vy) + squareTransform.position.vy);// + sin(glm::degrees(squareTransform.orientation.vx));
        vertices[i * 3 + 2] = ((psrConst[i * 3 + 2] * squareTransform.scale.vz) + squareTransform.position.vz);// + sin(glm::degrees(squareTransform.orientation.vy)) * cos(glm::degrees(squareTransform.orientation.vx));
    }

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);*/
}

void AWS::Aws_Square::SetRotation(float x, float y, float z)
{
    psr[2][0] = x;
    psr[2][1] = y;
    psr[2][2] = z;

    transform = glm::translate(glm::mat4(1.0), glm::vec3(psr[0][0], psr[0][1], psr[0][2]));
    transform = glm::rotate(transform, glm::radians(psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(psr[1][0], psr[1][1], psr[1][2]));

    /*squareTransform.orientation = vec(x, y, z);

    for(int i = 0; i < 4; i++)
    {
        vertices[i * 3] = ((psrConst[i * 3] * squareTransform.scale.vx) + squareTransform.position.vx);// + cos(glm::degrees(squareTransform.orientation.vy)) * cos(glm::degrees(squareTransform.orientation.vx));
        vertices[i * 3 + 1] = ((psrConst[i * 3 + 1] * squareTransform.scale.vy) + squareTransform.position.vy);// + sin(glm::degrees(squareTransform.orientation.vx));
        vertices[i * 3 + 2] = ((psrConst[i * 3 + 2] * squareTransform.scale.vz) + squareTransform.position.vz);// + sin(glm::degrees(squareTransform.orientation.vy)) * cos(glm::degrees(squareTransform.orientation.vx));
    }

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);*/
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