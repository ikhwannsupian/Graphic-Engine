#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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
    std::vector<vk::ImageView>        swapchainImageView        ,
    vk::PhysicalDevice                physicalDevice            ,
    vk::Pipeline                      pipeline                  ,
    vk::Buffer                        vertexBuffer              ,
    vk::Viewport                      viewport                  ,
    vk::Rect2D                        scissor                              
)
{
    this->device                    = device                    ;
    this->graphicsQueue             = graphicsQueue             ;
    this->graphicsQueueFamilyIndex  = graphicsQueueFamilyIndex  ;
    this->swapchain                 = swapchain                 ;
    this->swapchainExtent           = swapchainExtent           ;
    this->swapchainImage            = swapchainImage            ;
    this->swapchainImageView        = swapchainImageView        ;
    this->physicalDevice            = physicalDevice            ;

}
void VulkanCommand::updateSwapchain
( 
    vk::SwapchainKHR                  swapchain                 , 
    vk::Extent2D                      swapchainExtent           , 
    std::vector<vk::Image>            swapchainImage            ,
    std::vector<vk::ImageView>        swapchainImageView        ,
    vk::Pipeline                      pipeline                  ,
    vk::Buffer                        vertexBuffer              ,
    vk::Viewport                      viewport                  ,
    vk::Rect2D                        scissor                     
)
{
    this->swapchain                 = swapchain                 ;
    this->swapchainExtent           = swapchainExtent           ;
    this->swapchainImage            = swapchainImage            ;
    this->swapchainImageView        = swapchainImageView        ;
    this->pipeline                  = pipeline                  ;
    this->vertexBuffer              = vertexBuffer              ;
    this->viewport                  = viewport                  ;
    this->scissor                   = scissor                   ;
}

void VulkanCommand::drawFrame()
{   
    if (waitForFence() == vk::Result::eSuccess)
    {
        resetFence();
        acquire();
        barrier();
        recordCommand();
        submit();

        vk::Result presentResult = present();
    }
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

void VulkanCommand::recordCommand()
{
    vk::ClearValue baseColor( vk::ClearColorValue( std::array< float, 4 >{ 0.0f, 0.0, 0.0f, 0.0f }));

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
    
    commandBuffer.reset();

    commandBuffer.begin(beginInfo);

    commandBuffer.pipelineBarrier2(dependencyInfo);

    commandBuffer.beginRendering(renderingInfo);

    commandBuffer.bindPipeline( vk::PipelineBindPoint::eGraphics, pipeline);

    commandBuffer.setViewport(0, viewport);

    commandBuffer.setScissor(0, scissor);

    vk::DeviceSize offset = 0;
    commandBuffer.bindVertexBuffers(0, vertexBuffer, offset);

    commandBuffer.draw(3, 1, 0, 0);

    commandBuffer.endRendering();

    commandBuffer.pipelineBarrier2(dependencyInfo2);

    commandBuffer.end();

}

void VulkanCommand::submit()
{
    vk::CommandBufferSubmitInfo commandBufferInfo{};

    commandBufferInfo
        .setCommandBuffer(commandBuffer);

    vk::SemaphoreSubmitInfo waitSemaphore{};

    waitSemaphore
        .setSemaphore(imageAvailableSemaphore)
        .setValue(0)
        .setStageMask(vk::PipelineStageFlagBits2::eColorAttachmentOutput);
        
    vk::SemaphoreSubmitInfo signalSemaphore{};

    signalSemaphore
        .setSemaphore(readerFinishedSemaphore[imageIndex])
        .setValue(0)
        .setStageMask(vk::PipelineStageFlagBits2::eAllGraphics);

    vk::SubmitInfo2 submitInfo{};

    submitInfo
        .setWaitSemaphoreInfos(waitSemaphore)
        .setCommandBufferInfos(commandBufferInfo)
        .setSignalSemaphoreInfos(signalSemaphore); 

    graphicsQueue.submit2(submitInfo, inFlightFence);
    lastFrame = imageIndex;
}

vk::Result VulkanCommand::present()
{
    vk::PresentInfoKHR presentInfo{};


    presentInfo
        .setWaitSemaphoreCount(1)
        .setWaitSemaphores(readerFinishedSemaphore[imageIndex])
        
        .setSwapchainCount(1)
        .setSwapchains(swapchain)

        .setImageIndices(imageIndex);

    vk::Result presentResult = graphicsQueue.presentKHR(presentInfo);

    return presentResult;

}

void VulkanCommand::destroy()
{


    device.freeCommandBuffers(commandPool, commandBuffer);
    device.destroyCommandPool(commandPool);

    device.destroySemaphore(imageAvailableSemaphore);

    for (uint32_t i = 0; i < swapchainImage.size(); i++)
    {
        device.destroySemaphore(readerFinishedSemaphore[i]);
    }

    device.destroyFence(inFlightFence);
    inFlightFence = nullptr;

}

VulkanCommand::~VulkanCommand()
{
    destroy();
}