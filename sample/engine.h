#pragma once
#include <GLFW/glfw3.h>
#include "config.h"

class Engine {

public:

    Engine();

    ~Engine();

private:

    //whether to print debug messages in functions
    bool debugMode = true;

    //glfw window parameters
    int width{ 640 };
    int height{ 480 };
    GLFWwindow* window{ nullptr };

    // instances
    vk::Instance instance{nullptr};    //vulkan instance
    vk::DebugUtilsMessengerEXT debugMessenger {nullptr };  //debug callback
    vk::DispatchLoaderDynamic dldi; //dynamic instance dispatcher


    //device related variables
    vk::PhysicalDevice physicalDevice{nullptr };

    //glfw setup
    void build_glfw_window();

    // vulkan instance setup
    void make_instance();

    void make_device();
};