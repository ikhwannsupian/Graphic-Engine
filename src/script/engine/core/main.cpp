#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <iostream>
#include <stdexcept>

#include <script/engine/window/window.h>
#include <script/engine/renderer/vkRenderer/renderer.h>

struct Chaos
{
    Window window;
    Renderer renderer; 
};

SDL_AppResult SDL_AppInit (void** appstate, int argc, char *argv[])
{
    freopen("log.txt", "w", stdout);
    freopen("log.txt", "a", stderr);
    Chaos* brokenWorld = new Chaos();
    *appstate = brokenWorld;
    Window& window = brokenWorld->window;
    Renderer& renderer = brokenWorld->renderer;

    if(!window.create("", 90, 90)) return SDL_APP_FAILURE;
    SDL_ShowWindow(window.getWindow()); // ✅ show window first
    try
    {
        renderer.run(window.getWindow());
    }
    catch (const std::exception& err)
    {
        std::cerr << err.what() << '\n';
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent (void* appstate, SDL_Event* event)
{
    Chaos* brokenWorld = static_cast<Chaos*>(appstate);
    Window& window = brokenWorld->window;
    Renderer& renderer = brokenWorld->renderer;

    renderer.recreateSwapchain(event);

    if(!window.WindowEventHandler(event)) return SDL_APP_SUCCESS;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate (void* appstate)
{
    Chaos* brokenWorld = static_cast<Chaos*>(appstate);
    Window& window = brokenWorld->window;
    Renderer& renderer = brokenWorld->renderer;

    renderer.running();

    return SDL_APP_CONTINUE;
}


void SDL_AppQuit (void* appstate, SDL_AppResult result)
{
    if (appstate)
    {
        Chaos* brokenWorld = static_cast<Chaos*>(appstate);
        brokenWorld->window.WindowDestroy();
        delete brokenWorld;
        brokenWorld = nullptr;
    }
    SDL_Quit();
}