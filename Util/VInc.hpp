#pragma once
#ifdef WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#define VK_PROTOTYPES
#endif
#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
//header to include vulkan.
// VInc <- Vulkan Include