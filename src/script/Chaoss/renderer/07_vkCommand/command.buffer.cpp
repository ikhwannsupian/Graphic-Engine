#include "command.h"

void VulkanCommand::createCommandBuffer()
{
    poolInfo
        .setQueueFamilyIndex(graphicsQueueFamilyIndex)
        .setFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer);

    commandPool = device.createCommandPool(poolInfo);

    bufferAllocateInfo
        .setCommandPool(commandPool)
        .setLevel(vk::CommandBufferLevel::ePrimary)
        .setCommandBufferCount(1);

    auto commandBuffers = device.allocateCommandBuffers(bufferAllocateInfo);

    commandBuffer = commandBuffers[0];

}