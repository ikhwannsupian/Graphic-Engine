#ifndef VULKANCOMMAND_H
#define VULKANCOMMAND_H
#include <vulkan/vulkan.hpp>

class VulkanCommand
{
    public:
        void init  
        ( 
            vk::Device                        device, 
            vk::Queue                         graphicsQueue,
            uint32_t                          graphicsQueueFamilyIndex, 
            vk::SwapchainKHR                  swapchain, 
            vk::Extent2D                      swapchainExtent, 
            std::vector<vk::Image>            swapchainImage,
            std::vector<vk::ImageView>        swapchainImageView
        );

        void create();        
        void createCommandBuffer();
        void createSyncObject();

        void destroy();

        ~VulkanCommand();
    private:
        void render();
        void acquire();
        void barrier();
        void submitAndPresent();


        vk::CommandPoolCreateInfo       poolInfo            {};
        vk::CommandBufferAllocateInfo   bufferAllocateInfo  {};
        vk::CommandBufferBeginInfo      beginInfo           {};
        vk::RenderingInfo               renderingInfo       {};
        vk::RenderingAttachmentInfo     attachmentInfo      {};

        vk::CommandPool                 commandPool         {};
        vk::CommandBuffer               commandBuffer       {};
        vk::ImageView                   VkImageView         {};

        vk::Device                      device              {};
        uint32_t                        graphicsQueueFamilyIndex = NULL;
        vk::SwapchainKHR                swapchain           {};
        vk::Extent2D                    swapchainExtent     {};
        std::vector<vk::ImageView>      swapchainImageView  {};
        std::vector<vk::Image>          swapchainImage      {};
        vk::Queue                       graphicsQueue       {};
        uint64_t imageIndex;

        vk::DependencyInfo dependencyInfo                   {};
        vk::DependencyInfo dependencyInfo2                  {};
        vk::Semaphore imageAvaiableSemaphore{};
        vk::Semaphore readerFinishedSemaphore{};
        
};


#endif