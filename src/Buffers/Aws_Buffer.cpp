#define GLEW_STATIC
#include <GL/glew.h>
#include <fstream>
#include "Aws_Buffer.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image/stb_image.h"

void AWS::Aws_VAO::create()
{
    glCreateVertexArrays(1, &ID);
}

void AWS::Aws_VAO::bind()
{
    glBindVertexArray(ID);
}

void AWS::Aws_VAO::unbind()
{
    glBindVertexArray(0);
}

void AWS::Aws_VAO::terminate()
{
    glDeleteVertexArrays(1, &ID);
}

void AWS::Aws_VBO::create()
{
    glCreateBuffers(1, &ID);
}

void AWS::Aws_VBO::bind(float* data, size_t dataSize, unsigned int index, unsigned short dimensions)
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(index, dimensions, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(index);
}

void AWS::Aws_VBO::terminate()
{
    glDeleteBuffers(1, &ID);
}

void AWS::Aws_EBO::create()
{
    glCreateBuffers(1, &ID);
}

void AWS::Aws_EBO::bind(unsigned int* data, size_t dataSize)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW);
}

void AWS::Aws_EBO::terminate()
{
    glDeleteBuffers(1, &ID);
}

void AWS::Aws_Shader::create(const std::string &vertexShader, const std::string &fragmentShader)
{
    std::ifstream f;

    f.open(vertexShader, std::ios::binary);

    if(f.bad())
    {
        vs = 0;
    }

    f.seekg(0, std::ios::end);

    int len = static_cast<int>(f.tellg());

    f.seekg(0, std::ios::beg);

    char* srcBufferVS = new char[(len + 1) * sizeof(char)];
    f.read(srcBufferVS, len);
    srcBufferVS[len] = '\0';
    f.close();

    vs = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vs, 1, const_cast<char**>(&srcBufferVS), NULL);

    delete[] srcBufferVS;

    glCompileShader(vs);

    f.open(fragmentShader, std::ios::binary);

    if(f.bad())
    {
        fs = 0;
    }

    f.seekg(0, std::ios::end);

    len = static_cast<int>(f.tellg());

    f.seekg(0, std::ios::beg);

    char* srcBufferFS = new char[(len + 1) * sizeof(char)];
    f.read(srcBufferFS, len);
    srcBufferFS[len] = '\0';
    f.close();

    fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fs, 1, const_cast<char**>(&srcBufferFS), NULL);

    delete[] srcBufferFS;

    glCompileShader(fs);

    ID = glCreateProgram();
    glAttachShader(ID, vs);
    glAttachShader(ID, fs);
    glLinkProgram(ID);
}

void AWS::Aws_Shader::bind()
{
    glUseProgram(ID);
}

void AWS::Aws_Shader::bind(const std::string &vertexShader, const std::string &fragmentShader)
{
    std::ifstream f;

    f.open(vertexShader, std::ios::binary);

    if(f.bad())
    {
        vs = 0;
    }

    f.seekg(0, std::ios::end);

    int len = static_cast<int>(f.tellg());

    f.seekg(0, std::ios::beg);

    char* srcBufferVS = new char[(len + 1) * sizeof(char)];
    f.read(srcBufferVS, len);
    srcBufferVS[len] = '\0';
    f.close();

    vs = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vs, 1, const_cast<char**>(&srcBufferVS), NULL);

    delete[] srcBufferVS;

    glCompileShader(vs);

    f.open(fragmentShader, std::ios::binary);

    if(f.bad())
    {
        fs = 0;
    }

    f.seekg(0, std::ios::end);

    len = static_cast<int>(f.tellg());

    f.seekg(0, std::ios::beg);

    char* srcBufferFS = new char[(len + 1) * sizeof(char)];
    f.read(srcBufferFS, len);
    srcBufferFS[len] = '\0';
    f.close();

    fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fs, 1, const_cast<char**>(&srcBufferFS), NULL);

    delete[] srcBufferFS;

    glCompileShader(fs);

    ID = glCreateProgram();
    glAttachShader(ID, vs);
    glAttachShader(ID, fs);
    glLinkProgram(ID);

    glUseProgram(ID);
}

void AWS::Aws_Shader::unbind()
{
    glUseProgram(0);
}

void AWS::Aws_Texture::create()
{
    glGenTextures(1, &ID);
}

void AWS::Aws_Texture::bind()
{
    glBindTexture(textureTypeL, ID);
}

void AWS::Aws_Texture::bind(const std::vector<std::string> path, int wrapping, int textureType)
{
    textureTypeL = textureType;

    if(textureTypeL == GL_TEXTURE_CUBE_MAP)
    {
        glBindTexture(textureTypeL, ID);

        for(int i = 0; i < path.size(); i++)
        {
            data = stbi_load(path[i].c_str(), &width, &height, &nrChannels, 0);
            if(data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Cube map tex fail" << path[i] << '\n';
                stbi_image_free(data);
            }
        }

        glTexParameteri(textureTypeL, GL_TEXTURE_WRAP_S, wrapping);
        glTexParameteri(textureTypeL, GL_TEXTURE_WRAP_T, wrapping);
        glTexParameteri(textureTypeL, GL_TEXTURE_WRAP_R, wrapping);
        glTexParameteri(textureTypeL, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(textureTypeL, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        glBindTexture(textureTypeL, ID);

        glTexParameteri(textureTypeL, GL_TEXTURE_WRAP_S, wrapping);
        glTexParameteri(textureTypeL, GL_TEXTURE_WRAP_T, wrapping);
        glTexParameteri(textureTypeL, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(textureTypeL, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(1);

        data = stbi_load(path[0].c_str(), &width, &height, &nrChannels, 0);
        if(data)
        {
            glTexImage2D(textureTypeL, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(textureTypeL);
        }
        else
        {
            std::cout << "Error loading image\n";
        }

        stbi_image_free(data);
    }
}

void AWS::Aws_Texture::unbind()
{
    glBindTexture(textureTypeL, 0);
}

void AWS::Aws_Texture::terminate()
{
    glDeleteTextures(1, &ID);
}