#include "_chaoss.h"

bool Chaoss::init()
{
    app      = new App()        ;
    window   = &app->window     ;
    renderer = &app->renderer   ;

    if(!window->create("", 90, 90)) return false;

    SDL_ShowWindow(window->getWindow());
    renderer->run(window->getWindow());
    return true;
}