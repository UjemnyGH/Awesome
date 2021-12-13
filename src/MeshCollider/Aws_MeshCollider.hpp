#pragma once

#include "../Aws_Types.hpp"
#include "../Object/Aws_Object.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace AWS
{
    struct Aws_CollisionHandler
    {
        Shader ch_sh[2];
        VAO ch_vao[2];
        VBO ch_vbo[2];
        EBO ch_ebo[2];

        glm::mat4 ch_transform[2] = { glm::mat4(1.0), glm::mat4(1.0) };

        std::vector<bool> isColliding;
        ObjectData ch_objectData1Save;
        ObjectData ch_objectData2Save;
        
        void CollisionCheck(const ObjectData& chf_objectData1, const std::vector<ObjectData>& chf_objectData2 = { ObjectData() }, float x = 0.8f, float y = 1.0f, float z = 0.8f);
        bool CollisionCheck(const ObjectData& chf_objectData1, const ObjectData& chf_objectData2, float x, float y, float z);
        void DebugInit();
        void DebugDraw(glm::mat4 proj, glm::mat4 view);
        void CollisionClear() { isColliding.clear(); }
    };

    void Aws_CollisionHandler::CollisionCheck(const ObjectData& chf_objectData1, const std::vector<ObjectData>& chf_objectData2, float x, float y, float z)
    {
        for(unsigned int i = 0; i < (1 * chf_objectData2.size()); i++)
        {
            bool collisionX = chf_objectData1.od_objectTranformData.odt_px + chf_objectData1.od_objectTranformData.odt_sx
                 >= chf_objectData2[i].od_objectTranformData.odt_px - (chf_objectData2[i].od_objectTranformData.odt_sx * x) && chf_objectData2[i].od_objectTranformData.odt_px + 
                chf_objectData2[i].od_objectTranformData.odt_sx >= chf_objectData1.od_objectTranformData.odt_px;

            bool collisionY = chf_objectData1.od_objectTranformData.odt_py + chf_objectData1.od_objectTranformData.odt_sy
                 >= chf_objectData2[i].od_objectTranformData.odt_py - (chf_objectData2[i].od_objectTranformData.odt_sy * y) && chf_objectData2[i].od_objectTranformData.odt_py + 
                chf_objectData2[i].od_objectTranformData.odt_sy >= chf_objectData1.od_objectTranformData.odt_py;

            bool collisionZ = chf_objectData1.od_objectTranformData.odt_pz + chf_objectData1.od_objectTranformData.odt_sz
                 >= chf_objectData2[i].od_objectTranformData.odt_pz - (chf_objectData2[i].od_objectTranformData.odt_sz * z) && chf_objectData2[i].od_objectTranformData.odt_pz + 
                chf_objectData2[i].od_objectTranformData.odt_sz >= chf_objectData1.od_objectTranformData.odt_pz;

            isColliding.push_back(collisionX && collisionY && collisionZ);
        }
    }

    bool Aws_CollisionHandler::CollisionCheck(const ObjectData& chf_objectData1, const ObjectData& chf_objectData2, float x, float y, float z)
    {
        ch_objectData1Save = chf_objectData1;
        ch_objectData2Save = chf_objectData2;

        bool collisionX = chf_objectData1.od_objectTranformData.odt_px + chf_objectData1.od_objectTranformData.odt_sx + glm::radians(chf_objectData1.od_objectTranformData.odt_rx)
             >= chf_objectData2.od_objectTranformData.odt_px - (chf_objectData2.od_objectTranformData.odt_sx * x) + glm::radians(chf_objectData2.od_objectTranformData.odt_rx)
             && chf_objectData2.od_objectTranformData.odt_px + chf_objectData2.od_objectTranformData.odt_sx + glm::radians(chf_objectData2.od_objectTranformData.odt_rx) >= 
            chf_objectData1.od_objectTranformData.odt_px;

        bool collisionY = chf_objectData1.od_objectTranformData.odt_py + chf_objectData1.od_objectTranformData.odt_sy + glm::radians(chf_objectData1.od_objectTranformData.odt_ry)
             >= chf_objectData2.od_objectTranformData.odt_py - (chf_objectData2.od_objectTranformData.odt_sy * y) + glm::radians(chf_objectData2.od_objectTranformData.odt_ry)
            && chf_objectData2.od_objectTranformData.odt_py + chf_objectData2.od_objectTranformData.odt_sy + glm::radians(chf_objectData2.od_objectTranformData.odt_ry) >= 
            chf_objectData1.od_objectTranformData.odt_py;

        bool collisionZ = chf_objectData1.od_objectTranformData.odt_pz + chf_objectData1.od_objectTranformData.odt_sz + glm::radians(chf_objectData1.od_objectTranformData.odt_rz)
             >= chf_objectData2.od_objectTranformData.odt_pz  - (chf_objectData2.od_objectTranformData.odt_sy * z) + glm::radians(chf_objectData2.od_objectTranformData.odt_rz)
            && chf_objectData2.od_objectTranformData.odt_pz + chf_objectData2.od_objectTranformData.odt_sz + glm::radians(chf_objectData2.od_objectTranformData.odt_rz) >= 
            chf_objectData1.od_objectTranformData.odt_pz;

        return collisionX && collisionY && collisionZ;
    }

    void Aws_CollisionHandler::DebugInit()
    {
        ch_sh[0].create(AWS::colorVS, AWS::colorFS);

        ch_vao[0].create();
        ch_vao[0].bind();

        ch_vbo[0].create();
        ch_vbo[0].bind(ch_objectData1Save.od_vertices.data(), ch_objectData1Save.od_vertices.size() * sizeof(float), 0, 3);

        ch_ebo[0].create();
        ch_ebo[0].bind(ch_objectData1Save.od_indices.data(), ch_objectData1Save.od_indices.size() * sizeof(unsigned int));

        ch_vao[0].unbind();

        ch_sh[1].create(AWS::colorVS, AWS::colorFS);

        ch_vao[1].create();
        ch_vao[1].bind();

        ch_vbo[1].create();
        ch_vbo[1].bind(ch_objectData2Save.od_vertices.data(), ch_objectData2Save.od_vertices.size() * sizeof(float), 0, 3);

        ch_ebo[1].create();
        ch_ebo[1].bind(ch_objectData2Save.od_indices.data(), ch_objectData2Save.od_indices.size() * sizeof(unsigned int));

        ch_vao[1].unbind();
    }

    void Aws_CollisionHandler::DebugDraw(glm::mat4 proj, glm::mat4 view)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        ch_sh[0].bind();
        ch_vao[0].bind();

        ch_transform[0] = glm::translate(glm::mat4(1.0), glm::vec3(ch_objectData1Save.od_objectTranformData.odt_px, ch_objectData1Save.od_objectTranformData.odt_py, ch_objectData1Save.od_objectTranformData.odt_pz));
        ch_transform[0] = glm::rotate(ch_transform[0], glm::radians(ch_objectData1Save.od_objectTranformData.odt_rx), glm::vec3(1.0f, 0.0f, 0.0f));
        ch_transform[0] = glm::rotate(ch_transform[0], glm::radians(ch_objectData1Save.od_objectTranformData.odt_ry), glm::vec3(0.0f, 1.0f, 0.0f));
        ch_transform[0] = glm::rotate(ch_transform[0], glm::radians(ch_objectData1Save.od_objectTranformData.odt_rz), glm::vec3(0.0f, 0.0f, 1.0f));
        ch_transform[0] = glm::scale(ch_transform[0], glm::vec3(ch_objectData1Save.od_objectTranformData.odt_sx, ch_objectData1Save.od_objectTranformData.odt_sy, ch_objectData1Save.od_objectTranformData.odt_sz));

        ch_vbo[0].bind(ch_objectData1Save.od_vertices.data(), ch_objectData1Save.od_vertices.size() * sizeof(float), 0, 3);
        ch_ebo[0].bind(ch_objectData1Save.od_indices.data(), ch_objectData1Save.od_indices.size() * sizeof(unsigned int));

        glUniform4f(glGetUniformLocation(ch_sh[0].GetID(), "iCol"), 0.0f, 1.0f, 0.0f, 1.0f);
        glUniformMatrix4fv(glGetUniformLocation(ch_sh[0].GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(proj * view * ch_transform[0]));

        glDrawElements(GL_TRIANGLES, ch_objectData1Save.od_vertices.size(), GL_UNSIGNED_INT, NULL);

        ch_vao[0].unbind();
        ch_sh[0].unbind();

        ch_sh[1].bind();
        ch_vao[1].bind();

        ch_transform[1] = glm::translate(glm::mat4(1.0), glm::vec3(ch_objectData2Save.od_objectTranformData.odt_px, ch_objectData2Save.od_objectTranformData.odt_py, ch_objectData2Save.od_objectTranformData.odt_pz));
        ch_transform[1] = glm::rotate(ch_transform[1], glm::radians(ch_objectData2Save.od_objectTranformData.odt_rx), glm::vec3(1.0f, 0.0f, 0.0f));
        ch_transform[1] = glm::rotate(ch_transform[1], glm::radians(ch_objectData2Save.od_objectTranformData.odt_ry), glm::vec3(0.0f, 1.0f, 0.0f));
        ch_transform[1] = glm::rotate(ch_transform[1], glm::radians(ch_objectData2Save.od_objectTranformData.odt_rz), glm::vec3(0.0f, 0.0f, 1.0f));
        ch_transform[1] = glm::scale(ch_transform[1], glm::vec3(ch_objectData2Save.od_objectTranformData.odt_sx, ch_objectData2Save.od_objectTranformData.odt_sy, ch_objectData2Save.od_objectTranformData.odt_sz));

        ch_vbo[1].bind(ch_objectData2Save.od_vertices.data(), ch_objectData2Save.od_vertices.size() * sizeof(float), 0, 3);
        ch_ebo[1].bind(ch_objectData2Save.od_indices.data(), ch_objectData2Save.od_indices.size() * sizeof(unsigned int));

        glUniform4f(glGetUniformLocation(ch_sh[1].GetID(), "iCol"), 0.0f, 1.0f, 0.0f, 1.0f);
        glUniformMatrix4fv(glGetUniformLocation(ch_sh[1].GetID(), "transform"), 1, GL_FALSE, glm::value_ptr(proj * view * ch_transform[1]));

        glDrawElements(GL_TRIANGLES, ch_objectData2Save.od_vertices.size(), GL_UNSIGNED_INT, NULL);

        ch_vao[1].unbind();
        ch_sh[1].unbind();

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    typedef Aws_CollisionHandler CollisionHandler;

    class Aws_CubeCollider
    {
    private:
        ObjectData cc_objectData = ObjectData(
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
                0
            },
            {
                0.0f
            },
            {
                0.0f
            },
            {
                0
            },
            {
                0
            }
        );

    public:
        /**
         * @brief Set the Position object
         * 
         * @param ccf_x x axis
         * @param ccf_y y axis
         * @param ccf_z z axis
         */
        void SetPosition(float ccf_x, float ccf_y, float ccf_z);

        /**
         * @brief Set the Scale object
         * 
         * @param ccf_x x axis
         * @param ccf_y y axis
         * @param ccf_z z axis
         */
        void SetScale(float ccf_x, float ccf_y, float ccf_z);

        /**
         * @brief Set the Rotation object
         * 
         * @param ccf_x x axis in degrees
         * @param ccf_y y axis in degrees
         * @param ccf_z z axis in degrees
         */
        void SetRotation(float ccf_x, float ccf_y, float ccf_z);

        /**
         * @brief Get the Object Data object
         * 
         * @return ObjectData 
         */
        ObjectData GetObjectData() { return cc_objectData; }
    };

    void Aws_CubeCollider::SetPosition(float ccf_x, float ccf_y, float ccf_z)
    {
        cc_objectData.od_objectTranformData.odt_px = ccf_x;
        cc_objectData.od_objectTranformData.odt_py = ccf_y;
        cc_objectData.od_objectTranformData.odt_pz = ccf_z;
    }

    void Aws_CubeCollider::SetScale(float ccf_x, float ccf_y, float ccf_z)
    {
        cc_objectData.od_objectTranformData.odt_sx = ccf_x;
        cc_objectData.od_objectTranformData.odt_sy = ccf_y;
        cc_objectData.od_objectTranformData.odt_sz = ccf_z;
    }

    void Aws_CubeCollider::SetRotation(float ccf_x, float ccf_y, float ccf_z)
    {
        cc_objectData.od_objectTranformData.odt_rx = ccf_x;
        cc_objectData.od_objectTranformData.odt_ry = ccf_y;
        cc_objectData.od_objectTranformData.odt_rz = ccf_z;
    }

    typedef Aws_CubeCollider CubeCollider;

    class Aws_SquareCollider
    {
    private:
        ObjectData sc_objectData = ObjectData(
            {
                1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f
            },
            {
                0
            },
            {
                0.0f
            },
            {
                0.0f
            },
            {
                0
            },
            {
                0
            }
        );

    public:
        /**
         * @brief Set the Position object
         * 
         * @param ccf_x x axis
         * @param ccf_y y axis
         * @param ccf_z z axis
         */
        void SetPosition(float scf_x, float scf_y, float scf_z);

        /**
         * @brief Set the Scale object
         * 
         * @param ccf_x x axis
         * @param ccf_y y axis
         * @param ccf_z z axis
         */
        void SetScale(float scf_x, float scf_y, float scf_z);

        /**
         * @brief Set the Rotation object
         * 
         * @param ccf_x x axis in degrees
         * @param ccf_y y axis in degrees
         * @param ccf_z z axis in degrees
         */
        void SetRotation(float scf_x, float scf_y, float scf_z);

        /**
         * @brief Get the Object Data object
         * 
         * @return ObjectData 
         */
        ObjectData GetObjectData() { return sc_objectData; }
    };

    void Aws_SquareCollider::SetPosition(float scf_x, float scf_y, float scf_z)
    {
        sc_objectData.od_objectTranformData.odt_px = scf_x;
        sc_objectData.od_objectTranformData.odt_py = scf_y;
        sc_objectData.od_objectTranformData.odt_pz = scf_z;
    }

    void Aws_SquareCollider::SetScale(float scf_x, float scf_y, float scf_z)
    {
        sc_objectData.od_objectTranformData.odt_sx = scf_x;
        sc_objectData.od_objectTranformData.odt_sy = scf_y;
        sc_objectData.od_objectTranformData.odt_sz = scf_z;
    }

    void Aws_SquareCollider::SetRotation(float scf_x, float scf_y, float scf_z)
    {
        sc_objectData.od_objectTranformData.odt_rx = scf_x;
        sc_objectData.od_objectTranformData.odt_ry = scf_y;
        sc_objectData.od_objectTranformData.odt_rz = scf_z;
    }

    typedef Aws_SquareCollider SquareCollider;
}