#pragma once
#include "config.h"

//for creation functions/definitions
namespace vkInit {
    bool supported(std::vector<const char * > &extensions,std::vector<const char *> &layers,bool debug){
        std::vector<vk::ExtensionProperties> supportedExtensions = vk::enumerateInstanceExtensionProperties();

        if (debug){
            std::cout << "Device can support the following extensions : \n";
            for (vk::ExtensionProperties supportedExtension: supportedExtensions){
                std::cout << '\t' << supportedExtension.extensionName << '\n';
            }
        }

        bool found;
        for (const char* extension:extensions){
            found = false;
            for (vk::ExtensionProperties supportedExtension: supportedExtensions) {
                if (strcmp(extension, supportedExtension.extensionName) == 0) {
                    found = true;
                    if (debug) {
                        std::cout << "Extension \"" << extension << "\" is supported!\n";
                    }
                }
            }
                if (!found){
                    if(debug){
                        std::cout << "Extension \"" << extension << "\" is not supported!\n";
                    }
                }


        }


        return true;
    }

vk::Instance make_instance(bool debug,const char * applicationName){
    if(debug){
        std::cout << "Making an Instance ....\n";
    }

    uint32_t version{ 0 };
    vkEnumerateInstanceVersion(&version);
    if (debug){
        std::cout << "System can suppot vulkan : " << VK_API_VERSION_VARIANT(version)
        << " , Major: " << VK_API_VERSION_MAJOR(version)
                << " , Minor: " << VK_API_VERSION_MINOR(version)
                << " , Path: " << VK_API_VERSION_PATCH(version)
                << std::endl;
    }

    //Drop to earlier api version
    version = VK_MAKE_API_VERSION(0,1,0,0);

    vk::ApplicationInfo applicationInfo = vk::ApplicationInfo(
            applicationName,
            version,
            "Doing it the hard way",
            version,
            version
            );

    uint32_t glfwExtensionCount = 0 ;
    const char ** glfwExtensions;
    std::vector<const char * > extensions(glfwExtensions,glfwExtensions+glfwExtensionCount);

    if (debug){
        extensions.push_back("VK_EXT_debug.utils");
    }

    if (debug){
        std::cout << "Extensions to be requested: \n";

        for (const char * extensionName: extensions){
            std::cout << "\t\'" << extensionName << "\"\n";
        }

    }

    std::vector<const char*> layers;
    if(debug){
        layers.push_back("VK_LAYER_KHRONOS_validation");
    }

    if (!supported(extensions,layers,debug)){
        return nullptr;
    }

    vk::InstanceCreateInfo createInfo = vk::InstanceCreateInfo(
            vk::InstanceCreateFlags(),
            &applicationInfo,
            static_cast<uint32_t>(layers.size()),
            layers.data(), //enabled layers
            static_cast<uint32_t>(extensions.size()),
            extensions.data() //enabled extensions
            );

    try{
        // create instance the second argument is a callback for memory allocation
        return vk::createInstance(createInfo, nullptr);
    }catch (vk::SystemError error){
        if (debug){
            std::cout << "Failed to create Instance \n";
        }
        return nullptr;
    }
}
}
