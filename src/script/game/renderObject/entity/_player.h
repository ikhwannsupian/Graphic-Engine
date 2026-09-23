#ifndef PLAYER_H
#define PLAYER_H
#include <renderObject/struct/class.h>

class Player : public RenderObjectClass
{
    public:
    Player()
    : RenderObjectClass(ObjectName::Player)
    {}


};

#endif