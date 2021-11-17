#pragma once

#include <iostream>
#include <vector>

namespace AWS
{
    class Aws_VAO
    {
    private:
        unsigned int ID;

    public:
        /**
         * @brief create VAO
         * 
         */
        void create();

        /**
         * @brief bind VAO
         * 
         */
        void bind();

        /**
         * @brief unbind VAO
         * 
         */
        void unbind();

        /**
         * @brief delete VAO
         * 
         */
        void terminate();

        /**
         * @brief Get VAO ID
         * 
         * @return unsigned int 
         */
        unsigned int GetID() { return ID; }
    };

    typedef Aws_VAO VAO;

    class Aws_VBO
    {
    private:
        unsigned int ID;

    public:
        /**
         * @brief create VBO
         * 
         */
        void create();

        /**
         * @brief bind VBO
         * 
         * @param data - table
         * @param dataSize - sizeof table
         * @param index - index in shader program
         * @param dimensions - dimensions ( 2 or 3 )
         */
        void bind(float* data, size_t dataSize, unsigned int index, unsigned short dimensions);

        /**
         * @brief delete VBO
         * 
         */
        void terminate();

        /**
         * @brief get VBO ID
         * 
         * @return unsigned int 
         */
        unsigned int GetID() { return ID; }
    };

    typedef Aws_VBO VBO;

    class Aws_EBO
    {
    private:
        unsigned int ID;

    public:
        /**
         * @brief create EBO
         * 
         */
        void create();

        /**
         * @brief bind EBO
         * 
         * @param data - table
         * @param dataSize - sizeof table
         */
        void bind(unsigned int* data, size_t dataSize);

        /**
         * @brief delete EBO
         * 
         */
        void terminate();

        /**
         * @brief get EBO ID
         * 
         * @return unsigned int 
         */
        unsigned int GetID() { return ID; }
    };

    typedef Aws_EBO EBO;

    class Aws_Shader
    {
    private:
        unsigned int ID, vs, fs;

    public:
        /**
         * @brief create shader
         * 
         * @param vertexShader - vertex shader path
         * @param fragmentShader - fragment shader path
         */
        void create(const std::string &vertexShader, const std::string &fragmentShader);

        /**
         * @brief bind shader program
         * 
         */
        void bind();

        /**
         * @brief 
         * 
         * @param vertexShader 
         * @param fragmentShader 
         */
        void bind(const std::string &vertexShader, const std::string &fragmentShader);

        /**
         * @brief unbind shader program
         * 
         */
        void unbind();

        /**
         * @brief get shader ID
         * 
         * @return unsigned int 
         */
        unsigned int GetID() { return ID; }
    };

    typedef Aws_Shader Shader;

    class Aws_Texture
    {
    private:
        int width, height, nrChannels, textureTypeL;

        unsigned int ID;

        unsigned char* data;
    
    public:
        /**
         * @brief create texture
         * 
         */
        void create();

        /**
         * @brief bind texture
         * 
         */
        void bind();

        /**
         * @brief bind texture and change it
         * 
         * @param path - path to texture
         * @param wrapping - GL_REPEAT
         */
        void bind(const std::vector<std::string> path, int wrapping, int textureType);

        /**
         * @brief unbind texture
         * 
         */
        void unbind();

        /**
         * @brief 
         * 
         * @return unsigned int 
         */
        unsigned int GetID() { return ID; }

        /**
         * @brief delete texture
         * 
         */
        void terminate();
    };

    typedef Aws_Texture Texture;
}