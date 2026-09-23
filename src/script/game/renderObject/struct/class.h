#ifndef CLASS_H
#define CLASS_H

#include "struct.h"

class RenderObjectClass
{
    public:
        RenderObjectClass(ObjectName name) 
        :visible(false),objectRdata(name, false, RenderState(visible))
        {
            objectRdata.name = name;
        }
        RenderObjectStruct& getPlayerRenderData()  { return objectRdata; }
        const RenderObjectStruct& getPlayerRenderData() const { return objectRdata; }

    protected: 
        RenderObjectStruct objectRdata;
        Transform ObjectTransform;
        bool visible;
};

#endif