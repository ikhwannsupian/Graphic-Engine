#ifndef VKSURFACE_H
#define VKSURFACE_H

#include <vulkan/vulkan.hpp>
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

class VulkanSurface
{   
    public:

        void create(SDL_Window* window, vk::Instance instance);
        vk::SurfaceKHR get() const;
        
        void destroy();
        ~VulkanSurface();

    private:

        vk::Instance    instance    {};
        vk::SurfaceKHR  surface     {};        

        VkSurfaceKHR    rawSurface  = VK_NULL_HANDLE;
};

#endif