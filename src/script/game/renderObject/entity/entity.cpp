#include "_entity.h"
#include <iostream>


void Entity::stateChange(bool hasBuffer)
{
    player.getPlayerRenderData().renderState.hasBuffer = hasBuffer;
}


void Entity::isVisible(bool visible)
{
    player.getPlayerRenderData().renderState.visible = visible;
    std::cout << "playerstate: "<< player.getPlayerRenderData().renderState.visible<<  '\n';

}