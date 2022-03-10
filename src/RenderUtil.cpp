//
// Created by Jeb Collins on 3/10/22.
//

#include "RenderUtil.hpp"



using namespace pecs;


void pecs::rglVertexAttribPointer(Vert3x3x2f v, int layoutOffset)
{
    glVertexAttribPointer(0 + layoutOffset, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0 + layoutOffset);

    glVertexAttribPointer(1 + layoutOffset, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(offsetof(Vert3x3x2f, r)) );
    glEnableVertexAttribArray(1 + layoutOffset);

    glVertexAttribPointer(2 + layoutOffset, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(offsetof(Vert3x3x2f, s)) );
    glEnableVertexAttribArray(2 + layoutOffset);
}