#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include <renderObject/entity/_entity.h>


class RenderObject
{
    public:
        const RenderObjectStruct& getRenderData() const { return entity.getRenderObject(); }
        void stateChange (bool hasBuffer) {entity.stateChange(hasBuffer);}
        void isVisible ();
    private:
        Entity entity; 
        bool visible = false;
};
#endif