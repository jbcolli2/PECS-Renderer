//
// Created by Jeb Collins on 3/14/22.
//

#ifndef PECS_RENDERER_CAMERA_HPP
#define PECS_RENDERER_CAMERA_HPP


#include "Components/Component.hpp"
#include "RenderUtil.hpp"


namespace pecs
{

class Camera : public Component
{
public:
    // View matrix
    glm::mat4 view{1.f};
    // Projection matrix
    glm::mat4 proj{1.f};

    // Camera position
    glm::vec3 position{0.f};
    // Camera direction
    glm::vec3 direction{-1.f};
};





} // End namespace pecs



#endif //PECS_RENDERER_CAMERA_HPP
