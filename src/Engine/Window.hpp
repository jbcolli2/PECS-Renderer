//
// Created by Jeb Collins on 2/24/22.
//

#ifndef PECS_RENDERER_WINDOW_HPP
#define PECS_RENDERER_WINDOW_HPP


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace pecs
{
namespace Window
{

static GLFWwindow* window;
static float aspectRatio = 4.f/3.f;

static int InitGLFW(int width, int height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if(window == NULL)
    {
        aspectRatio = 0.f;
        std::cout << "Failed to create glfw window\n";
        glfwTerminate();
        return -1;
    }
    aspectRatio = static_cast<float>(width)/static_cast<float>(height);
    glfwMakeContextCurrent(window);
    return 0;
}


static int InitGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 0;
}


} // End Window namespace
} // End pecs namespace




#endif //PECS_RENDERER_WINDOW_HPP
