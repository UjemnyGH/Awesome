#pragma once

#include "../Square/Aws_Square.hpp"
#include "../Cube/Aws_Cube.hpp"
#include "../Buffers/Aws_Buffer.hpp"
#include <iostream>

namespace AWS
{
    enum ShaderType
    {
        colorShader = 0,
        textureShader = 1,
        cubemapShader = 2
    };

    class Aws_BatchRenderer
    {
    private:
        VAO vao;
        VBO vbo[3];
        EBO ebo;
        Shader sh;

        Texture tex;

        glm::mat4* transform;

        float* vertices;
        float* texture;
        float* bcolor;
        unsigned int* indices;

        std::string texturePath;

        bool binded = false;
        bool texBind;

    public:
        void create(const std::string texturePathC);
        void redisplay();
        template<class T>
        void drawBRO(int shaderType, std::vector<T> object, glm::mat4 projection, glm::mat4 view);
        void terminate();
    };

    typedef Aws_BatchRenderer BatchRenderer;
    
} // namespace AWS
