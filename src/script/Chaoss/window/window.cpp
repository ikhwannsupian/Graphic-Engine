#include <SDL3/SDL.h>
#include <script/Chaoss/window/window.h>
#include <iostream>

bool Window::create(const char* title, int width, int height)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) return false;

    window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN | SDL_WINDOW_HIDDEN);
    SDL_SetWindowAspectRatio(window, 16.0 / 9.0, 16.0 / 9.0f);
    SDL_SetWindowMinimumSize(window, 800, 450);
    SDL_SetWindowBordered(window, true);

    displayID = SDL_GetDisplayForWindow(window);
    mode = SDL_GetDesktopDisplayMode(displayID);
    this->width = width;
    this->height = height;

    
    return window != nullptr ;    
}

bool Window::WindowEventHandler(const SDL_Event* event)
{

    char buffer[256];

    SDL_GetEventDescription(event, buffer, sizeof(buffer));


    switch(event->type)
    {
        case SDL_EVENT_QUIT: 
            running = false; 
            break;
        case SDL_EVENT_WINDOW_RESIZED:
            break;


    }

    if(event->key.key == SDLK_F11 && event->type == SDL_EVENT_KEY_DOWN && !event->key.repeat)
    {
        displayID = SDL_GetDisplayForWindow(window);
        
        if (fullscreen)
        {
            SDL_SetWindowBordered( window, true );

            SDL_SetWindowSize( window, width, height );

            SDL_SetWindowPosition( window, x, y );

        }
        else
        {   
            SDL_GetWindowPosition(window, &x, &y);

            SDL_SetWindowBordered( window, false );


            SDL_GetWindowSize( window, &width, &height );
            SDL_SetWindowSize( window, mode->w, mode->h );

            SDL_SetWindowPosition( window, SDL_WINDOWPOS_CENTERED_DISPLAY(displayID), SDL_WINDOWPOS_CENTERED_DISPLAY(displayID) );

        }

        fullscreen = !fullscreen;
    }

    return running;
}


SDL_Window* Window::getWindow()
{
    return window;
}


void Window::destroy()
{
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

Window::~Window()
{
    destroy();
}