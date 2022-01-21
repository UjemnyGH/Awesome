#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

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

    const std::string shadeTextureVS = "data/shaders/shades/texture/shadeColorVS.glsl";
    const std::string shadeTextureFS = "data/shaders/shades/texture/shadeColorFS.glsl";

    const std::string diffuseVS = "data/shaders/diffuse/color/diffuseVS.glsl";
    const std::string diffuseFS = "data/shaders/diffuse/color/diffuseFS.glsl";

    const std::string textureVS = "data/shaders/texture/textureVS.glsl";
    const std::string textureFS = "data/shaders/texture/textureFS.glsl";

    const std::string cubeVS = "data/shaders/cube/cubeVS.glsl";
    const std::string cubeFS = "data/shaders/cube/cubeFS.glsl";
	
	const char* vsAtlas =
	"#version 450 core\n"
	"uniform mat4 transform;\n"
	"uniform mat4 projection;\n"
	"uniform mat4 view;\n"
	"layout(location = 0)in vec4 iPos;\n"
	"layout(location = 1)in vec2 iTex;\n"
	"layout(location = 2)in vec4 iCol;\n"
	"out vec4 ioCol;\n"
	"out vec2 ioTex;\n"
	"void main()\n"
	"{\n"
	"gl_Position = (projection * view * transform) * iPos;\n"
	"ioCol = iCol;\n"
	"ioTex = iTex;\n"
	"}\n";

	const char* fsAtlas =
	"#version 450 core\n"
	"uniform sampler2D textures;\n"
	"out vec4 oCol;\n"
	"in vec4 ioCol;\n"
	"in vec2 ioTex;\n"
	"void main()\n"
	"{\n"
	"vec4 fragment;\n"
	"fragment = texture(textures, ioTex) * ioCol;\n"
	"if(fragment.w < 0.1) discard;\n"
	"oCol = fragment;\n"
	"}\n";

    int windowWidth = 800;
    int windowHeight = 600;
    float windowMouseX = 1.0f;
    float windowMouseY = 1.0f;

    void SetWindowAndMouseParameters(const int & width, const int & height, const float & mouseX, const float & mouseY)
    {
        windowWidth = width;
        windowHeight = height;
        windowMouseX = mouseX;
        windowMouseY = mouseY;
    }
	
	unsigned int ShaderFromCode(const char* shader, int type)
	{
		unsigned int shad = glCreateShader(type);
		glShaderSource(shad, 1, &shader, nullptr);
		glCompileShader(shad);

		return shad;
	}

	const double pixelInAtlas128 = 1.0 / 128.0;
	const double sizeAtlas128 = (1.0 / 128.0) * 16.0;

	struct TextureAtlasData
	{
		float x0;
		float y0;

		float x1;
		float y1;

		float x2;
		float y2;

		float x3;
		float y3;

		float x4;
		float y4;

		float x5;
		float y5;

		TextureAtlasData(float nx0, float ny0, float nx1, float ny1, float nx2, float ny2, float nx3, float ny3, float nx4, float ny4, float nx5, float ny5)
		{
			x0 = nx0;
			y0 = ny0;

			x1 = nx1;
			y1 = ny1;

			x2 = nx2;
			y2 = ny2;

			x3 = nx3;
			y3 = ny3;

			x4 = nx4;
			y4 = ny4;

			x5 = nx5;
			y5 = ny5;
		}

		TextureAtlasData(const TextureAtlasData& TAD)
		{
			x0 = TAD.x0;
			y0 = TAD.y0;

			x1 = TAD.x1;
			y1 = TAD.y1;

			x2 = TAD.x2;
			y2 = TAD.y2;

			x3 = TAD.x3;
			y3 = TAD.y3;

			x4 = TAD.x4;
			y4 = TAD.y4;

			x5 = TAD.x5;
			y5 = TAD.y5;
		}
	};

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

        /**
         * @brief 
         * 
         * @param vec1 
         * @return Aws_vec& 
         */
        Aws_vec& operator=(const Aws_vec & vec1) { this->vx = vec1.vx; this->vy = vec1.vy; this->vz = vec1.vz; this->vz = vec1.vz; return *this; }
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

        Aws_dvec& operator=(const Aws_dvec & vec1) { this->vx = vec1.vx; this->vy = vec1.vy; this->vz = vec1.vz; this->vz = vec1.vz; return *this; }
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

    struct Aws_ObjectTransformData
    {
        float odt_px = 0.0f;
        float odt_py = 0.0f;
        float odt_pz = 0.0f;
        float odt_sx = 1.0f;
        float odt_sy = 1.0f;
        float odt_sz = 1.0f;
        float odt_rx = 0.0f;
        float odt_ry = 0.0f;
        float odt_rz = 0.0f;

        Aws_ObjectTransformData operator=(const Aws_ObjectTransformData & otdf_objectTransformData)
        {
            this->odt_px = otdf_objectTransformData.odt_px;
            this->odt_py = otdf_objectTransformData.odt_py;
            this->odt_pz = otdf_objectTransformData.odt_pz;
            this->odt_sx = otdf_objectTransformData.odt_sx;
            this->odt_sy = otdf_objectTransformData.odt_sy;
            this->odt_sz = otdf_objectTransformData.odt_sz;
            this->odt_rx = otdf_objectTransformData.odt_rx;
            this->odt_ry = otdf_objectTransformData.odt_ry;
            this->odt_rz = otdf_objectTransformData.odt_rz;

            return *this;
        }
    };

    typedef Aws_ObjectTransformData ObjectTransformData;

    struct Aws_ObjectData
    {
        ObjectTransformData od_objectTranformData;

        std::vector<float> od_vertices{1.0f};
        std::vector<unsigned int> od_indices{1};
        std::vector<unsigned int> od_indicesTex{1};
        std::vector<unsigned int> od_indicesNor{1};
        std::vector<float> od_textureCoordinates{1.0f};
        std::vector<float> od_normals{1.0f};

        bool arrayOn = false;

        Aws_ObjectData()
        {
            od_vertices[0] = {0.0f};
            od_indices[0] = {0};
            od_textureCoordinates[0] = {0.0f};
            od_normals[0] = {0.0f};
            od_indicesTex[0] = {0};
            od_indicesNor[0] = {0};
        }

        Aws_ObjectData(const std::vector<float> & odf_vertices, const std::vector<unsigned int> & odf_indices, const std::vector<float> & odf_textureCoords, const std::vector<float> & odf_normals, const std::vector<unsigned int> & odf_indicesTexture, const std::vector<unsigned int> & odf_indicesNormal)
        {
            this->od_vertices.clear();
            this->od_indices.clear();
            this->od_textureCoordinates.clear();
            this->od_normals.clear();
            this->od_indicesTex.clear();
            this->od_indicesNor.clear();

            od_vertices = odf_vertices;
            od_indices = odf_indices;
            od_textureCoordinates = odf_textureCoords;
            od_normals = odf_normals;
            od_indicesTex = odf_indicesTexture;
            od_indicesNor = odf_indicesNormal;
        }

        Aws_ObjectData& operator=(const Aws_ObjectData & objData)
        {
            this->od_vertices.clear();
            this->od_indices.clear();
            this->od_textureCoordinates.clear();
            this->od_normals.clear();
            this->od_indicesTex.clear();
            this->od_indicesNor.clear();

            this->od_vertices = objData.od_vertices;
            this->od_indices = objData.od_indices;
            this->od_textureCoordinates = objData.od_textureCoordinates;
            this->od_normals = objData.od_normals;
            this->od_indicesTex = objData.od_indicesTex;
            this->od_indicesNor = objData.od_indicesNor;

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

    const ObjectData cubeTextured(
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
}
