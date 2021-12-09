#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include "../Buffers/Aws_Buffer.hpp"
#include "../MeshLoader/Aws_MeshLoader.hpp"
#include "../MeshLoader/Obj_Wavefront_Loader.hpp"
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
     * @param array true - glDrawArrays
     * @return ObjectData 
     */
    ObjectData LoadMesh(const std::string & meshPath, bool array = false)
    {
        ObjectData mesh_objectData;

        Obj::MeshData m_data;
        Obj::BufferMeshData b_data;

        if(!array)
        {
            m_data = Obj::LoadMesh(meshPath, true);

            mesh_objectData.od_normals = m_data.normals;
            mesh_objectData.od_textureCoordinates = m_data.textureCoordinates;
            mesh_objectData.od_vertices = m_data.vertices;

            mesh_objectData.od_indices = m_data.indices;
            mesh_objectData.od_indicesNor = m_data.indicesNormals;
            mesh_objectData.od_indicesTex = m_data.indicesTexture;

            mesh_objectData.arrayOn = false;
        }
        else
        {
            b_data = Obj::LoadMeshBuffer(meshPath);

            mesh_objectData.od_normals = b_data.normals;
            mesh_objectData.od_textureCoordinates = b_data.textureCoordinates;
            mesh_objectData.od_vertices = b_data.vertices;

            mesh_objectData.arrayOn = true;
        }

        return mesh_objectData;
    }

    ObjectData TransformToTextureData(const ObjectData & tdf_objectData)
    {
        ObjectData td_objectData;

        for(unsigned int i = 0; i < (1 * tdf_objectData.od_vertices.size()) / 3; i++)
        {
            td_objectData.od_vertices.push_back(tdf_objectData.od_vertices[(1 * tdf_objectData.od_indices[i * 3])]);
            td_objectData.od_vertices.push_back(tdf_objectData.od_vertices[(1 * tdf_objectData.od_indices[i * 3 + 1])]);
            td_objectData.od_vertices.push_back(tdf_objectData.od_vertices[(1 * tdf_objectData.od_indices[i * 3 + 2])]);
        }

        for(unsigned int i = 0; i < (1 * tdf_objectData.od_textureCoordinates.size()) / 6; i++)
        {
            td_objectData.od_textureCoordinates.push_back(tdf_objectData.od_textureCoordinates[(1 * tdf_objectData.od_indicesTex[i * 6])]);
            td_objectData.od_textureCoordinates.push_back(tdf_objectData.od_textureCoordinates[(1 * tdf_objectData.od_indicesTex[i * 6]) + 1]);

            td_objectData.od_textureCoordinates.push_back(tdf_objectData.od_textureCoordinates[(1 * tdf_objectData.od_indicesTex[i * 6]) + 2]);
            td_objectData.od_textureCoordinates.push_back(tdf_objectData.od_textureCoordinates[(1 * tdf_objectData.od_indicesTex[i * 6]) + 3]);

            td_objectData.od_textureCoordinates.push_back(tdf_objectData.od_textureCoordinates[(1 * tdf_objectData.od_indicesTex[i * 6]) + 4]);
            td_objectData.od_textureCoordinates.push_back(tdf_objectData.od_textureCoordinates[(1 * tdf_objectData.od_indicesTex[i * 6]) + 5]);
        }

        for(unsigned int i = 0; i < (1 * tdf_objectData.od_normals.size()) / 3; i++)
        {
            td_objectData.od_normals.push_back(tdf_objectData.od_normals[tdf_objectData.od_indicesNor[i]]);
            td_objectData.od_normals.push_back(tdf_objectData.od_normals[tdf_objectData.od_indicesNor[i + 1]]);
            td_objectData.od_normals.push_back(tdf_objectData.od_normals[tdf_objectData.od_indicesNor[i + 2]]);

            td_objectData.od_normals.push_back(tdf_objectData.od_normals[tdf_objectData.od_indicesNor[i]]);
            td_objectData.od_normals.push_back(tdf_objectData.od_normals[tdf_objectData.od_indicesNor[i + 1]]);
            td_objectData.od_normals.push_back(tdf_objectData.od_normals[tdf_objectData.od_indicesNor[i + 3]]);
        }

        return td_objectData;
    }

    class Aws_Object
    {
    private:
        Shader o_sh;

        VAO o_vao;
        VBO o_vbo[3];
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
         * @param arrays true - glDrawArrays, false - glDrawElements
         */
        void Create(unsigned int of_shadeType = AWS::ShadeType::solid, std::string of_vertName = AWS::colorVS, std::string of_fragName = AWS::colorFS);

        /**
         * @brief Draw object on screen
         * 
         * @param of_drawType draw mode (GL_POINTS, GL_LINES, GL_TRIANGLES ...)
         * @param of_textures Arrays or elements draw
         */
        void DrawObject(unsigned int of_drawType);

        /**
         * @brief Draw object on screen
         * 
         * @param of_drawType draw mode (GL_POINTS, GL_LINES, GL_TRIANGLES ...)
         * @param projection glm::perspective
         * @param view glm::lookat
         * @param of_textures Arrays or elements draw
         */
        void DrawObject(unsigned int of_drawType, glm::mat4 projection, glm::mat4 view);

        /**
         * @brief Zero all uniforms speufied in data
         * 
         * @param of_data names of uniforms
         */
        void ZeroData(const std::vector<std::string> & of_data);

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
         * @brief Get the Texture ID object
         * 
         * @return unsigned int 
         */
        unsigned int GetTextureID() { return o_tex.GetID(); }

        /**
         * @brief Get the Object Data object
         * 
         * @return ObjectData 
         */
        ObjectData GetObjectData() { return o_objectData; }

        /**
         * @brief Set the Object Data object
         * 
         * @param of_objectData - class represents data to draw object (you can define your own AWS::ObjectData class if you want)
         */
        void SetObjectData(ObjectData of_objectData);

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
        o_vbo[1].bind(o_objectData.od_textureCoordinates.data(), sizeof(float) * o_objectData.od_textureCoordinates.size(), 2, 2);

        o_vbo[2].create();
        o_vbo[2].bind(o_objectData.od_normals.data(), sizeof(float) * o_objectData.od_normals.size(), 3, 3);

        if(!o_objectData.arrayOn)
        {
            o_ebo.create();
            o_ebo.bind(o_objectData.od_indices.data(), sizeof(unsigned int) * o_objectData.od_indices.size());
        }

        o_tex.create();
        o_tex.bind({"data/texture/white.png"}, GL_REPEAT, GL_TEXTURE_2D);

        o_sh.bind();

        glUniform1i(glGetUniformLocation(o_sh.GetID(), "tex"), 0);
        glUniform4f(glGetUniformLocation(o_sh.GetID(), "iCol"), 1.0f, 1.0f, 1.0f, 1.0f);

        glUniform3f(glGetUniformLocation(o_sh.GetID(), "viewPos"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(o_sh.GetID(), "lig_pos"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(o_sh.GetID(), "lig_col"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(o_sh.GetID(), "ambientV"), 0.1f);
        glUniform1f(glGetUniformLocation(o_sh.GetID(), "specularV"), 0.5f);
        
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

        if(!o_objectData.arrayOn)
            glDrawElements(of_drawType, 2 * o_objectData.od_vertices.size(), GL_UNSIGNED_INT, NULL);
        else
            glDrawArrays(of_drawType, 0, 2 * o_objectData.od_vertices.size());

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

        if(!o_objectData.arrayOn)
            glDrawElements(of_drawType, 2 * o_objectData.od_vertices.size(), GL_UNSIGNED_INT, NULL);
        else
            glDrawArrays(of_drawType, 0, 2 * o_objectData.od_vertices.size());

        o_sh.unbind();
        o_vao.unbind();
    }

    void Aws_Object::ZeroData(const std::vector<std::string> & of_data)
    {
        o_vao.bind();
        o_sh.bind();

        for(int i = 0; i < of_data.size(); i++)
        {
            glUniform3f(glGetUniformLocation(o_sh.GetID(), of_data[i].c_str()), 0.0f, 0.0f, 0.0f);
        }

        o_sh.unbind();
        o_vao.unbind();
    }

    void Aws_Object::SetObjectData(ObjectData of_objectData)
    {
        o_objectData = of_objectData;
        o_objectData.arrayOn = of_objectData.arrayOn;

        o_vbo[0].bind(o_objectData.od_vertices.data(), sizeof(float) * o_objectData.od_vertices.size(), 0, 3);
        o_vbo[1].bind(o_objectData.od_textureCoordinates.data(), sizeof(float) * o_objectData.od_textureCoordinates.size(), 2, 2);
        o_vbo[2].bind(o_objectData.od_normals.data(), sizeof(float) * o_objectData.od_normals.size(), 3, 3);
        if(!o_objectData.arrayOn)
            o_ebo.bind(o_objectData.od_indices.data(), sizeof(unsigned int) * o_objectData.od_indices.size());
        else
            o_ebo.terminate();
    }

    void Aws_Object::SetPosition(float of_x, float of_y, float of_z)
    {
        o_objectData.od_objectTranformData.odt_px = of_x;
        o_objectData.od_objectTranformData.odt_py = of_y;
        o_objectData.od_objectTranformData.odt_pz = of_z;

        o_transform = glm::translate(glm::mat4(1.0), glm::vec3(o_objectData.od_objectTranformData.odt_px, o_objectData.od_objectTranformData.odt_py, o_objectData.od_objectTranformData.odt_pz));
        o_transform = glm::rotate(o_transform, glm::radians(o_objectData.od_objectTranformData.odt_rx), glm::vec3(1.0f, 0.0f, 0.0f));
        o_transform = glm::rotate(o_transform, glm::radians(o_objectData.od_objectTranformData.odt_ry), glm::vec3(0.0f, 1.0f, 0.0f));
        o_transform = glm::rotate(o_transform, glm::radians(o_objectData.od_objectTranformData.odt_rz), glm::vec3(0.0f, 0.0f, 1.0f));
        o_transform = glm::scale(o_transform, glm::vec3(o_objectData.od_objectTranformData.odt_sx, o_objectData.od_objectTranformData.odt_sy, o_objectData.od_objectTranformData.odt_sz));
    }

    void Aws_Object::SetScale(float of_x, float of_y, float of_z)
    {
        o_objectData.od_objectTranformData.odt_sx = of_x;
        o_objectData.od_objectTranformData.odt_sy = of_y;
        o_objectData.od_objectTranformData.odt_sz = of_z;

        o_transform = glm::translate(glm::mat4(1.0), glm::vec3(o_objectData.od_objectTranformData.odt_px, o_objectData.od_objectTranformData.odt_py, o_objectData.od_objectTranformData.odt_pz));
        o_transform = glm::rotate(o_transform, glm::radians(o_objectData.od_objectTranformData.odt_rx), glm::vec3(1.0f, 0.0f, 0.0f));
        o_transform = glm::rotate(o_transform, glm::radians(o_objectData.od_objectTranformData.odt_ry), glm::vec3(0.0f, 1.0f, 0.0f));
        o_transform = glm::rotate(o_transform, glm::radians(o_objectData.od_objectTranformData.odt_rz), glm::vec3(0.0f, 0.0f, 1.0f));
        o_transform = glm::scale(o_transform, glm::vec3(o_objectData.od_objectTranformData.odt_sx, o_objectData.od_objectTranformData.odt_sy, o_objectData.od_objectTranformData.odt_sz));
    }

    void Aws_Object::SetRotation(float of_x, float of_y, float of_z)
    {
        o_objectData.od_objectTranformData.odt_rx = of_x;
        o_objectData.od_objectTranformData.odt_ry = of_y;
        o_objectData.od_objectTranformData.odt_rz = of_z;

        o_transform = glm::translate(glm::mat4(1.0), glm::vec3(o_objectData.od_objectTranformData.odt_px, o_objectData.od_objectTranformData.odt_py, o_objectData.od_objectTranformData.odt_pz));
        o_transform = glm::rotate(o_transform, glm::radians(o_objectData.od_objectTranformData.odt_rx), glm::vec3(1.0f, 0.0f, 0.0f));
        o_transform = glm::rotate(o_transform, glm::radians(o_objectData.od_objectTranformData.odt_ry), glm::vec3(0.0f, 1.0f, 0.0f));
        o_transform = glm::rotate(o_transform, glm::radians(o_objectData.od_objectTranformData.odt_rz), glm::vec3(0.0f, 0.0f, 1.0f));
        o_transform = glm::scale(o_transform, glm::vec3(o_objectData.od_objectTranformData.odt_sx, o_objectData.od_objectTranformData.odt_sy, o_objectData.od_objectTranformData.odt_sz));
    }

    void Aws_Object::SetColor(float of_r, float of_g, float of_b, float of_a)
    {
        o_sh.bind();
        o_vao.bind();

        glUniform4f(glGetUniformLocation(o_sh.GetID(), "iCol"), of_r, of_g, of_b, of_a);

        o_vao.unbind();
        o_sh.unbind();
    }

    void Aws_Object::SetTexture(const std::string & texturePath, int of_wrapping)
    {
        o_textureOn = true;

        o_vao.bind();

        o_tex.bind({texturePath}, of_wrapping, GL_TEXTURE_2D);

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

            o_vbo[1].bind(o_objectData.od_textureCoordinates.data(), sizeof(float) * o_objectData.od_textureCoordinates.size(), 2, 2);
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