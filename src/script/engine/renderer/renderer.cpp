#include <iostream>
#include <vector>

#include <vulkan/vulkan.hpp>
#include <script/engine/renderer/renderer.h>

void Renderer::createInstance()
{  
    vk::ApplicationInfo appInfo;
    appInfo.setPApplicationName("Broken World")
            .setApplicationVersion(VK_MAKE_VERSION(0, 0, 1))
            .setPEngineName("Chaos")
            .setEngineVersion(VK_MAKE_VERSION(0, 0, 1))
            .setApiVersion(VK_API_VERSION_1_0);

    vk::InstanceCreateInfo instanceInfo
    (
        {},
        &appInfo
    );
    instance = vk::createInstance(instanceInfo);

    std::cout << "[Vulkan] Instance created successfully using vulkan.hpp!" << '\n';
}
void Renderer::createDevice()
{
    vk::DeviceCreateInfo deviceInfo{};

    std::vector<vk::PhysicalDevice> physicalDevices =
        instance.enumeratePhysicalDevices();

    if (physicalDevices.empty())
        throw std::runtime_error("Failed to find GPU!");

    vk::PhysicalDevice physicalDevice = physicalDevices.front();

    std::cout
        << "[Vulkan] Selected GPU: "
        << physicalDevice.getProperties().deviceName
        << '\n';

    device = physicalDevice.createDevice(deviceInfo);
}


void Renderer::cleanup()
{
    while(device)
    {
        device.waitIdle();
        device.destroy();
        device = nullptr;
    }
    while(instance)
    {
        instance.destroy();
        instance = nullptr;
    }
}