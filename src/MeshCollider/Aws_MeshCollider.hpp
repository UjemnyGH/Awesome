#pragma once

#include "../Aws_Types.hpp"

namespace AWS
{
    struct Aws_CollisionHandler
    {
        ObjectData & ch_objectData1;
        ObjectData & ch_objectData2;
        
        bool CollisionCheck(const ObjectData & chf_objectData1, const ObjectData & chf_objectData2);
    };

    bool Aws_CollisionHandler::CollisionCheck(const ObjectData & chf_objectData1, const ObjectData & chf_objectData2)
    {
        
    }

    typedef Aws_CollisionHandler CollisionHandler;
}