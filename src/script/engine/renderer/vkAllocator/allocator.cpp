#include <cstdlib>
#include <cstddef>
#include <malloc.h>

#include <vulkan/vulkan.hpp>

#include "allocator.h"


void* VKAPI_PTR vkAllocate(
    void* userData,
    size_t size,
    size_t alignment,
    VkSystemAllocationScope scope
)
{
    return _aligned_malloc(size, alignment);
}

void* VKAPI_PTR vkReallocate(
    void* userData,
    void* original,
    size_t size,
    size_t alignment,
    VkSystemAllocationScope scope
)
{
    return _aligned_realloc(original, size, alignment);
}

void VKAPI_PTR vkFree(
    void* userData,
    void* memory
)
{
    _aligned_free(memory);
}