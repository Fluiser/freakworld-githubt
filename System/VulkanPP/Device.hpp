#pragma once
#include <Util/VInc.hpp>

namespace Engine {
    namespace Window {
        namespace Wrapper {
            class wDevice {
                VkDevice _device;
                VkPhysicalDevice _physicalDevice;

                public:

                int create(VkPhysicalDevice dev);
                int create( VkPhysicalDevice,
                            std::vector<VkDeviceQueueCreateInfo> crQueue,
                            std::vector<const char*> deviceExtension);
            };
        }
    }
}