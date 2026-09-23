#ifndef STRUCT_ENTITY_H
#define STRUCT_ENTITY_H
#include "enum.name.h"
#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 uv;
};

struct RenderState
{
    bool& visible;
    bool hasBuffer = false;
};
struct MeshHandle
{
    std::vector<Vertex> vertex =
    {
        {{-20.0f, -20.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 20.0f, -20.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 20.0f,  20.0f, 0.0f}, {1.0f, 1.0f}},
        {{-20.0f,  20.0f, 0.0f}, {0.0f, 1.0f}}
    };
    std::vector<uint32_t> indices =
    { 0, 1, 2, 0, 2, 3};
};

struct MaterialHandle
{

};
struct RenderObjectStruct
{
    ObjectName name;
    bool dirty     = false;
    RenderState renderState;
    
    MeshHandle     mesh;
    MaterialHandle material;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};


#endif