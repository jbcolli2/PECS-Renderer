

#include "Engine/Window.hpp"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>





using namespace pecs;

int main()
{
    Window::InitGLFW(800, 600);
    Window::InitGlad();


    while(!glfwWindowShouldClose(Window::window))
    {
        glClearColor(.8f, 0.f, 6.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(Window::window);
        glfwPollEvents();
    }

    glfwTerminate();


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
