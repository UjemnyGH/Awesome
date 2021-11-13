#include "Aws_Cube.hpp"

void AWS::Aws_Cube::create(const std::string &vertName, const std::string &fragName)
{
    texturesOn = false;

    sh.create(vertName, fragName);
}

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