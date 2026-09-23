#ifndef RENDERER_H
#define RENDERER_H

#include <openGL/_core.h>

class Renderer
{
    public:
        Renderer(SDL_Window* window);


        ~Renderer();

        void screenUpdate();
        bool render(const RenderObjectStruct& renderObjectData);

    private:

    GLRenderer GlRenderer;
};

#endif