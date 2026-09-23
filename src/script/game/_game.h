#ifndef GAME_H
#define GAME_H

#include "_renderer.h"
#include <renderObject/_renderObject.h>

class Game
{
    public:
        // Game();
        void render(Renderer& renderer);
        void event(const SDL_Event* event);
        void update();

    private:
    RenderObject renderObject;
};

#endif