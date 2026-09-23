#include "_world.h"

uint32_t World::createObject(Type objectType)
{
    id++;

    type.push_back(objectType);

    positionX.push_back(0.0f);
    positionY.push_back(0.0f);
    positionZ.push_back(0.0f);

    scaleX.push_back(1.0f);
    scaleY.push_back(1.0f);
    scaleZ.push_back(1.0f);

    rotationX.push_back(0.0f);
    rotationY.push_back(0.0f);
    rotationZ.push_back(0.0f);

    visible.push_back(true);
    hasBuffer.push_back(false);
    exist.push_back(true);

    return id;
}