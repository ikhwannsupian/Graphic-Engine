#include <iostream>
#include <vector>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include "surface.h"

void VulkanSurface::create(SDL_Window* window, vk::Instance instance)
{
    this->instance = instance;

    SDL_Vulkan_CreateSurface(window, static_cast<VkInstance>(instance), nullptr, &rawSurface);
    
    surface = vk::SurfaceKHR(rawSurface);

    std::cout << "[Vulkan] Surface succesfully create" << '\n';
}
vk::SurfaceKHR VulkanSurface::get() const
{
    return surface;
}

void VulkanSurface::destroy()
{
    instance.destroySurfaceKHR(surface);
    surface = nullptr;
}

VulkanSurface::~VulkanSurface()
{
    destroy();
}