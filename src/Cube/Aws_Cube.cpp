#include "Aws_Cube.hpp"

void AWS::Aws_Cube::create(const std::string &vertName, const std::string &fragName)
{
    texturesOn = false;

    sh.create(vertName, fragName);

    vao.create();
    vao.bind();

    vbo[0].create();
    vbo[0].bind(vertices, sizeof(vertices), 0, 3);

    vbo[1].create();
    vbo[1].bind(cbColor, sizeof(cbColor), 1, 4);

    ebo.create();
    ebo.bind(indices, sizeof(indices));

    vao.unbind();
}

void AWS::Aws_Cube::create(const std::string textureName, const int textureType, const std::string &vertName, const std::string &fragName)
{
    texturesOn = true;

    sh.create(vertName, fragName);

    vao.create();
    vao.bind();

    vbo[0].create();
    vbo[0].bind(vertices, sizeof(vertices), 0, 3);

    vbo[1].create();
    vbo[1].bind(cbColor, sizeof(cbColor), 1, 4);

    if(textureType == CubeTexturing::cubemap)
    {
        vbo[2].create();
        vbo[2].bind(cubemapTexture, sizeof(cubemapTexture), 2, 3);
    }
    else
    {
        vbo[2].create();
        vbo[2].bind(texture, sizeof(texture), 2, 2);
    }

    ebo.create();
    ebo.bind(indices, sizeof(indices));

    tex.create();
    tex.bind({textureName}, GL_REPEAT, textureType);

    sh.bind();

    glUniform1i(glGetUniformLocation(sh.GetID(), "tex"), 0);

    sh.unbind();

    vao.unbind();
}

void AWS::Aws_Cube::create(const std::vector<std::string> textureName, const std::string &vertName, const std::string &fragName)
{
    texturesOn = true;

    sh.create(vertName, fragName);

    vao.create();
    vao.bind();

    vbo[0].create();
    vbo[0].bind(vertices, sizeof(vertices), 0, 3);

    vbo[1].create();
    vbo[1].bind(cbColor, sizeof(cbColor), 1, 4);

    vbo[2].create();
    vbo[2].bind(cubemapTexture, sizeof(cubemapTexture), 2, 3);

    ebo.create();
    ebo.bind(indices, sizeof(indices));

    tex.create();
    tex.bind(textureName, GL_REPEAT, GL_TEXTURE_CUBE_MAP);

    sh.bind();

    glUniform1i(glGetUniformLocation(sh.GetID(), "tex"), 0);

    sh.unbind();

    vao.unbind();
}

void AWS::Aws_Cube::draw(const unsigned int &drawMode)
{
    sh.bind();
    vao.bind();
    if(texturesOn)
    {
        tex.bind();
    }

    glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(transform));

    glDrawElements(drawMode, sizeof(vertices) / 2, GL_UNSIGNED_INT, NULL);

    sh.unbind();
    vao.unbind();
}

void AWS::Aws_Cube::draw(const unsigned int &drawMode, glm::mat4x4 projection, glm::mat4x4 view)
{
    sh.bind();
    vao.bind();
    if(texturesOn)
    {
        tex.bind();
    }

    glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(projection * view * transform));

    glDrawElements(drawMode, sizeof(vertices) / 2, GL_UNSIGNED_INT, NULL);

    sh.unbind();
    vao.unbind();
}

void AWS::Aws_Cube::SetPSR(float px, float py, float pz, float sx, float sy, float sz, float rx, float ry, float rz)
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

    /*for(int i = 0; i < 8; i++)
    {
        position[0] = px;
        position[1] = py;
        position[2] = pz;

        scale[0] = sx;
        scale[1] = sy;
        scale[2] = sz;

        rotation[0] = rx;
        rotation[1] = ry;
        rotation[2] = rz;
    }

    for(int i = 0; i < 8; i++)
    {
        vertices[i * 3] = (psrConst[i * 3] * scale[0]) + position[0];
        vertices[i * 3 + 1] = (psrConst[i * 3 + 1] * scale[1]) + position[1];
        vertices[i * 3 + 2] = (psrConst[i * 3 + 2] * scale[2]) + position[2];
    }

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);*/
}

void AWS::Aws_Cube::SetPosition(float x, float y, float z)
{
    psr[0][0] = x;
    psr[0][1] = y;
    psr[0][2] = z;

    transform = glm::translate(glm::mat4(1.0), glm::vec3(psr[0][0], psr[0][1], psr[0][2]));
    transform = glm::rotate(transform, glm::radians(psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(psr[1][0], psr[1][1], psr[1][2]));
    
    /*position[0] = x;
    position[1] = y;
    position[2] = z;

    for(int i = 0; i < 8; i++)
    {
        vertices[i * 3] = (psrConst[i * 3] * scale[0]) + position[0];
        vertices[i * 3 + 1] = (psrConst[i * 3 + 1] * scale[1]) + position[1];
        vertices[i * 3 + 2] = (psrConst[i * 3 + 2] * scale[2]) + position[2];
    }

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);*/
}

void AWS::Aws_Cube::SetScale(float x, float y, float z)
{
    psr[1][0] = x;
    psr[1][1] = y;
    psr[1][2] = z;

    transform = glm::translate(glm::mat4(1.0), glm::vec3(psr[0][0], psr[0][1], psr[0][2]));
    transform = glm::rotate(transform, glm::radians(psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(psr[1][0], psr[1][1], psr[1][2]));
    
    /*scale[0] = x;
    scale[1] = y;
    scale[2] = z;

    for(int i = 0; i < 8; i++)
    {
        vertices[i * 3] = (psrConst[i * 3] * scale[0]) + position[0];
        vertices[i * 3 + 1] = (psrConst[i * 3 + 1] * scale[1]) + position[1];
        vertices[i * 3 + 2] = (psrConst[i * 3 + 2] * scale[2]) + position[2];
    }

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);*/
}

void AWS::Aws_Cube::SetRotation(float x, float y, float z)
{
    psr[2][0] = x;
    psr[2][1] = y;
    psr[2][2] = z;

    transform = glm::translate(glm::mat4(1.0), glm::vec3(psr[0][0], psr[0][1], psr[0][2]));
    transform = glm::rotate(transform, glm::radians(psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(psr[1][0], psr[1][1], psr[1][2]));
    
    /*rotation[0] = x;
    rotation[1] = y;
    rotation[2] = z;

    for(int i = 0; i < 8; i++)
    {
        vertices[i * 3] = (psrConst[i * 3] * scale[0]) + position[0];
        vertices[i * 3 + 1] = (psrConst[i * 3 + 1] * scale[1]) + position[1];
        vertices[i * 3 + 2] = (psrConst[i * 3 + 2] * scale[2]) + position[2];
    }

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);*/
}

void AWS::Aws_Cube::SetTexture(const std::string textureName, const int wrapping, const int textureType)
{
    vao.bind();

    tex.bind({textureName}, wrapping, textureType);

    vao.unbind();
}

void AWS::Aws_Cube::SetTexture(const std::vector<std::string> textureName, const int wrapping)
{
    vao.bind();

    tex.bind(textureName, wrapping, GL_TEXTURE_CUBE_MAP);

    vao.unbind();
}

void AWS::Aws_Cube::SetColor(const float r, const float g, const float b, const float a)
{
    for(int i = 0; i < 8; i++)
    {
        cbColor[i * 4] = r;
        cbColor[i * 4 + 1] = g;
        cbColor[i * 4 + 2] = b;
        cbColor[i * 4 + 3] = a;
    }

    vbo[1].bind(cbColor, sizeof(cbColor), 1, 4);
}

void AWS::Aws_Cube::terminate()
{
    vao.terminate();
    vbo->terminate();
    ebo.terminate();
    tex.terminate();
}