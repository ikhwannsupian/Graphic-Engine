#include <SDL3/SDL.h>

#include "_chaoss.h"

bool Chaoss::event(SDL_Event* event)
{
    renderer->recreateSwapchain(event);

    if(!window->WindowEventHandler(event)) return false;

    return true;
}