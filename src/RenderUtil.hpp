//
// Created by Jeb Collins on 3/8/22.
//

#ifndef PECS_RENDERER_RENDERUTIL_HPP
#define PECS_RENDERER_RENDERUTIL_HPP

#include "Util.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>


//***********************************************************
//       Any utility functions or data structures needed for rendering
//***********************************************************
namespace pecs
{

/***************** RenderType enum  ******************
 * @brief A scoped enum listing the various types of renderables allowed.
 *      This type will be tell the RenderPipeline system how to fill the
 *      vertex data.
***************************************************///
enum class RenderType
{
    Cube,
    Plane,
    Model
};





/***************** Vert?x?x?x?  ******************
 * @brief Data structure to hold a vertex with attributes in a
 *      renderable component, i.e. a shape or model.  This will hold the
 *      attributes of a vertex in a contiguous portion of memory as needed
 *      by OpenGL.
 *
 *      Each different Vert structure holds different lengths of attributes
 *      in different orders.  The loadVBO function takes this vertex
 *      type and uses it to automatically determine how to set up the vertex
 *      attributes in the VAO.
***************************************************///
struct Vert3x3x2f
{
    float x,y,z;
    float r,g,b;
    float s,t;

    Vert3x3x2f() : x(0.f), y(0.f), z(0.f), r(0.f), g(0.f), b(0.f), s(0.f), t(0.f) {};
    Vert3x3x2f(float x, float y, float z, float r, float g, float b, float s, float t) :
            x(x), y(y), z(z), r(r), g(g), b(b), s(s), t(t) {};
};





//*********************************************
//            Set Vertex attributes
//*********************************************
void rglVertexAttribPointer(Vert3x3x2f v, int layoutOffset = 0);










//*********************************************
//            Graphics data loading functions
//*********************************************


/***************** loadVBOData  ******************
 * @brief Generates a vertex buffer object and loads vertex data into it.
 *      The type of the vertex data must be one of the Vert?x?x... data structures,
 *      as this is then used to setup the correct vertex attributes.
 *
 *      Note: The corresponding VAO must be bound before this method is called in
 *      order to attach it to the VAO.
 *
 * @param verts The vector of vertices of type Vert?x?x...
 * @param layoutOffset Used for instance rendering
 *      TODO: This is not currently implemented.
 *
 * @returns Handle to the VBO.
******************************************************************/
template <class T>
unsigned int loadVBOData(std::vector<T> verts, int layoutOffset = 0)
{
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(T), &verts.front(), GL_STATIC_DRAW);

    rglVertexAttribPointer(verts[0], layoutOffset);

    return VBO;
}




// TODO: Fill in comments for these functions.
//template <class T>
//unsigned int loadEBOData(std::vector<T> verts)
//{
//    unsigned int EBO;
//    glGenBuffers(1, &EBO);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, verts.size() * sizeof(T), &verts.front(), GL_STATIC_DRAW);
//
//    return EBO;
//}


// TODO: Fill in comments for these functions
//unsigned int loadTextureFromFile(const char* path, bool sRGB);
//unsigned int loadTextureFromFile(const char* path, std::string directory, bool sRGB);




} // end namespace pecs





#endif //PECS_RENDERER_RENDERUTIL_HPP
