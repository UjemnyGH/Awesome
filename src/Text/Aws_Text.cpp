#include "Aws_Text.hpp"
#include "../Aws_Engine.hpp"

void AWS::Aws_TextRenderer::create()
{
    sh.create(AWS::textureVS, AWS::textureFS);

    vao.create();
    vao.bind();

    vbo->create();

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);
    vbo[1].bind(textureCoords, sizeof(textureCoords), 2, 2);

    tex.create();
    tex.bind({"data/texture/textAtlas.png"}, GL_REPEAT, GL_TEXTURE_2D);

    ebo.create();
    ebo.bind(indices, sizeof(indices));

    sh.bind();

    glUniform1i(glGetUniformLocation(sh.GetID(), "tex"), 0);

    sh.unbind();

    vao.unbind();
}

void AWS::Aws_TextRenderer::SetPosition(float x, float y, float z)
{
    position[0] = x;
    position[1] = y;
    position[2] = z;

    for(int text = 0; text < textToRender.length(); text++)
    {
        for(int i = 0; i < 4; i++)
        {
            vertices[i * 3] = psrConst[i * 3] * scale[0] + position[0] + (position[0] * text);
            vertices[i * 3 + 1] = psrConst[i * 3 + 1] * scale[1] + position[1];
            vertices[i * 3 + 2] = psrConst[i * 3 + 2] * scale[2] + position[2];
        }

        for(int i = 0; i < 4; i++)
        {
            textureCoords[i * 2] = ctextureCoords[i * 2] + (onePixel * 32.0f) * (int)textToRender[text];

            if(textureCoords[i * 2] > 1.0f)
            {
                textureCoords[i * 2 + 1] = textureCoords[i * 2] / 512.0 * (onePixel * 32.0f);
            }
        }

        for(int i = 0; i < 2; i++)
        {
            indices[i * 3] = cindices[i * 3] + 4 * text;
            indices[i * 3 + 1] = cindices[i * 3 + 1] + 4 * text;
            indices[i * 3 + 2] = cindices[i * 3 + 2] + 4 * text;
        }
    }

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);
    vbo[1].bind(textureCoords, sizeof(textureCoords), 2, 2);
    ebo.bind(indices, sizeof(indices));
}

void AWS::Aws_TextRenderer::SetScale(float x, float y, float z)
{
    scale[0] = x;
    scale[1] = y;
    scale[2] = z;

    for(int text = 0; text < textToRender.length(); text++)
    {
        for(int i = 0; i < 4; i++)
        {
            vertices[i * 3] = psrConst[i * 3] * scale[0] + position[0] + (position[0] * text);
            vertices[i * 3 + 1] = psrConst[i * 3 + 1] * scale[1] + position[1];
            vertices[i * 3 + 2] = psrConst[i * 3 + 2] * scale[2] + position[2];
        }

        for(int i = 0; i < 4; i++)
        {
            textureCoords[i * 2] = ctextureCoords[i * 2] + (onePixel * 32.0f) * (int)textToRender[text];

            if(textureCoords[i * 2] > 1.0f)
            {
                textureCoords[i * 2 + 1] = textureCoords[i * 2] / 512.0 * (onePixel * 32.0f);
            }
        }

        for(int i = 0; i < 2; i++)
        {
            indices[i * 3] = cindices[i * 3] + 4 * text;
            indices[i * 3 + 1] = cindices[i * 3 + 1] + 4 * text;
            indices[i * 3 + 2] = cindices[i * 3 + 2] + 4 * text;
        }
    }

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);
    vbo[1].bind(textureCoords, sizeof(textureCoords), 2, 2);
    ebo.bind(indices, sizeof(indices));
}

void AWS::Aws_TextRenderer::SetRotation(float x, float y, float z)
{
    rotation[0] = x;
    rotation[1] = y;
    rotation[2] = z;

    for(int text = 0; text < textToRender.length(); text++)
    {
        for(int i = 0; i < 4; i++)
        {
            vertices[i * 3] = psrConst[i * 3] * scale[0] + position[0] + (position[0] * text);
            vertices[i * 3 + 1] = psrConst[i * 3 + 1] * scale[1] + position[1];
            vertices[i * 3 + 2] = psrConst[i * 3 + 2] * scale[2] + position[2];
        }

        for(int i = 0; i < 4; i++)
        {
            textureCoords[i * 2] = ctextureCoords[i * 2] + (onePixel * 32.0f) * (int)textToRender[text];

            if(textureCoords[i * 2] > 1.0f)
            {
                textureCoords[i * 2 + 1] = textureCoords[i * 2] / 512.0 * (onePixel * 32.0f);
            }
        }

        for(int i = 0; i < 2; i++)
        {
            indices[i * 3] = cindices[i * 3] + 4 * text;
            indices[i * 3 + 1] = cindices[i * 3 + 1] + 4 * text;
            indices[i * 3 + 2] = cindices[i * 3 + 2] + 4 * text;
        }
    }

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);
    vbo[1].bind(textureCoords, sizeof(textureCoords), 2, 2);
    ebo.bind(indices, sizeof(indices));
}

void AWS::Aws_TextRenderer::SetColor(const float r, const float g, const float b, const float a)
{
    textColor[0] = r;
    textColor[1] = g;
    textColor[2] = b;
    textColor[3] = a;

    float textColorV[4 * 4] = {
        textColor[0], textColor[1], textColor[2], textColor[3],
        textColor[0], textColor[1], textColor[2], textColor[3],
        textColor[0], textColor[1], textColor[2], textColor[3],
        textColor[0], textColor[1], textColor[2], textColor[3]
    };

    vbo[2].bind(textColorV, sizeof(textColorV), 1, 4);
}

void AWS::Aws_TextRenderer::Text(const std::string text)
{
    textToRender = text;

    for(int text = 0; text < textToRender.length(); text++)
    {
        for(int i = 0; i < 4; i++)
        {
            vertices[i * 3] = psrConst[i * 3] * scale[0] + position[0] + (position[0] * text);
            vertices[i * 3 + 1] = psrConst[i * 3 + 1] * scale[1] + position[1];
            vertices[i * 3 + 2] = psrConst[i * 3 + 2] * scale[2] + position[2];
        }

        for(int i = 0; i < 4; i++)
        {
            textureCoords[i * 2] = ctextureCoords[i * 2] + (onePixel * 32.0f) * (int)textToRender[text];

            if(textureCoords[i * 2] > 1.0f)
            {
                textureCoords[i * 2 + 1] = textureCoords[i * 2] / 512.0 * (onePixel * 32.0f);
            }
        }

        for(int i = 0; i < 2; i++)
        {
            indices[i * 3] = cindices[i * 3] + 4 * text;
            indices[i * 3 + 1] = cindices[i * 3 + 1] + 4 * text;
            indices[i * 3 + 2] = cindices[i * 3 + 2] + 4 * text;
        }
    }

    vbo[0].bind(vertices, sizeof(vertices), 0, 3);
    vbo[1].bind(textureCoords, sizeof(textureCoords), 2, 2);
    ebo.bind(indices, sizeof(indices));
}

void AWS::Aws_TextRenderer::draw()
{
    vao.bind();
    sh.bind();
    tex.bind();

    glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "camera"), 1, GL_FALSE, glm::value_ptr(glm::mat4x4(1.0)));

    glDrawElements(GL_TRIANGLES, sizeof(vertices) / 2, GL_UNSIGNED_INT, NULL);

    sh.unbind();
    vao.unbind();
}

void AWS::Aws_TextRenderer::draw(glm::mat4x4 camera)
{
    vao.bind();
    sh.bind();
    tex.bind();

    glUniformMatrix4fv(glGetUniformLocation(sh.GetID(), "camera"), 1, GL_FALSE, glm::value_ptr(camera));

    glDrawElements(GL_TRIANGLES, sizeof(vertices) / 2, GL_UNSIGNED_INT, NULL);

    sh.unbind();
    vao.unbind();
}