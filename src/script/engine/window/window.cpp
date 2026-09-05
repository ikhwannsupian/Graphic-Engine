#include <SDL3/SDL.h>
#include <script/engine/window/window.h>

bool Window::Init(const char* title, int width, int height)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) return false;

    window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);
    SDL_SetWindowAspectRatio(window, 16.0 / 9.0, 16.0 / 9.0f);
    SDL_SetWindowMinimumSize(window, 800, 450);
    SDL_SetWindowBordered(window, true);

    return window != nullptr || !(width < 800 || height < 450);    
}

bool Window::WindowEventHandler(const SDL_Event* event)
{
    switch(event->type)
    {
        case SDL_EVENT_QUIT: running = false; break;
    }

    if(event->key.key == SDLK_F11 && event->type == SDL_EVENT_KEY_DOWN && !event->key.repeat)
    {
        fullscreen = !fullscreen;
        SDL_SetWindowFullscreen(window, fullscreen);
        SDL_SetWindowBordered(window, !fullscreen);
    }

    if(event->key.key == SDLK_ESCAPE && event->type == SDL_EVENT_KEY_DOWN && !event->key.repeat) 
    {
        fullscreen = false;
        SDL_SetWindowFullscreen(window, fullscreen);
        SDL_SetWindowBordered(window, !fullscreen);

    }
    return running;
}

void Window::WindowDestroy()
{
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

