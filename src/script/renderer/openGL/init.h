#ifndef GL_INIT_H
#define GL_INIT_H
#include <glad/gl.h>

#include <SDL3/SDL.h>
class GlContext
{
    public:
    GlContext(SDL_Window* window)
    {
        context = SDL_GL_CreateContext(window);
        gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
    }
    ~GlContext()
    {
        SDL_GL_DestroyContext(context);
    }
    private:
        SDL_GLContext context;

};

#endif