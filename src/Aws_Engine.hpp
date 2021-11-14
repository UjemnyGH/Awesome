#pragma once

#include "Window/Aws_Window.hpp"
#include "Time/Aws_Time.hpp"
#include "Buffers/Aws_Buffer.hpp"
#include "Square/Aws_Square.hpp"
#include "Cube/Aws_Cube.hpp"
#include "Camera/Aws_Camera.hpp"
#include <iostream>
#include <glm/glm.hpp>

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
}
