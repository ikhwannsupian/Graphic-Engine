#ifndef VKSWAPCHAIN_H
#define VKSWAPCHAIN_H
#include <vulkan/vulkan.hpp>

class VulkanSwapchain
{
    public:
        void create(vk::Device device, vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, SDL_Window* window);

        ~VulkanSwapchain();
    private:
        vk::Device device = nullptr;
        vk::SwapchainKHR swapchain;
        std::vector<vk::Image> swapchainImages;
};
#endif