#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <glm/glm.hpp>

#include <enum/enum.h>

class World
{
    public:
        uint32_t createObject(Type objectType);

    private:
        uint32_t id;
        std::vector<Type> type;

        std::vector<float> positionX    ;
        std::vector<float> positionY    ;
        std::vector<float> positionZ    ;

        std::vector<float> scaleX       ;
        std::vector<float> scaleY       ;
        std::vector<float> scaleZ       ;

        std::vector<float> rotationX    ;
        std::vector<float> rotationY    ;
        std::vector<float> rotationZ    ;

        std::vector<bool> visible       ;
        std::vector<bool> hasBuffer     ;
        std::vector<bool> exist         ;

};

#endif