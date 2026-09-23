#ifndef PROJECTION_H
#define PROJECTION_H

#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <script/renderer/openGL/opengl.raii.h>

class Projection
{
    public:
        Projection(SDL_Window* window)
        :projectionShader(GL_VERTEX_SHADER, "shaders/triangle.vert"), 
         projectionProgram(&projectionShader)
        {
            this->window = window;
            int width, height;
            SDL_GetWindowSize(window, &width, &height);
            glViewport(0, 0, width, height);
            glViewport(0, 0, width, height);
            projection = glm::ortho(
                -(float)width/2,
                (float)width/2,
                -(float)height/2,
                (float)height/2
            );   

            projectionLocation = glGetUniformLocation(projectionProgram.program, "projection");

            glUseProgram(projectionProgram.program);

            glUniformMatrix4fv(
                projectionLocation,   
                1,                     
                GL_FALSE,             
                glm::value_ptr(projection) 
            );
        }
        void updateProjection()
        {
            int width, height;
            SDL_GetWindowSize(window, &width, &height);
            glViewport(0, 0, width, height);
            glViewport(0, 0, width, height);
            projection = glm::ortho(
                -(float)width/2,
                (float)width/2,
                -(float)height/2,
                (float)height/2
            );               
            glUseProgram(projectionProgram.program);

            glUniformMatrix4fv(
                projectionLocation,   
                1,                     
                GL_FALSE,             
                glm::value_ptr(projection) 
            );
            std::cout << "[OPENGL] Window is Sizing!" << '\n';
        }
    private:
        SDL_Window* window;
        Shader projectionShader;
        ShaderProgram projectionProgram;
        GLint projectionLocation;
        glm::mat4 projection;
};

#endif