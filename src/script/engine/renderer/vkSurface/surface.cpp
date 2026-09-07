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

    if(!SDL_Vulkan_CreateSurface(window, static_cast<VkInstance>(instance), nullptr, &rawSurface)) std::cerr << "[SURFACE] Surface creation fail" << '\n';
    surface = vk::SurfaceKHR(rawSurface);

    std::cout << "[Vulkan] Surface succesfully create" << '\n';
}
vk::SurfaceKHR VulkanSurface::get() const
{
    return surface;
}

VulkanSurface::~VulkanSurface()
{
    instance.destroySurfaceKHR(surface);
    surface = nullptr;
}