#ifndef ENTITY_H
#define ENTITY_H

#include "_player.h"
class Entity
{
    public:
        RenderObjectStruct& getRenderObject() { return player.getPlayerRenderData();}
        const RenderObjectStruct& getRenderObject() const { return player.getPlayerRenderData();}
        void stateChange(bool hasBuffer);
        void isVisible(bool visible);

    private:
        Player player;

};

#endif