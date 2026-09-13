#ifndef VULKANCOMMAND_H
#define VULKANCOMMAND_H
#include <vulkan/vulkan.hpp>


class VulkanCommand
{
    public:
        void init  
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
        );

        void updateSwapchain
        (
            vk::SwapchainKHR                  swapchain                 , 
            vk::Extent2D                      swapchainExtent           , 
            std::vector<vk::Image>            swapchainImage            ,
            std::vector<vk::ImageView>        swapchainImageView        ,
            vk::Pipeline                      pipeline                  ,
            vk::Buffer                        vertexBuffer              ,
            vk::Viewport                      viewport                  ,
            vk::Rect2D                        scissor                     
        );

        void drawFrame();        
        void createCommandBuffer();
        void createSyncObject();


        void destroy();

        ~VulkanCommand();
    private:
        vk::Result waitForFence();
        void resetFence();
        void acquire();
        void recordCommand();
        void barrier();
        void submit();
        uint32_t findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags properties);
        vk::Result present();



        vk::CommandPoolCreateInfo       poolInfo            {};
        vk::CommandBufferAllocateInfo   bufferAllocateInfo  {};
        vk::CommandBufferBeginInfo      beginInfo           {};
        vk::RenderingInfo               renderingInfo       {};
        vk::RenderingAttachmentInfo     attachmentInfo      {};

        vk::CommandPool                 commandPool         {};
        vk::CommandBuffer               commandBuffer       {};
        vk::Pipeline                    pipeline            {};

        vk::ImageView                   VkImageView         {};
        vk::Viewport                    viewport            {};
        vk::Rect2D                      scissor             {};
        vk::Buffer                      vertexBuffer        {};


        vk::Device                      device              {};
        vk::PhysicalDevice              physicalDevice      {};
        uint32_t                        graphicsQueueFamilyIndex;
        vk::SwapchainKHR                swapchain           {};
        vk::Extent2D                    swapchainExtent     {};
        std::vector<vk::ImageView>      swapchainImageView  {};
        std::vector<vk::Image>          swapchainImage      {};
        vk::Queue                       graphicsQueue       {};

        uint32_t imageIndex = 0;
        uint32_t lastFrame = 0;

        vk::DependencyInfo dependencyInfo                   {};
        vk::DependencyInfo dependencyInfo2                  {};
        vk::Semaphore imageAvailableSemaphore{};
        std::vector<vk::Semaphore> readerFinishedSemaphore{};
        vk::Fence inFlightFence{};
        vk::ImageMemoryBarrier2 barrierToAttach;
        vk::ImageMemoryBarrier2 barrierToPresent;

};


#endif