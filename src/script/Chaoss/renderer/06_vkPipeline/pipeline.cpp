#include <vulkan/vulkan.hpp>
#include "pipeline.h"
#include <iostream>
#include <vector>
#include <fstream>

void VulkanPipeline::init 
(
    vk::Device                      device              ,
    vk::PhysicalDevice              physicalDevice      ,
    vk::Extent2D                    swapchainExtent     ,
    vk::SurfaceFormatKHR            surfaceFormat       
)
{
    this->device                    = device            ;
    this->physicalDevice            = physicalDevice    ;
    this->swapchainExtent           = swapchainExtent   ;
    this->surfaceFormat             = surfaceFormat     ;
}
vk::DescriptorSetLayoutBinding uboBinding()
{
    vk::DescriptorSetLayoutBinding binding{};

    binding
        .setBinding(0)
        .setDescriptorType(vk::DescriptorType::eUniformBuffer)
        .setDescriptorCount(1)
        .setStageFlags(vk::ShaderStageFlagBits::eVertex);

    return binding;
}

void VulkanPipeline::create()
{
    createVertexBuffer();
    createIndexBuffer();
    createUniformBuffer();
    createDescriptor();
    graphicsPipeline();
}
void VulkanPipeline::update(vk::Extent2D swapchainExtent)
{
    device.destroyPipeline(pipeline);
    device.destroyPipelineLayout(pipelineLayout);

    this->swapchainExtent = swapchainExtent;
    vk::PipelineLayoutCreateInfo        pipelineLayoutInfo  {};

    pipelineLayoutInfo
        .setSetLayouts(descriptorSetLayout);

    pipelineLayout = device.createPipelineLayout(pipelineLayoutInfo);

    graphicsPipeline();
}

std::vector<char> VulkanPipeline::readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);


    if (!file.is_open())
        throw std::runtime_error("Failed to open file: " + filename);
    size_t size = file.tellg();


    std::vector<char> buffer(size);

    file.seekg(0);
    file.read(buffer.data(), size);

    return buffer;
}

void VulkanPipeline::graphicsPipeline()
{
    auto vertCode = readFile("triangle.vert.spv");
    auto fragCode = readFile("triangle.frag.spv");

    auto binding    = Vertex::getBindingDescription();
    auto attributes = Vertex::getAttributeDescriptions();


    vertexInput
        .setVertexBindingDescriptions(binding)
        .setVertexAttributeDescriptions(attributes);

    vertInfo
        .setCodeSize(vertCode.size())
        .setPCode(reinterpret_cast<const uint32_t*>(vertCode.data()));

    fragInfo
        .setCodeSize(fragCode.size())
        .setPCode(reinterpret_cast<const uint32_t*>(fragCode.data()));


    vertShader = device.createShaderModule(vertInfo);
    fragShader = device.createShaderModule(fragInfo);

    vertStage
        .setStage(vk::ShaderStageFlagBits::eVertex)
        .setModule(vertShader)
        .setPName("main");

    fragStage
        .setStage(vk::ShaderStageFlagBits::eFragment)
        .setModule(fragShader)
        .setPName("main");

    std::array stages {vertStage, fragStage};



    inputAssembly
        .setTopology(vk::PrimitiveTopology::eTriangleList)
        .setPrimitiveRestartEnable(false);

    viewport
        .setX(0)
        .setY(0)
        .setWidth((float)swapchainExtent.width)
        .setHeight((float)swapchainExtent.height)
        .setMinDepth(0.0f)
        .setMaxDepth(1.0f);

    scissor
        .setOffset({0, 0})
        .setExtent(swapchainExtent);

    viewportStateInfo
        .setViewportCount(1)
        .setScissorCount(1);

    std::array<vk::DynamicState, 2> dynamicStates =
    {
        vk::DynamicState::eViewport,
        vk::DynamicState::eScissor
    };

    dynamicState
        .setDynamicStates(dynamicStates);

    rasterizer
        .setDepthClampEnable(false)
        .setRasterizerDiscardEnable(false)
        .setPolygonMode(vk::PolygonMode::eFill)
        .setCullMode(vk::CullModeFlagBits::eNone)
        .setFrontFace(vk::FrontFace::eClockwise)
        .setLineWidth(1.0f);

    multisampling
        .setRasterizationSamples(vk::SampleCountFlagBits::e1);

    colorBlendingAttachment
        .setBlendEnable(false)
        .setColorWriteMask(
            vk::ColorComponentFlagBits::eR |
            vk::ColorComponentFlagBits::eG |
            vk::ColorComponentFlagBits::eB |
            vk::ColorComponentFlagBits::eA
        );

    colorBlending
        .setLogicOpEnable(false)
        .setAttachments(colorBlendingAttachment);

    pipelineRenderingInfo
        .setColorAttachmentFormats(surfaceFormat.format);

    pipelineInfo
        .setStages(stages)
        .setPVertexInputState(&vertexInput)
        .setPInputAssemblyState(&inputAssembly)
        .setPViewportState(&viewportStateInfo)
        .setPRasterizationState(&rasterizer)
        .setPMultisampleState(&multisampling)
        .setPColorBlendState(&colorBlending)
        .setPDynamicState(&dynamicState)
        .setLayout(pipelineLayout)
        .setRenderPass(nullptr)
        .setPNext(&pipelineRenderingInfo);

    try
    {
        auto [result, p] = device.createGraphicsPipeline(nullptr, pipelineInfo);
        
        if (result != vk::Result::eSuccess)
            throw std::runtime_error("Pipeline result: " + vk::to_string(result));

        pipeline = p;
    }
    catch (vk::SystemError& e)
    {
        throw std::runtime_error("Pipeline exception: " + std::string(e.what()));
    }


    device.destroyShaderModule(vertShader);
    device.destroyShaderModule(fragShader);

}
void VulkanPipeline::destroy()
{
    device.destroyBuffer(vertexBuffer);
    device.freeMemory(vertexBufferMemory);
    device.destroyPipeline(pipeline);
    device.destroyPipelineLayout(pipelineLayout);

        if (indexBuffer)
    {
        device.destroyBuffer(indexBuffer);
        device.freeMemory(indexBufferMemory);
        indexBuffer       = nullptr;
        indexBufferMemory = nullptr;
    }

    
    pipeline = nullptr;
    pipelineLayout = nullptr;;
    vertexBuffer       = nullptr;
    vertexBufferMemory = nullptr;
}

VulkanPipeline::~VulkanPipeline()
{
    destroy();
}