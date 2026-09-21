#ifndef CLASS_H
#define CLASS_H

#include <struct.h>

class RenderObjectClass
{
    public:
        const RenderObjectStruct& getPlayerRenderData() const { return player; }

    protected: 
        RenderObjectStruct player;
        Transform playerTransform;
};

#endif