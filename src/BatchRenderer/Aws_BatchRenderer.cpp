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

template<class T>
void AWS::Aws_BatchRenderer::drawBRO(int shaderType, std::vector<T> object, glm::mat4 projection, glm::mat4 view)
{
    if(!binded)
    {
        if(shaderType == ShaderType::colorShader)
        {
            texBind = false;
            sh.bind(AWS::colorVS, AWS::colorFS);

            for(int i = 0; i < object.size(); i++)
            {
                for(int j = 0; j < sizeof(object[0].GetVertices()) / 2; j++)
                {
                    vertices[j * 3] = object[i].GetVertices()[j * 3];
                    vertices[j * 3 + 1] = object[i].GetVertices()[j * 3 + 1];
                    vertices[j * 3 + 2] = object[i].GetVertices()[j * 3 + 2];
                }

                for(int j = 0; j < sizeof(object[0].GetIndices()) / 4; j++)
                {
                    indices[j * 3] = object[i].GetIndices()[j * 3];
                    indices[j * 3 + 1] = object[i].GetIndices()[j * 3 + 1];
                    indices[j * 3 + 2] = object[i].GetIndices()[j * 3 + 2];
                }

                for(int j = 0; j < sizeof(object[0].GetTexturteCoords()) / 2; j++)
                {
                    texture[j * 2] = object[i].GetTexturteCoords()[j * 2];
                    texture[j * 2 + 1] = object[i].GetTexturteCoords()[j * 2 + 1];
                }

                for(int j = 0; j < sizeof(object[0].GetColor()) / 2; j++)
                {
                    bcolor[j * 4] = object[i].GetColor()[j * 4];
                    bcolor[j * 4 + 1] = object[i].GetColor()[j * 4 + 1];
                    bcolor[j * 4 + 2] = object[i].GetColor()[j * 4 + 1];
                    bcolor[j * 4 + 3] = object[i].GetColor()[j * 4 + 1];
                }
            }
        }
        else if(shaderType == ShaderType::textureShader)
        {
            texBind = true;
            sh.bind(AWS::textureVS, AWS::textureFS);

            for(int i = 0; i < object.size(); i++)
            {
                for(int j = 0; j < sizeof(object[0].GetVertices()) / 2; j++)
                {
                    vertices[j * 3] = object[i].GetVertices()[j * 3];
                    vertices[j * 3 + 1] = object[i].GetVertices()[j * 3 + 1];
                    vertices[j * 3 + 2] = object[i].GetVertices()[j * 3 + 2];
                }

                for(int j = 0; j < sizeof(object[0].GetIndices()) / 4; j++)
                {
                    indices[j * 3] = object[i].GetIndices()[j * 3];
                    indices[j * 3 + 1] = object[i].GetIndices()[j * 3 + 1];
                    indices[j * 3 + 2] = object[i].GetIndices()[j * 3 + 2];
                }

                for(int j = 0; j < sizeof(object[0].GetTexturteCoords()) / 2; j++)
                {
                    texture[j * 2] = object[i].GetTexturteCoords()[j * 2];
                    texture[j * 2 + 1] = object[i].GetTexturteCoords()[j * 2 + 1];
                }

                for(int j = 0; j < sizeof(object[0].GetColor()) / 2; j++)
                {
                    bcolor[j * 4] = object[i].GetColor()[j * 4];
                    bcolor[j * 4 + 1] = object[i].GetColor()[j * 4 + 1];
                    bcolor[j * 4 + 2] = object[i].GetColor()[j * 4 + 1];
                    bcolor[j * 4 + 3] = object[i].GetColor()[j * 4 + 1];
                }
            }
        }
        vao.bind();
        vbo[0].bind(vertices, sizeof(vertices), 0, 3); 
        vbo[1].bind(bcolor, sizeof(bcolor), 1, 3); 
        vbo[2].bind(texture, sizeof(texture), 2, 2);

        ebo.bind(indices, sizeof(indices));
        vao.unbind();

        binded = true;
    }

    vao.bind();
    sh.bind();
    if(texBind)
        tex.bind();

    glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(projection * transform * view));

    glDrawElements(GL_TRIANGLES, object.size() * 4, GL_UNSIGNED_INT, NULL);

    vao.unbind();
    sh.unbind();
}

void AWS::Aws_BatchRenderer::terminate()
{
    vao.terminate();
    vbo->terminate();
    ebo.terminate();
    tex.terminate();
}