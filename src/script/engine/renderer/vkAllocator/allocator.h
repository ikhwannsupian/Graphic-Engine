#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstdlib>
#include <cstddef>
#include <vulkan/vulkan.hpp>

void* VKAPI_PTR vkAllocate(
    void* userData,
    size_t size,
    size_t alignment,
    VkSystemAllocationScope scope
);

void* VKAPI_PTR vkReallocate(
    void* userData,
    void* original,
    size_t size,
    size_t alignment,
    VkSystemAllocationScope scope
);

void VKAPI_PTR vkFree(
    void* userData,
    void* memory
);
#endif