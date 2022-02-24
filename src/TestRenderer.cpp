

#include <iostream>

#include <GLFW/glfw3.h>






int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    int width = 800;
    int height = 600;


    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create glfw window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    float time = 0.f;
    while(time < 50000.f)
    {
        time += .1f;
    }

    glfwTerminate();


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
