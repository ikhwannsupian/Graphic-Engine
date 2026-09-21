#ifndef OPEN_GL_H
#define OPEN_GL_H
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glad/gl.h>
#include <glm/ext/matrix_clip_space.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include "projection.h"

#include <SDL3/SDL.h>

class GLRenderer
{
    public:
        GLRenderer(SDL_Window* window);
        ~GLRenderer();

        void screenUpdate();
        void render();
        void render2();
    private:

        SDL_Window* window;
        SDL_GLContext context;
        Projection projection;

        VBO vboPlayer;
        VAO vaoPlayer;
        EBO eboPlayer;
};


#endif