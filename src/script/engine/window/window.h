#ifndef WINDOW_H
#define WINDOW_H
#include <SDL3/SDL.h>

class Window 
{
    public :
        bool Init(const char* title, int width, int height);
        bool WindowEventHandler(const SDL_Event* event);
        void WindowDestroy();
        bool fullscreen = true;
        bool running = true;

    private :
        SDL_Window* window = nullptr;

};

#endif