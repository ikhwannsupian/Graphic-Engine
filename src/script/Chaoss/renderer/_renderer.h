#ifndef RENDERER_H
#define RENDERER_H

#include <script/Chaoss/renderer/00_vkInstance/instance.h>
#include <script/Chaoss/renderer/01_vkSurface/surface.h>
#include <script/Chaoss/renderer/02_vkDevice/device.h>
#include <script/Chaoss/renderer/03_vkSwapchain/swapchain.h>
#include <script/Chaoss/renderer/04_vkImageView/imageView.h>
#include <script/Chaoss/renderer/05_vkPipeline/pipeline.h>
#include <script/Chaoss/renderer/06_vkCommand/command.h>

#include <vulkan/vulkan.hpp>

class Renderer
{
    public:
        Renderer() = default;

        void run(SDL_Window* window);
        void recreateSwapchain(const SDL_Event* event);

        void running();
        void destroy();

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