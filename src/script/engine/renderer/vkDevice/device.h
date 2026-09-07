#ifndef VKDEVICE_H
#define VKDEVICE_H

#include <vulkan/vulkan.hpp>

class VulkanDevice
{   
    public:
        void create(vk::Instance instance);

        vk::Device getDevice() const;      
        vk::Queue getQueues() const;

        ~VulkanDevice();
    private:
        void findQueues();
        void findPhysicalDevice(vk::Instance instance);
        void createDevice();
        void createQueue();

        vk::DeviceCreateInfo deviceInfo{};
        vk::Device device = nullptr;
        vk::PhysicalDevice physicalDevice = nullptr;
        uint32_t graphicsFamily = UINT32_MAX;
        vk::DeviceQueueCreateInfo queueInfo{};
        vk::Queue graphicsQueue = nullptr;
};

#endif