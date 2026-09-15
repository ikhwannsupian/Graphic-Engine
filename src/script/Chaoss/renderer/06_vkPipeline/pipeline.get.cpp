#include "pipeline.h"


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

vk::Buffer VulkanPipeline::getIndexBuffer()
{
    return indexBuffer;
}

uint32_t VulkanPipeline::getIndices()
{
    return  indices.size();
}

vk::PipelineLayout VulkanPipeline::getPipelineLayout()
{
    return pipelineLayout;
}

vk::DescriptorSet  VulkanPipeline::getDescriptorSet()
{
    return descriptorSet;
}