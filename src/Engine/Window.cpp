//
// Created by Jeb Collins on 4/1/22.
//

#include "Window.hpp"



using namespace pecs;


int WindowManager::InitGLFW(int width, int height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    m_window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (m_window == NULL)
    {
        m_aspectRatio = 0.f;
        std::cout << "Failed to create glfw window\n";
        glfwTerminate();
        return -1;
    }
    m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    glfwMakeContextCurrent(m_window);

    glfwSetKeyCallback(m_window, ::pecs::keyCallback);
    glfwSetCursorPosCallback(m_window, ::pecs::cursorPositionCallback);
    glfwSetMouseButtonCallback(m_window, ::pecs::mouseButtonCallback);


    return 0;
}




