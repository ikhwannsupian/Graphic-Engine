#include <iostream>
#include <vector>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan.h>

#include "command.h"

void VulkanCommand::init
( 
    vk::Device                        device                    , 
    vk::Queue                         graphicsQueue             ,
    uint32_t                          graphicsQueueFamilyIndex  , 
    vk::SwapchainKHR                  swapchain                 , 
    vk::Extent2D                      swapchainExtent           , 
    std::vector<vk::Image>            swapchainImage            ,
    std::vector<vk::ImageView>        swapchainImageView
)
{
    this->device                    = device                    ;
    this->graphicsQueue             = graphicsQueue             ;
    this->graphicsQueueFamilyIndex  = graphicsQueueFamilyIndex  ;
    this->swapchain                 = swapchain                 ;
    this->swapchainExtent           = swapchainExtent           ;
    this->swapchainImage            = swapchainImage            ;
    this->swapchainImageView        = swapchainImageView        ;
}
void VulkanCommand::create()
{   
    acquire();
    barrier();
    render();
    submitAndPresent();
}

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

void VulkanCommand::createSyncObject()
{
    vk::SemaphoreCreateInfo semaphoreInfo{};

    imageAvaiableSemaphore = device.createSemaphore(semaphoreInfo);

    readerFinishedSemaphore = device.createSemaphore(semaphoreInfo);
}

void VulkanCommand::acquire()
{

    auto result = device.acquireNextImageKHR( swapchain, UINT64_MAX, imageAvaiableSemaphore );

    imageIndex = result.value;

}

void VulkanCommand::barrier()
{

    vk::ImageMemoryBarrier2 barrierToAttach;
    vk::ImageMemoryBarrier2 barrierToPresent;


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
        
        .setOldLayout(vk::ImageLayout::ePresentSrcKHR)
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

void VulkanCommand::submitAndPresent()
{
    vk::CommandBufferSubmitInfo commandBufferInfo{};

    commandBufferInfo
        .setCommandBuffer(commandBuffer);

    vk::SemaphoreSubmitInfo waitSemaphore{};

    waitSemaphore
        .setSemaphore(imageAvaiableSemaphore)
        .setValue(0)
        .setStageMask(vk::PipelineStageFlagBits2::eColorAttachmentOutput);
        
    vk::SemaphoreSubmitInfo signalSemaphore{};

    signalSemaphore
        .setSemaphore(readerFinishedSemaphore)
        .setValue(0)
        .setStageMask(vk::PipelineStageFlagBits2::eAllGraphics);

    vk::SubmitInfo2 submitInfo{};

    submitInfo
        .setWaitSemaphoreInfos(waitSemaphore)
        .setCommandBufferInfos(commandBufferInfo)
        .setSignalSemaphoreInfos(signalSemaphore); 

    graphicsQueue.submit2(submitInfo);

    vk::PresentInfoKHR presentInfo{};

    presentInfo
        .setWaitSemaphoreCount(1)
        .setWaitSemaphores(readerFinishedSemaphore)
        
        .setSwapchainCount(1)
        .setSwapchains(swapchain)

        .setImageIndices(imageIndex);

    graphicsQueue.presentKHR(presentInfo);
}

void VulkanCommand::render()
{
    vk::ClearValue baseColor( vk::ClearColorValue( std::array< float, 4 >{ 0.1f, 0.1f, 0.1f, 0.1f }));

    vk::ImageView imageView = swapchainImageView[imageIndex];

    beginInfo
        .setFlags(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

    attachmentInfo
        .setImageView(imageView)
        .setImageLayout(vk::ImageLayout::eColorAttachmentOptimal)
        .setLoadOp(vk::AttachmentLoadOp::eClear)
        .setStoreOp(vk::AttachmentStoreOp::eStore)
        .setClearValue(baseColor);


    renderingInfo
        .setRenderArea({{ 0, 0 }, swapchainExtent})
        .setLayerCount(1)
        .setColorAttachments(attachmentInfo);

    commandBuffer.begin(beginInfo);

    commandBuffer.pipelineBarrier2(dependencyInfo);

    commandBuffer.beginRendering(renderingInfo);



    commandBuffer.endRendering();

    commandBuffer.pipelineBarrier2(dependencyInfo2);

    commandBuffer.end();

}

VulkanCommand::~VulkanCommand()
{
    destroy();
}