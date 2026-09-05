#ifndef RENDERER_H
#define RENDERER_H

#include <vulkan/vulkan.hpp>

class Renderer
{
    public:
        vk::Instance instance = nullptr;
        vk::Device device = nullptr;
        void runInstance()
        {
            createInstance();
            createDevice();
        };

        void cleanup();

    private:

        void createInstance();
        void createDevice();      


};

#endif 