#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <iostream>
#include <stdexcept>

#include <script/Chaoss/_chaoss.h>


SDL_AppResult SDL_AppInit (void** appstate, int argc, char *argv[])
{
    freopen("log.txt", "w", stdout);
    freopen("log.txt", "a", stderr);
    Chaoss* chaoss = new Chaoss();
    *appstate = chaoss;

    if(!chaoss->init())
        return SDL_APP_FAILURE;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent (void* appstate, SDL_Event* event)
{
    Chaoss* chaoss = static_cast<Chaoss*>(appstate);

    if(!chaoss->event(event))
        return SDL_APP_FAILURE;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate (void* appstate)
{
    Chaoss* chaoss = static_cast<Chaoss*>(appstate);

    chaoss->render();

    return SDL_APP_CONTINUE;
}


void SDL_AppQuit (void* appstate, SDL_AppResult result)
{
    if (appstate)
    {
        Chaoss* chaoss = static_cast<Chaoss*>(appstate);

        chaoss->destroy();

        delete chaoss;
        chaoss = nullptr;
    }
    SDL_Quit();
}