#ifndef WINDOW_H
#define WINDOW_H
#include <SDL3/SDL.h>

class Window 
{
    public :

        bool create(const char* title, int width, int height);
        SDL_Window* getWindow();
        bool WindowEventHandler(const SDL_Event* event);
        void WindowDestroy();

    private :

        SDL_Window* window = nullptr;

        bool fullscreen = true;
        bool running = true;

};

#endif