// #define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>
#include <cmath>

#include "_core.h"

GLRenderer::GLRenderer(SDL_Window* window)
:context(window), projection(window)
{}

GLRenderer::~GLRenderer()
{}

void GLRenderer::screenUpdate()
{
    projection.updateProjection();
}





