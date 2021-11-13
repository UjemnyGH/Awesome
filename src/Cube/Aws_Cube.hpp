#pragma once

#include "../Buffers/Aws_Buffer.hpp"
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>

namespace AWS
{
    class Aws_Cube
    {
    private:
        Shader sh;
        VAO vao;
        VBO vbo[3];
        EBO ebo;

        Texture tex;

        bool texturesOn = false;

        float vertices[3 * 8] = {
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f
        };

        float position[3 * 8] = {
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f
        };

        float scale[3 * 8] = {
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f
        };

        float rotation[3 * 8] = {
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f
        };

        const float psrConst[3 * 8] = {
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f
        };

        unsigned int indices[3 * 12] = {
            0, 1, 2,
            1, 2, 3,
            4, 5, 6,
            5, 6, 7,
            0, 2, 4,
            2, 4, 6,
            1, 3, 5,
            3, 5, 7,
            0, 1, 4,
            1, 4, 5,
            2, 3, 6,
            3, 6, 7
        };

        float texture[2 * 16] = {
            0.375f, 0.0f,
            0.625f, 0.0f,
            0.625f, 0.25f,
            0.375f, 0.25f,
            0.625f, 0.5f,
            0.375f, 0.5f,
            0.625f, 0.75f,
            0.375f, 0.75f,
            0.625f, 1.0f,
            0.375f, 1.0f,
            0.125f, 0.50f,
            0.125f, 0.75f,
            0.875f, 0.5f,
            0.875f, 0.75f
        };

        float cbColor[3 * 8] = {
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f
        };

    public:
        /**
         * @brief create square
         * 
         * @param vertName 
         * @param fragName 
         */
        void create(const std::string &vertName, const std::string &fragName);

        /**
         * @brief create square
         * 
         * @param vertName 
         * @param fragName 
         */
        void create(const std::string &vertName, const std::string &fragName, const std::string textureName);

        /**
         * @brief draw square
         * 
         * @param drawMode 
         */
        void draw(const unsigned int &drawMode);

        /**
         * @brief set position scale and rotation
         * 
         * @param px 
         * @param py 
         * @param pz 
         * @param sx 
         * @param sy 
         * @param sz 
         * @param rx 
         * @param ry 
         * @param rz 
         */
        void SetPSR(float px, float py, float pz, float sx, float sy, float sz, float rx, float ry, float rz);

        /**
         * @brief Set the Texture object
         * 
         * @param textureName 
         * @param wrapping 
         */
        void SetTexture(const std::string textureName, const int wrapping);

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
         * @param color 
         */
        void SetColor(const float r, const float g, const float b);

        /**
         * @brief delete square
         * 
         */
        void terminate();
    };

    typedef Aws_Cube Cube;
}