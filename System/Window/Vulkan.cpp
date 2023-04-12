#include "Vulkan.hpp"
#include <cstring>

namespace Engine {
    namespace Window {
        namespace Wrapper {

            VulkanDriver::VulkanDriver() {}
            VulkanDriver::~VulkanDriver() {}

            void VulkanDriver::init(std::vector<const char*> req_ext)
            {
                uint32_t size;
                std::vector<VkExtensionProperties> ExtProps;

                vkEnumerateInstanceExtensionProperties(0, &size, 0);
                if (size) {
                    ExtProps.resize(size);
                    vkEnumerateInstanceExtensionProperties(0, &size, ExtProps.data());
                }
                
                { // layers
                    const char** strExtensions = glfwGetRequiredInstanceExtensions(&size);
                    for(uint32_t i = 0; i < size; ++i)
                        req_ext.push_back(strExtensions[i]);

                    #ifdef WIN32
                    req_ext.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
                    #else
                    req_ext.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
                    #endif
                }

                memset((void*)&appInfo, 0, sizeof(appInfo));
                appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
                appInfo.pApplicationName = "FreakWorld";
                appInfo.pEngineName = "FreakEngine";
                appInfo.apiVersion = VK_API_VERSION_1_2;

                VkInstanceCreateInfo crInfo;
                memset((void*)&crInfo, 0, sizeof(crInfo));
                crInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
                crInfo.ppEnabledExtensionNames = req_ext.data();

                VkResult res = vkCreateInstance(&crInfo, VK_NULL_HANDLE, &instance);
            }

        }

        
    }
}