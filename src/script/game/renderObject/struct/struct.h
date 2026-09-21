#ifndef STRUCT_ENTITY_H
#define STRUCT_ENTITY_H

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 uv;
};


struct MeshHandle
{
    std::vector<Vertex> vertex =
    {
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f}}
    };
    std::vector<uint32_t> indices =
    { 1, 2, 3, 2, 4, 3};
};

struct MaterialHandle
{

};
struct RenderObjectStruct
{
    bool dirty = false;
    
    MeshHandle mesh;
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