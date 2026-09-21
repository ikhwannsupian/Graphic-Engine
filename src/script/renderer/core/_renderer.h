#ifndef RENDERER_H
#define RENDERER_H

#include <script/renderer/openGL/_core.h>

class Renderer
{
    public:
        Renderer(SDL_Window* window);


        ~Renderer();

        void screenUpdate();
        void render();

    private:

    GLRenderer GlRenderer;
};

#endif