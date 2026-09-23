#include "_renderObject.h"
#include <iostream>
void RenderObject::isVisible()
{
    visible = !visible;
    entity.isVisible(visible);
    std::cout << "called " << visible <<  '\n';
}