#include "_core.h"

bool GLRenderer::render(const RenderObjectStruct& renderData)
{
    if (!renderData.renderState.hasBuffer)
    {
        vaoPlayer.bind();
        vboPlayer.data(renderData.mesh.vertex);

        eboPlayer.data(renderData.mesh.indices);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        glEnableVertexAttribArray(1);    
        std::cout << "[OPENGL]"  << " buffer created :: id: " << static_cast<int>(renderData.name) << '\n';  
    }
    if(renderData.renderState.visible)
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        vaoPlayer.bind();
        glDrawElements(
            GL_TRIANGLES,
            6,
            GL_UNSIGNED_INT,
            nullptr
        );
    }
    else
    {
        glClearColor(0.3f, 0.6f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    return  true;
}