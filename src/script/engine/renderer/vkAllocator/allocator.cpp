#include <cstdlib>
#include <cstddef>
#include <vulkan/vulkan.hpp>

#include "allocator.h"

void* VKAPI_PTR vkAllocate(
    void* UserData,
    size_t size,
    size_t alingment,
    VkSystemAllocationScope allocationScope
)
{
    _aligned_malloc(size, alingment);
}

void* VKAPI_PTR vkReallocate(
    void* UserData,
    void* Original,
    size_t size,
    size_t alingment,
    VkSystemAllocationScope allocationScope
)
{
    return nullptr;
}

void VKAPI_PTR vkFree(
    void* UserData,
    void* memory
)
{
    _aligned_free(memory);
}