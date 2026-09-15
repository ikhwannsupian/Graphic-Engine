#include "_chaoss.h"

void Chaoss::destroy()
{
    if(!app)
        return;
        
    renderer->  destroy();
    window  ->  destroy();

    delete app;
    app = nullptr;
}

Chaoss::~Chaoss()
{
    destroy();
}