#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>



#include <script/window/core/_window.h>
#include <script/renderer/core/_renderer.h>
#include <script/game/core/_core.h>


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