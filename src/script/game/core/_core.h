#ifndef GAME_H
#define GAME_H

#include <script/renderer/core/_renderer.h>
#include <script/game/renderObject/_core/_renderObject.h>

class Game
{
    public:
        Game();
        void render(Renderer& renderer);
        void update();

    private:
    RenderObject renderObject;
};

#endif