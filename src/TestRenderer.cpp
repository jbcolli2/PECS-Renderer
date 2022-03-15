

#include "RenderUtil.hpp"

#include "Engine/Window.hpp"
#include "Objects/Object.hpp"

#include "Components/Component.hpp"
#include "Components/Transform.hpp"
#include "Components/Renderable.hpp"
#include "Components/Light.hpp"



#include "Systems/RenderPipeline.hpp"



#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>





using namespace pecs;

int main()
{
    Window::InitGLFW(800, 600);
    Window::InitGlad();


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
    objectList.back().AddComponent(Renderable());
    objectList.back().GetComponent<DirLight>()->direction.z = 1.f;
    objectList.back().GetComponent<Light>()->diffuse.r = .4f;

    // ******** Systems  ********** //
    RenderPipeline renderPipeline{};
    renderPipeline.SetSignature<Pipeline>();

    for(auto& obj : objectList)
    {
        renderPipeline.AddObjSameSignature(obj);
    }

    renderPipeline.SetupPipeline();
    renderPipeline.SetupShape();

    while(!glfwWindowShouldClose(Window::window))
    {
        renderPipeline.Render();

        glfwSwapBuffers(Window::window);
        glfwPollEvents();
    }

    glfwTerminate();


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
