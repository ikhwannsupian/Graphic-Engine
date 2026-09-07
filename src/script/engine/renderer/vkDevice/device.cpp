#include <iostream>
#include <vector>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include "device.h"

void VulkanDevice::create(vk::Instance instance)
{
    findPhysicalDevice(instance);
    findQueues();
    createDevice();
    createQueue();    
}

void VulkanDevice::findQueues()
{
    auto queueFamilies =
        physicalDevice.getQueueFamilyProperties();

    for (uint32_t i = 0; i < queueFamilies.size(); i++)
    {
        if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics)
        {
            graphicsFamily = i;
            break;
        }
    }

    if (graphicsFamily == UINT32_MAX)
        throw std::runtime_error("No graphics queue found!");

    float queuePriority = 1.0f;

    queueInfo
        .setQueueFamilyIndex(graphicsFamily)
        .setQueueCount(1)
        .setPQueuePriorities(&queuePriority);

}
void VulkanDevice::findPhysicalDevice(vk::Instance instance)
{


    std::vector<vk::PhysicalDevice> Devices = instance.enumeratePhysicalDevices();


    if (Devices.empty())
        throw std::runtime_error("Failed to find GPU!");
    physicalDevice = Devices.front();

}
void VulkanDevice::createDevice()
{
    deviceInfo
        .setQueueCreateInfoCount(1)
        .setPQueueCreateInfos(&queueInfo);
    std::cout
        << "[Vulkan] Selected GPU: "
        << physicalDevice.getProperties().deviceName
        << '\n';

    device = physicalDevice.createDevice(deviceInfo);
}

void VulkanDevice::createQueue()
{
    graphicsQueue = device.getQueue(graphicsFamily, 0);
    std::cout << "[Vulkan] Graphics Queue succesfully build" << '\n';

}
vk::Queue VulkanDevice::getQueues() const
{
    return graphicsQueue;
}
vk::Device VulkanDevice::getDevice() const
{
    return device;
}

VulkanDevice::~VulkanDevice()
{
    device.destroy();
    device = nullptr;
}