#include <iostream>
#include <vector>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan.h>

#include <SDL3/SDL.h>

#include "renderer.h"

void Renderer::run(SDL_Window* window)
{
    this->window = window;
    instance.create();
    surface.create(window, instance.get());
    device.create(instance.get());
    swapchain.create(device.getDevice(), device.getPhysicalDevice(), surface.get(), window);
    imageView.create(device.getDevice(), swapchain.getSwapchainImage(), swapchain.getSurfaceFormat());

    pipeline.init(
        device.getDevice(),
        device.getPhysicalDevice(),
        swapchain.getExtent(),
        swapchain.getSurfaceFormat()
    );
    pipeline.create();

    command.init(
        device.getDevice(),
        device.getQueues(),
        device.getFamilyIndex(),
        swapchain.getSwapchain(),
        swapchain.getExtent(),
        swapchain.getSwapchainImage(),
        imageView.getImageViews(),
        device.getPhysicalDevice(),
        pipeline.getPipeline(),
        pipeline.getVertexBuffer(),
        pipeline.getViewport(),
        pipeline.getScissor()
    );



    command.createCommandBuffer();
    command.createSyncObject();

}

void Renderer::recreateSwapchain(const SDL_Event* event)
{   
    if(event->type != SDL_EVENT_WINDOW_RESIZED) return;

    device.getDevice().waitIdle();
    imageView.destroy();
    swapchain.destroy();
    swapchain.create(device.getDevice(), device.getPhysicalDevice(), surface.get(), window);
    imageView.create(device.getDevice(), swapchain.getSwapchainImage(), swapchain.getSurfaceFormat());
    pipeline.update(swapchain.getExtent());

    command.updateSwapchain(
        swapchain.getSwapchain(),
        swapchain.getExtent(),
        swapchain.getSwapchainImage(),
        imageView.getImageViews(),
        pipeline.getPipeline(),
        pipeline.getVertexBuffer(),
        pipeline.getViewport(),
        pipeline.getScissor()
    );


}


void Renderer::running()
{
    command.drawFrame();
}

Renderer::~Renderer()
{
    device.getDevice().waitIdle();
    pipeline.destroy();
    command.destroy();
    imageView.destroy();
    swapchain.destroy();
    device.destroy();
    surface.destroy();
    instance.destroy();
}