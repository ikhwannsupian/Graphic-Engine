#ifndef VKINSTANCE_H
#define VKINSTANCE_H

#include <vulkan/vulkan.hpp>

class VulkanInstance
{   
    public:
        void create();
        vk::Instance get() const;

        ~VulkanInstance();
    private:
        vk::Instance instance = nullptr;
        vk::ApplicationInfo appInfo{};
        vk::InstanceCreateInfo instanceInfo{};

        uint32_t extCount = 0;
};

#endif