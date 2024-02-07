#pragma once
#include "config.h"

namespace vkInit{
    vk::PhysicalDevice choose_physical_device(vk::Instance& instance, bool debug){



        if(debug){
            std::cout << "Choosing physical device\n";
        }

        std::vector<vk::PhysicalDevice> availableDevices = instance.enumeratePhysicalDevices();

        if(debug){
            std::cout << "There are " << availableDevices.size() << " physical devices available on this system\n";
        }

        for(vk::PhysicalDevice device: availableDevices){
            if(debug){
                //log_device_properties(device);
            }
        }

        return nullptr;
    }
}