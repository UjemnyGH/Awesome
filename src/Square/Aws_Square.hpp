#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include "../Buffers/Aws_Buffer.hpp"
#include "../Aws_Types.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * s_ - square variable
 * st_ -square table variable
 * sc_ scale const
 * sf_ - function variable
 * 
 */

namespace AWS
{
    class Aws_Square
    {
    private:
        Shader s_sh;
        VAO s_vao;
        VBO s_vbo[3];
        EBO s_ebo;

        Texture s_tex;

        bool s_textureOn = false;

        float st_vertices[3 * 4] = {
            1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f
        };

        glm::mat4 s_transform = glm::mat4(1.0f);

        float st_psr[3][3] = {
            {   0.0f, 0.0f, 0.0f    },
            {   1.0f, 1.0f, 1.0f    },
            {   0.0f, 0.0f, 0.0f    }
        };

        unsigned int st_indices[3 * 2] = {
            0, 1, 2,
            1, 2, 3
        };

        float st_textureCoords[2 * 4] = {
            1.0f, 1.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        };

        float st_color[4 * 4] = { 1.0f, 1.0f, 1.0f, 1.0f };

    public:
        /**
         * @brief Create square
         * 
         * @param sf_vertName vertex shader
         * @param sf_fragName fragment shader
         */
        void Create(const std::string &sf_vertName = "data/shaders/color/colorVS.glsl", const std::string &sf_fragName = "data/shaders/color/colorFS.glsl");

        /**
         * @brief Create square
         * 
         * @param sf_textureName path to folder with texture
         * @param sf_vertName vertex shader
         * @param sf_fragName fragment shader
         */
        void Create(const std::string sf_textureName, const std::string &sf_vertName, const std::string &sf_fragName);

        /**
         * @brief Draw square on screen
         * 
         * @param sf_drawMode drawing mode (GL_POINTS, GL_LINES, GL_TRIANGLES...)
         */
        void DrawSquare(const unsigned int &sf_drawMode);

        /**
         * @brief Draw square on screen
         * 
         * @param sf_drawMode drawing mode (GL_POINTS, GL_LINES, GL_TRIANGLES...)
         * @param sf_projection glm::perspective
         * @param sf_view glm::lookAt
         */
        void DrawSquare(const unsigned int &sf_drawMode, glm::mat4x4 sf_projection, glm::mat4x4 sf_view);

        /**
         * @brief Get the Position object
         * 
         * @return float* 
         */
        float* GetPosition() { return st_psr[0]; }

        /**
         * @brief Get the Scale object
         * 
         * @return float* 
         */
        float* GetScale() { return st_psr[1]; }

        /**
         * @brief Get the Rotation object
         * 
         * @return float* 
         */
        float* GetRotation() { return st_psr[2]; }

        /**
         * @brief Get the Shader I D object
         * 
         * @return unsigned int 
         */
        unsigned int GetShaderID() { return s_sh.GetID(); }

        /**
         * @brief Get the Indices object
         * 
         * @return unsigned* 
         */
        unsigned int* GetIndices() { return st_indices; }

        /**
         * @brief Get the Color object
         * 
         * @return float* 
         */
        float* GetColor() { return st_color; }

        /**
         * @brief Get the Vertices object
         * 
         * @return float* 
         */
        float* GetVertices() { return st_vertices; }

        /**
         * @brief Get the Texturte Coords object
         * 
         * @return float* 
         */
        float* GetTexturteCoords() { return st_textureCoords; }

        /**
         * @brief Set the Position object
         * 
         * @param sf_x X axis
         * @param sf_y y axis
         * @param sf_z Z axis
         */
        void SetPosition(float sf_x, float sf_y, float sf_z);

        /**
         * @brief Set the Scale object
         * 
         * @param sf_x X axis
         * @param sf_y y axis
         * @param sf_z Z axis
         */
        void SetScale(float sf_x, float sf_y, float sf_z);

        /**
         * @brief Set the Rotation object
         * 
         * @param sf_x X axis
         * @param sf_y y axis
         * @param sf_z Z axis
         */
        void SetRotation(float sf_x, float sf_y, float sf_z);

        /**
         * @brief Set the Texture object
         * 
         * @param sf_textureName path to floder with texture
         * @param sf_wrapping default is GL_REPEAT
         */
        void SetTexture(const std::string sf_textureName, const int sf_wrapping = GL_REPEAT);

        /**
         * @brief Set the Texture Coordinates object 
         * 
         * @param sf_x coordinates x
         * @param sf_y coordinates y
         */
        void SetTextureCoordinates(float sf_x, float sf_y);

        /**
         * @brief Set the Color object
         * 
         * @param r red
         * @param g green
         * @param b blue
         * @param a alpha
         */
        void SetColor(const float r, const float g, const float b, const float a);

        /**
         * @brief Terminate square
         * 
         */
        void Terminate();
    };

    void Aws_Square::Create(const std::string &sf_vertName, const std::string &sf_fragName)
    {
        s_textureOn = false;

        s_sh.create(sf_vertName, sf_fragName);

        s_vao.create();
        s_vao.bind();

        s_vbo[0].create();
        s_vbo[0].bind(st_vertices, sizeof(st_vertices), 0, 3);

        s_vbo[1].create();
        s_vbo[1].bind(st_color, sizeof(st_color), 1, 4);

        s_ebo.create();
        s_ebo.bind(st_indices, sizeof(st_indices));

        s_vao.unbind();
    }

    void Aws_Square::Create(const std::string sf_textureName, const std::string &sf_vertName, const std::string &sf_fragName)
    {
        s_textureOn = true;

        s_sh.create(sf_vertName, sf_fragName);

        s_vao.create();
        s_vao.bind();

        s_vbo[0].create();
        s_vbo[0].bind(st_vertices, sizeof(st_vertices), 0, 3);

        s_vbo[1].create();
        s_vbo[1].bind(st_color, sizeof(st_color), 1, 4);

        s_vbo[2].create();
        s_vbo[2].bind(st_textureCoords, sizeof(st_textureCoords), 2, 2);
    
        s_ebo.create();
        s_ebo.bind(st_indices, sizeof(st_indices));

        s_tex.create();
        s_tex.bind({sf_textureName}, GL_REPEAT, GL_TEXTURE_2D);

        s_sh.bind();

        glUniform4f(glGetUniformLocation(s_sh.GetID(), "iCol"), 1.0f, 1.0f, 1.0f, 1.0f);
        glUniform1i(glGetUniformLocation(s_sh.GetID(), "tex"), 0);

        s_sh.unbind();

        s_vao.unbind();
    }

    void Aws_Square::DrawSquare(const unsigned int &sf_drawMode)
    {  
        s_sh.bind();
        s_vao.bind();
        if(s_textureOn)
        {
            s_tex.bind();
        }

        glUniformMatrix4fv(glGetUniformLocation(s_sh.GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(s_transform));

        glDrawElements(sf_drawMode, 6, GL_UNSIGNED_INT, NULL);

        s_sh.unbind();
        s_vao.unbind();
    }

    void Aws_Square::DrawSquare(const unsigned int &sf_drawMode, glm::mat4x4 projection, glm::mat4x4 view)
    {
        s_sh.bind();
        s_vao.bind();
        if(s_textureOn)
        {
            s_tex.bind();
        }

        glUniformMatrix4fv(glGetUniformLocation(s_sh.GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(projection * view * s_transform));

        glDrawElements(sf_drawMode, sizeof(st_vertices) / 4, GL_UNSIGNED_INT, NULL);

        s_sh.unbind();
        s_vao.unbind();
    }

    void Aws_Square::SetPosition(float sf_x, float sf_y, float sf_z)
    {
        st_psr[0][0] = sf_x;
        st_psr[0][1] = sf_y;
        st_psr[0][2] = sf_z;

        s_transform = glm::translate(glm::mat4(1.0), glm::vec3(st_psr[0][0], st_psr[0][1], st_psr[0][2]));
        s_transform = glm::rotate(s_transform, glm::radians(st_psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
        s_transform = glm::rotate(s_transform, glm::radians(st_psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
        s_transform = glm::rotate(s_transform, glm::radians(st_psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
        s_transform = glm::scale(s_transform, glm::vec3(st_psr[1][0], st_psr[1][1], st_psr[1][2]));
    }

    void Aws_Square::SetScale(float sf_x, float sf_y, float sf_z)
    {
        st_psr[1][0] = sf_x;
        st_psr[1][1] = sf_y;
        st_psr[1][2] = sf_z;

        s_transform = glm::translate(glm::mat4(1.0), glm::vec3(st_psr[0][0], st_psr[0][1], st_psr[0][2]));
        s_transform = glm::rotate(s_transform, glm::radians(st_psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
        s_transform = glm::rotate(s_transform, glm::radians(st_psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
        s_transform = glm::rotate(s_transform, glm::radians(st_psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
        s_transform = glm::scale(s_transform, glm::vec3(st_psr[1][0], st_psr[1][1], st_psr[1][2]));
    }

    void Aws_Square::SetRotation(float sf_x, float sf_y, float sf_z)
    {
        st_psr[2][0] = sf_x;
        st_psr[2][1] = sf_y;
        st_psr[2][2] = sf_z;

        s_transform = glm::translate(glm::mat4(1.0), glm::vec3(st_psr[0][0], st_psr[0][1], st_psr[0][2]));
        s_transform = glm::rotate(s_transform, glm::radians(st_psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
        s_transform = glm::rotate(s_transform, glm::radians(st_psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
        s_transform = glm::rotate(s_transform, glm::radians(st_psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
        s_transform = glm::scale(s_transform, glm::vec3(st_psr[1][0], st_psr[1][1], st_psr[1][2]));
    }

    void Aws_Square::SetTexture(const std::string st_textureName, const int wrapping)
    {
        s_vao.bind();

        s_tex.bind({st_textureName}, wrapping, GL_TEXTURE_2D);

        s_vao.unbind();
    }

    void Aws_Square::SetTextureCoordinates(float sf_x, float sf_y)
    {
        st_textureCoords[0] = sf_x;
        st_textureCoords[1] = sf_y;
        st_textureCoords[3] = sf_y;
        st_textureCoords[4] = sf_x;

        s_vbo[2].bind(st_textureCoords, sizeof(st_textureCoords), 2, 2);
    }

    void Aws_Square::SetColor(const float r, const float g, const float b, const float a)
    {
        s_sh.bind();
        s_vao.bind();

        glUniform4f(glGetUniformLocation(s_sh.GetID(), "iCol"), r, g, b, a);

        s_vao.unbind();
        s_sh.unbind();
    }

    void Aws_Square::Terminate()
    {
        s_vao.terminate();
        s_vbo->terminate();
        s_ebo.terminate();
        s_tex.terminate();
    }

    typedef Aws_Square Square;
}