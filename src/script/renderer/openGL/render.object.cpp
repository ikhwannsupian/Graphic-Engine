#include "_core.h"

// bool GLRenderer::render()
// {
//     if ()
//     {
//         vaoPlayer.bind();
//         vboPlayer.data();

//         eboPlayer.data();

//         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(), (void*)offsetof());
//         glEnableVertexAttribArray(0);

//         glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Ver), (void*)offsetof());
//         glEnableVertexAttribArray(1);    
//         std::cout << "[OPENGL]"  << " buffer created :: id: " << static_cast<int>() << '\n';  
//     }
//     if(renderData.renderState.visible)
//     {
//         glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);
//         vaoPlayer.bind();
//         glDrawElements(
//             GL_TRIANGLES,
//             6,
//             GL_UNSIGNED_INT,
//             nullptr
//         );
//     }
//     else
//     {
//         glClearColor(0.3f, 0.6f, 1.0f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);
//     }
//     return  true;
// }