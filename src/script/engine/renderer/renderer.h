#ifndef RENDERER_H
#define RENDERER_H

#include <vulkan/vulkan.hpp>

class Renderer
{
    public:

        void runInstance(SDL_Window* window)
        {
            createInstance();
            createDevice();
            createSurface(window);
        
        };

        void cleanup();

    private:
        vk::Instance instance = nullptr;
        vk::SurfaceKHR surface = nullptr;        
        vk::Device device = nullptr;
        vk::PhysicalDevice physicalDevice = nullptr;
        vk::Queue queue;

        vk::AllocationCallbacks allocator{};

        void createAllocator();
        void createInstance();
        void createSurface(SDL_Window* window);
        void createDevice();      
};

#endif 