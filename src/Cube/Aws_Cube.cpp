#include "Aws_Cube.hpp"

void AWS::Aws_Cube::create(const int shadeType, const std::string &vertName, const std::string &fragName)
{
    texturesOn = false;
    cshadeType = shadeType;

    sh.create(vertName, fragName);

    vao.create();
    vao.bind();

    vbo[0].create();
    vbo[0].bind(vertices, sizeof(vertices), 0, 3);

    if(cshadeType == solid)
    {
        vbo[1].create();
        vbo[1].bind(cbColor, sizeof(cbColor), 1, 4);
    }
    else if(cshadeType == shade)
    {
        vbo[3].create();
        vbo[3].bind(normals, sizeof(normals), 3, 3);
    }

    ebo.create();
    ebo.bind(indices, sizeof(indices));

    vao.unbind();
}

void AWS::Aws_Cube::create(const int shadeType, const std::string textureName, const int textureType, const std::string &vertName, const std::string &fragName)
{
    texturesOn = true;

    cshadeType = shadeType;

    sh.create(vertName, fragName);

    vao.create();
    vao.bind();

    vbo[0].create();
    vbo[0].bind(vertices, sizeof(vertices), 0, 3);

    if(cshadeType == solid)
    {
        vbo[1].create();
        vbo[1].bind(cbColor, sizeof(cbColor), 1, 4);
    }
    else if(cshadeType == shade)
    {
        vbo[3].create();
        vbo[3].bind(normals, sizeof(normals), 3, 3);
    }

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

void AWS::Aws_Cube::create(const int shadeType, const std::vector<std::string> textureName, const std::string &vertName, const std::string &fragName)
{
    texturesOn = true;
    cshadeType = shadeType;

    sh.create(vertName, fragName);

    vao.create();
    vao.bind();

    vbo[0].create();
    vbo[0].bind(vertices, sizeof(vertices), 0, 3);

    if(cshadeType == solid)
    {
        vbo[1].create();
        vbo[1].bind(cbColor, sizeof(cbColor), 1, 4);
    }
    else if(cshadeType == shade)
    {
        vbo[3].create();
        vbo[3].bind(normals, sizeof(normals), 3, 3);
    }

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

    if(cshadeType == solid)
    {
        glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(transform));
    }
    else if(cshadeType == shade)
    {
        glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "projectionTransform"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));
        glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "viewTransform"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));
        glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "modelTransform"), 1, GL_FALSE, glm::value_ptr(transform));
    }

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

    if(cshadeType == solid)
    {
        glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(projection * view * transform));
    }
    else if(cshadeType == shade)
    {
        glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "projectionTransform"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "viewTransform"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "modelTransform"), 1, GL_FALSE, glm::value_ptr(transform));
    }

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
    if(cshadeType == solid)
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
    else if(cshadeType == shade)
    {
        sh.bind();

        glUniform3f(glGetUniformLocation(sh.GetID(), "objectColor"), r, g, b);
        glUniform1f(glGetUniformLocation(sh.GetID(), "alpha"), a);

        sh.unbind();
    }
}

void AWS::Aws_Cube::SetLightColor(const float r, const float g, const float b)
{
    if(cshadeType == shade)
    {
        sh.bind();

        glUniform3f(glGetUniformLocation(sh.GetID(), "lightColor"), r, g, b);

        sh.unbind();
    }
}

void AWS::Aws_Cube::SetLightPosition(const float x, const float y, const float z)
{
    if(cshadeType == shade)
    {
        sh.bind();

        glUniform3f(glGetUniformLocation(sh.GetID(), "lightPos"), x, y, z);

        sh.unbind();
    }
}

void AWS::Aws_Cube::SetCameraPosition(const float x, const float y, const float z)
{
    if(cshadeType == shade)
    {
        sh.bind();

        glUniform3f(glGetUniformLocation(sh.GetID(), "viewPos"), x, y, z);

        sh.unbind();
    }
}

void AWS::Aws_Cube::SetAmbientSpecular(const float ambient, const float specular)
{
    if(cshadeType == shade)
    {
        sh.bind();

        glUniform1f(glGetUniformLocation(sh.GetID(), "ambientStr"), ambient);
        glUniform1f(glGetUniformLocation(sh.GetID(), "specularStr"), specular);

        sh.unbind();
    }
}

void AWS::Aws_Cube::terminate()
{
    vao.terminate();
    vbo->terminate();
    ebo.terminate();
    tex.terminate();
}