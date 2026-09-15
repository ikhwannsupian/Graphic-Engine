#ifndef CHAOSS_H
#define CHAOSS_H

#include <script/Chaoss/window/window.h>
#include <script/Chaoss/renderer/renderer.h>

struct App
{
    Window      window  ;
    Renderer    renderer; 
};
class Chaoss
{
    public:
        bool init   ();
        bool event  (SDL_Event* event);
        bool render ();
        void destroy();

        ~Chaoss();

    private:
        App*        app     ;
        Window*     window  ;
        Renderer*   renderer;
};
#endif