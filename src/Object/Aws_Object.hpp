#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include "../Buffers/Aws_Buffer.hpp"
#include "../Aws_Types.hpp"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * o_ - object variable
 * ot_ - object table variable
 * oc_ - object const
 * of_ - object function variable
 * ov_ - object vector
 * 
 * od_ - objectData vbariable
 * odf_ - objectData function variable
 * 
 */

namespace AWS
{   
    /**
     * @brief As name says load mesh
     * 
     * @param meshPath path to mesh
     * @return ObjectData 
     */
    ObjectData LoadMesh(const std::string & meshPath)
    {
        ObjectData mesh_objectData;

        mesh_objectData.od_color.clear();
        mesh_objectData.od_indices.clear();
        mesh_objectData.od_indicesNor.clear();
        mesh_objectData.od_indicesTex.clear();
        mesh_objectData.od_normals.clear();
        mesh_objectData.od_textureCoordinates.clear();
        mesh_objectData.od_vertices.clear();

        std::ifstream f;
    
        f.open(meshPath, std::ios::binary);

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

                mesh_objectData.od_vertices.push_back(x);
                mesh_objectData.od_color.push_back(y);
                mesh_objectData.od_color.push_back(z);
            }
            else if(line.find("vt ") == 0)
            {
                std::stringstream ss(line.c_str() + 3);
                float u, v, w;
                ss >> u >> v >> w;

                mesh_objectData.od_textureCoordinates.push_back(u);
                mesh_objectData.od_textureCoordinates.push_back(v);
                mesh_objectData.od_textureCoordinates.push_back(w);
            }
            else if(line.find("vn ") == 0)
            {
                std::stringstream ss(line.c_str() + 3);
                float x, y, z;
                ss >> x >> y >> z;

                mesh_objectData.od_normals.push_back(x);
                mesh_objectData.od_normals.push_back(y);
                mesh_objectData.od_normals.push_back(z);
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

                mesh_objectData.od_indices.push_back(indX - 1);
                mesh_objectData.od_indices.push_back(indY - 1);
                mesh_objectData.od_indices.push_back(indZ - 1);

                mesh_objectData.od_indices.push_back(indX - 1);
                mesh_objectData.od_indices.push_back(indZ - 1);
                mesh_objectData.od_indices.push_back(indW - 1);

                mesh_objectData.od_indicesTex.push_back(texX - 1);
                mesh_objectData.od_indicesTex.push_back(texY - 1);
                mesh_objectData.od_indicesTex.push_back(texZ - 1);
                mesh_objectData.od_indicesTex.push_back(texW - 1);

                mesh_objectData.od_indicesNor.push_back(norX - 1);
                mesh_objectData.od_indicesNor.push_back(norY - 1);
                mesh_objectData.od_indicesNor.push_back(norZ - 1);

                mesh_objectData.od_indicesNor.push_back(norX - 1);
                mesh_objectData.od_indicesNor.push_back(norZ - 1);
                mesh_objectData.od_indicesNor.push_back(norW - 1);
            }
        }

        return mesh_objectData;
    }

    class Aws_Object
    {
    private:
        Shader o_sh;

        VAO o_vao;
        VBO o_vbo[4];
        EBO o_ebo;

        Texture o_tex;

        bool o_textureOn = false;
        unsigned int oc_shadeType = 0;

        glm::mat4 o_transform = glm::mat4(1.0);

        float ot_psr[3][3] = {
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f},
            {0.0f, 0.0f, 0.0f}
        };

        ObjectData o_objectData = square;

    public:
        /**
         * @brief Create object
         * 
         * @param of_shadeType type of shade(AWS::ShadeType::solid default)
         * @param of_vertName vertex shader path
         * @param of_fragName fragment shader path
         */
        void Create(unsigned int of_shadeType = AWS::ShadeType::solid, std::string of_vertName = AWS::colorVS, std::string of_fragName = AWS::colorFS);

        /**
         * @brief Draw object on screen
         * 
         * @param of_drawType draw mode (GL_POINTS, GL_LINES, GL_TRIANGLES ...)
         */
        void DrawObject(unsigned int of_drawType);

        /**
         * @brief Draw object on screen
         * 
         * @param of_drawType draw mode (GL_POINTS, GL_LINES, GL_TRIANGLES ...)
         * @param projection glm::perspective
         * @param view glm::lookat
         */
        void DrawObject(unsigned int of_drawType, glm::mat4 projection, glm::mat4 view);

        /**
         * @brief Get the Position object
         * 
         * @return float* 
         */
        float* GetPosition() { return ot_psr[0]; }

        /**
         * @brief Get the Scale object
         * 
         * @return float* 
         */
        float* GetScale() { return ot_psr[1]; }

        /**
         * @brief Get the Rotation object
         * 
         * @return float* 
         */
        float* GetRotation() { return ot_psr[2]; }

        /**
         * @brief Get the Vertices object
         * 
         * @return float* 
         */
        float* GetVertices() { return o_objectData.od_vertices.data(); }

        /**
         * @brief Get the Indices object
         * 
         * @return unsigned* 
         */
        unsigned int* GetIndices() { return o_objectData.od_indices.data(); }

        /**
         * @brief Get the Texture Coords object
         * 
         * @return float* 
         */
        float* GetTextureCoords() { return o_objectData.od_textureCoordinates.data(); }

        /**
         * @brief Get the Color object
         * 
         * @return float* 
         */
        float* GetColor() { return o_objectData.od_color.data(); }

        /**
         * @brief Get the Normals object
         * 
         * @return float* 
         */
        float* GetNormals() { return o_objectData.od_normals.data(); }

        /**
         * @brief Get the Shader ID object
         * 
         * @return unsigned int 
         */
        unsigned int GetShaderID() { return o_sh.GetID(); }

        /**
         * @brief Set the Object Data object
         * 
         * @param of_objectData - class represents data to draw object (you can define your own AWS::ObjectData class if you want)
         */
        void SetObjectData(const ObjectData & of_objectData);

        /**
         * @brief Set the Position object
         * 
         * @param of_x x axis
         * @param of_y y axis
         * @param of_z z axis
         */
        void SetPosition(float of_x, float of_y, float of_z);

        /**
         * @brief Set the Scale object
         * 
         * @param of_x x axis
         * @param of_y y axis
         * @param of_z z axis
         */
        void SetScale(float of_x, float of_y, float of_z);

        /**
         * @brief Set the Rotation object
         * 
         * @param of_x x axis
         * @param of_y y axis
         * @param of_z z axis
         */
        void SetRotation(float of_x, float of_y, float of_z);

        /**
         * @brief Set the Color object
         * 
         * @param of_r red
         * @param of_g green
         * @param of_b blue
         * @param of_a alpha
         */
        void SetColor(float of_r, float of_g, float of_b, float of_a);

        /**
         * @brief Set the Texture object
         * 
         * @param texturePath path to texture folder
         * @param of_wrapping set this to GL_REPEAT (default)
         */
        void SetTexture(const std::string & texturePath, int of_wrapping = GL_REPEAT);

        /**
         * @brief Set the Texture Coordinates object
         * 
         * @param of_x texture x axis coordiantes
         * @param of_y texture y axis coordinates
         */
        void SetTextureCoordinates(float of_x, float of_y);

        /**
         * @brief terminate object
         * 
         */
        void Terminate();
    };

    void Aws_Object::Create(unsigned int of_shadeType, std::string of_vertName, std::string of_fragName)
    {
        oc_shadeType = of_shadeType;

        o_sh.create(of_vertName, of_fragName);

        o_vao.create();
        o_vao.bind();

        o_vbo[0].create();
        o_vbo[0].bind(o_objectData.od_vertices.data(), sizeof(float) * o_objectData.od_vertices.size(), 0, 3);

        o_vbo[1].create();
        o_vbo[1].bind(o_objectData.od_color.data(), sizeof(float) * o_objectData.od_color.size(), 1, 4);

        o_vbo[2].create();
        o_vbo[3].create();

        o_ebo.create();
        o_ebo.bind(o_objectData.od_indices.data(), sizeof(unsigned int) * o_objectData.od_indices.size());

        o_tex.create();

        o_sh.bind();

        glUniform1i(glGetUniformLocation(o_sh.GetID(), "tex"), 0);

        o_sh.unbind();

        o_vao.unbind();
    }

    void Aws_Object::DrawObject(unsigned int of_drawType)
    {
        o_sh.bind();
        o_vao.bind();

        if(o_textureOn)
        {
            o_tex.bind();
        }

        if(oc_shadeType == AWS::ShadeType::solid)
        {
            glUniformMatrix4fv(glGetUniformLocation(o_sh.GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(o_transform));
        }
        else if(oc_shadeType == AWS::ShadeType::shade)
        {
            glUniformMatrix4fv(glGetUniformLocation(o_sh.GetID(), "projectionTransform"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));
            glUniformMatrix4fv(glGetUniformLocation(o_sh.GetID(), "viewTransform"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));
            glUniformMatrix4fv(glGetUniformLocation(o_sh.GetID(), "modelTransform"), 1, GL_FALSE, glm::value_ptr(o_transform));
        }

        glDrawElements(of_drawType, 2 * o_objectData.od_vertices.size(), GL_UNSIGNED_INT, NULL);

        o_sh.unbind();
        o_vao.unbind();
    }

    void Aws_Object::DrawObject(unsigned int of_drawType, glm::mat4 projection, glm::mat4 view)
    {
        o_sh.bind();
        o_vao.bind();

        if(o_textureOn)
        {
            o_tex.bind();
        }

        if(oc_shadeType == AWS::ShadeType::solid)
        {
            glUniformMatrix4fv(glGetUniformLocation(o_sh.GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(projection * view * o_transform));
        }
        else if(oc_shadeType == AWS::ShadeType::shade)
        {
            glUniformMatrix4fv(glGetUniformLocation(o_sh.GetID(), "projectionTransform"), 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(o_sh.GetID(), "viewTransform"), 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(glGetUniformLocation(o_sh.GetID(), "modelTransform"), 1, GL_FALSE, glm::value_ptr(o_transform));
        }

        glDrawElements(of_drawType, 2 * o_objectData.od_vertices.size(), GL_UNSIGNED_INT, NULL);

        o_sh.unbind();
        o_vao.unbind();
    }

    void Aws_Object::SetObjectData(const ObjectData & of_objectData)
    {
        o_objectData = of_objectData;

        o_vbo[0].bind(o_objectData.od_vertices.data(), sizeof(float) * o_objectData.od_vertices.size(), 0, 3);
        o_vbo[1].bind(o_objectData.od_color.data(), sizeof(float) * o_objectData.od_color.size(), 1, 4);
        o_vbo[2].bind(o_objectData.od_textureCoordinates.data(), sizeof(float) * o_objectData.od_textureCoordinates.size(), 2, 2);
        o_vbo[3].bind(o_objectData.od_normals.data(), sizeof(float) * o_objectData.od_normals.size(), 3, 3);
        o_ebo.bind(o_objectData.od_indices.data(), sizeof(unsigned int) * o_objectData.od_indices.size());
    }

    void Aws_Object::SetPosition(float of_x, float of_y, float of_z)
    {
        ot_psr[0][0] = of_x;
        ot_psr[0][1] = of_y;
        ot_psr[0][2] = of_z;

        o_transform = glm::translate(glm::mat4(1.0), glm::vec3(ot_psr[0][0], ot_psr[0][1], ot_psr[0][2]));
        o_transform = glm::rotate(o_transform, ot_psr[2][0], glm::vec3(1.0f, 0.0f, 0.0f));
        o_transform = glm::rotate(o_transform, ot_psr[2][1], glm::vec3(0.0f, 1.0f, 0.0f));
        o_transform = glm::rotate(o_transform, ot_psr[2][2], glm::vec3(0.0f, 0.0f, 1.0f));
        o_transform = glm::scale(o_transform, glm::vec3(ot_psr[1][0], ot_psr[1][1], ot_psr[1][2]));
    }

    void Aws_Object::SetScale(float of_x, float of_y, float of_z)
    {
        ot_psr[1][0] = of_x;
        ot_psr[1][1] = of_y;
        ot_psr[1][2] = of_z;

        o_transform = glm::translate(glm::mat4(1.0), glm::vec3(ot_psr[0][0], ot_psr[0][1], ot_psr[0][2]));
        o_transform = glm::rotate(o_transform, ot_psr[2][0], glm::vec3(1.0f, 0.0f, 0.0f));
        o_transform = glm::rotate(o_transform, ot_psr[2][1], glm::vec3(0.0f, 1.0f, 0.0f));
        o_transform = glm::rotate(o_transform, ot_psr[2][2], glm::vec3(0.0f, 0.0f, 1.0f));
        o_transform = glm::scale(o_transform, glm::vec3(ot_psr[1][0], ot_psr[1][1], ot_psr[1][2]));
    }

    void Aws_Object::SetRotation(float of_x, float of_y, float of_z)
    {
        ot_psr[2][0] = of_x;
        ot_psr[2][1] = of_y;
        ot_psr[2][2] = of_z;

        o_transform = glm::translate(glm::mat4(1.0), glm::vec3(ot_psr[0][0], ot_psr[0][1], ot_psr[0][2]));
        o_transform = glm::rotate(o_transform, ot_psr[2][0], glm::vec3(1.0f, 0.0f, 0.0f));
        o_transform = glm::rotate(o_transform, ot_psr[2][1], glm::vec3(0.0f, 1.0f, 0.0f));
        o_transform = glm::rotate(o_transform, ot_psr[2][2], glm::vec3(0.0f, 0.0f, 1.0f));
        o_transform = glm::scale(o_transform, glm::vec3(ot_psr[1][0], ot_psr[1][1], ot_psr[1][2]));
    }

    void Aws_Object::SetColor(float of_r, float of_g, float of_b, float of_a)
    {
        for(unsigned int i = 0; i < o_objectData.od_color.size() / 4; i++)
        {
            o_objectData.od_color[i * 4] = of_r;
            o_objectData.od_color[i * 4 + 1] = of_g;
            o_objectData.od_color[i * 4 + 2] = of_b;
            o_objectData.od_color[i * 4 + 3] = of_a;
        }

        o_vbo[1].bind(o_objectData.od_color.data(), sizeof(float) * o_objectData.od_color.size(), 1, 4);
    }

    void Aws_Object::SetTexture(const std::string & texturePath, int of_wrapping)
    {
        o_textureOn = true;

        o_vao.bind();
        o_sh.bind();

        o_tex.bind({texturePath}, of_wrapping, GL_TEXTURE_2D);

        glUniform1i(glGetUniformLocation(o_sh.GetID(), "tex"), 0);

        o_sh.unbind();
        o_vao.unbind();
    }

    void Aws_Object::SetTextureCoordinates(float of_x, float of_y)
    {
        if(of_x != 0.0f || of_y != 0.0f)
        {
            for(int i = 0; i < o_objectData.od_textureCoordinates.size() / 2; i++)
            {
                if(o_objectData.od_textureCoordinates[i * 2] > 0.0f)
                {
                    o_objectData.od_textureCoordinates[i * 2] = of_x;
                }

                if(o_objectData.od_textureCoordinates[i * 2 + 1] > 0.0f)
                {
                    o_objectData.od_textureCoordinates[i * 2 + 1] = of_y;
                }
            }

            o_vbo[2].bind(o_objectData.od_textureCoordinates.data(), sizeof(float) * o_objectData.od_textureCoordinates.size(), 2, 2);
        }
    }

    void Aws_Object::Terminate()
    {
        o_vao.terminate();
        o_vbo->terminate();
        o_ebo.terminate();
        o_tex.terminate();
    }

    typedef Aws_Object Object;
}