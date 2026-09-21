#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>
#include <cmath>

#include "_core.h"

GLRenderer::GLRenderer(SDL_Window* window)
:projection(window)
{
    this->window = window;
    context = SDL_GL_CreateContext(window);
    gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
}
GLRenderer::~GLRenderer()
{
    SDL_GL_DestroyContext(context);
}
void GLRenderer::screenUpdate()
{
    projection.updateProjection();
}




void GLRenderer::render()
{

}

