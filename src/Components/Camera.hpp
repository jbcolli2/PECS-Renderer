//
// Created by Jeb Collins on 3/14/22.
//

#ifndef PECS_RENDERER_CAMERA_HPP
#define PECS_RENDERER_CAMERA_HPP


#include "Components/Component.hpp"
#include "RenderUtil.hpp"

#include <glm/glm.hpp>


namespace pecs
{

class Camera : public Component
{
public:
    // View matrix
    glm::mat4 view{1.f};


    // Camera position
    glm::vec3 position{0.f};
    // Camera direction
    glm::vec3 direction{0.f, 0.f, -1.f};
    // Field of view, in radians
    float fov{glm::radians(45.f)};

    // Is this main camera?  Make sure there is only one of these at a time
    bool mainCamera{true};


};





} // End namespace pecs



#endif //PECS_RENDERER_CAMERA_HPP
