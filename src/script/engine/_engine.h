#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>



#include "_window.h"
#include "_renderer.h"
#include "_game.h"


class Engine
{
    public:
        Engine();
        
        bool event  (const SDL_Event* event);
        bool render ();

        ~Engine();

    private:
        Window* window = nullptr;
        Renderer* renderer = nullptr;
        Game* game = nullptr;

};

#endif