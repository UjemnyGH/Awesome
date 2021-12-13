#pragma once

#include "../Aws_Types.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace AWS
{
    struct RayData
    {
        glm::vec3 rayStart;
        glm::vec3 rayEnd;
    };

    /*float CheckRayPos(float rayX, float rayY, float rayZ, float endRayX, float endRayY, float endRayZ, const ObjectData & obj_data)
    {
        float rayLength = 0.0f;
        unsigned int closestIndex = 0;

        for(unsigned int i = 0; i < obj_data.od_vertices.size() / 3; i++)
        {
            
        }

        return rayLength;
    }*/

    float CheckRayPlane(float rayX, float rayY, float rayZ, float endRayX, float endRayY, float endRayZ, const ObjectData & obj_data)
    {
        float hit = 0.0;

        for(unsigned int i = 0; i < obj_data.od_normals.size() / 3; i++)
        {
            float dotP = glm::dot(glm::vec3(rayX, rayY, rayZ), glm::vec3(obj_data.od_normals[i * 3], obj_data.od_normals[i * 3 + 1], obj_data.od_normals[i * 3 + 2]));

            if(dotP == 0.0)
            {
                continue;
            }
            
            float distToHit = glm::dot(glm::vec3(obj_data.od_objectTranformData.odt_px, obj_data.od_objectTranformData.odt_py, obj_data.od_objectTranformData.odt_pz) - glm::vec3(endRayX, endRayY, endRayZ), glm::vec3(obj_data.od_normals[i * 3], obj_data.od_normals[i * 3 + 1], obj_data.od_normals[i * 3 + 2])) / dotP;
            if(distToHit < 0.0)
            {
                continue;
            }
            
            hit = distToHit;

            if(hit > 0.0f)
            {
                break;
            }
        }

        return hit;
    }

    bool CheckRayVertices(float rayX, float rayY, float rayZ, float endRayX, float endRayY, float endRayZ, glm::mat4 projection, glm::mat4 view, const ObjectData & obj_data)
    {
        RayData ray_data;

        ray_data.rayStart = glm::unProject(glm::vec3(rayX, rayY, rayZ), view, projection, glm::vec4(0.0f, 0.0f, windowWidth, windowHeight));
        ray_data.rayEnd = glm::unProject(glm::vec3(endRayX, endRayY, endRayZ), view, projection, glm::vec4(0.0f, 0.0f, windowWidth, windowHeight));

        glm::vec3 lineDirection = glm::normalize(ray_data.rayEnd - ray_data.rayStart);
        float lineLength = glm::distance(ray_data.rayStart, ray_data.rayEnd);

        for(unsigned int i = 0; i < obj_data.od_vertices.size() / 3; i++)
        {
            if(obj_data.od_vertices[i * 3 + 1] >= ray_data.rayEnd.y && obj_data.od_vertices[i * 3 + 1] <= ray_data.rayStart.y &&
            obj_data.od_vertices[i * 3] <= ray_data.rayEnd.x &&
            obj_data.od_vertices[i * 3 + 2] <= ray_data.rayEnd.z)
            {
                return true;
            }
        }

        return false;
    }

    glm::vec3 CheckRay(float rayX, float rayY, float rayZ, float endRayX, float endRayY, float endRayZ, glm::mat4 projection, glm::mat4 view, const ObjectData & obj_data)
    {
        RayData ray_data;

        ray_data.rayStart = glm::unProject(glm::vec3(rayX, rayY, rayZ), view, projection, glm::vec4(0.0f, 0.0f, windowWidth, windowHeight));
        ray_data.rayEnd = glm::unProject(glm::vec3(endRayX, endRayY, endRayZ), view, projection, glm::vec4(0.0f, 0.0f, windowWidth, windowHeight));

        glm::vec3 lineDirection = glm::normalize(ray_data.rayEnd - ray_data.rayStart);
        float lineLength = glm::distance(ray_data.rayStart, ray_data.rayEnd);

        glm::vec3 obj_Coords = glm::vec3(obj_data.od_objectTranformData.odt_px, obj_data.od_objectTranformData.odt_py, obj_data.od_objectTranformData.odt_pz);
        glm::vec3 dirToObject = obj_Coords - ray_data.rayStart;
        float t = glm::dot(dirToObject, lineDirection);

        glm::vec3 cl_Point;

        if(t <= 0.0f)
        {
            cl_Point = ray_data.rayStart;
        }
        else if(t >= lineLength)
        {
            cl_Point = ray_data.rayEnd;
        }
        else
        {
            cl_Point = ray_data.rayStart + lineDirection * t;
        }

        return cl_Point;
    }
}