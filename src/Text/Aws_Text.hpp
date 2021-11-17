#pragma once

#include "../Buffers/Aws_Buffer.hpp"
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
        VBO vbo[3];
        EBO ebo;

        Texture tex;

        std::string textToRender;

        float* vertices;
        unsigned int* indices;
        float* textureCoords;

        const unsigned int cindices[2 * 3] = {
            0, 1, 2,
            1, 2, 3
        };

        float position[3] = { 0.0f, 0.0f, 0.0f};
        float scale[3] = { 1.0f, 1.0f, 1.0f};
        float rotation[3] = { 0.0f, 0.0f, 0.0f};

        const float ctextureCoords[2 * 4] = {
            1.0f, 1.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        };

        const float onePixel = 1.0f / 512.0f;

        float textColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};

        const float psrConst[3 * 4] = {
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f
        };

    public:
        /**
         * @brief create text object
         * 
         */
        void create();

        /**
         * @brief Set the Position object
         * 
         * @param x 
         * @param y 
         * @param z 
         */
        void SetPosition(float x, float y, float z);

        /**
         * @brief Set the Scale object
         * 
         * @param x 
         * @param y 
         * @param z 
         */
        void SetScale(float x, float y, float z);

        /**
         * @brief Set the Rotation object
         * 
         * @param x 
         * @param y 
         * @param z 
         */
        void SetRotation(float x, float y, float z);

        /**
         * @brief Set the Color object
         * 
         * @param r 
         * @param g 
         * @param b 
         * @param a 
         */
        void SetColor(const float r, const float g, const float b, const float a);

        /**
         * @brief change text
         * 
         * @param text 
         */
        void Text(const std::string text);

        /**
         * @brief draw
         * 
         * @param drawMode 
         */
        void draw();

        /**
         * @brief draw
         * 
         * @param drawMode 
         * @param camera 
         */
        void draw(glm::mat4x4 camera);
    };

    typedef Aws_TextRenderer TextRenderer;
}