#ifndef VULKANPIPELINE_H
#define VULKANPIPELINE_H
#include <vulkan/vulkan.hpp>
#include <array>
struct Vec2
{
    float x, y;
};

struct Vec4
{
    float r, g, b, a;
};
struct uniformBufferObject
{
    Vec4 model;
    Vec4 view;
    Vec4 projection;
};
struct Vertex
{
    Vec2 position;
    Vec4 color;

    static vk::VertexInputBindingDescription getBindingDescription ()
    {
        vk::VertexInputBindingDescription binding{};

        binding
            .setBinding(0)
            .setStride(sizeof(Vertex)) // size next vertex in byte
            .setInputRate(vk::VertexInputRate::eVertex);

        return binding;
    }

    static std::array<vk::VertexInputAttributeDescription, 2> getAttributeDescriptions ()
    {
        std::array<vk::VertexInputAttributeDescription, 2> attributes{};

        attributes[0]
            .setBinding(0)
            .setLocation(0)
            .setFormat(vk::Format::eR32G32Sfloat)
            .setOffset(offsetof(Vertex, position));

        attributes[1]
            .setBinding(0)
            .setLocation(1)
            .setFormat(vk::Format::eR32G32B32A32Sfloat)
            .setOffset(offsetof(Vertex, color));

        return attributes;
    }
};

vk::DescriptorSetLayoutBinding uboBinding();

class VulkanPipeline
{
    public:
        void init 
        (
        vk::Device                      device              ,
        vk::PhysicalDevice              physicalDevice      ,
        vk::Extent2D                    swapchainExtent     ,
        vk::SurfaceFormatKHR            surfaceFormat       
        );

        void create();
        void update(vk::Extent2D swapchainExtent);

        std::vector<char> readFile(const std::string& filename);
        void createVertexBuffer();
        void createIndexBuffer();
        void createUniformBuffer();
        void createDescriptor();
        void graphicsPipeline();

        uint32_t findMemoryType( uint32_t typeFilter, vk::MemoryPropertyFlags properties );
        vk::Buffer      getVertexBuffer ();
        vk::Buffer      getIndexBuffer  ();
        vk::Pipeline    getPipeline     ();
        vk::Rect2D      getScissor      ();
        vk::Viewport    getViewport     ();
        uint32_t        getIndices      ();
        vk::PipelineLayout getPipelineLayout();
        vk::DescriptorSet  getDescriptorSet();

        void destroy();

        ~VulkanPipeline();

    private:
    
        vk::PipelineVertexInputStateCreateInfo      vertexInput             {};
        vk::ShaderModuleCreateInfo                  vertInfo                {};
        vk::ShaderModuleCreateInfo                  fragInfo                {};
        vk::ShaderModule                            vertShader              {};
        vk::ShaderModule                            fragShader              {};
        vk::PipelineShaderStageCreateInfo           vertStage               {};
        vk::PipelineShaderStageCreateInfo           fragStage               {};
        vk::DescriptorSetLayout                     descriptorSetLayout     {};
        vk::DescriptorPool                          descriptorPool          {};
        vk::DescriptorSet                           descriptorSet           {};

        vk::PipelineInputAssemblyStateCreateInfo    inputAssembly           {};
        vk::PipelineViewportStateCreateInfo         viewportStateInfo       {};
        vk::PipelineDynamicStateCreateInfo          dynamicState            {};
        vk::PipelineRasterizationStateCreateInfo    rasterizer              {};
        vk::PipelineMultisampleStateCreateInfo      multisampling           {};
        vk::PipelineColorBlendAttachmentState       colorBlendingAttachment {};
        vk::PipelineColorBlendStateCreateInfo       colorBlending           {};
        vk::PipelineRenderingCreateInfo             pipelineRenderingInfo   {};
        vk::GraphicsPipelineCreateInfo              pipelineInfo            {};

        vk::Device                      device              {};
        vk::PhysicalDevice              physicalDevice      {};
        vk::Extent2D                    swapchainExtent     {};
        vk::SurfaceFormatKHR            surfaceFormat       {};


        vk::PipelineLayout              pipelineLayout      {};
        vk::Pipeline                    pipeline            {};
        vk::Buffer                      vertexBuffer        {};
        vk::DeviceMemory                vertexBufferMemory  {};
        vk::Buffer                      indexBuffer         {};
        vk::DeviceMemory                indexBufferMemory   {};
        vk::Buffer                      uniformBuffer       {};
        vk::DeviceMemory                uniformBufferMemory {};
        vk::Viewport                    viewport            {};
        vk::Rect2D                      scissor             {};


        std::vector<Vertex> vertices =
        {
            {{ 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}}, 
            {{ 0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}}, 
            {{-0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}}, 
            {{-0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}} 
        };
        std::vector<uint16_t> indices =
        {
            0, 1, 2, 
            0, 2, 3 
        };

    struct uniformBufferObject
    {
        float value;
    };

    uniformBufferObject ubo{0.5};


};
#endif 