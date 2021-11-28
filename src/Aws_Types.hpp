#pragma once

#include <glm/glm.hpp>
#include <string>

namespace AWS
{
    enum ShadeType
    {
        solid,
        shade,
        light
    };

    enum CubeTexturing
    {
        cubemap = GL_TEXTURE_CUBE_MAP,
        texture2D = GL_TEXTURE_2D
    };

    const std::string colorVS = "data/shaders/color/colorVS.glsl";
    const std::string colorFS = "data/shaders/color/colorFS.glsl";

    const std::string shadeColorVS = "data/shaders/shades/color/shadeColorVS.glsl";
    const std::string shadeColorFS = "data/shaders/shades/color/shadeColorFS.glsl";

    const std::string textureVS = "data/shaders/texture/textureVS.glsl";
    const std::string textureFS = "data/shaders/texture/textureFS.glsl";

    const std::string cubeVS = "data/shaders/cube/cubeVS.glsl";
    const std::string cubeFS = "data/shaders/cube/cubeFS.glsl";

    struct Aws_ObjectData
    {
        std::vector<float> od_vertices{1.0f};
        std::vector<float> od_color{1.0f};
        std::vector<unsigned int> od_indices{1};
        std::vector<unsigned int> od_indicesTex{1};
        std::vector<unsigned int> od_indicesNor{1};
        std::vector<float> od_textureCoordinates{1.0f};
        std::vector<float> od_normals{1.0f};

        Aws_ObjectData()
        {
            od_vertices[0] = {0.0f};
            od_color[0] = {0.0f};
            od_indices[0] = {0};
            od_textureCoordinates[0] = {0.0f};
            od_normals[0] = {0.0f};
            od_indicesTex[0] = {0};
            od_indicesNor[0] = {0};
        }

        Aws_ObjectData(const std::vector<float> & odf_vertices, const std::vector<float> & odf_color, const std::vector<unsigned int> & odf_indices, const std::vector<float> & odf_textureCoords, const std::vector<float> & odf_normals, const std::vector<unsigned int> & odf_indicesTexture, const std::vector<unsigned int> & odf_indicesNormal)
        {
            od_vertices.resize(odf_vertices.size());
            od_vertices = odf_vertices;
            od_color.resize(odf_color.size());
            od_color = odf_color;
            od_indices.resize(odf_indices.size());
            od_indices = odf_indices;
            od_textureCoordinates.resize(odf_textureCoords.size());
            od_textureCoordinates = odf_textureCoords;
            od_normals.resize(odf_normals.size());
            od_normals = odf_normals;
            od_indicesTex.resize(odf_indicesTexture.size());
            od_indicesTex = odf_indicesTexture;
            od_indicesNor.resize(odf_indicesNormal.size());
            od_indicesNor = odf_indicesNormal;
        }

        Aws_ObjectData& operator=(const Aws_ObjectData & objData)
        {
            od_vertices.resize(objData.od_vertices.size());
            od_vertices = objData.od_vertices;
            od_color.resize(objData.od_color.size());
            od_color = objData.od_color;
            od_indices.resize(objData.od_indices.size());
            od_indices = objData.od_indices;
            od_textureCoordinates.resize(objData.od_textureCoordinates.size());
            od_textureCoordinates = objData.od_textureCoordinates;
            od_normals.resize(objData.od_normals.size());
            od_normals = objData.od_normals;
            od_indicesTex.resize(objData.od_indicesTex.size());
            od_indicesTex = objData.od_indicesTex;
            od_indicesNor.resize(objData.od_indicesNor.size());
            od_indicesNor = objData.od_indicesNor;

            return *this;
        }
    };

    typedef Aws_ObjectData ObjectData;

    const ObjectData square(
        {
            1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f
        },
        {
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f
        },
        {
            0, 1, 2,
            1, 2, 3
        },
        {
            1.0f, 1.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        },
        {
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f
        },
        {
            1
        },
        {
            1
        }
    );

    const ObjectData cube(
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
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f
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
            1.0f, 1.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,

            1.0f, 1.0f,
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
            1
        },
        {
            1
        }
    );

    struct Aws_vec
    {
        float vx = 0.0f, vy = 0.0f, vz = 0.0f, vw = 0.0f;

        glm::vec4 glmConvert = glm::vec4(vx, vy, vz, vw);

        /**
         * @brief Construct a new Aws_vec object
         * 
         * @param x 
         * @param y 
         */
        Aws_vec(const float &x, const float &y) { vx = x; vy = y; }

        /**
         * @brief Construct a new Aws_vec object
         * 
         * @param x 
         * @param y 
         * @param z 
         */
        Aws_vec(const float &x, const float &y, const float &z) { vx = x; vy = y; vz = z; }

        /**
         * @brief Construct a new Aws_vec object
         * 
         * @param x 
         * @param y 
         * @param z 
         * @param w 
         */
        Aws_vec(const float &x, const float &y, const float &z, const float &w) { vx = x; vy = y; vz = z; vw = w; }
    };

    typedef Aws_vec vec;

    struct Aws_dvec
    {
        double vx = 0.0, vy = 0.0, vz = 0.0, vw = 0.0;

        glm::dvec4 glmConvert = glm::dvec4(vx, vy, vz, vw);

        /**
         * @brief Construct a new Aws_dvec object
         * 
         * @param x 
         * @param y 
         */
        Aws_dvec(const double &x, const double &y) { vx = x; vy = y; }

        /**
         * @brief Construct a new Aws_dvec object
         * 
         * @param x 
         * @param y 
         * @param z 
         */
        Aws_dvec(const double &x, const double &y, const double &z) { vx = x; vy = y; vz = z; }

        /**
         * @brief Construct a new Aws_dvec object
         * 
         * @param x 
         * @param y 
         * @param z 
         * @param w 
         */
        Aws_dvec(const double &x, const double &y, const double &z, const double &w) { vx = x; vy = y; vz = z; vw = w; }
    };

    typedef Aws_dvec dvec;

    struct Aws_Transform
    {
        vec position = vec(0.0f, 0.0f, 0.0f, 1.0f);
        vec scale = vec(1.0f, 1.0f, 1.0f, 1.0f);
        vec orientation = vec(0.0f, 0.0f, 0.0f, 1.0f);

        vec forward = vec(0.0f, 0.0f, 0.0f, 1.0f);
        vec right = vec(0.0f, 0.0f, 0.0f, 1.0f);
        vec up = vec(0.0f, 0.0f, 0.0f, 1.0f);

        float p[3] = {position.vx, position.vy, position.vz};
        float s[3] = {scale.vx, scale.vy, scale.vz};
        float o[3] = {orientation.vx, orientation.vy, orientation.vz};
        float f[3] = {forward.vx, forward.vy, forward.vz};
        float r[3] = {right.vx, right.vy, right.vz};
        float u[3] = {up.vx, up.vy, up.vz};

        /**
         * @brief Get the Position object
         * 
         * @return float* 
         */
        float* GetPosition() { return p; }

        /**
         * @brief Get the Scale object
         * 
         * @return float* 
         */
        float* GetScale() { return s; }

        /**
         * @brief Get the Orientation object
         * 
         * @return float* 
         */
        float* GetOrientation() { return o; }

        /**
         * @brief Get the Forward object
         * 
         * @return float* 
         */
        float* GetForward() { return f; }

        /**
         * @brief Get the Right object
         * 
         * @return float* 
         */
        float* GetRight() { return r; }

        /**
         * @brief Get the Up object
         * 
         * @return float* 
         */
        float* GetUp() { return u; }
    };
    
    typedef Aws_Transform Transform;    

    struct Aws_color
    {
        float vr = 0.0f, vg = 0.0f, vb = 0.0f;

        glm::vec3 glmConvert = glm::vec3(vr, vg, vb);

        /**
         * @brief Construct a new Aws_color object
         * 
         * @param r 
         * @param g 
         * @param b 
         */
        Aws_color(const float &r, const float &g, const float &b) { vr = r; vg = g; vb = b; }
    };

    typedef Aws_color color;

    typedef struct Aws_Orientation
    {
        vec X = vec(1.0f, 0.0f, 0.0f);
        vec Y = vec(0.0f, 1.0f, 0.0f);
        vec Z = vec(0.0f, 0.0f, 1.0f);
    } Orientation;
}
