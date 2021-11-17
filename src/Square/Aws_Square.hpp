#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include "../Buffers/Aws_Buffer.hpp"
#include "../Aws_Engine.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace AWS
{
    class Aws_Square
    {
    private:
        Shader sh;
        VAO vao;
        VBO vbo[3];
        EBO ebo;

        Texture tex;

        bool textureOn = false;

        float vertices[3 * 4] = {
            1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f
        };

        float position[3 * 4] = {
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f
        };

        float scale[3 * 4] = {
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f
        };

        float rotation[3 * 4] = {
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f
        };

        const float psrConst[3 * 4] = {
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f
        };

        unsigned int indices[3 * 2] = {
            0, 1, 2,
            1, 2, 3
        };

        float textureCoords[2 * 4] = {
            1.0f, 1.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        };

        float sqColor[4 * 4] = {
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f
        };

    public:
        /**
         * @brief create square
         * 
         * @param vertName 
         * @param fragName 
         */
        void create(const std::string &vertName = "data/shaders/color/colorVS.glsl", const std::string &fragName = "data/shaders/color/colorFS.glsl");

        /**
         * @brief create square
         * 
         * @param vertName 
         * @param fragName 
         */
        void create(const std::string textureName, const std::string &vertName, const std::string &fragName);

        /**
         * @brief draw square
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
        void SetColor(const float r, const float g, const float b, const float a);

        /**
         * @brief Get the Position object
         * 
         * @return float* 
         */
        float* GetPosition() { return position; }

        /**
         * @brief Get the Scale object
         * 
         * @return float* 
         */
        float* GetScale() { return scale; }

        /**
         * @brief Get the Rotation object
         * 
         * @return float* 
         */
        float* GetRotation() { return rotation; }

        /**
         * @brief Get the Indices object
         * 
         * @return unsigned* 
         */
        unsigned int* GetIndices() { return indices; }

        /**
         * @brief Get the Vertices Const object
         * 
         * @return const float* 
         */
        const float* GetVerticesConst() { return psrConst; }

        /**
         * @brief Get the Color object
         * 
         * @return float* 
         */
        float* GetColor() { return sqColor; }

        /**
         * @brief Get the Vertices object
         * 
         * @return float* 
         */
        float* GetVertices() { return vertices; }

        /**
         * @brief Get the Texturte Coords object
         * 
         * @return float* 
         */
        float* GetTexturteCoords() { return textureCoords; }

        /**
         * @brief delete square
         * 
         */
        void terminate();
    };

    typedef Aws_Square Square;
}