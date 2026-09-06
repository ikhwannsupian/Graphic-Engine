#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <iostream>
#include <stdexcept>

#include <script/engine/window/window.h>
#include <script/engine/renderer/renderer.h>


SDL_AppResult SDL_AppInit (void** appstate, int argc, char *argv[])
{
    Window* window = new Window();
    *appstate = window;
    if(!window->Init("", 1600, 900)) return SDL_APP_FAILURE;

    try
    {
        Renderer render;
        render.runInstance(window->getWindow());
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
    Window* window = static_cast<Window*>(appstate);
    if(!window->WindowEventHandler(event)) return SDL_APP_SUCCESS;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate (void* appstate)
{
    Window* window = static_cast<Window*>(appstate);
    return SDL_APP_CONTINUE;
}


void SDL_AppQuit (void* appstate, SDL_AppResult result)
{
    if (appstate)
    {
        Renderer* render = static_cast<Renderer*>(appstate);
        render->cleanup();
        Window* window = static_cast<Window*>(appstate);
        window->WindowDestroy();
        delete window;
        window = nullptr;
    }
    SDL_Quit();
}