#pragma once

#include "../Square/Aws_Square.hpp"
#include "../Cube/Aws_Cube.hpp"
#include "../Buffers/Aws_Buffer.hpp"
#include <iostream>
#include <vector>

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

        std::vector <float*> vertices;
        std::vector <float*> texture;
        std::vector <float*> bcolor;
        std::vector <unsigned int*> indices;
        std::vector <size_t> index;

        std::string texturePath;

        bool binded = false;
        bool texBind;

    public:
        void create(const std::string texturePathC = "data/texture/dvd.png");
        void redisplay();
        void drawBROCube(int shaderType, std::vector<AWS::Aws_Cube> object, glm::mat4x4 camera);
        //void drawBROSquare(int shaderType, std::vector<AWS::Aws_Square> object, glm::mat4x4 camera);
        void terminate();
    };

    typedef Aws_BatchRenderer BatchRenderer;
    
} // namespace AWS
