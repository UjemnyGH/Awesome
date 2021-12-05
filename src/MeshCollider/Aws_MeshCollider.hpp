#pragma once

#include "../Aws_Types.hpp"
#include "../Object/Aws_Object.hpp"

namespace AWS
{
    struct Aws_CollisionHandler
    {
        std::vector<bool> isColliding;
        
        void CollisionCheck(const ObjectData& chf_objectData1, const std::vector<ObjectData>& chf_objectData2 = { ObjectData() });
        bool CollisionCheck(const ObjectData& chf_objectData1, const ObjectData& chf_objectData2);
        void CollisionClear() { isColliding.clear(); }
    };

    void Aws_CollisionHandler::CollisionCheck(const ObjectData& chf_objectData1, const std::vector<ObjectData>& chf_objectData2)
    {
        for(unsigned int i = 0; i < (1 * chf_objectData2.size()); i++)
        {
            bool collisionX = chf_objectData1.od_objectTranformData.odt_px + chf_objectData1.od_objectTranformData.odt_sx
                 >= chf_objectData2[i].od_objectTranformData.odt_px - (chf_objectData2[i].od_objectTranformData.odt_sx * 0.8f) && chf_objectData2[i].od_objectTranformData.odt_px + 
                chf_objectData2[i].od_objectTranformData.odt_sx >= chf_objectData1.od_objectTranformData.odt_px;

            bool collisionY = chf_objectData1.od_objectTranformData.odt_py + chf_objectData1.od_objectTranformData.odt_sy
                 >= chf_objectData2[i].od_objectTranformData.odt_py - (chf_objectData2[i].od_objectTranformData.odt_sy * 1.0f) && chf_objectData2[i].od_objectTranformData.odt_py + 
                chf_objectData2[i].od_objectTranformData.odt_sy >= chf_objectData1.od_objectTranformData.odt_py;

            bool collisionZ = chf_objectData1.od_objectTranformData.odt_pz + chf_objectData1.od_objectTranformData.odt_sz
                 >= chf_objectData2[i].od_objectTranformData.odt_pz - (chf_objectData2[i].od_objectTranformData.odt_sz * 0.8f) && chf_objectData2[i].od_objectTranformData.odt_pz + 
                chf_objectData2[i].od_objectTranformData.odt_sz >= chf_objectData1.od_objectTranformData.odt_pz;

            isColliding.push_back(collisionX && collisionY && collisionZ);
        }
    }

    bool Aws_CollisionHandler::CollisionCheck(const ObjectData& chf_objectData1, const ObjectData& chf_objectData2)
    {
        bool collisionX = chf_objectData1.od_objectTranformData.odt_px + chf_objectData1.od_objectTranformData.odt_sx
             >= chf_objectData2.od_objectTranformData.odt_px - (chf_objectData2.od_objectTranformData.odt_sx * 0.8f) && chf_objectData2.od_objectTranformData.odt_px + 
            chf_objectData2.od_objectTranformData.odt_sx >= chf_objectData1.od_objectTranformData.odt_px;

        bool collisionY = chf_objectData1.od_objectTranformData.odt_py + chf_objectData1.od_objectTranformData.odt_sy
             >= chf_objectData2.od_objectTranformData.odt_py - (chf_objectData2.od_objectTranformData.odt_sy * 1.0f) && chf_objectData2.od_objectTranformData.odt_py + 
            chf_objectData2.od_objectTranformData.odt_sy >= chf_objectData1.od_objectTranformData.odt_py;

        bool collisionZ = chf_objectData1.od_objectTranformData.odt_pz + chf_objectData1.od_objectTranformData.odt_sz
             >= chf_objectData2.od_objectTranformData.odt_pz && chf_objectData2.od_objectTranformData.odt_pz + 
            chf_objectData2.od_objectTranformData.odt_sz - (chf_objectData2.od_objectTranformData.odt_sy * 0.8f) >= chf_objectData1.od_objectTranformData.odt_pz;

        return collisionX && collisionY && collisionZ;
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