#include "_renderer.h"

Renderer::Renderer(SDL_Window* window)
: GlRenderer(window)
{

}


Renderer::~Renderer()
{

}

void Renderer::screenUpdate()
{
    GlRenderer.screenUpdate();
}

bool Renderer::render()
{
    return GlRenderer.render();
}
