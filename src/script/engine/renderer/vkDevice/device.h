#ifndef VKDEVICE_H
#define VKDEVICE_H

#include <vulkan/vulkan.hpp>

class VulkanDevice
{   
    public:

        void create(vk::Instance instance);

        vk::PhysicalDevice  getPhysicalDevice() const;      
        vk::Device          getDevice() const;      
        vk::Queue           getQueues() const;
        uint32_t            getFamilyIndex() const;

        void destroy();
        ~VulkanDevice();

    private:

        void findQueues();
        void findPhysicalDevice(vk::Instance instance);
        void createDevice();
        void createQueue();

        vk::DeviceCreateInfo        deviceInfo      {};
        vk::DeviceQueueCreateInfo   queueInfo       {};

        vk::Device                  device          {};
        vk::PhysicalDevice          physicalDevice  {};
        vk::Queue                   graphicsQueue   {};
        std::vector<vk::PhysicalDevice> Devices     {};

        uint32_t graphicsFamily                     = UINT32_MAX;

};

#endif