#ifndef WINDOW_H
#define WINDOW_H
#include <SDL3/SDL.h>
#include <iostream>
class Window 
{
    public :
        Window() = default;

        bool create(const char* title, int width, int height);
        SDL_Window* getWindow();
        // void setApp(Chaos* app);
        bool WindowEventHandler(const SDL_Event* event);
        void transform();
        bool getTransform();
        void destroy();

        ~Window();

    private :
        int width, height;
        int cWidth, cHeight;
        int x, y;

        SDL_Window* window = nullptr;
        SDL_DisplayID displayID = UINT32_MAX;


        const SDL_DisplayMode* mode;

        bool fullscreen = false;
        bool running = true;
};

#endif