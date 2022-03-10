//
// Created by Jeb Collins on 2/26/22.
//

#ifndef PECS_RENDERER_TRANSFORM_HPP
#define PECS_RENDERER_TRANSFORM_HPP

#include "Component.hpp"

#include <glm/glm.hpp>

namespace pecs
{
class Transform : public Component
{
public:
    glm::vec3 position{0.f, 0.f, 0.f};
    glm::vec3 rotation{0.f, 0.f, 0.f};
    glm::vec3 scale{1.f, 1.f, 1.f};
};


} // End pecs namespace


#endif //PECS_RENDERER_TRANSFORM_HPP
