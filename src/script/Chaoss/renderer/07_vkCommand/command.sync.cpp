#include "command.h"

void VulkanCommand::createSyncObject()
{
    vk::SemaphoreCreateInfo semaphoreInfo{};
    uint32_t imageCount = swapchainImage.size();

    imageAvailableSemaphore = device.createSemaphore(semaphoreInfo);
    readerFinishedSemaphore.resize(imageCount);

    for (uint32_t i = 0; i < imageCount; i++)
    {
        
        readerFinishedSemaphore[i] = device.createSemaphore(semaphoreInfo);
    }

    vk::FenceCreateInfo fenceInfo{};

    fenceInfo
        .setFlags(vk::FenceCreateFlagBits::eSignaled);

    inFlightFence = device.createFence(fenceInfo);
}

vk::Result VulkanCommand::waitForFence()
{
    vk::Result result = device.waitForFences(inFlightFence, VK_TRUE, UINT64_MAX);
    return result;
}

void VulkanCommand::resetFence()
{
    device.resetFences(inFlightFence);
}

void VulkanCommand::acquire()
{

    auto result = device.acquireNextImageKHR( swapchain, UINT64_MAX, imageAvailableSemaphore );

    imageIndex = result.value;

}

void VulkanCommand::barrier()
{

    vk::ImageSubresourceRange subresourceRange;
    subresourceRange
        .setAspectMask(vk::ImageAspectFlagBits::eColor)

        .setBaseMipLevel(0)
        .setLevelCount(1)

        .setBaseArrayLayer(0)
        .setLayerCount(1);

    barrierToAttach
        .setSrcStageMask(vk::PipelineStageFlagBits2::eNone)
        .setSrcAccessMask(vk::AccessFlagBits2::eNone)

        .setDstStageMask(vk::PipelineStageFlagBits2::eColorAttachmentOutput)
        .setDstAccessMask(vk::AccessFlagBits2::eColorAttachmentWrite)
        
        .setOldLayout(vk::ImageLayout::eUndefined)
        .setNewLayout(vk::ImageLayout::eColorAttachmentOptimal)
        
        .setImage(swapchainImage[imageIndex])
        .setSubresourceRange(subresourceRange);

    barrierToPresent
        .setSrcStageMask(vk::PipelineStageFlagBits2::eColorAttachmentOutput)
        .setSrcAccessMask(vk::AccessFlagBits2::eColorAttachmentWrite)

        .setDstStageMask(vk::PipelineStageFlagBits2::eNone)
        .setDstAccessMask(vk::AccessFlagBits2::eNone)
        
        .setOldLayout(vk::ImageLayout::eColorAttachmentOptimal)
        .setNewLayout(vk::ImageLayout::ePresentSrcKHR)
        
        .setImage(swapchainImage[imageIndex])
        .setSubresourceRange(subresourceRange);

    dependencyInfo
        .setImageMemoryBarriers(barrierToAttach);

    dependencyInfo2
        .setImageMemoryBarriers(barrierToPresent);

}
