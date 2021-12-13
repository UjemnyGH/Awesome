#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "../Object/Aws_Object.hpp"

namespace AWS
{
    struct Aws_EditorObjectData
    {
        Object object;
        std::string objectPath = "\0";
        std::string objectTexture = "\0";

        float p[3];
        float s[3];
        float r[3];
        float col[4];

        Aws_EditorObjectData& operator=(const Aws_EditorObjectData& data)
        {
            this->objectPath = data.objectPath;
            this->objectTexture = data.objectTexture;

            this->p[0] = data.p[0];
            this->p[1] = data.p[1];
            this->p[2] = data.p[2];
            this->s[0] = data.s[0];
            this->s[1] = data.s[1];
            this->s[2] = data.s[2];
            this->r[0] = data.r[0];
            this->r[1] = data.r[1];
            this->r[2] = data.r[2];
            this->col[0] = data.col[0];
            this->col[1] = data.col[1];
            this->col[2] = data.col[2];
            this->col[3] = data.col[3];

            if(this->objectPath.size() > 0)
                this->object.SetObjectData(AWS::LoadMesh(this->objectPath, true));

            if(this->objectTexture.size() > 0)
                this->object.SetTexture(this->objectTexture);

            return *this;
        }
    };

    typedef Aws_EditorObjectData EditorObjectData;

    static unsigned int objectCount;

    size_t EdObjDataSize(size_t sizeofEditorObjData) { return sizeofEditorObjData / sizeof(Aws_EditorObjectData); }

    static Aws_EditorObjectData editorObjectDataOnLoad[32767];

    void LoadScene(const std::string & loadPath)
    {
        std::ifstream f;

        f.open(loadPath + std::string(".awescene"), std::ios_base::binary);

        std::string line;

        int objectID;

        while(!f.eof())
        {
            getline(f, line);

            if(line.find("ObjectCount ") == 0)
            {
                std::stringstream ss(line.c_str() + 12);

                ss >> objectCount;
            }
            else if(line.find("ObjectID ") == 0)
            {
                std::stringstream ss(line.c_str() + 9);

                int id;

                ss >> id;

                objectID = id;
            }
            else if(line.find("Position ") == 0)
            {
                std::stringstream ss(line.c_str() + 9);

                float x, y, z;

                ss >> x >> y >> z;

                editorObjectDataOnLoad[objectID].p[0] = x;
                editorObjectDataOnLoad[objectID].p[1] = y;
                editorObjectDataOnLoad[objectID].p[2] = z;
            }
            else if(line.find("Scale ") == 0)
            {
                std::stringstream ss(line.c_str() + 6);

                float x, y, z;

                ss >> x >> y >> z;

                editorObjectDataOnLoad[objectID].s[0] = x;
                editorObjectDataOnLoad[objectID].s[1] = y;
                editorObjectDataOnLoad[objectID].s[2] = z;
            }
            else if(line.find("Rotation ") == 0)
            {
                std::stringstream ss(line.c_str() + 9);

                float x, y, z;

                ss >> x >> y >> z;

                editorObjectDataOnLoad[objectID].r[0] = x;
                editorObjectDataOnLoad[objectID].r[1] = y;
                editorObjectDataOnLoad[objectID].r[2] = z;
            }
            else if(line.find("Color ") == 0)
            {
                std::stringstream ss(line.c_str() + 6);

                float r, g, b, a;

                ss >> r >> g >> b >> a;

                editorObjectDataOnLoad[objectID].col[0] = r;
                editorObjectDataOnLoad[objectID].col[1] = g;
                editorObjectDataOnLoad[objectID].col[2] = b;
                editorObjectDataOnLoad[objectID].col[3] = a;
            }
            else if(line.find("Mesh ") == 0)
            {
                std::stringstream ss(line.c_str() + 5);

                std::string meshPath;

                ss >> meshPath;

                editorObjectDataOnLoad[objectID].objectPath = meshPath;
            }
            else if(line.find("Texture ") == 0)
            {
                std::stringstream ss(line.c_str() + 8);

                std::string texturePath;

                ss >> texturePath;

                editorObjectDataOnLoad[objectID].objectTexture = texturePath;
            }
        }

        f.close();
    }

    void SaveScene(const Aws_EditorObjectData* data, const std::string & savePath, const int objectCount)
    {
        std::ofstream f;

        f.open(savePath + std::string(".awescene"), std::ios_base::binary);

        std::string saveData;

        saveData += std::string("ObjectCount ") + std::to_string(objectCount) + std::string("\n\n");

        for(unsigned int i = 0; i <= objectCount; i++)
        {
            saveData += std::string("ObjectID ") + std::to_string(i) + std::string("\n");
            saveData += std::string("Position ") + std::to_string(data[i].p[0]) + std::string(" ") + std::to_string(data[i].p[1]) + std::string(" ") + std::to_string(data[i].p[2]) + std::string("\n");
            saveData += std::string("Scale ") + std::to_string(data[i].s[0]) + std::string(" ") + std::to_string(data[i].s[1]) + std::string(" ") + std::to_string(data[i].s[2]) + std::string("\n");
            saveData += std::string("Rotation ") + std::to_string(data[i].r[0]) + std::string(" ") + std::to_string(data[i].r[1]) + std::string(" ") + std::to_string(data[i].r[2]) + std::string("\n");
            saveData += std::string("Color ") + std::to_string(data[i].col[0]) + std::string(" ") + std::to_string(data[i].col[1]) + std::string(" ") + std::to_string(data[i].col[2]) + std::string(" ") + std::to_string(data[i].col[3]) + std::string("\n");
            saveData += std::string("Mesh ") + std::string(data[i].objectPath) + std::string("\n");
            saveData += std::string("Texture ") + std::string(data[i].objectTexture) + std::string("\n");
            saveData += std::string("\n");
        }

        f.write(saveData.c_str(), saveData.size());

        f.close();
    }
}