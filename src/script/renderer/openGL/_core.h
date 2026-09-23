#ifndef OPEN_GL_H
#define OPEN_GL_H
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glad/gl.h>
#include <glm/ext/matrix_clip_space.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include "projection.h"
#include "init.h"
#include "buffer.h"
#include <iostream>
#include <SDL3/SDL.h>
#include <random>

class GLRenderer
{
    public:
        GLRenderer(SDL_Window* window);
        ~GLRenderer();

        void screenUpdate();
        bool render();
    private:

        GlContext context;
        Projection projection;

        VBO vboPlayer;
        VAO vaoPlayer;
        EBO eboPlayer;
        bool create = false;


    // std::vector<glm::vec3> vertices;

    // std::random_device rd;
    // std::mt19937 gen(rd());

    // std::uniform_real_distribution<float> dist(-500.0f, 500.0f);

    };


#endif