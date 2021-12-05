#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <sstream>
#include <map>

/**
 * ml_ - mesh loader
 * mmodv_ - mesh object data
 * mmd_ - mesh material data
 * 
 */

namespace AWS
{
    struct Aws_MeshObjectData
    {
        //obj files
        std::vector<float> modv_vertices;
        std::vector<float> modv_textureCoords;
        std::vector<float> modv_normal;
        std::vector<float> modv_parameter;

        std::vector<unsigned int> modv_indices;
        std::vector<unsigned int> modv_indicesTexture;
        std::vector<unsigned int> modv_indicesNormal;

        std::vector<std::string> modv_objectName;
        std::vector<std::string> modv_groupName;

        short mod_smoothShading;
        std::string mod_mtlFileName;
        std::vector<std::string> modv_materialName;

        Aws_MeshObjectData& operator=(const Aws_MeshObjectData & data)
        {
            this->modv_vertices = data.modv_vertices;
            this->modv_textureCoords = data.modv_textureCoords;
            this->modv_normal = data.modv_normal;
            this->modv_parameter = data.modv_parameter;
            this->modv_indices = data.modv_indices;
            this->modv_indicesTexture = data.modv_indicesTexture;
            this->modv_indicesNormal = data.modv_indicesNormal;
            this->modv_objectName = data.modv_objectName;
            this->modv_groupName = data.modv_groupName;
            this->mod_smoothShading = data.mod_smoothShading;
            this->mod_mtlFileName = data.mod_mtlFileName;
            this->modv_materialName = data.modv_materialName;

            return *this;
        }
    };

    typedef Aws_MeshObjectData MeshObjectData;

    struct Aws_MeshMaterialData
    {
        //mtl
        std::vector<float> mmdv_ambient;
        std::vector<float> mmdv_diffuse;
        std::vector<float> mmdv_specular;

        std::vector<float> mmdv_transparent;
        std::vector<float> mmdv_transmissionFilter;
        std::vector<float> mmdv_density;
        std::vector<short> mmdv_illumination;
    };

    class Aws_MeshLoader
    {
    private:
        MeshObjectData ml_meshObjectData;
        MeshObjectData ml_workObjectData;

    public:
        /**
         * @brief Load mesh from file
         * 
         * @param meshPath path to mesh obj
         */
        void LoadMesh(const std::string & mlf_meshPath);

        /**
         * @brief Load mesh from file with glDrawArray setup
         * 
         * @param meshPath path to mesh obj
         */
        void LoadArrayMesh(const std::string & mlf_meshPath);

        /**
         * @brief Get the Data object
         * 
         * @return MeshObjectData 
         */
        MeshObjectData GetData() { return ml_meshObjectData; }
        
    };

    void Aws_MeshLoader::LoadMesh(const std::string & mlf_meshPath)
    {
        std::ifstream f;
    
        f.open(mlf_meshPath, std::ios::binary);

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

                ml_meshObjectData.modv_vertices.push_back(x);
                ml_meshObjectData.modv_vertices.push_back(y);
                ml_meshObjectData.modv_vertices.push_back(z);
            }
            else if(line.find("vt ") == 0)
            {
                std::stringstream ss(line.c_str() + 3);
                float u, v, w;
                ss >> u >> v >> w;

                ml_meshObjectData.modv_textureCoords.push_back(u);
                ml_meshObjectData.modv_textureCoords.push_back(v);
                ml_meshObjectData.modv_textureCoords.push_back(w);
            }
            else if(line.find("vn ") == 0)
            {
                std::stringstream ss(line.c_str() + 3);
                float x, y, z;
                ss >> x >> y >> z;

                ml_meshObjectData.modv_normal.push_back(x);
                ml_meshObjectData.modv_normal.push_back(y);
                ml_meshObjectData.modv_normal.push_back(z);
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

                ml_meshObjectData.modv_indices.push_back(indX - 1);
                ml_meshObjectData.modv_indices.push_back(indY - 1);
                ml_meshObjectData.modv_indices.push_back(indZ - 1);

                ml_meshObjectData.modv_indices.push_back(indX - 1);
                ml_meshObjectData.modv_indices.push_back(indZ - 1);
                ml_meshObjectData.modv_indices.push_back(indW - 1);

                ml_meshObjectData.modv_indicesTexture.push_back(texX - 1);
                ml_meshObjectData.modv_indicesTexture.push_back(texY - 1);
                ml_meshObjectData.modv_indicesTexture.push_back(texZ - 1);

                ml_meshObjectData.modv_indicesTexture.push_back(texX - 1);
                ml_meshObjectData.modv_indicesTexture.push_back(texZ - 1);
                ml_meshObjectData.modv_indicesTexture.push_back(texW - 1);

                ml_meshObjectData.modv_indicesNormal.push_back(norX - 1);
                ml_meshObjectData.modv_indicesNormal.push_back(norY - 1);
                ml_meshObjectData.modv_indicesNormal.push_back(norZ - 1);

                ml_meshObjectData.modv_indicesNormal.push_back(norX - 1);
                ml_meshObjectData.modv_indicesNormal.push_back(norZ - 1);
                ml_meshObjectData.modv_indicesNormal.push_back(norW - 1);
            }
            else if(line.find("mtllib "))
            {
                std::stringstream ss(line.c_str() + 7);

                std::string mtl;

                ss >> mtl;

                ml_meshObjectData.mod_mtlFileName = mtl;
            }
            else if(line.find("o "))
            {
                std::stringstream ss(line.c_str() + 2);

                std::string objectName;

                ss >> objectName;

                ml_meshObjectData.modv_objectName.push_back(objectName);
            }
            else if(line.find("g "))
            {
                std::stringstream ss(line.c_str() + 2);

                std::string groupName;

                ss >> groupName;

                ml_meshObjectData.modv_groupName.push_back(groupName);
            }
            else if(line.find("usemtl "))
            {
                std::stringstream ss(line.c_str() + 7);

                std::string materialName;

                ss >> materialName;

                ml_meshObjectData.modv_materialName.push_back(materialName);
            }
            else if(line.find("s "))
            {
                std::stringstream ss(line.c_str() + 2);

                short smoothLevel;
                std::string level;

                ss >> level;

                if(level == "off")
                {
                    smoothLevel = 0;
                }
                else
                {
                    ss >> smoothLevel;
                }

                ml_meshObjectData.mod_smoothShading = smoothLevel;
            }
        }
    }

    void Aws_MeshLoader::LoadArrayMesh(const std::string & mlf_meshPath)
    {
        std::ifstream f;
    
        f.open(mlf_meshPath, std::ios::binary);

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

                ml_workObjectData.modv_vertices.push_back(x);
                ml_workObjectData.modv_vertices.push_back(y);
                ml_workObjectData.modv_vertices.push_back(z);
            }
            else if(line.find("vt ") == 0)
            {
                std::stringstream ss(line.c_str() + 3);
                float u, v, w;
                ss >> u >> v >> w;

                ml_workObjectData.modv_textureCoords.push_back(u);
                ml_workObjectData.modv_textureCoords.push_back(v);
                ml_workObjectData.modv_textureCoords.push_back(w);
            }
            else if(line.find("vn ") == 0)
            {
                std::stringstream ss(line.c_str() + 3);
                float x, y, z;
                ss >> x >> y >> z;

                ml_workObjectData.modv_normal.push_back(x);
                ml_workObjectData.modv_normal.push_back(y);
                ml_workObjectData.modv_normal.push_back(z);
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

                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indX - 1]);
                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indX]);
                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indX + 1]);

                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indY - 1]);
                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indY]);
                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indY + 1]);

                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indZ - 1]);
                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indZ]);
                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indZ + 1]);

                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indX - 1]);
                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indX]);
                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indX + 1]);

                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indZ - 1]);
                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indZ]);
                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indZ + 1]);

                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indX - 1]);
                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indZ - 1]);
                ml_meshObjectData.modv_vertices.push_back(ml_workObjectData.modv_vertices[indW - 1]);

                ml_meshObjectData.modv_textureCoords.push_back(ml_workObjectData.modv_textureCoords[texX - 1]);
                ml_meshObjectData.modv_textureCoords.push_back(ml_workObjectData.modv_textureCoords[texX]);

                ml_meshObjectData.modv_textureCoords.push_back(ml_workObjectData.modv_textureCoords[texY - 1]);
                ml_meshObjectData.modv_textureCoords.push_back(ml_workObjectData.modv_textureCoords[texY]);

                ml_meshObjectData.modv_textureCoords.push_back(ml_workObjectData.modv_textureCoords[texZ - 1]);
                ml_meshObjectData.modv_textureCoords.push_back(ml_workObjectData.modv_textureCoords[texZ]);

                ml_meshObjectData.modv_textureCoords.push_back(ml_workObjectData.modv_textureCoords[texX - 1]);
                ml_meshObjectData.modv_textureCoords.push_back(ml_workObjectData.modv_textureCoords[texX]);

                ml_meshObjectData.modv_textureCoords.push_back(ml_workObjectData.modv_textureCoords[texZ - 1]);
                ml_meshObjectData.modv_textureCoords.push_back(ml_workObjectData.modv_textureCoords[texZ]);

                ml_meshObjectData.modv_textureCoords.push_back(ml_workObjectData.modv_textureCoords[texW - 1]);
                ml_meshObjectData.modv_textureCoords.push_back(ml_workObjectData.modv_textureCoords[texW]);

                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norX - 1]);
                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norX]);
                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norX + 1]);

                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norY - 1]);
                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norY]);
                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norY + 1]);

                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norZ - 1]);
                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norZ]);
                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norZ + 1]);

                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norX - 1]);
                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norX]);
                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norX + 1]);

                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norZ - 1]);
                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norZ]);
                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norZ + 1]);

                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norW - 1]);
                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norW]);
                ml_meshObjectData.modv_normal.push_back(ml_workObjectData.modv_normal[norW + 1]);
            }
            else if(line.find("mtllib "))
            {
                std::stringstream ss(line.c_str() + 7);

                std::string mtl;

                ss >> mtl;

                ml_meshObjectData.mod_mtlFileName = mtl;
            }
            else if(line.find("o "))
            {
                std::stringstream ss(line.c_str() + 2);

                std::string objectName;

                ss >> objectName;

                ml_meshObjectData.modv_objectName.push_back(objectName);
            }
            else if(line.find("g "))
            {
                std::stringstream ss(line.c_str() + 2);

                std::string groupName;

                ss >> groupName;

                ml_meshObjectData.modv_groupName.push_back(groupName);
            }
            else if(line.find("usemtl "))
            {
                std::stringstream ss(line.c_str() + 7);

                std::string materialName;

                ss >> materialName;

                ml_meshObjectData.modv_materialName.push_back(materialName);
            }
            else if(line.find("s "))
            {
                std::stringstream ss(line.c_str() + 2);

                short smoothLevel;
                std::string level;

                ss >> level;

                if(level == "off")
                {
                    smoothLevel = 0;
                }
                else
                {
                    ss >> smoothLevel;
                }

                ml_meshObjectData.mod_smoothShading = smoothLevel;
            }
        }
    }

    typedef Aws_MeshLoader MeshLoader;
}