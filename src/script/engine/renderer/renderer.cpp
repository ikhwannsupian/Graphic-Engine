#include <iostream>
#include <vector>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include "renderer.h"

void Renderer::run(SDL_Window* window)
{
    instance.create();
    surface.create(window, instance.get());
    device.create(instance.get());
}


