#include "Device.hpp"
#include <System/Util.hpp>
#include "Base.hpp"

namespace Engine {
    namespace Window {
        namespace Wrapper {

                int wDevice::create(VkPhysicalDevice dev)
                {

                }
                int wDevice::create( VkPhysicalDevice,
                            std::vector<VkDeviceQueueCreateInfo> crQueue,
                            std::vector<const char*> deviceExtension)
                {
                    safeWrapper<VkPhysicalDeviceFeatures> devFeatures;
                    safeWrapper<VkDeviceCreateInfo> createInfo;
                    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
                    createInfo.pQueueCreateInfos = crQueue.data();
                    createInfo.queueCreateInfoCount = static_cast<uint32_t>(crQueue.size());
                    createInfo.pEnabledFeatures = &devFeatures;
                    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtension.size()); // @DeviceExtension
                    createInfo.ppEnabledExtensionNames = deviceExtension.data();
                }
        }
    }
}