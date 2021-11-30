#pragma once

#include "../Buffers/Aws_Buffer.hpp"
#include "../Aws_Types.hpp"
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

/**
 * c_ - cube variable
 * ct_ - cube table
 * cf_ - cube function variable
 * cc_ - cube const
 * 
 */

namespace AWS
{
    class Aws_Cube
    {
    private:
        Shader c_sh;
        VAO c_vao;
        VBO c_vbo[3];
        EBO c_ebo;

        Texture c_tex;

        int cc_shadeType = 0;
        bool c_texturesOn = false;

        ObjectData c_objectData = ObjectData(
            {
                1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f,
                1.0f, 1.0f, -1.0f,
                -1.0f, 1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f
            },
            {
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
            },
            {
                0.0f
            },
            {
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,

                0.0f, 0.0f, -1.0f,
                0.0f, 0.0f, -1.0f,
                0.0f, 0.0f, -1.0f,
                0.0f, 0.0f, -1.0f,
                0.0f, 0.0f, -1.0f,
                0.0f, 0.0f, -1.0f,

                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,

                -1.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f,

                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                
                0.0f, -1.0f, 0.0f,
                0.0f, -1.0f, 0.0f,
                0.0f, -1.0f, 0.0f,
                0.0f, -1.0f, 0.0f,
                0.0f, -1.0f, 0.0f,
                0.0f, -1.0f, 0.0f
            },
            {
                0
            },
            {
                0
            }
        );

        ObjectData c_textureObjectData = ObjectData(
            {
                //front
                1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 1.0f,
                //front 2
                -1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f,

                //back
                1.0f, 1.0f, -1.0f,
                -1.0f, 1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                //back 2
                -1.0f, 1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,

                //up
                1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, -1.0f,
                //up 2
                -1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, -1.0f,
                -1.0f, 1.0f, -1.0f,

                //down
                1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f,
                1.0f, -1.0f, -1.0f,
                //down 2
                -1.0f, -1.0f, 1.0f,
                1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,

                //right
                1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 1.0f,
                1.0f, 1.0f, -1.0f,
                //right 2
                1.0f, -1.0f, 1.0f,
                1.0f, 1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,

                //left
                -1.0f, 1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f,
                -1.0f, 1.0f, -1.0f,
                //left 2
                -1.0f, -1.0f, 1.0f,
                -1.0f, 1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,
            },
            {
                0
            },
            {
                1.0f, 1.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,

                0.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f,

                1.0f, 1.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,

                0.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f,

                1.0f, 1.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,

                0.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f,

                1.0f, 1.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,

                0.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f,

                1.0f, 1.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,

                0.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f,

                1.0f, 1.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,

                0.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f
            },
            {
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,

                0.0f, 0.0f, -1.0f,
                0.0f, 0.0f, -1.0f,
                0.0f, 0.0f, -1.0f,
                0.0f, 0.0f, -1.0f,
                0.0f, 0.0f, -1.0f,
                0.0f, 0.0f, -1.0f,

                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,

                -1.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f,
                
                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,

                0.0f, -1.0f, 0.0f,
                0.0f, -1.0f, 0.0f,
                0.0f, -1.0f, 0.0f,
                0.0f, -1.0f, 0.0f,
                0.0f, -1.0f, 0.0f,
                0.0f, -1.0f, 0.0f
            },
            {
                0
            },
            {
                0
            }
        );

        glm::mat4 c_transform = glm::mat4x4(1.0);

        float ct_psr[3][3] = {
            {   0.0f, 0.0f, 0.0f    },
            {   1.0f, 1.0f, 1.0f    },
            {   0.0f, 0.0f, 0.0f    }
        };

        float ct_cubemapTexture[3 * 36] = {
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

    public:
        /**
         * @brief Create cube
         * 
         * @param cf_shadeType type of shade (AWS::ShadeType::solid)
         * @param cf_vertName vertex shader
         * @param cf_fragName fragment shader
         */
        void Create(const int cf_shadeType, const std::string &cf_vertName = "data/shaders/color/colorVS.glsl", const std::string &cf_fragName = "data/shaders/color/colorFS.glsl");

        /**
         * @brief Create cube
         * 
         * @param cf_shadeType type of shade (AWS::ShadeType::solid)
         * @param cf_textureName path to folder with texture
         * @param cf_textureType type of texture (default is GL_TEXTURE_2D)
         * @param cf_vertName vertex shader
         * @param cf_fragName fragment shader
         */
        void Create(const int cf_shadeType, const std::string cf_textureName, const int cf_textureType = GL_TEXTURE_2D, const std::string &cf_vertName = "data/shaders/ct_texture/textureVS.glsl", const std::string &cf_fragName = "data/shaders/ct_texture/textureFS.glsl");

        /**
         * @brief Create cube
         * 
         * @param cf_shadeType type of shade (AWS::ShadeType::solid)
         * @param cf_textureName path to folder with texture (can be more than one)
         * @param cf_vertName vertex shader
         * @param cf_fragName fragment shader
         */
        void Create(const int cf_shadeType, const std::vector<std::string> cf_textureName, const std::string &cf_vertName = "data/shaders/cube/cubeVS.glsl", const std::string &cf_fragName = "data/shaders/cube/cubeFS.glsl");
        
        /**
         * @brief Draw call
         * 
         * @param cf_drawMode draw mode (GL_POINTS, GL_LINES, GL_TRIANGLES ...)
         */
        void DrawCube(const unsigned int &cf_drawMode);

        /**
         * @brief Draw call
         * 
         * @param cf_drawMode draw mode (GL_POINTS, GL_LINES, GL_TRIANGLES)
         * @param cf_projection glm::perspective
         * @param cf_view glm::lookAt
         */
        void DrawCube(const unsigned int &cf_drawMode, glm::mat4x4 cf_projection, glm::mat4x4 cf_view);

        /**
         * @brief Get the Textured Object Data object
         * 
         * @return ObjectData 
         */
        ObjectData GetTexturedObjectData() { return c_textureObjectData; }

        /**
         * @brief Get the Object Data object
         * 
         * @return ObjectData 
         */
        ObjectData GetObjectData() { return c_objectData; }

        /**
         * @brief Get the Position object
         * 
         * @return float* 
         */
        float* GetPosition() { return ct_psr[0]; }

        /**
         * @brief Get the Scale object
         * 
         * @return float* 
         */
        float* GetScale() { return ct_psr[1]; }

        /**
         * @brief Get the Rotation object
         * 
         * @return float* 
         */
        float* GetRotation() { return ct_psr[2]; }

        /**
         * @brief Get the Shader ID object
         * 
         * @return unsigned int 
         */
        unsigned int GetShaderID() { return c_sh.GetID(); }

        /**
         * @brief Get the Indices object
         * 
         * @return unsigned* 
         */
        unsigned int* GetIndices() { return c_objectData.od_indices.data(); }

        /**
         * @brief Get the Vertices object
         * 
         * @return float* 
         */
        float* GetVertices(bool array = false) { if(array) return c_textureObjectData.od_vertices.data(); else return c_objectData.od_vertices.data(); }

        /**
         * @brief Get the Texturte Coords object
         * 
         * @return float* 
         */
        float* GetTexturteCoords() { return c_textureObjectData.od_textureCoordinates.data(); }

        /**
         * @brief Set the Position object
         * 
         * @param cf_x X axis
         * @param cf_y Y axis
         * @param cf_z Z axis
         */
        void SetPosition(float cf_x, float cf_y, float cf_z);

        /**
         * @brief Set the Scale object
         * 
         * @param cf_x X axis
         * @param cf_y Y axis
         * @param cf_z Z axis
         */
        void SetScale(float cf_x, float cf_y, float cf_z);

        /**
         * @brief Set the Rotation object
         * 
         * @param cf_x X axis
         * @param cf_y Y axis
         * @param cf_z Z axis
         */
        void SetRotation(float cf_x, float cf_y, float cf_z);

        /**
         * @brief Set the Color object
         * 
         * @param r red
         * @param g green
         * @param b blue
         * @param a alpha
         */
        void SetColor(const float r, const float g, const float b, const float a);

        /**
         * @brief Set the Texture object
         * 
         * @param cf_textureName path to floder with texture
         * @param cf_wrapping set this to GL_REPEAT (default)
         * @param cf_textureType set this to GL_TEXTURE_2D (default) or GL_TEXTURE_CUBE_MAP
         */
        void SetTexture(const std::string cf_textureName, const int cf_wrapping = GL_REPEAT, const int cf_textureType = GL_TEXTURE_2D);

        /**
         * @brief Set the Texture object
         * 
         * @param cf_textureName path to folder with texture
         * @param cf_wrapping set this to GL_REPEAT (default)
         */
        void SetTexture(const std::vector<std::string> cf_textureName, const int cf_wrapping = GL_REPEAT);

        /**
         * @brief Set the Texture Coordinates object
         * 
         * @param cf_x texture x
         * @param cf_y texture y
         */
        void SetTextureCoordinates(float cf_x, float cf_y);

        /**
         * @brief terminate cube
         * 
         */
        void Terminate();
    };

    void Aws_Cube::Create(const int cf_shadeType, const std::string &cf_vertName, const std::string &cf_fragName)
    {
        c_texturesOn = false;
        cc_shadeType = cf_shadeType;

        c_sh.create(cf_vertName, cf_fragName);

        c_vao.create();
        c_vao.bind();

        c_vbo[0].create();
        c_vbo[0].bind(c_objectData.od_vertices.data(), sizeof(float) * c_objectData.od_vertices.size(), 0, 3);

        if(cc_shadeType == solid)
        {

        }
        else if(cc_shadeType == shade)
        {
            c_vbo[2].create();
            c_vbo[2].bind(c_objectData.od_normals.data(), sizeof(float) * c_objectData.od_normals.size(), 3, 3);
        }

        c_ebo.create();
        c_ebo.bind(c_objectData.od_indices.data(), sizeof(unsigned int) * c_objectData.od_indices.size());

        c_sh.bind();

        glUniform4f(glGetUniformLocation(c_sh.GetID(), "iCol"), 1.0f, 1.0f, 1.0f, 1.0f);

        c_sh.unbind();

        c_vao.unbind();
    }

    void Aws_Cube::Create(const int cf_shadeType, const std::string cf_textureName, const int cf_textureType, const std::string &cf_vertName, const std::string &cf_fragName)
    {
        c_texturesOn = true;

        cc_shadeType = cf_shadeType;

        c_sh.create(cf_vertName, cf_fragName);

        c_vao.create();
        c_vao.bind();

        c_vbo[0].create();
        c_vbo[0].bind(c_textureObjectData.od_vertices.data(), sizeof(float) * c_textureObjectData.od_vertices.size(), 0, 3);

        if(cc_shadeType == solid)
        {

        }
        else if(cc_shadeType == shade)
        {
            c_vbo[2].create();
            c_vbo[2].bind(c_textureObjectData.od_normals.data(), sizeof(float) * c_textureObjectData.od_normals.size(), 3, 3);
        }

        if(cf_textureType == CubeTexturing::cubemap)
        {
            c_vbo[1].create();
            c_vbo[1].bind(ct_cubemapTexture, sizeof(ct_cubemapTexture), 2, 3);
        }
        else
        {
            c_vbo[1].create();
            c_vbo[1].bind(c_textureObjectData.od_textureCoordinates.data(), sizeof(float) * c_textureObjectData.od_textureCoordinates.size(), 2, 2);
        }

        /*c_ebo.create();
        c_ebo.bind(ct_indices, sizeof(ct_indices));*/

        c_tex.create();
        c_tex.bind({cf_textureName}, GL_REPEAT, cf_textureType);

        c_sh.bind();

        glUniform4f(glGetUniformLocation(c_sh.GetID(), "iCol"), 1.0f, 1.0f, 1.0f, 1.0f);
        glUniform1i(glGetUniformLocation(c_sh.GetID(), "tex"), 0);

        c_sh.unbind();

        c_vao.unbind();
    }

    void Aws_Cube::Create(const int cf_shadeType, const std::vector<std::string> cf_textureName, const std::string &cf_vertName, const std::string &cf_fragName)
    {
        c_texturesOn = true;
        cc_shadeType = cf_shadeType;

        c_sh.create(cf_vertName, cf_fragName);

        c_vao.create();
        c_vao.bind();

        c_vbo[0].create();
        c_vbo[0].bind(c_objectData.od_vertices.data(), sizeof(float) * c_objectData.od_vertices.size(), 0, 3);

        if(cc_shadeType == solid)
        {

        }
        else if(cc_shadeType == shade)
        {
            c_vbo[2].create();
            c_vbo[2].bind(c_objectData.od_normals.data(), sizeof(float) * c_objectData.od_normals.size(), 3, 3);
        }

        c_vbo[1].create();
        c_vbo[1].bind(ct_cubemapTexture, sizeof(ct_cubemapTexture), 2, 3);

        c_ebo.create();
        c_ebo.bind(c_objectData.od_indices.data(), sizeof(unsigned int) * c_objectData.od_indices.size());

        c_tex.create();
        c_tex.bind(cf_textureName, GL_REPEAT, GL_TEXTURE_CUBE_MAP);

        c_sh.bind();

        glUniform4f(glGetUniformLocation(c_sh.GetID(), "iCol"), 1.0f, 1.0f, 1.0f, 1.0f);
        glUniform1i(glGetUniformLocation(c_sh.GetID(), "tex"), 0);

        c_sh.unbind();

        c_vao.unbind();
    }

    void Aws_Cube::DrawCube(const unsigned int &cf_drawMode)
    {
        c_textureObjectData.od_objectTranformData.odt_px = c_objectData.od_objectTranformData.odt_px = ct_psr[0][0];
        c_textureObjectData.od_objectTranformData.odt_py = c_objectData.od_objectTranformData.odt_py = ct_psr[0][1];
        c_textureObjectData.od_objectTranformData.odt_pz = c_objectData.od_objectTranformData.odt_pz = ct_psr[0][2];
        c_textureObjectData.od_objectTranformData.odt_sx = c_objectData.od_objectTranformData.odt_sx = ct_psr[1][0];
        c_textureObjectData.od_objectTranformData.odt_sy = c_objectData.od_objectTranformData.odt_sy = ct_psr[1][1];
        c_textureObjectData.od_objectTranformData.odt_sz = c_objectData.od_objectTranformData.odt_sz = ct_psr[1][2];
        c_textureObjectData.od_objectTranformData.odt_rx = c_objectData.od_objectTranformData.odt_rx = ct_psr[2][0];
        c_textureObjectData.od_objectTranformData.odt_ry = c_objectData.od_objectTranformData.odt_ry = ct_psr[2][1];
        c_textureObjectData.od_objectTranformData.odt_rz = c_objectData.od_objectTranformData.odt_rz = ct_psr[2][2];

        c_sh.bind();
        c_vao.bind();
        if(c_texturesOn)
        {
            c_tex.bind();
        }

        if(cc_shadeType == solid)
        {
            glUniformMatrix4fv(glGetUniformLocation(c_sh.GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(c_transform));
        }
        else if(cc_shadeType == shade)
        {
            glUniformMatrix4fv(glGetUniformLocation(c_sh.GetID(), "projectionTransform"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));
            glUniformMatrix4fv(glGetUniformLocation(c_sh.GetID(), "viewTransform"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));
            glUniformMatrix4fv(glGetUniformLocation(c_sh.GetID(), "modelTransform"), 1, GL_FALSE, glm::value_ptr(c_transform));
        }

        if(!c_texturesOn)
            glDrawElements(cf_drawMode, (sizeof(float) * c_objectData.od_vertices.size()) / 2, GL_UNSIGNED_INT, NULL);
        else
            glDrawArrays(cf_drawMode, 0, 36);

        c_sh.unbind();
        c_vao.unbind();
    }

    void Aws_Cube::DrawCube(const unsigned int &cf_drawMode, glm::mat4x4 cf_projection, glm::mat4x4 cf_view)
    {
        c_textureObjectData.od_objectTranformData.odt_px = c_objectData.od_objectTranformData.odt_px = ct_psr[0][0];
        c_textureObjectData.od_objectTranformData.odt_py = c_objectData.od_objectTranformData.odt_py = ct_psr[0][1];
        c_textureObjectData.od_objectTranformData.odt_pz = c_objectData.od_objectTranformData.odt_pz = ct_psr[0][2];
        c_textureObjectData.od_objectTranformData.odt_sx = c_objectData.od_objectTranformData.odt_sx = ct_psr[1][0];
        c_textureObjectData.od_objectTranformData.odt_sy = c_objectData.od_objectTranformData.odt_sy = ct_psr[1][1];
        c_textureObjectData.od_objectTranformData.odt_sz = c_objectData.od_objectTranformData.odt_sz = ct_psr[1][2];
        c_textureObjectData.od_objectTranformData.odt_rx = c_objectData.od_objectTranformData.odt_rx = ct_psr[2][0];
        c_textureObjectData.od_objectTranformData.odt_ry = c_objectData.od_objectTranformData.odt_ry = ct_psr[2][1];
        c_textureObjectData.od_objectTranformData.odt_rz = c_objectData.od_objectTranformData.odt_rz = ct_psr[2][2];

        c_sh.bind();
        c_vao.bind();
        if(c_texturesOn)
        {
            c_tex.bind();
        }

        if(cc_shadeType == solid)
        {
            glUniformMatrix4fv(glGetUniformLocation(c_sh.GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(cf_projection * cf_view * c_transform));
        }
        else if(cc_shadeType == shade)
        {
            glUniformMatrix4fv(glGetUniformLocation(c_sh.GetID(), "projectionTransform"), 1, GL_FALSE, glm::value_ptr(cf_projection));
            glUniformMatrix4fv(glGetUniformLocation(c_sh.GetID(), "viewTransform"), 1, GL_FALSE, glm::value_ptr(cf_view));
            glUniformMatrix4fv(glGetUniformLocation(c_sh.GetID(), "modelTransform"), 1, GL_FALSE, glm::value_ptr(c_transform));
        }

        if(!c_texturesOn)
            glDrawElements(cf_drawMode, (sizeof(float) * c_objectData.od_vertices.size()) / 2, GL_UNSIGNED_INT, NULL);
        else
            glDrawArrays(cf_drawMode, 0, 36);

        c_sh.unbind();
        c_vao.unbind();
    }

    void Aws_Cube::SetPosition(float cf_x, float cf_y, float cf_z)
    {
        ct_psr[0][0] = cf_x;
        ct_psr[0][1] = cf_y;
        ct_psr[0][2] = cf_z;

        c_transform = glm::translate(glm::mat4(1.0), glm::vec3(ct_psr[0][0], ct_psr[0][1], ct_psr[0][2]));
        c_transform = glm::rotate(c_transform, glm::radians(ct_psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
        c_transform = glm::rotate(c_transform, glm::radians(ct_psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
        c_transform = glm::rotate(c_transform, glm::radians(ct_psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
        c_transform = glm::scale(c_transform, glm::vec3(ct_psr[1][0], ct_psr[1][1], ct_psr[1][2]));
    }

    void Aws_Cube::SetScale(float cf_x, float cf_y, float cf_z)
    {
        ct_psr[1][0] = cf_x;
        ct_psr[1][1] = cf_y;
        ct_psr[1][2] = cf_z;

        c_transform = glm::translate(glm::mat4(1.0), glm::vec3(ct_psr[0][0], ct_psr[0][1], ct_psr[0][2]));
        c_transform = glm::rotate(c_transform, glm::radians(ct_psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
        c_transform = glm::rotate(c_transform, glm::radians(ct_psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
        c_transform = glm::rotate(c_transform, glm::radians(ct_psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
        c_transform = glm::scale(c_transform, glm::vec3(ct_psr[1][0], ct_psr[1][1], ct_psr[1][2]));
    }

    void Aws_Cube::SetRotation(float cf_x, float cf_y, float cf_z)
    {
        ct_psr[2][0] = cf_x;
        ct_psr[2][1] = cf_y;
        ct_psr[2][2] = cf_z;

        c_transform = glm::translate(glm::mat4(1.0), glm::vec3(ct_psr[0][0], ct_psr[0][1], ct_psr[0][2]));
        c_transform = glm::rotate(c_transform, glm::radians(ct_psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
        c_transform = glm::rotate(c_transform, glm::radians(ct_psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
        c_transform = glm::rotate(c_transform, glm::radians(ct_psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
        c_transform = glm::scale(c_transform, glm::vec3(ct_psr[1][0], ct_psr[1][1], ct_psr[1][2]));
    }

    void Aws_Cube::SetTexture(const std::string cf_textureName, const int cf_wrapping, const int cf_textureType)
    {
        c_vao.bind();

        c_tex.bind({cf_textureName}, cf_wrapping, cf_textureType);

        c_vao.unbind();
    }

    void Aws_Cube::SetTexture(const std::vector<std::string> cf_textureName, const int cf_wrapping)
    {
        c_vao.bind();

        c_tex.bind(cf_textureName, cf_wrapping, GL_TEXTURE_CUBE_MAP);

        c_vao.unbind();
    }

    void Aws_Cube::SetColor(const float r, const float g, const float b, const float a)
    {
        if(cc_shadeType == solid)
        {
            c_sh.bind();
            c_vao.bind();

            glUniform4f(glGetUniformLocation(c_sh.GetID(), "iCol"), r, g, b, a);

            c_vao.unbind();
            c_sh.unbind();
        }
        else if(cc_shadeType == shade)
        {
            c_sh.bind();

            glUniform3f(glGetUniformLocation(c_sh.GetID(), "objectColor"), r, g, b);
            glUniform1f(glGetUniformLocation(c_sh.GetID(), "alpha"), a);

            c_sh.unbind();
        }
    }

    void Aws_Cube::SetTextureCoordinates(float cf_x, float cf_y)
    {
        if(cf_x != 0.0f || cf_y != 0.0f)
        {
            for(int i = 0; i < (1 * c_textureObjectData.od_textureCoordinates.size()) / 2; i++)
            {
                if(c_textureObjectData.od_textureCoordinates[i * 2] > 0.0f)
                {
                    c_textureObjectData.od_textureCoordinates[i * 2] = cf_x;
                }

                if(c_textureObjectData.od_textureCoordinates[i * 2 + 1] > 0.0f)
                {
                    c_textureObjectData.od_textureCoordinates[i * 2 + 1] = cf_y;
                }
            }

            c_vbo[1].bind(c_textureObjectData.od_textureCoordinates.data(), sizeof(float) * c_textureObjectData.od_textureCoordinates.size(), 2, 2);
        }
    }

    void Aws_Cube::Terminate()
    {
        c_vao.terminate();
        c_vbo->terminate();
        c_ebo.terminate();
        c_tex.terminate();
    }

    typedef Aws_Cube Cube;
}