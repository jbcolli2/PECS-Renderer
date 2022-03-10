

#include "RenderUtil.hpp"

#include "Engine/Window.hpp"
#include "Objects/Object.hpp"

#include "Components/Transform.hpp"
#include "Components/Renderable.hpp"

#include "Systems/RenderPipeline.hpp"



#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>





using namespace pecs;

int main()
{
    Window::InitGLFW(800, 600);
    Window::InitGlad();
    /*
     * ComponentManager compManager();
     * std::vector<Object> objects
     * Object cube();
     * compManager.AddComponent(cube, Cube(width, height, depth));
     * compManager.AddComponent(cube, Transform(pos, rot, scale));
     * objects.push_back(new Object());
     *
     * System renderer();
     * renderer.SetSignature()
     *
     * for(auto& entity: objects)
     * {
     * renderer.AddObjSameSignature(entity);
     * }
     *
     * renderer.Setup()
     *
     *
     * while()
     * {
     * renderer.Render();
     * }
     */

    std::vector<Object> objectList{};
    Object obj;

    Transform trans;
    Renderable renderComponent(RenderType::Cube);
    obj.AddComponent(trans);
    obj.AddComponent(renderComponent);
    objectList.push_back(obj);

    // ******** Systems  ********** //
    RenderPipeline renderPipeline{};
    renderPipeline.SetSignature<Transform>();
    renderPipeline.SetSignature<Renderable>();

    for(auto& obj : objectList)
    {
        renderPipeline.AddObjSameSignature(obj);
    }

    renderPipeline.SetupPipeline();
    renderPipeline.SetupShape();

    while(!glfwWindowShouldClose(Window::window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderPipeline.Update();

        glfwSwapBuffers(Window::window);
        glfwPollEvents();
    }

    glfwTerminate();


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
