//
// Created by Jeb Collins on 3/30/22.
//

#ifndef PECS_RENDERER_CAMERACONTROLLER_HPP
#define PECS_RENDERER_CAMERACONTROLLER_HPP

#include "Systems/System.hpp"
#include "Components/Camera.hpp"
#include "Engine/Input.hpp"
#include "Engine/Window.hpp"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>


namespace pecs
{
class CameraController : public System
{
private:
    float m_positionSpeed{2.5f};
    float m_directionSpeed{3.5f};

    bool m_settingCamDir{false};
    glm::vec2 m_lastMousePos{0.f};



    std::shared_ptr<Camera> getMainCamera();
    /***************** updateDirection  ******************
     * @brief Move the direction of the camera by an offset determined by an offset
     *      of the pitch and yaw.
     *
     * @param pitchOffset, yawOffset An offset for the pitch and yaw.
    ******************************************************************/
    void updateDirection(float pitchOffset, float yawOffset);
public:
    CameraController()
    {
        SetSignature<Camera>();
    };

    /***************** Setup  ******************
     * @brief Initialize the camera settings.  This will compute the view and proj matrices given the
     *      initial settings for the position and direction of the camera.
    ******************************************************************/
    void Setup();

    /***************** Update  ******************
     * @brief This will process the input to move the camera and if needed update the view and proj matrices.
     *
     * @param deltaTime The amount of time elapsed since last frame.
    ******************************************************************/
    void Update(float deltaTime);
}; // End CameraController Class



} // End pecs namespace


#endif //PECS_RENDERER_CAMERACONTROLLER_HPP
