#include "Vulkan.hpp"
#include <cstring>
#include <System/Util.hpp>
#include <iostream>
#include <optional>
#include <set>
#define CHECK_VULKAN_CALLBACK(CB)                         \
    {                                                     \
        auto result = CB;                                 \
        if (result != VK_SUCCESS)                         \
        {                                                 \
            std::cout << #CB ": " << (int)result << "\n"; \
        }                                                 \
    }

namespace Engine
{
    namespace Window
    {
        namespace Wrapper
        {

            VulkanDriver::VulkanDriver() {}
            VulkanDriver::~VulkanDriver()
            {
                vkDestroySwapchainKHR(_device, _swapchain, nullptr);
                vkDestroyDevice(_device, nullptr);
                vkDestroySurfaceKHR(_instance, _surface, nullptr);
                vkDestroyInstance(_instance, nullptr);
            }

            void VulkanDriver::init(std::vector<const char *> req_ext, std::vector<const char *> deviceExtension, GLFWwindow *window, Math::vec2i WindowSIZE)
            {
                uint32_t size;
                std::vector<VkExtensionProperties> ExtProps;

                vkEnumerateInstanceExtensionProperties(0, &size, 0);
                if (size)
                {
                    ExtProps.resize(size);
                    vkEnumerateInstanceExtensionProperties(0, &size, ExtProps.data());
                }

                { // no layers
                    const char **strExtensions = glfwGetRequiredInstanceExtensions(&size);
                    for (uint32_t i = 0; i < size; ++i)
                        req_ext.push_back(strExtensions[i]);
                }

                ZeroMem(_appInfo);
                _appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
                _appInfo.pApplicationName = "FreakWorld";
                _appInfo.pEngineName = "FreakEngine";
                _appInfo.apiVersion = VK_API_VERSION_1_2;

                VkInstanceCreateInfo crInfo;
                ZeroMem(crInfo);
                crInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
                crInfo.ppEnabledExtensionNames = req_ext.data();
                crInfo.enabledExtensionCount = (uint32_t)req_ext.size();
                crInfo.enabledLayerCount = 0;
                crInfo.ppEnabledLayerNames = nullptr;

                CHECK_VULKAN_CALLBACK(vkCreateInstance(&crInfo, nullptr, &_instance));
                CHECK_VULKAN_CALLBACK(glfwCreateWindowSurface(_instance, window, nullptr, &_surface));
                // Select device
                CHECK_VULKAN_CALLBACK(vkEnumeratePhysicalDevices(_instance, &size, 0));

                if (size < 1)
                    CRITICAL_ERROR("vkEnumeratePhysicalDevices return size = 0")

                std::vector<VkPhysicalDevice> devices;
                devices.resize(size);
                CHECK_VULKAN_CALLBACK(vkEnumeratePhysicalDevices(_instance, &size, devices.data()));

                VkPhysicalDeviceProperties prop;
                std::vector<VkQueueFamilyProperties> familyProp;

                uint32_t idxFamilyQueue = 0;
                std::optional<uint32_t> idxFamilyPresent;

                for (auto &dev : devices)
                {
                    vkGetPhysicalDeviceProperties(dev, &prop);

                    if (prop.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                    {
                        _PhysicalDevice = dev;
                    }

                    vkGetPhysicalDeviceQueueFamilyProperties(dev, &size, nullptr);
                    familyProp.resize(size);
                    vkGetPhysicalDeviceQueueFamilyProperties(dev, &size, familyProp.data());

                    VkBool32 canPresent = false;
                    for (auto &fprop : familyProp)
                    {
                        CHECK_VULKAN_CALLBACK(vkGetPhysicalDeviceSurfaceSupportKHR(dev, idxFamilyQueue, _surface, &canPresent));
                        if (canPresent)
                        {
                            idxFamilyPresent = idxFamilyQueue;
                        }
                        if (fprop.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                        {
                            _PhysicalDevice = dev;
                            DEB_LOG("Selected suitable device: " << prop.deviceName << " {" << prop.deviceID << "}\n");
                            if (!idxFamilyPresent.has_value())
                            {
                                uint32_t i = 1 + idxFamilyQueue;
                                while (i < familyProp.size())
                                {
                                    CHECK_VULKAN_CALLBACK(vkGetPhysicalDeviceSurfaceSupportKHR(dev, idxFamilyQueue, _surface, &canPresent));
                                    if (canPresent)
                                    {
                                        idxFamilyPresent = i;
                                        break;
                                    }
                                    ++i;
                                }
                            }
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
                std::vector<VkDeviceQueueCreateInfo> crQueue;
                float queuePriority = 1.0f;

                {
                    std::set<uint32_t> _unique_family_queue = {idxFamilyQueue, idxFamilyPresent.value()};
                    for (uint32_t queueFamily : _unique_family_queue)
                    {
                        crQueue.emplace_back();
                        auto &inf = crQueue.back();
                        ZeroMem(inf);

                        inf.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                        inf.queueFamilyIndex = queueFamily;
                        inf.queueCount = 1;
                        inf.pQueuePriorities = &queuePriority;
                        inf.pNext = nullptr;
                    }
                }

/////////////////////////////////////////////////////////////////////////////
                VkPhysicalDeviceFeatures deviceFeatures{};
                ZeroMem(deviceFeatures);
/////////////////////////////////////////////////////////////////////////////
                VkDeviceCreateInfo devInfo;
                ZeroMem(devInfo);
                devInfo.pQueueCreateInfos = crQueue.data();
                devInfo.queueCreateInfoCount = (uint32_t)crQueue.size();
                devInfo.pEnabledFeatures = &deviceFeatures;
                devInfo.enabledExtensionCount = (uint32_t)deviceExtension.size(); // @DeviceExtension
                devInfo.ppEnabledExtensionNames = deviceExtension.data();
/////////////////////////////////////////////////////////////////////////////
                auto res = vkCreateDevice(_PhysicalDevice, &devInfo, nullptr, &_device);
                if (res != VK_SUCCESS)
                {
                    std::string s = "vkCreateDevice return ";
                    s += std::to_string(res);
                    CRITICAL_ERROR(s.c_str());
                }
/////////////////////////////////////////////////////////////////////////////
                vkGetDeviceQueue(_device, idxFamilyQueue, 0, &_renderq);
                vkGetDeviceQueue(_device, idxFamilyPresent.value(), 0, &_presentq);
                /////////////////////////////////////////////////////////////////////////////
                VkSurfaceCapabilitiesKHR capabilities;
                vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_PhysicalDevice, _surface, &capabilities);
/////////////////////////////////////////////////////////////////////////////
                VkPresentModeKHR presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
                VkExtent2D extent;
                extent.width = WindowSIZE.x;
                extent.height = WindowSIZE.y;

                vkGetPhysicalDeviceSurfacePresentModesKHR(_PhysicalDevice, _surface, &size, nullptr);
                { // Select optimal mode.
                    std::vector<VkPresentModeKHR> modes;
                    modes.resize(size);
                    vkGetPhysicalDeviceSurfacePresentModesKHR(_PhysicalDevice, _surface, &size, modes.data());
                    for (const auto &m : modes)
                    {
                        if (m == VK_PRESENT_MODE_FIFO_RELAXED_KHR)
                        {
                            presentMode = m;
                            break;
                        }
                    }
                }

                VkSwapchainCreateInfoKHR crsc; // create swapchain
                ZeroMem(crsc);
                crsc.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
                crsc.surface = _surface;
                crsc.minImageCount = (capabilities.minImageCount + 1);
                crsc.imageFormat = VK_FORMAT_R8G8B8A8_SRGB;
                crsc.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
                crsc.imageExtent = extent;
                crsc.imageArrayLayers = 1;
                crsc.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; // Пока у нас одноуровневый рендер.
                // Но это не значит, что он будет таким всегда. //@imageUsage

                uint32_t queueFamilyIndices[] = {idxFamilyPresent.value(), idxFamilyQueue};

                if(idxFamilyPresent.value() != idxFamilyQueue)
                {
                    crsc.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
                    crsc.queueFamilyIndexCount = 2;
                    crsc.pQueueFamilyIndices = queueFamilyIndices;
                } else {
                    crsc.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
                    crsc.queueFamilyIndexCount = 0;
                    crsc.pQueueFamilyIndices = nullptr;
                }
                crsc.preTransform = capabilities.currentTransform;
                crsc.compositeAlpha = VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR;
                crsc.presentMode = presentMode;
                crsc.clipped = VK_TRUE;
                crsc.oldSwapchain = VK_NULL_HANDLE;

                res = vkCreateSwapchainKHR(_device, &crsc, nullptr, &_swapchain);
                if (res != VK_SUCCESS)
                {
                    std::string s = "vkCreateSwapchainKHR return ";
                    s += std::to_string(res);
                    CRITICAL_ERROR(s.c_str());
                }

                
            }
        }
    }
}