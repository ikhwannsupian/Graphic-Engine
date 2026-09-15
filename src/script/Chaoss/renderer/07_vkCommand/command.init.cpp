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
    vk::Rect2D                        scissor                   ,
    vk::Buffer                        indexBuffer               ,
    uint32_t                          indicesCount              ,
    vk::PipelineLayout                pipelineLayout            ,
    vk::DescriptorSet                 descriptorSet
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
    this->pipeline                  = pipeline                  ;
    this->vertexBuffer              = vertexBuffer              ;
    this->viewport                  = viewport                  ;
    this->scissor                   = scissor                   ;
    this->indexBuffer               = indexBuffer               ;
    this->indicesCount              = indicesCount              ;
    this->pipelineLayout            = pipelineLayout            ;
    this->descriptorSet             = descriptorSet             ;

}

void VulkanCommand::updateSwapchain
( 
    vk::SwapchainKHR                  swapchain                 , 
    vk::Extent2D                      swapchainExtent           , 
    std::vector<vk::Image>            swapchainImage            ,
    std::vector<vk::ImageView>        swapchainImageView        ,
    vk::PipelineLayout                pipelineLayout            ,
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
    this->pipelineLayout            = pipelineLayout            ;
    this->pipeline                  = pipeline                  ;
    this->vertexBuffer              = vertexBuffer              ;
    this->viewport                  = viewport                  ;
    this->scissor                   = scissor                   ;
}