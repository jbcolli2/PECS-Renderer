//
// Created by Jeb Collins on 3/14/22.
//

#ifndef PECS_RENDERER_LIGHT_HPP
#define PECS_RENDERER_LIGHT_HPP

#include "Components/Component.hpp"
#include "RenderUtil.hpp"


namespace pecs
{

class Light : public Component
{
public:
    // Diffuse light emitted
    glm::vec3 diffuse{1.f};
    // Specular light emitted
    glm::vec3 specular{.5f};
    // Scale factor of diffuse used to compute ambient light emitted
    float ambientFactor = 0.2f;

    // Attenuation factors used in equations
    // (const + lin*d + quad*d^2)^{-1}
    float attenConst{0.f};
    float attenLin{1.f};
    float attenQuad{0.f};


    // Ctor
    Light(const glm::vec3& diffuse = glm::vec3(1.f), const glm::vec3& specular = glm::vec3(.5f),
          float ambFactor = .2f, float attenConst = 0.f, float attenLin = 1.f, float attenQuad = 0.f)
          : diffuse(diffuse), specular(specular), ambientFactor(ambFactor),
          attenConst(attenConst), attenLin(attenLin), attenQuad(attenQuad) {};
};


class DirLight : public Component
{
public:
    static const std::string name;


    glm::vec3 direction{0.f, -1.f, -1.f};


    DirLight(const glm::vec3 &direction = glm::vec3{0.f, -1.f, -1.f})
            : direction(direction) {};
};



} // end namespace pecs







#endif //PECS_RENDERER_LIGHT_HPP
