#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstdlib>
#include <cstddef>
#include <vulkan/vulkan.hpp>

void* VKAPI_PTR vkAllocate(
    void* pUserData,
    size_t size,
    size_t alingment,
    VkSystemAllocationScope allocationScope
);
void* VKAPI_PTR vkReallocate(
    void* pUserData,
    void* pOriginal,
    size_t size,
    size_t alingment,
    VkSystemAllocationScope allocationScope
);
void VKAPI_PTR vkFree(
    void* userData,
    void* pMemory
);

#endif