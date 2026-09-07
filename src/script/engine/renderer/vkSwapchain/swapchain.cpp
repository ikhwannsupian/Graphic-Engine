#include <iostream>
#include <vector>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan.h>

#include <SDL3/SDL_vulkan.h>

#include "swapchain.h"

void VulkanSwapchain::create(vk::Device device, vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, SDL_Window* window)
{
    this->device = device;

    auto capabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);
    auto formats = physicalDevice.getSurfaceFormatsKHR(surface);
    auto presentModes = physicalDevice.getSurfacePresentModesKHR(surface);

    vk::SurfaceFormatKHR surfaceFormat = formats[0];

    for (const auto& format : formats)
    {
        if (format.format == vk::Format::eB8G8R8A8Srgb && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
        {
            surfaceFormat = format;
            break;
        }
    }


    vk::PresentModeKHR presentMode = vk::PresentModeKHR::eFifo;

    vk::Extent2D extent;

    if (capabilities.currentExtent.width != UINT32_MAX)
    {
        extent = capabilities.currentExtent;
    }
    else
    {
        int width;
        int height;
        SDL_GetWindowSizeInPixels(window, &width, &height);

        vk::Extent2D extent{
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };

        extent.width = std::clamp(
            extent.width,
            capabilities.minImageExtent.width,
            capabilities.maxImageExtent.width);

        extent.height = std::clamp(
            extent.height,
            capabilities.minImageExtent.height,
            capabilities.maxImageExtent.height);
    }

    uint32_t imageCount = capabilities.minImageCount + 1;

    if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount)
    {
        imageCount = capabilities.maxImageCount;
    }

    vk::SwapchainCreateInfoKHR swapchainInfo{};

    swapchainInfo
        .setSurface(surface)
        .setMinImageCount(imageCount)
        .setImageFormat(surfaceFormat.format)
        .setImageColorSpace(surfaceFormat.colorSpace)
        .setImageExtent(extent)
        .setImageArrayLayers(1)
        .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment)
        .setImageSharingMode(vk::SharingMode::eExclusive)
        .setPreTransform(capabilities.currentTransform)
        .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
        .setPresentMode(presentMode)
        .setClipped(VK_TRUE);

    if(!(swapchain = device.createSwapchainKHR(swapchainInfo))) std::cerr << "[SWAPCHAIN] Swapchain creation fail" << '\n';

    swapchainImages = device.getSwapchainImagesKHR(swapchain);

    std::cout << "[Vulkan] Swapchain and Swapchain Images successfully created!\n";
}

VulkanSwapchain::~VulkanSwapchain()
{
    device.destroySwapchainKHR(swapchain);
}