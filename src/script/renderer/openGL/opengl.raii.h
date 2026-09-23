#ifndef OPENGL_RAII_H
#define OPENGL_RAII_H
#include <glad/gl.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stb/stb_image.h>
#include <iostream>

class VBO
{
    public:
        VBO () {    glGenBuffers   (1, &VBOid  );    }
        ~VBO() {    glDeleteBuffers(1, &VBOid  );    }
        void bind()  {glBindBuffer(GL_ARRAY_BUFFER, VBOid);}
        template <typename T> 
        void data(const std::vector<T>& vertices) 
        {
            glBindBuffer(GL_ARRAY_BUFFER, VBOid);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(T)), vertices.data(), GL_STATIC_DRAW);
        }
        GLuint id() const { return VBOid; }
        VBO(const VBO&) = delete;
        VBO& operator=(const VBO&) = delete;
    private:
        GLuint VBOid;
};
class EBO
{
    public:
        EBO () {    glGenBuffers   (1, &EBOid  );    }
        ~EBO() {    glDeleteBuffers(1, &EBOid  );    }
        void bind() {glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOid);}
        template <typename T> 
        void data(const T& vertices) 
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOid);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(T)), vertices.data(), GL_STATIC_DRAW);
        }
        GLuint id() const { return EBOid; }
        EBO(const EBO&) = delete;
        EBO& operator=(const EBO&) = delete;
    private:
        GLuint EBOid;
};
class VAO
{
    public:
        VAO () {    glGenVertexArrays   (1, &VAOid  );    }
        ~VAO() {    glDeleteVertexArrays(1, &VAOid  );    }
        void bind() {glBindVertexArray(VAOid);}
        GLuint id() const { return VAOid;}
        VAO(const VAO&) = delete;
        VAO& operator=(const VAO&) = delete;
    private:
        GLuint VAOid;
};

class Framebuffer
{
    public:
        GLuint id;

        Framebuffer() { glGenFramebuffers(1, &id); }
        ~Framebuffer() { glDeleteFramebuffers(1, &id); }
        Framebuffer(const Framebuffer&) = delete;
        Framebuffer& operator=(const Framebuffer&) = delete;
        void bind() { glBindFramebuffer(GL_FRAMEBUFFER, id); }
        void unbind(){ glBindFramebuffer(GL_FRAMEBUFFER, 0); }
};
class Shader
{
    public:
        GLuint shader;

        Shader(GLenum type, const char* path)
        {
            shader = glCreateShader(type);
            std::string source = loadShader(path);
            const char* sourcePtr = source.c_str();
            glShaderSource( shader, 1, &sourcePtr, nullptr);
            glCompileShader( shader );            
        }
        ~Shader()  {  glDeleteShader( shader );  }
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
    private:
        std::string loadShader(const char* path)
        {
            std::ifstream file(path);

            if (!file)
                throw std::runtime_error("Failed to open shader");

            std::stringstream buffer;
            buffer << file.rdbuf();

            return buffer.str();
        }
};
class ShaderProgram
{
    public:
        GLuint program;
        ShaderProgram( const Shader* vertex, const Shader* fragment = nullptr)
        {
            program = glCreateProgram();
            glAttachShader(program, vertex->shader);
            if ( fragment )glAttachShader(program, fragment->shader);
            glLinkProgram(program);
        }
        ~ShaderProgram() {  glDeleteProgram(program);  }
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;
        void bind()  {  glUseProgram(program); }
};

class Texture
{
public:
    GLuint id;
    Texture(const char* path)
    {
        glGenTextures(1, &id);

        glBindTexture(GL_TEXTURE_2D, id);
        int width, height, channels;

        unsigned char* pixels = stbi_load( path, &width, &height, &channels, 4 );
        if (!pixels)   {std::cout << "Failed to load " << path << '\n'; return;}
        glTexImage2D(  GL_TEXTURE_2D, 0, GL_RGBA,  width,  height,  0,  GL_RGBA,  GL_UNSIGNED_BYTE,  pixels  );
        stbi_image_free(pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    void setFilter(GLint min, GLint mag)
    {
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
    }
    void setWrap(GLint s, GLint t)
    {
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t );
    }
    ~Texture() { glDeleteTextures(1, &id); }
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    void bind(){ glBindTexture(GL_TEXTURE_2D, id); }
};


#endif