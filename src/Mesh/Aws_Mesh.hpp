#pragma once

#include "../Buffers/Aws_Buffer.hpp"
#include "../Aws_Types.hpp"
#include "../Aws_Engine.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

/**
 * m_ - mesh variable
 * mc_ - mesh const variable
 * mv_ - mesh vector variable
 * mf_ - mesh function variable
 * mt_ - mesh table
 * 
 */

namespace AWS
{
    class Aws_Mesh
    {
    private:
        VAO m_vao;
        VBO m_vbo[4];
        EBO m_ebo;

        Shader m_sh;

        Texture m_tex;

        glm::mat4 m_transform = glm::mat4(1.0);

        bool m_isTexture = false;
        unsigned int mc_textureType = 0;
        unsigned int mc_shadeType = 0;

        float mt_psr[3][3] = {
            {   0.0f, 0.0f, 0.0f    },
            {   1.0f, 1.0f, 1.0f    },
            {   0.0f, 0.0f, 0.0f    }
        };

        float mt_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

        std::vector<float> mv_vertices;
        std::vector<float> mv_color;
        std::vector<float> mv_textureCoordinates;
        std::vector<float> mv_normals;
        std::vector<unsigned int> mv_indices;
        std::vector<unsigned int> mv_indicesNormal;
        std::vector<unsigned int> mv_indicesTexture;

        /**
         * @brief ReadMesh
         * 
         * @param mf_meshPath path to mesh
         */
        void ReadMesh(const std::string & mf_meshPath);

    public:
        /**
         * @brief Create mesh
         * 
         * @param mf_meshPath path to folder with wavefront mesh
         * @param mf_shadeType shading type (AWS::ShadeType::solid, AWS::ShadeType::shade, ...)
         * @param mf_vertex vertex shader
         * @param mf_fragment fragment shader
         */
        void Create(const std::string & mf_meshPath, const unsigned int & mf_shadeType = 0, const std::string & mf_vertex = AWS::colorVS, const std::string & mf_fragment = AWS::colorFS);

        /**
         * @brief Create mesh
         * 
         * @param mf_meshPath path to folder with wavefront mesh
         * @param mf_textureName path to folder with texture
         * @param mf_textureType type of texture (default is GL_TEXTURE_2D)
         * @param mf_shadeType shading type (AWS::ShadeType::solid, AWS::ShadeType::shade, ...)
         * @param mf_vertex vertex shader
         * @param mf_fragment fragment shader
         */
        void Create(const std::string & mf_meshPath, const std::string & mf_textureName, const unsigned int & mf_textureType = GL_TEXTURE_2D, const unsigned int & mf_shadeType = 0, const std::string & mf_vertex = AWS::textureVS, const std::string & mf_fragment = AWS::textureFS);
        
        /**
         * @brief Get the Vertices object
         * 
         * @return float* 
         */
        float* GetVertices() { return mv_vertices.data(); }

        /**
         * @brief Get the Indices object
         * 
         * @return unsigned* 
         */
        unsigned int* GetIndices() { return mv_indices.data(); }

        /**
         * @brief Get the Texture Coordinate object
         * 
         * @return float* 
         */
        float* GetTextureCoordinate() { return mv_textureCoordinates.data(); }

        /**
         * @brief Get the Position object
         * 
         * @return float* 
         */
        float* GetPosition() { return mt_psr[0]; }

        /**
         * @brief Get the Scale object
         * 
         * @return float* 
         */
        float* GetScale() { return mt_psr[1]; }

        /**
         * @brief Get the Rotation object
         * 
         * @return float* 
         */
        float* GetRotation() { return mt_psr[2]; }

        /**
         * @brief Get the Shader ID object
         * 
         * @return unsigned int 
         */
        unsigned int GetShaderID() { return m_sh.GetID(); }

        /**
         * @brief Set the Position object
         * 
         * @param mf_x X axis
         * @param mf_y Y axis
         * @param mf_z Z axis
         */
        void SetPosition(float mf_x, float mf_y, float mf_z);

        /**
         * @brief Set the Scale object
         * 
         * @param mf_x X axis
         * @param mf_y Y axis
         * @param mf_z Z axis
         */
        void SetScale(float mf_x, float mf_y, float mf_z);

        /**
         * @brief Set the Rotation object
         * 
         * @param mf_x X axis
         * @param mf_y Y axis
         * @param mf_z Z axis
         */
        void SetRotation(float mf_x, float mf_y, float mf_z);

        /**
         * @brief Set the Texture object
         * 
         * @param mf_texturePath path to folder with texture
         */
        void SetTexture(const std::string & mf_texturePath);

        /**
         * @brief Set the Mesh object
         * 
         * @param mf_meshPath path to filder with mesh
         */
        void SetMesh(const std::string & mf_meshPath);

        /**
         * @brief Set the Color object
         * 
         * @param r red
         * @param g green
         * @param b blue
         * @param a alpha
         */
        void SetColor(float r, float g, float b, float a);

        /**
         * @brief Draw mesh on screen
         * 
         * @param mf_drawType draw object type (GL_POINTS, GL_LINES, GL_TRIANGLES, GL_QUADS, default is GL_TRIANGLES)
         */
        void DrawMesh(const unsigned int & mf_drawType = GL_TRIANGLES);

        /**
         * @brief Draw mesh on screen
         * 
         * @param mf_drawType draw object type (GL_POINTS, GL_LINES, GL_TRIANGLES, GL_QUADS, default is GL_TRIANGLES)
         * @param mf_projection glm::perspective
         * @param mf_view glm::lookAt
         */
        void DrawMesh(const unsigned int & mf_drawType, const glm::mat4 & mf_projection, const glm::mat4 & mf_view);

        /**
         * @brief Terminate mesh
         * 
         */
        void Terminate();
    };

    void Aws_Mesh::ReadMesh(const std::string & mf_meshPath)
    {
        std::ifstream f;
    
        f.open(mf_meshPath, std::ios::binary);

        if(!f)
        {
            std::cout << "No file";
        }

        std::string line;

        while(!f.eof())
        {
            std::getline(f, line);

            if(line.find("v ") == 0)
            {
                std::stringstream ss(line.c_str() + 2);
                float x, y, z;
                ss >> x >> y >> z;

                mv_vertices.push_back(x);
                mv_vertices.push_back(y);
                mv_vertices.push_back(z);
            }
            else if(line.find("vt ") == 0)
            {
                std::stringstream ss(line.c_str() + 3);
                float u, v, w;
                ss >> u >> v >> w;

                mv_textureCoordinates.push_back(u);
                mv_textureCoordinates.push_back(v);
                mv_textureCoordinates.push_back(w);
            }
            else if(line.find("vn ") == 0)
            {
                std::stringstream ss(line.c_str() + 3);
                float x, y, z;
                ss >> x >> y >> z;

                mv_normals.push_back(x);
                mv_normals.push_back(y);
                mv_normals.push_back(z);
            }
            else if(line.find("f ") == 0)
            {
                int slashNum = 0;
                size_t lastSlashIX = 0;
                bool doubleSlash = false;

                for(size_t i = 0; i < line.size(); i++)
                {
                    if(line[i] == '/')
                    {
                        line[i] = ' ';

                        lastSlashIX = i;
                        slashNum++;
                    }
                }

                std::stringstream ss(line.c_str() + 2);

                unsigned int indX = 0, texX = 0, norX = 0, indY = 0, texY = 0, norY = 0, indZ = 0, texZ = 0, norZ = 0, indW = 0, texW = 0, norW = 0;

                ss >> indX >> texX >> norX >> indY >> texY >> norY >> indZ >> texZ >> norZ >> indW >> texW >> norW;

                mv_indices.push_back(indX - 1);
                mv_indices.push_back(indY - 1);
                mv_indices.push_back(indZ - 1);

                mv_indices.push_back(indX - 1);
                mv_indices.push_back(indZ - 1);
                mv_indices.push_back(indW - 1);

                mv_indicesTexture.push_back(texX - 1);
                mv_indicesTexture.push_back(texY - 1);
                mv_indicesTexture.push_back(texZ - 1);
                mv_indicesTexture.push_back(texW - 1);

                mv_indicesNormal.push_back(norX - 1);
                mv_indicesNormal.push_back(norY - 1);
                mv_indicesNormal.push_back(norZ - 1);
    
                mv_indicesNormal.push_back(norX - 1);
                mv_indicesNormal.push_back(norZ - 1);
                mv_indicesNormal.push_back(norW - 1);
            }
        }
    }

    void Aws_Mesh::Create(const std::string & mf_meshPath, const unsigned int & mf_shadeType, const std::string & mf_vertex, const std::string & mf_fragment)
    {
        m_isTexture = false;
        mc_shadeType = mf_shadeType;

        ReadMesh(mf_meshPath);

        m_sh.create(mf_vertex, mf_fragment);

        m_vao.create();
        m_vao.bind();

        m_vbo[0].create();
        m_vbo[0].bind(mv_vertices.data(), mv_vertices.size() * sizeof(float), 0, 3);

        m_vbo[1].create();
        m_vbo[1].bind(mv_color.data(), mv_color.size() * sizeof(float), 1, 4);

        /**
         * 
         * More vertex buffer objects
         * 
         */

        m_ebo.create();
        m_ebo.bind(mv_indices.data(), mv_indices.size() * sizeof(unsigned int));

        m_vao.unbind();
    }

    void Aws_Mesh::Create(const std::string & mf_meshPath, const std::string & mf_textureName, const unsigned int & mf_textureType, const unsigned int & mf_shadeType, const std::string & mf_vertex, const std::string & mf_fragment)
    {
        m_isTexture = true;
        mc_shadeType = mf_shadeType;

        ReadMesh(mf_meshPath);

        m_sh.create(mf_vertex, mf_fragment);

        m_vao.create();
        m_vao.bind();

        m_vbo[0].create();
        m_vbo[0].bind(mv_vertices.data(), mv_vertices.size() * sizeof(float), 0, 3);

        m_vbo[1].create();
        m_vbo[1].bind(mv_color.data(), mv_color.size() * sizeof(float), 1, 4);

        m_vbo[2].create();
        m_vbo[2].bind(mv_textureCoordinates.data(), mv_textureCoordinates.size() * sizeof(float), 2, 2);

        m_vbo[3].create();
        m_vbo[3].bind(mv_normals.data(), mv_normals.size() * sizeof(float), 3, 3);

        /**
         * 
         * More vertex buffer objects
         * 
         */

        if(m_isTexture)
        {
            m_tex.create();
            m_tex.bind({mf_textureName}, GL_REPEAT, mf_textureType);
        }

        m_ebo.create();
        m_ebo.bind(mv_indicesTexture.data(), mv_indicesTexture.size() * sizeof(unsigned int));

        m_sh.bind();

        glUniform1i(glGetUniformLocation(m_sh.GetID(), "tex"), 0);

        m_sh.unbind();

        m_vao.unbind();
    }

    void Aws_Mesh::SetPosition(float mf_x, float mf_y, float mf_z)
    {
        mt_psr[0][0] = mf_x;
        mt_psr[0][1] = mf_y;
        mt_psr[0][2] = mf_z;

        m_transform = glm::translate(glm::mat4(1.0), glm::vec3(mt_psr[0][0], mt_psr[0][2], mt_psr[0][2]));
        m_transform = glm::rotate(m_transform, glm::radians(mt_psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
        m_transform = glm::rotate(m_transform, glm::radians(mt_psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
        m_transform = glm::rotate(m_transform, glm::radians(mt_psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
        m_transform = glm::scale(m_transform, glm::vec3(mt_psr[1][0], mt_psr[1][2], mt_psr[1][2]));
    }

    void Aws_Mesh::SetScale(float mf_x, float mf_y, float mf_z)
    {
        mt_psr[1][0] = mf_x;
        mt_psr[1][1] = mf_y;
        mt_psr[1][2] = mf_z;

        m_transform = glm::translate(glm::mat4(1.0), glm::vec3(mt_psr[0][0], mt_psr[0][2], mt_psr[0][2]));
        m_transform = glm::rotate(m_transform, glm::radians(mt_psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
        m_transform = glm::rotate(m_transform, glm::radians(mt_psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
        m_transform = glm::rotate(m_transform, glm::radians(mt_psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
        m_transform = glm::scale(m_transform, glm::vec3(mt_psr[1][0], mt_psr[1][2], mt_psr[1][2]));
    }

    void Aws_Mesh::SetRotation(float mf_x, float mf_y, float mf_z)
    {
        mt_psr[2][0] = mf_x;
        mt_psr[2][1] = mf_y;
        mt_psr[2][2] = mf_z;

        m_transform = glm::translate(glm::mat4(1.0), glm::vec3(mt_psr[0][0], mt_psr[0][2], mt_psr[0][2]));
        m_transform = glm::rotate(m_transform, glm::radians(mt_psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
        m_transform = glm::rotate(m_transform, glm::radians(mt_psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
        m_transform = glm::rotate(m_transform, glm::radians(mt_psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
        m_transform = glm::scale(m_transform, glm::vec3(mt_psr[1][0], mt_psr[1][2], mt_psr[1][2]));
    }

    void Aws_Mesh::SetTexture(const std::string & mf_texturePath)
    {
        m_vao.bind();
        m_sh.bind();

        m_tex.bind({mf_texturePath}, GL_REPEAT, GL_TEXTURE_2D);

        m_vao.unbind();
        m_sh.unbind();
    }

    void Aws_Mesh::SetMesh(const std::string & mf_meshPath)
    {
        ReadMesh(mf_meshPath);

        m_vbo[0].bind(mv_vertices.data(), mv_vertices.size() * sizeof(float), 0, 3);
        m_vbo[2].bind(mv_textureCoordinates.data(), mv_textureCoordinates.size() * sizeof(float), 2, 2);
        m_vbo[3].bind(mv_normals.data(), mv_normals.size() * sizeof(float), 3, 3);
    }

    void Aws_Mesh::SetColor(float r, float g, float b, float a)
    {
        mt_color[0] = r;
        mt_color[1] = g;
        mt_color[2] = b;
        mt_color[3] = a;

        for(unsigned int i = 0; i < mv_vertices.size(); i++)
        {
            mv_color[i * 4] = mt_color[0];
            mv_color[i * 4 + 1] = mt_color[1];
            mv_color[i * 4 + 2] = mt_color[2];
            mv_color[i * 4 + 3] = mt_color[3];
        }

        m_vbo[1].bind(mv_color.data(), mv_color.size() * sizeof(float), 1, 4);
    }

    void Aws_Mesh::DrawMesh(const unsigned int & mf_drawType)
    {
        m_sh.bind();
        m_vao.bind();
        if(m_isTexture)
            m_tex.bind();

        if(mc_shadeType == AWS::ShadeType::solid)
        {
            glUniformMatrix4fv(glGetUniformLocation(m_sh.GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(m_transform));
        }
        else if(mc_shadeType == AWS::ShadeType::shade)
        {
            glUniformMatrix4fv(glGetUniformLocation(m_sh.GetID(), "projectionTransform"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));
            glUniformMatrix4fv(glGetUniformLocation(m_sh.GetID(), "viewTransform"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));
            glUniformMatrix4fv(glGetUniformLocation(m_sh.GetID(), "modelTransform"), 1, GL_FALSE, glm::value_ptr(m_transform));
        }

        glDrawElements(mf_drawType, mv_vertices.size(), GL_UNSIGNED_INT, NULL);

        m_sh.unbind();
        m_vao.unbind();
    }

    void Aws_Mesh::DrawMesh(const unsigned int & mf_drawType, const glm::mat4 & mf_projection, const glm::mat4 & mf_view)
    {
        m_sh.bind();
        m_vao.bind();
        if(m_isTexture)
            m_tex.bind();

        if(mc_shadeType == AWS::ShadeType::solid)
        {
            glUniformMatrix4fv(glGetUniformLocation(m_sh.GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(m_transform));
        }
        else if(mc_shadeType == AWS::ShadeType::shade)
        {
            glUniformMatrix4fv(glGetUniformLocation(m_sh.GetID(), "projectionTransform"), 1, GL_FALSE, glm::value_ptr(mf_projection));
            glUniformMatrix4fv(glGetUniformLocation(m_sh.GetID(), "viewTransform"), 1, GL_FALSE, glm::value_ptr(mf_view));
            glUniformMatrix4fv(glGetUniformLocation(m_sh.GetID(), "modelTransform"), 1, GL_FALSE, glm::value_ptr(m_transform));
        }

        glDrawElements(mf_drawType, mv_vertices.size(), GL_UNSIGNED_INT, NULL);

        m_sh.unbind();
        m_vao.unbind();
    }


    void Aws_Mesh::Terminate()
    {
        m_vao.terminate();
        m_vbo->terminate();
        m_ebo.terminate();
        m_tex.terminate();
    }

    typedef Aws_Mesh Mesh;
}