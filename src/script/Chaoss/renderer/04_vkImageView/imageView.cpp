#include <iostream>
#include <vector>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan.h>
#include <SDL3/SDL_vulkan.h>
#include "imageView.h"

void VulkanImageView::create(vk::Device device, const std::vector<vk::Image>& swapchainImage, vk::SurfaceFormatKHR surfaceFormat)
{
    this->device = device;
    swapchainFormat = surfaceFormat.format;

    for(vk::Image image : swapchainImage)
    {

        imageViewInfo
            .setImage(image)
            .setViewType(vk::ImageViewType::e2D)
            .setFormat(swapchainFormat)
            .setComponents({
                vk::ComponentSwizzle::eIdentity,
                vk::ComponentSwizzle::eIdentity,
                vk::ComponentSwizzle::eIdentity,
                vk::ComponentSwizzle::eIdentity
            })
            .setSubresourceRange({vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});

        swapchainImageView.push_back(device.createImageView(imageViewInfo));

    }
    std::cout << "[VULKAN] Image View creation success!" << '\n';
}

std::vector<vk::ImageView> VulkanImageView::getImageViews()
{
    return swapchainImageView;
}

void VulkanImageView::destroy()
{
    for(vk::ImageView imageView : swapchainImageView)
    {
        device.destroyImageView(imageView);
    }
    swapchainImageView.clear();
}

VulkanImageView::~VulkanImageView()
{
    destroy();
}