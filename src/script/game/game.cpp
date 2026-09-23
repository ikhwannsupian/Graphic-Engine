#include "_game.h"

void Game::render(Renderer& renderer)
{

}

void Game::event(const SDL_Event* event)
{
    if (event->key.key == SDLK_Q && event->type == SDL_EVENT_KEY_DOWN && !event->key.repeat)
    {
    }
}