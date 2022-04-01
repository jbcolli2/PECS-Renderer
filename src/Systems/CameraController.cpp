//
// Created by Jeb Collins on 3/30/22.
//

#include "CameraController.hpp"


using namespace pecs;


/***************** Setup  ******************
 * @brief Initialize the camera settings.  This will compute the view and proj matrices given the
 *      initial settings for the position and direction of the camera.
 *
 *      We know all objects in the system are cameras because we set the signature in the ctor.
******************************************************************/
void CameraController::Setup()
{
    std::shared_ptr<Camera> camComp{nullptr};
    for(auto camera : m_objects)
    {
        camComp = camera->GetComponent<Camera>();
        camComp->view = glm::lookAt(camComp->position, camComp->position + camComp->direction, glm::vec3(0.f, 1.f, 0.f));
    }
}


/***************** Update  ******************
 * @brief This will process the input to move the camera and if needed update the view and proj matrices.
 *
 * @param deltaTime The amount of time elapsed since last frame.
******************************************************************/
void CameraController::Update(float deltaTime)
{
    // If we move the camera at all or change direction, change this flag to true and recompute view matrix
    bool updateView{false};

    std::shared_ptr<Camera> camComp{getMainCamera()};


    // ************* Update camera based on Input  **************************** //
    if(Input::GetInstance().KeyPress(GLFW_KEY_A))
    {
        camComp->position.x -= m_positionSpeed*deltaTime;
        updateView = true;
    }
    if (Input::GetInstance().KeyPress(GLFW_KEY_D))
    {
        camComp->position.x += m_positionSpeed * deltaTime;
        updateView = true;
    }
    if (Input::GetInstance().KeyPress(GLFW_KEY_W))
    {
        camComp->position.z -= m_positionSpeed * deltaTime;
        updateView = true;
    }
    if (Input::GetInstance().KeyPress(GLFW_KEY_S))
    {
        camComp->position.z += m_positionSpeed * deltaTime;
        updateView = true;
    }
    if (Input::GetInstance().KeyPress(GLFW_KEY_Q))
    {
        camComp->position.y -= m_positionSpeed * deltaTime;
        updateView = true;
    }
    if (Input::GetInstance().KeyPress(GLFW_KEY_E))
    {
        camComp->position.y += m_positionSpeed * deltaTime;
        updateView = true;
    }



    // ************* Camera Direction  **************************** //


    GLFWwindow* window = WindowManager::GetInstance().GetWindow();
    if(Input::GetInstance().RightMouseDown())
    {
        m_settingCamDir = true;
        m_lastMousePos = Input::GetInstance().MousePosition();
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    if(Input::GetInstance().RightMouseUp())
    {
        m_settingCamDir = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if(m_settingCamDir)
    {
        glm::vec2 currentMousePos = Input::GetInstance().MousePosition();
        glm::vec2 mouseOffset = (currentMousePos - m_lastMousePos);
        if (glm::length(mouseOffset) > 1e-6)
        {
            updateView = true;
            mouseOffset *= m_directionSpeed * deltaTime;
            updateDirection(mouseOffset.x, -mouseOffset.y);
        }

        m_lastMousePos = currentMousePos;
    }







    if(updateView)
        camComp->view = glm::lookAt(camComp->position, camComp->position + camComp->direction, glm::vec3(0.f, 1.f, 0.f));
}







/***************** getMainCamera  ******************
 * @brief Returns the main camera from m_objects vector.
******************************************************************/
std::shared_ptr<Camera> CameraController::getMainCamera()
{
    std::shared_ptr<Camera> camComp{nullptr};
    // Find main camera, will just pick out first camera that is main, assuming there is only one
    for (auto camera: m_objects)
    {
        camComp = camera->GetComponent<Camera>();
        if (camComp->mainCamera)
            return camComp;
    }
    assert("There is no main camera in CameraController::Update" && camComp != nullptr);

    return nullptr;
}

/***************** updateDirection  ******************
 * @brief Move the direction of the camera by an offset determined by an offset
 *      of the pitch and yaw.
 *
 *      First normalizes the direction.
 *      Uses the pitch/yaw offset to compute an offset direction vector.
 *      Uses offset direction vector to update known direction vector.
******************************************************************/
void CameraController::updateDirection(float pitchOffset, float yawOffset)
{
    auto camComp{getMainCamera()};

    float pitchRad = glm::radians(pitchOffset);
    float yawRad = glm::radians(yawOffset);

    glm::vec3 offsetDir{glm::cos(yawRad)*glm::sin(pitchRad), glm::sin(yawRad), -glm::cos(yawRad)*glm::cos(pitchRad)+1};

    glm::normalize(camComp->direction);

    camComp->direction += offsetDir;
}