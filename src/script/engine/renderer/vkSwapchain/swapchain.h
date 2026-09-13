#ifndef VKSWAPCHAIN_H
#define VKSWAPCHAIN_H
#include <vulkan/vulkan.hpp>

class VulkanSwapchain
{
    public:

        void create(vk::Device device, vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, SDL_Window* window);

        std::vector<vk::Image> getSwapchainImage();
        vk::SurfaceFormatKHR getSurfaceFormat();
        vk::SwapchainKHR    getSwapchain();
        vk::Extent2D        getExtent();

        void destroy();

        ~VulkanSwapchain();

    private:

        vk::Device              device          {};    
        vk::Extent2D            extent{};
        vk::SurfaceFormatKHR    surfaceFormat   {};
        vk::SwapchainKHR        swapchain       {};
        std::vector<vk::Image>  swapchainImages  {};

};
#endif