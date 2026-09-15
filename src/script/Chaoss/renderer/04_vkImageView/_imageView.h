#ifndef VKIMAGE_H
#define VKIMAGE_H
#include <vulkan/vulkan.hpp>
#include <vector>

class VulkanImageView
{
    public:

        void create(vk::Device device, const std::vector<vk::Image> &swapchainImage, vk::SurfaceFormatKHR surfaceFormat);
        std::vector<vk::ImageView> getImageViews();
        void destroy();

        ~VulkanImageView();

    private:

        vk::Device                  device              {};
        vk::ImageViewCreateInfo     imageViewInfo       {};
        std::vector<vk::ImageView>  swapchainImageView  {};

        vk::Format swapchainFormat  = vk::Format::eUndefined;
};
#endif