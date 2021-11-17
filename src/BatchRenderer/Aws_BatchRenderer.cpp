#include "Aws_BatchRenderer.hpp"

void AWS::Aws_BatchRenderer::create(const std::string texturePathC)
{
    texturePath = texturePathC;

    sh.create(AWS::colorVS, AWS::colorFS);

    vao.create();

    vbo->create();

    ebo.create();

    tex.create();
    tex.bind({texturePath}, GL_REPEAT, GL_TEXTURE_2D);
}

void AWS::Aws_BatchRenderer::redisplay()
{
    binded = false;
}

void AWS::Aws_BatchRenderer::drawBROCube(int shaderType, std::vector<AWS::Aws_Cube> object, glm::mat4x4 camera)
{
    if(!binded)
    {
        if(shaderType == ShaderType::colorShader)
        {
            texBind = false;
            sh.bind(AWS::colorVS, AWS::colorFS);

            for(int i = 0; i < object.size(); i++)
            {
                vertices[i] = object[i].GetVertices();
                indices[i] = object[i].GetIndices();
                bcolor[i] = object[i].GetColor();

                index[i] = i;
            }
        }
        else if(shaderType == ShaderType::textureShader)
        {
            texBind = true;
            sh.bind(AWS::textureVS, AWS::textureFS);

            for(int i = 0; i < object.size(); i++)
            {
                vertices[i] = object[i].GetVertices();
                indices[i] = object[i].GetIndices();
                texture[i] = object[i].GetTexturteCoords();
                bcolor[i] = object[i].GetColor();

                index[i] = i;
            }
        }
        vao.bind();
        vbo[0].bind(*vertices.data(), vertices.size() * sizeof(float), 0, 3); 
        vbo[1].bind(*bcolor.data(), bcolor.size() * sizeof(float), 1, 3); 
        vbo[2].bind(*texture.data(), texture.size() * sizeof(float), 2, 2);

        ebo.bind(*indices.data(), indices.size() * sizeof(unsigned int));
        vao.unbind();

        binded = true;
    }

    vao.bind();
    sh.bind();
    if(texBind)
        tex.bind();

    glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "camera"), 1, GL_FALSE, glm::value_ptr(camera));

    glDrawElements(GL_TRIANGLES, object.size() * 4, GL_UNSIGNED_INT, NULL);

    vao.unbind();
    sh.unbind();
}

/*void AWS::Aws_BatchRenderer::drawBROSquare(int shaderType, std::vector<AWS::Aws_Square> object, glm::mat4x4 camera)
{
    if(!binded)
    {
        if(shaderType == ShaderType::colorShader)
        {
            texBind = false;
            sh.bind(AWS::colorVS, AWS::colorFS);

            for(int i = 0; i < object.size(); i++)
            {
                vertices[i] = object[i].GetVertices();
                indices[i] = object[i].GetIndices();
                bcolor[i] = object[i].GetColor();

                index[i] = i;
            }
        }
        else if(shaderType == ShaderType::textureShader)
        {
            texBind = true;
            sh.bind(AWS::textureVS, AWS::textureFS);

            for(int i = 0; i < object.size(); i++)
            {
                vertices[i] = object[i].GetVertices();
                indices[i] = object[i].GetIndices();
                texture[i] = object[i].GetTexturteCoords();
                bcolor[i] = object[i].GetColor();

                index[i] = i;
            }
        }
        vao.bind();
        vbo[0].bind(*vertices.data(), vertices.size() * sizeof(float), 0, 3); 
        vbo[1].bind(*bcolor.data(), bcolor.size() * sizeof(float), 1, 3); 
        vbo[2].bind(*texture.data(), texture.size() * sizeof(float), 2, 2);

        ebo.bind(*indices.data(), indices.size() * sizeof(unsigned int));
        vao.unbind();

        binded = true;
    }

    vao.bind();
    sh.bind();
    if(texBind)
        tex.bind();

    glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "camera"), 1, GL_FALSE, glm::value_ptr(camera));

    glDrawElements(GL_TRIANGLES, object.size() * 4, GL_UNSIGNED_INT, NULL);

    vao.unbind();
    sh.unbind();
}*/

void AWS::Aws_BatchRenderer::terminate()
{
    vao.terminate();
    vbo->terminate();
    ebo.terminate();
    tex.terminate();
}