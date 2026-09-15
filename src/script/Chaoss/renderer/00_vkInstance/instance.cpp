#include <iostream>
#include <vector>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan.h>
#include <SDL3/SDL_vulkan.h>
#include "instance.h"

void VulkanInstance::create()
{
    const char* const* sdlExtensions = SDL_Vulkan_GetInstanceExtensions(&extCount);

    std::vector<const char*> extensions(sdlExtensions, sdlExtensions + extCount);

    std::vector<const char*> layers = 
    {
        "VK_LAYER_KHRONOS_validation"
    };

    appInfo
        .setPApplicationName("Broken World")
        .setApplicationVersion(VK_MAKE_VERSION(0, 0, 1))
        .setPEngineName("Chaos")
        .setEngineVersion(VK_MAKE_VERSION(0, 0, 1))
        .setApiVersion(VK_API_VERSION_1_4);


    instanceInfo
        .setPApplicationInfo(&appInfo)
        .setPEnabledExtensionNames(extensions)
        .setPEnabledLayerNames(layers);

    
    instance = vk::createInstance(instanceInfo);

    std::cout << "[Vulkan] Instance created successfully!\n";
}

vk::Instance VulkanInstance::get() const
{
    return instance;
}

void VulkanInstance::destroy()
{
    instance.destroy();
    instance = nullptr;
}

VulkanInstance::~VulkanInstance()
{
    destroy();
}