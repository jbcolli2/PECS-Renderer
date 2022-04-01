//
// Created by Jeb Collins on 2/24/22.
//

#ifndef PECS_RENDERER_WINDOW_HPP
#define PECS_RENDERER_WINDOW_HPP

#include "Engine/Input.hpp"


#include <GLFW/glfw3.h>

#include <iostream>

namespace pecs
{

class WindowManager
{
private:
    GLFWwindow* m_window{nullptr};
    float m_aspectRatio{4.f/3.f};

public:
    static WindowManager& GetInstance()
    {
        static WindowManager instance{};
        return instance;
    }


    // ************* Getters/Setters  **************************** //

    // Return the window pointer
    GLFWwindow* GetWindow() {return m_window;};
    // Set the aspect ratio
    float GetAspectRatio() {return m_aspectRatio;};


    // ************* Initialization methods  ****************** //
    int InitGLFW(int width, int height);
};







} // End pecs namespace




#endif //PECS_RENDERER_WINDOW_HPP
