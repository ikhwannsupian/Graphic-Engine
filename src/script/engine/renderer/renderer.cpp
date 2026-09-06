#include <iostream>
#include <vector>

#include <vulkan/vulkan.hpp>
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include <script/engine/renderer/vkAllocator/allocator.h>
#include "renderer.h"

void Renderer::createAllocator()
{
    allocator
        .setPfnAllocation(vkAllocate)
        .setPfnReallocation(vkReallocate)
        .setPfnFree(vkFree);
}

void Renderer::createInstance()
{  
    vk::ApplicationInfo appInfo{};
    appInfo.setPApplicationName("Broken World")
            .setApplicationVersion(VK_MAKE_VERSION(0, 0, 1))
            .setPEngineName("Chaos")
            .setEngineVersion(VK_MAKE_VERSION(0, 0, 1))
            .setApiVersion(VK_API_VERSION_1_4);

    vk::InstanceCreateInfo instanceInfo
    (
        {},
        &appInfo
    );
    instance = vk::createInstance(instanceInfo, allocator);

    std::cout << "[Vulkan] Instance created successfully using vulkan.hpp!" << '\n';
}

void Renderer::createSurface(SDL_Window* window)
{
    VkSurfaceKHR rawSurface = VK_NULL_HANDLE;
    uint32_t extCount = 0;
    SDL_Vulkan_GetInstanceExtensions(&extCount);
    std::vector<const char*> extensions(extCount);

    SDL_Vulkan_CreateSurface(window, static_cast<VkInstance>(instance), allocator, &rawSurface);
    surface = static_cast<vk::SurfaceKHR>(rawSurface);
}

void Renderer::createDevice()
{
    vk::DeviceCreateInfo deviceInfo{};

    std::vector<vk::PhysicalDevice> Devices =
        instance.enumeratePhysicalDevices();

    if (Devices.empty())
        throw std::runtime_error("Failed to find GPU!");

    physicalDevice = Devices.front();

    std::cout
        << "[Vulkan] Selected GPU: "
        << physicalDevice.getProperties().deviceName
        << '\n';

    device = physicalDevice.createDevice(deviceInfo);
}

void Renderer::cleanup()
{
    if(device)
    {
        device.waitIdle();
        device.destroy();
        device = nullptr;
    }
    if(instance)
    {
        instance.destroy();
        instance = nullptr;
    }
}