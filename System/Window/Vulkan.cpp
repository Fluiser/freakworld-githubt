#include "Vulkan.hpp"
#include <cstring>
#include <System/Util.hpp>

namespace Engine {
    namespace Window {
        namespace Wrapper {

            VulkanDriver::VulkanDriver() {}
            VulkanDriver::~VulkanDriver()
            {
                vkDestroySurfaceKHR(instance, surface, 0);
                vkDestroyInstance(instance, 0);
            }

            void VulkanDriver::init(std::vector<const char*> req_ext)
            {
                uint32_t size;
                std::vector<VkExtensionProperties> ExtProps;

                vkEnumerateInstanceExtensionProperties(0, &size, 0);
                if (size) {
                    ExtProps.resize(size);
                    vkEnumerateInstanceExtensionProperties(0, &size, ExtProps.data());
                }
                
                { // no layers
                    const char** strExtensions = glfwGetRequiredInstanceExtensions(&size);
                    for(uint32_t i = 0; i < size; ++i)
                        req_ext.push_back(strExtensions[i]);

                }

                ZeroMem(appInfo);
                appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
                appInfo.pApplicationName = "FreakWorld";
                appInfo.pEngineName = "FreakEngine";
                appInfo.apiVersion = VK_API_VERSION_1_2;

                VkInstanceCreateInfo crInfo;
                ZeroMem(crInfo);
                crInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
                crInfo.ppEnabledExtensionNames = req_ext.data();

                vkCreateInstance(&crInfo, VK_NULL_HANDLE, &instance);
                
                //Select device
                vkEnumeratePhysicalDevices(instance, &size, 0);
                
                if(size < 1) CRITICAL_ERROR("vkEnumeratePhysicalDevices return size = 0")

                std::vector<VkPhysicalDevice> devices;
                devices.resize(size);
                vkEnumeratePhysicalDevices(instance, &size, devices.data());

                VkPhysicalDeviceProperties prop; 
                std::vector<VkQueueFamilyProperties> familyProp;
                int idxFamilyQueue = 0;
                for(auto& dev: devices)
                {
                    vkGetPhysicalDeviceProperties(dev, &prop);

                    if(prop.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                    {
                        _PhysicalDevice = dev;
                        DEB_LOG("Selected device: " << prop.deviceName << " {" << prop.deviceID << "}\n");
                        goto _work_with_device;
                    }

                    vkGetPhysicalDeviceQueueFamilyProperties(dev, &size, nullptr);
                    familyProp.resize(size);
                    vkGetPhysicalDeviceQueueFamilyProperties(dev, &size, familyProp.data());
                    for(auto& fprop: familyProp)
                    {
                        if(fprop.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                        {
                            _PhysicalDevice = dev;
                            DEB_LOG("Selected suitable device: " << prop.deviceName << " {" << prop.deviceID << "}\n");
                            goto _work_with_device;
                        }
                        ++idxFamilyQueue;
                    }
                }
                _PhysicalDevice = devices.front();
                vkGetPhysicalDeviceProperties(_PhysicalDevice, &prop);
                DEB_LOG("Selected FIRST device: " << prop.deviceName << " {" << prop.deviceID << "}\n");

_work_with_device:
/////////////////////////////////////////////////////////////////////////////
                VkDeviceQueueCreateInfo crQueue;
                float queuePriority = 1.0f;
                ZeroMem(crQueue);
                
                crQueue.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                crQueue.queueFamilyIndex = idxFamilyQueue;
                crQueue.queueCount = 1;
                crQueue.pQueuePriorities = &queuePriority;
/////////////////////////////////////////////////////////////////////////////
                VkPhysicalDeviceFeatures deviceFeatures{};
                ZeroMem(deviceFeatures);
/////////////////////////////////////////////////////////////////////////////
                VkDeviceCreateInfo devInfo;
                ZeroMem(devInfo);
                devInfo.pQueueCreateInfos = &crQueue;
                devInfo.queueCreateInfoCount = 1;
                devInfo.pEnabledFeatures = &deviceFeatures;
                devInfo.enabledExtensionCount = 0; // @DeviceExtension
                devInfo.ppEnabledExtensionNames = nullptr;
/////////////////////////////////////////////////////////////////////////////
                
                auto res = vkCreateDevice(_PhysicalDevice, &devInfo, nullptr, &_device);
                if(res != VK_SUCCESS) {
                    std::string s = "vkCreateDevice return ";
                    s += std::to_string(res);
                    CRITICAL_ERROR(s.c_str());
                }
            }
        } 
    }
}