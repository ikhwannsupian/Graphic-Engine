#include "pipeline.h"

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
void VulkanPipeline::createIndexBuffer()
{
    vk::BufferCreateInfo bufferInfo{};
    bufferInfo
        .setSize(sizeof(uint16_t) * indices.size())
        .setUsage(vk::BufferUsageFlagBits::eIndexBuffer)
        .setSharingMode(vk::SharingMode::eExclusive);

    indexBuffer = device.createBuffer(bufferInfo);

    vk::MemoryRequirements memReqs = 
        device.getBufferMemoryRequirements(indexBuffer);

    vk::MemoryAllocateInfo allocInfo{};
    allocInfo
        .setAllocationSize(memReqs.size)
        .setMemoryTypeIndex(findMemoryType(
            memReqs.memoryTypeBits,
            vk::MemoryPropertyFlagBits::eHostVisible |
            vk::MemoryPropertyFlagBits::eHostCoherent
        ));

    indexBufferMemory = device.allocateMemory(allocInfo);
    device.bindBufferMemory(indexBuffer, indexBufferMemory, 0);

    void* data = device.mapMemory(indexBufferMemory, 0, bufferInfo.size);
    memcpy(data, indices.data(), bufferInfo.size);
    device.unmapMemory(indexBufferMemory);
}

void VulkanPipeline::createUniformBuffer()
{

    vk::BufferCreateInfo bufferInfo{};

    bufferInfo
        .setSize(sizeof(ubo))
        .setUsage(vk::BufferUsageFlagBits::eUniformBuffer)
        .setSharingMode(vk::SharingMode::eExclusive);

    uniformBuffer = device.createBuffer(bufferInfo);

    vk::MemoryRequirements memReqs = 
        device.getBufferMemoryRequirements(uniformBuffer);

    vk::MemoryAllocateInfo allocInfo{};
    allocInfo
        .setAllocationSize(memReqs.size)
        .setMemoryTypeIndex(findMemoryType(
            memReqs.memoryTypeBits,
            vk::MemoryPropertyFlagBits::eHostVisible |
            vk::MemoryPropertyFlagBits::eHostCoherent
        ));
    uniformBufferMemory = device.allocateMemory(allocInfo);

    device.bindBufferMemory(uniformBuffer, uniformBufferMemory, 0);

    void* data = device.mapMemory(uniformBufferMemory, 0, bufferInfo.size);
    memcpy(data, &ubo, sizeof(ubo));
    device.unmapMemory(uniformBufferMemory);
}

void VulkanPipeline::createDescriptor()
{
    auto layout     = uboBinding();

    vk::DescriptorPoolSize              poolSize            {};
    vk::DescriptorSetLayoutCreateInfo   layoutInfo          {};
    vk::DescriptorPoolCreateInfo        poolInfo            {};
    vk::DescriptorSetAllocateInfo       allocInfo           {};
    vk::PipelineLayoutCreateInfo        pipelineLayoutInfo  {};

    layoutInfo
        .setBindingCount(1)
        .setBindings(layout);

    poolSize
        .setType(vk::DescriptorType::eUniformBuffer)
        .setDescriptorCount(1);

    poolInfo
        .setMaxSets(1)
        .setPoolSizeCount(1)
        .setPPoolSizes(&poolSize);  
        
    descriptorSetLayout = device.createDescriptorSetLayout(layoutInfo);
    descriptorPool = device.createDescriptorPool(poolInfo);

    allocInfo
        .setDescriptorPool(descriptorPool)
        .setDescriptorSetCount(1)
        .setSetLayouts(descriptorSetLayout);

    descriptorSet = device.allocateDescriptorSets(allocInfo).front();


    pipelineLayoutInfo
        .setSetLayouts(descriptorSetLayout);

    pipelineLayout = device.createPipelineLayout(pipelineLayoutInfo);

    vk::DescriptorBufferInfo bufferInfo{};
    bufferInfo
        .setBuffer(uniformBuffer)
        .setOffset(0)
        .setRange(sizeof(uniformBufferObject));

    vk::WriteDescriptorSet write{};

    write
        .setDstSet(descriptorSet)
        .setDstBinding(0)
        .setDescriptorType(vk::DescriptorType::eUniformBuffer)
        .setBufferInfo(bufferInfo);

    device.updateDescriptorSets(write, {});
}
