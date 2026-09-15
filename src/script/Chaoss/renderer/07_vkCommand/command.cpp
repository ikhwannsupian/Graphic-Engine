#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan.h>

#include "command.h"




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



void VulkanCommand::recordCommand()
{
    std::cout << "Command device: "
          << static_cast<VkDevice>(device)
          << '\n';
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


    commandBuffer.bindDescriptorSets(
        vk::PipelineBindPoint::eGraphics,
        pipelineLayout,
        0,
        descriptorSet,
        {}
    );

    commandBuffer.drawIndexed(indicesCount, 1, 0, 0, 0);

    commandBuffer.endRendering();

    commandBuffer.pipelineBarrier2(dependencyInfo2);

    commandBuffer.end();

}
void VulkanCommand::recordCommandEmpty()
{
    commandBuffer.reset();
    commandBuffer.begin(beginInfo);

    // transition image
    commandBuffer.pipelineBarrier2(dependencyInfo);

    // begin rendering with clear color only — no draw calls
    commandBuffer.beginRendering(renderingInfo);
    // ← nothing here = blank screen
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