#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <iostream>
#include <stdexcept>

#include <script/engine/window/window.h>
#include <script/engine/renderer/renderer.h>

struct Chaos
{
    Window window;
    Renderer renderer; 
};

SDL_AppResult SDL_AppInit (void** appstate, int argc, char *argv[])
{
    Chaos* brokenWorld = new Chaos();
    *appstate = brokenWorld;
    Window& window = brokenWorld->window;
    Renderer& renderer = brokenWorld->renderer;

    if(!window.Init("", 1600, 900)) return SDL_APP_FAILURE;

    try
    {
        renderer.runInstance(window.getWindow());
    }
    catch (const std::exception& err)
    {
        std::cerr << err.what() << std::endl;
        return SDL_APP_FAILURE;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent (void* appstate, SDL_Event* event)
{
    Chaos* brokenWorld = static_cast<Chaos*>(appstate);
    Window& window = brokenWorld->window;
    Renderer& renderer = brokenWorld->renderer;

    if(!window.WindowEventHandler(event)) return SDL_APP_SUCCESS;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate (void* appstate)
{
    Chaos* brokenWorld = static_cast<Chaos*>(appstate);
    Window& window = brokenWorld->window;
    Renderer& renderer = brokenWorld->renderer;

    return SDL_APP_CONTINUE;
}


void SDL_AppQuit (void* appstate, SDL_AppResult result)
{
    if (appstate)
    {
        Chaos* brokenWorld = static_cast<Chaos*>(appstate);
        brokenWorld->renderer.cleanup();
        brokenWorld->window.WindowDestroy();
        delete brokenWorld;
        brokenWorld = nullptr;
    }
    SDL_Quit();
}