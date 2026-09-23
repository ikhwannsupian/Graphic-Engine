#include "_engine.h"

Engine::Engine()
{
    window = new Window();
    renderer = new Renderer(window->getWindowFirst());
    game = new Game();

}



bool Engine::event(const SDL_Event* event)
{

    if (event->type == SDL_EVENT_WINDOW_RESIZED)
    {
        renderer->screenUpdate();
    }
    game->event(event);

    return window->event(event);
}

bool Engine::render()
{
    game->render(*renderer);
    SDL_GL_SwapWindow(window->getWindowFirst());
    return true;
}



Engine::~Engine()
{
    delete game;
    game = nullptr;
    delete renderer;
    renderer = nullptr;
    delete window;
    window = nullptr;
}