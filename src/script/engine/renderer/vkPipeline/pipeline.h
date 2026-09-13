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
struct Vertex
{
    Vec2 position;
    Vec4 color;

    static vk::VertexInputBindingDescription getBindingDescription ()
    {
        vk::VertexInputBindingDescription binding{};

        binding
            .setBinding(0)
            .setStride(sizeof(Vertex))
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
        uint32_t findMemoryType( uint32_t typeFilter, vk::MemoryPropertyFlags properties );
        void graphicsPipeline();

        vk::Buffer  getVertexBuffer();
        vk::Pipeline getPipeline();
        vk::Rect2D  getScissor();
        vk::Viewport getViewport();

        void destroy();

        ~VulkanPipeline();


    private:
        vk::Device                      device              {};
        vk::PhysicalDevice              physicalDevice      {};
        vk::Extent2D                    swapchainExtent     {};
        vk::SurfaceFormatKHR            surfaceFormat       {};


        vk::PipelineLayout              pipelineLayout      {};
        vk::Pipeline                    pipeline            {};
        vk::Buffer                      vertexBuffer        {};
        vk::DeviceMemory                vertexBufferMemory  {};
        vk::Viewport                    viewport            {};
        vk::Rect2D                      scissor             {};


            std::vector<Vertex> vertices =
        {
            {{ 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}},
            {{-0.5f,  -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}},
            {{-0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}}

        };

};

#endif 