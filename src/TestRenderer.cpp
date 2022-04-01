

#include "RenderUtil.hpp"

#include "Engine/Window.hpp"
#include "Objects/Object.hpp"

#include "Components/Component.hpp"
#include "Components/Transform.hpp"
#include "Components/Renderable.hpp"
#include "Components/Light.hpp"



#include "Systems/RenderPipeline.hpp"
#include "Systems/CameraController.hpp"



#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>





using namespace pecs;

int main()
{
    WindowManager::GetInstance().InitGLFW(800, 600);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    GLFWwindow* window = WindowManager::GetInstance().GetWindow();


    std::vector<Object> objectList{};
    Object obj;

    // Cube
    Transform trans;
    Renderable renderComponent(RenderType::Cube);
    obj.AddComponent(trans);
    obj.AddComponent(renderComponent);
    objectList.push_back(obj);

    // DirLight
    objectList.emplace_back(Object());
    objectList.back().AddComponent(Light());
    objectList.back().AddComponent(DirLight());
    objectList.back().GetComponent<DirLight>()->direction.z = 1.f;
    objectList.back().GetComponent<Light>()->diffuse.r = .4f;

    // Camera
    objectList.emplace_back(Object());
    objectList.back().AddComponent(Camera());
    objectList.back().GetComponent<Camera>()->position = glm::vec3(-2.f, 0.f, 5.f);


    // ******** Systems  ********** //
    RenderPipeline renderPipeline{};
    renderPipeline.SetSignature<Pipeline>();

    CameraController cameraController{};

    for(auto& obj : objectList)
    {
        renderPipeline.AddObjSameSignature(obj);
        cameraController.AddObjSameSignature(obj);
    }

    renderPipeline.SetupPipeline();
    renderPipeline.SetupShape();
    cameraController.Setup();

    float currentFrame = 0.f;
    float lastFrame = 0.f;
    float deltaTime = 0.f;

    while(!glfwWindowShouldClose(window))
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
        Input::GetInstance().HandleNewInputs();

        if(Input::GetInstance().KeyDown(GLFW_KEY_P))
            glfwSetWindowShouldClose(window, true);

        cameraController.Update(deltaTime);


        renderPipeline.Render();

        glfwSwapBuffers(window);

    }

    glfwTerminate();


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
