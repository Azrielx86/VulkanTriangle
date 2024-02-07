//
// Created by tsukasa on 2/3/24.
//

#ifndef GLOBAL_H
#define GLOBAL_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

struct GLFWDestroyWindow
{
    void operator()(GLFWwindow* win) const { glfwDestroyWindow(win); }
};

#endif //GLOBAL_H
