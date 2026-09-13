#ifndef RENDERER_H
#define RENDERER_H
#include <script/engine/renderer/vkDevice/device.h>
#include <script/engine/renderer/vkInstance/instance.h>
#include <script/engine/renderer/vkSurface/surface.h>
#include <script/engine/renderer/vkSwapchain/swapchain.h>
#include <script/engine/renderer/vkImageView/imageView.h>
#include <script/engine/renderer/vkCommand/command.h>
#include <script/engine/renderer/vkPipeline/pipeline.h>

#include <vulkan/vulkan.hpp>

class Renderer
{
    public:
        void run(SDL_Window* window);
        void recreateSwapchain(const SDL_Event* event);
        void running();

        ~Renderer();
        
    private:
        SDL_Window* window = nullptr;

        VulkanInstance  instance;
        VulkanSurface   surface;
        VulkanDevice    device;
        VulkanSwapchain swapchain;
        VulkanImageView imageView;
        VulkanCommand   command;
        VulkanPipeline pipeline;
};

#endif 