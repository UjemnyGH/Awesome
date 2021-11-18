#pragma once

#include <glm/glm.hpp>
#include <string>

namespace AWS
{
    const std::string colorVS = "data/shaders/color/colorVS.glsl";
    const std::string colorFS = "data/shaders/color/colorFS.glsl";

    const std::string textureVS = "data/shaders/texture/textureVS.glsl";
    const std::string textureFS = "data/shaders/texture/textureFS.glsl";

    const std::string cubeVS = "data/shaders/cube/cubeVS.glsl";
    const std::string cubeFS = "data/shaders/cube/cubeFS.glsl";

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
