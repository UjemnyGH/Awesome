#pragma once

#include "../Buffers/Aws_Buffer.hpp"
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

namespace AWS
{
    enum CubeTexturing
    {
        cubemap = GL_TEXTURE_CUBE_MAP,
        texture2D = GL_TEXTURE_2D
    };

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

        float position[3] = {
            0.0f, 0.0f, 0.0f,
        };

        float scale[3] = {
            1.0f, 1.0f, 1.0f,
        };

        float rotation[3] = {
            1.0f, 1.0f, 1.0f
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

        float texture[2 * 8] = {
            1.0f, 1.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,

            1.0f, 1.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        };

        float cubemapTexture[3 * 36] = {
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
        };

        float cbColor[4 * 8] = {
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f
        };

    public:
        /**
         * @brief create cube
         * 
         * @param vertName 
         * @param fragName 
         */
        void create(const std::string &vertName = "data/shaders/color/colorVS.glsl", const std::string &fragName = "data/shaders/color/colorFS.glsl");

        /**
         * @brief create cube
         * 
         * @param vertName 
         * @param fragName
         * @param textureType
         */
        void create(const std::string textureName, const int textureType = GL_TEXTURE_2D, const std::string &vertName = "data/shaders/texture/textureVS.glsl", const std::string &fragName = "data/shaders/texture/textureFS.glsl");

        /**
         * @brief create cube
         * 
         * @param vertName 
         * @param fragName 
         * @param textureName 
         */
        void create(const std::vector<std::string> textureName, const std::string &vertName = "data/shaders/cube/cubeVS.glsl", const std::string &fragName = "data/shaders/cube/cubeFS.glsl");

        /**
         * @brief draw cube
         * 
         * @param drawMode 
         */
        void draw(const unsigned int &drawMode);

        /**
         * @brief 
         * 
         * @param drawMode 
         * @param camera 
         */
        void draw(const unsigned int &drawMode, glm::mat4x4 camera);

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
         * @param textureType
         */
        void SetTexture(const std::string textureName, const int wrapping, const int textureType);

        /**
         * @brief Set the Texture object
         * 
         * @param textureName 
         * @param wrapping 
         */
        void SetTexture(const std::vector<std::string> textureName, const int wrapping);

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
        void SetColor(const float r, const float g, const float b, float a);

        /**
         * @brief delete cube
         * 
         */
        void terminate();
    };

    typedef Aws_Cube Cube;
}