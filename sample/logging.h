#pragma once
#include "config.h"

namespace vkInit {
    /**
        Logging callback function.

        \param messageSeverity describes the severity level of the message
        \param messageType describes the type of the message
        \param pCallbackData standard data associated with the message
        \param pUserData custom extra data which can be associated with the message
        \returns whether to end program execution
    */
    VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
    );

    /**
        Make a debug messenger

        \param instance The Vulkan instance which will be debugged.
        \param dldi dynamically loads instance based dispatch functions
        \returns the created messenger
    */
    vk::DebugUtilsMessengerEXT make_debug_messenger(vk::Instance& instance, vk::DispatchLoaderDynamic& dldi);
}