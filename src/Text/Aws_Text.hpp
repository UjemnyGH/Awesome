#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include "../Buffers/Aws_Buffer.hpp"
#include "../stb_image/stb_easy_font.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

namespace AWS
{
    class Aws_TextRenderer
    {
    private:
        Shader sh;
        VAO vao;

    public:
        void Create();
        void DrawText(float tr_x, float tr_y, char* tr_text, float tr_r, float tr_g, float tr_b);
        void DrawText(float tr_x, float tr_y, char* tr_text, float tr_r, float tr_g, float tr_b, const glm::mat4 & tr_projection, const glm::mat4 & view);
    };

    void Aws_TextRenderer::Create()
    {
        sh.create(AWS::colorVS, AWS::colorFS);

        vao.create();
        vao.bind();

        vao.unbind();
    }

    void Aws_TextRenderer::DrawText(float tr_x, float tr_y, char* tr_text, float tr_r, float tr_g, float tr_b)
    {
        static char t_buffer[99999];
        int num_triangles;

        num_triangles = stb_easy_font_print(tr_x, tr_y, tr_text, NULL, t_buffer, sizeof(t_buffer));

        vao.bind();
        sh.bind();

        glUniform4f(glGetUniformLocation(sh.GetID(), "iCol"), tr_r, tr_g, tr_b, 1.0f);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 16, t_buffer);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_TRIANGLES, 0, num_triangles * 3);

        sh.unbind();
        vao.unbind();
        
    }

    typedef Aws_TextRenderer TextRenderer;
}