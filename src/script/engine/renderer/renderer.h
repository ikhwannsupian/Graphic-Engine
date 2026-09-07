#ifndef RENDERER_H
#define RENDERER_H
#include <script/engine/renderer/vkDevice/device.h>
#include <script/engine/renderer/vkInstance/instance.h>
#include <script/engine/renderer/vkSurface/surface.h>
#include <vulkan/vulkan.hpp>

class Renderer
{
    public:

        void run(SDL_Window* window);


    private:
        VulkanInstance instance;
        VulkanSurface surface;
        VulkanDevice device;



};

#endif 