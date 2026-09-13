#include <vulkan/vulkan.hpp>
#include "pipeline.h"
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

void VulkanPipeline::create()
{
    createVertexBuffer();
    graphicsPipeline();
}
void VulkanPipeline::update(vk::Extent2D swapchainExtent)
{
    device.destroyPipeline(pipeline);
    device.destroyPipelineLayout(pipelineLayout);

    this->swapchainExtent = swapchainExtent;

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
void VulkanPipeline::createVertexBuffer()
{
    vk::BufferCreateInfo bufferInfo{};

    bufferInfo
        .setSize(sizeof(Vertex) * vertices.size())
        .setUsage(vk::BufferUsageFlagBits::eVertexBuffer)
        .setSharingMode(vk::SharingMode::eExclusive);

    vertexBuffer = device.createBuffer(bufferInfo);

    vk::MemoryRequirements memReqs = device.getBufferMemoryRequirements(vertexBuffer);

    vk::MemoryAllocateInfo allocInfo{};

    allocInfo
        .setAllocationSize(memReqs.size)
        .setMemoryTypeIndex(findMemoryType(memReqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent));

    vertexBufferMemory = device.allocateMemory(allocInfo);

    device.bindBufferMemory(vertexBuffer, vertexBufferMemory, 0);
    void* data = device.mapMemory(vertexBufferMemory, 0, bufferInfo.size);
    memcpy(data, vertices.data(), bufferInfo.size);
    device.unmapMemory(vertexBufferMemory);

}

uint32_t VulkanPipeline::findMemoryType( uint32_t typeFilter, vk::MemoryPropertyFlags properties)
{
    vk::PhysicalDeviceMemoryProperties memProperties =
        physicalDevice.getMemoryProperties();

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i)) &&
            (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            return i;
        }
    }

    throw std::runtime_error("Failed to find suitable memory type!");
}
void VulkanPipeline::graphicsPipeline()
{
    auto vertCode = readFile("triangle.vert.spv");
    auto fragCode = readFile("triangle.frag.spv");

    auto binding    = Vertex::getBindingDescription();
    auto attributes = Vertex::getAttributeDescriptions();

    vk::PipelineVertexInputStateCreateInfo vertexInput{};
    vertexInput
        .setVertexBindingDescriptions(binding)
        .setVertexAttributeDescriptions(attributes);

    vk::ShaderModuleCreateInfo vertInfo{};
    vk::ShaderModuleCreateInfo fragInfo{};

    vertInfo
        .setCodeSize(vertCode.size())
        .setPCode(reinterpret_cast<const uint32_t*>(vertCode.data()));

    fragInfo
        .setCodeSize(fragCode.size())
        .setPCode(reinterpret_cast<const uint32_t*>(fragCode.data()));

    vk::ShaderModule vertShader{};
    vk::ShaderModule fragShader{};

    vertShader = device.createShaderModule(vertInfo);
    fragShader = device.createShaderModule(fragInfo);

    vk::PipelineShaderStageCreateInfo vertStage{};
    vk::PipelineShaderStageCreateInfo fragStage{};

    vertStage
        .setStage(vk::ShaderStageFlagBits::eVertex)
        .setModule(vertShader)
        .setPName("main");

    fragStage
        .setStage(vk::ShaderStageFlagBits::eFragment)
        .setModule(fragShader)
        .setPName("main");

    std::array stages {vertStage, fragStage};

    vk::PipelineLayoutCreateInfo layoutInfo{};

    pipelineLayout = device.createPipelineLayout(layoutInfo);

    
    vk::PipelineInputAssemblyStateCreateInfo inputAssembly{};

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

    vk::PipelineViewportStateCreateInfo viewportStateInfo{};

    viewportStateInfo
        .setViewportCount(1)
        .setScissorCount(1);

    std::array<vk::DynamicState, 2> dynamicStates =
    {
        vk::DynamicState::eViewport,
        vk::DynamicState::eScissor
    };

    vk::PipelineDynamicStateCreateInfo dynamicState{};

    dynamicState
        .setDynamicStates(dynamicStates);

    vk::PipelineRasterizationStateCreateInfo rasterizer{};

    rasterizer
        .setDepthClampEnable(false)
        .setRasterizerDiscardEnable(false)
        .setPolygonMode(vk::PolygonMode::eFill)
        .setCullMode(vk::CullModeFlagBits::eNone)
        .setFrontFace(vk::FrontFace::eClockwise)
        .setLineWidth(1.0f);

    vk::PipelineMultisampleStateCreateInfo multisampling{};

    multisampling
        .setRasterizationSamples(vk::SampleCountFlagBits::e1);


    vk::PipelineColorBlendAttachmentState colorBlendingAttachment{};

    colorBlendingAttachment
        .setBlendEnable(false)
        .setColorWriteMask(
            vk::ColorComponentFlagBits::eR |
            vk::ColorComponentFlagBits::eG |
            vk::ColorComponentFlagBits::eB |
            vk::ColorComponentFlagBits::eA
        );

    vk::PipelineColorBlendStateCreateInfo colorBlending{};

    colorBlending
        .setLogicOpEnable(false)
        .setAttachments(colorBlendingAttachment);

    vk::PipelineRenderingCreateInfo pipelineRenderingInfo{};

    pipelineRenderingInfo
        .setColorAttachmentFormats(surfaceFormat.format);

    vk::GraphicsPipelineCreateInfo pipelineInfo{};

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
vk::Buffer  VulkanPipeline::getVertexBuffer()
{
    return vertexBuffer;
}
vk::Pipeline VulkanPipeline::getPipeline()
{
    return pipeline;
}
vk::Rect2D  VulkanPipeline::getScissor()
{
    return scissor;
}
vk::Viewport VulkanPipeline::getViewport()
{
    return viewport;
}

void VulkanPipeline::destroy()
{
    device.destroyBuffer(vertexBuffer);
    device.freeMemory(vertexBufferMemory);
    device.destroyPipeline(pipeline);
    device.destroyPipelineLayout(pipelineLayout);
    
    pipeline = nullptr;
    pipelineLayout = nullptr;;
    vertexBuffer       = nullptr;
    vertexBufferMemory = nullptr;
}

VulkanPipeline::~VulkanPipeline()
{
    destroy();
}