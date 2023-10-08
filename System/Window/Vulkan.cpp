#include "Vulkan.hpp"
#include <cstring>
#include <System/Util.hpp>
#include <iostream>
#include <optional>
#include <set>
#include <algorithm>
#include <chrono>

#ifdef DEBUG
#include <map>
namespace {std::map<int, const char*> TranslateFormats = {        {0, "VK_FORMAT_UNDEFINED"},        {1, "VK_FORMAT_R4G4_UNORM_PACK8"},        {2, "VK_FORMAT_R4G4B4A4_UNORM_PACK16"},        {3, "VK_FORMAT_B4G4R4A4_UNORM_PACK16"},        {4, "VK_FORMAT_R5G6B5_UNORM_PACK16"},        {5, "VK_FORMAT_B5G6R5_UNORM_PACK16"},        {6, "VK_FORMAT_R5G5B5A1_UNORM_PACK16"},        {7, "VK_FORMAT_B5G5R5A1_UNORM_PACK16"},        {8, "VK_FORMAT_A1R5G5B5_UNORM_PACK16"},        {9, "VK_FORMAT_R8_UNORM"},        {10, "VK_FORMAT_R8_SNORM"},        {11, "VK_FORMAT_R8_USCALED"},        {12, "VK_FORMAT_R8_SSCALED"},        {13, "VK_FORMAT_R8_UINT"},        {14, "VK_FORMAT_R8_SINT"},        {15, "VK_FORMAT_R8_SRGB"},        {16, "VK_FORMAT_R8G8_UNORM"},        {17, "VK_FORMAT_R8G8_SNORM"},        {18, "VK_FORMAT_R8G8_USCALED"},        {19, "VK_FORMAT_R8G8_SSCALED"},        {20, "VK_FORMAT_R8G8_UINT"},        {21, "VK_FORMAT_R8G8_SINT"},        {22, "VK_FORMAT_R8G8_SRGB"},        {23, "VK_FORMAT_R8G8B8_UNORM"},        {24, "VK_FORMAT_R8G8B8_SNORM"},        {25, "VK_FORMAT_R8G8B8_USCALED"},        {26, "VK_FORMAT_R8G8B8_SSCALED"},        {27, "VK_FORMAT_R8G8B8_UINT"},        {28, "VK_FORMAT_R8G8B8_SINT"},        {29, "VK_FORMAT_R8G8B8_SRGB"},        {30, "VK_FORMAT_B8G8R8_UNORM"},        {31, "VK_FORMAT_B8G8R8_SNORM"},        {32, "VK_FORMAT_B8G8R8_USCALED"},        {33, "VK_FORMAT_B8G8R8_SSCALED"},        {34, "VK_FORMAT_B8G8R8_UINT"},        {35, "VK_FORMAT_B8G8R8_SINT"},        {36, "VK_FORMAT_B8G8R8_SRGB"},        {37, "VK_FORMAT_R8G8B8A8_UNORM"},        {38, "VK_FORMAT_R8G8B8A8_SNORM"},        {39, "VK_FORMAT_R8G8B8A8_USCALED"},        {40, "VK_FORMAT_R8G8B8A8_SSCALED"},        {41, "VK_FORMAT_R8G8B8A8_UINT"},        {42, "VK_FORMAT_R8G8B8A8_SINT"},        {43, "VK_FORMAT_R8G8B8A8_SRGB"},        {44, "VK_FORMAT_B8G8R8A8_UNORM"},        {45, "VK_FORMAT_B8G8R8A8_SNORM"},        {46, "VK_FORMAT_B8G8R8A8_USCALED"},        {47, "VK_FORMAT_B8G8R8A8_SSCALED"},        {48, "VK_FORMAT_B8G8R8A8_UINT"},        {49, "VK_FORMAT_B8G8R8A8_SINT"},        {50, "VK_FORMAT_B8G8R8A8_SRGB"},        {51, "VK_FORMAT_A8B8G8R8_UNORM_PACK32"},        {52, "VK_FORMAT_A8B8G8R8_SNORM_PACK32"},        {53, "VK_FORMAT_A8B8G8R8_USCALED_PACK32"},        {54, "VK_FORMAT_A8B8G8R8_SSCALED_PACK32"},        {55, "VK_FORMAT_A8B8G8R8_UINT_PACK32"},        {56, "VK_FORMAT_A8B8G8R8_SINT_PACK32"},        {57, "VK_FORMAT_A8B8G8R8_SRGB_PACK32"},        {58, "VK_FORMAT_A2R10G10B10_UNORM_PACK32"},        {59, "VK_FORMAT_A2R10G10B10_SNORM_PACK32"},        {60, "VK_FORMAT_A2R10G10B10_USCALED_PACK32"},        {61, "VK_FORMAT_A2R10G10B10_SSCALED_PACK32"},        {62, "VK_FORMAT_A2R10G10B10_UINT_PACK32"},        {63, "VK_FORMAT_A2R10G10B10_SINT_PACK32"},        {64, "VK_FORMAT_A2B10G10R10_UNORM_PACK32"},        {65, "VK_FORMAT_A2B10G10R10_SNORM_PACK32"},        {66, "VK_FORMAT_A2B10G10R10_USCALED_PACK32"},        {67, "VK_FORMAT_A2B10G10R10_SSCALED_PACK32"},        {68, "VK_FORMAT_A2B10G10R10_UINT_PACK32"},        {69, "VK_FORMAT_A2B10G10R10_SINT_PACK32"},        {70, "VK_FORMAT_R16_UNORM"},        {71, "VK_FORMAT_R16_SNORM"},        {72, "VK_FORMAT_R16_USCALED"},        {73, "VK_FORMAT_R16_SSCALED"},        {74, "VK_FORMAT_R16_UINT"},        {75, "VK_FORMAT_R16_SINT"},        {76, "VK_FORMAT_R16_SFLOAT"},        {77, "VK_FORMAT_R16G16_UNORM"},        {78, "VK_FORMAT_R16G16_SNORM"},        {79, "VK_FORMAT_R16G16_USCALED"},        {80, "VK_FORMAT_R16G16_SSCALED"},        {81, "VK_FORMAT_R16G16_UINT"},        {82, "VK_FORMAT_R16G16_SINT"},        {83, "VK_FORMAT_R16G16_SFLOAT"},        {84, "VK_FORMAT_R16G16B16_UNORM"},        {85, "VK_FORMAT_R16G16B16_SNORM"},        {86, "VK_FORMAT_R16G16B16_USCALED"},        {87, "VK_FORMAT_R16G16B16_SSCALED"},        {88, "VK_FORMAT_R16G16B16_UINT"},        {89, "VK_FORMAT_R16G16B16_SINT"},        {90, "VK_FORMAT_R16G16B16_SFLOAT"},        {91, "VK_FORMAT_R16G16B16A16_UNORM"},        {92, "VK_FORMAT_R16G16B16A16_SNORM"},        {93, "VK_FORMAT_R16G16B16A16_USCALED"},        {94, "VK_FORMAT_R16G16B16A16_SSCALED"},        {95, "VK_FORMAT_R16G16B16A16_UINT"},        {96, "VK_FORMAT_R16G16B16A16_SINT"},        {97, "VK_FORMAT_R16G16B16A16_SFLOAT"},        {98, "VK_FORMAT_R32_UINT"},        {99, "VK_FORMAT_R32_SINT"},        {100, "VK_FORMAT_R32_SFLOAT"},        {101, "VK_FORMAT_R32G32_UINT"},        {102, "VK_FORMAT_R32G32_SINT"},        {103, "VK_FORMAT_R32G32_SFLOAT"},        {104, "VK_FORMAT_R32G32B32_UINT"},        {105, "VK_FORMAT_R32G32B32_SINT"},        {106, "VK_FORMAT_R32G32B32_SFLOAT"},        {107, "VK_FORMAT_R32G32B32A32_UINT"},        {108, "VK_FORMAT_R32G32B32A32_SINT"},        {109, "VK_FORMAT_R32G32B32A32_SFLOAT"},        {110, "VK_FORMAT_R64_UINT"},        {111, "VK_FORMAT_R64_SINT"},        {112, "VK_FORMAT_R64_SFLOAT"},        {113, "VK_FORMAT_R64G64_UINT"},        {114, "VK_FORMAT_R64G64_SINT"},        {115, "VK_FORMAT_R64G64_SFLOAT"},        {116, "VK_FORMAT_R64G64B64_UINT"},        {117, "VK_FORMAT_R64G64B64_SINT"},        {118, "VK_FORMAT_R64G64B64_SFLOAT"},        {119, "VK_FORMAT_R64G64B64A64_UINT"},        {120, "VK_FORMAT_R64G64B64A64_SINT"},        {121, "VK_FORMAT_R64G64B64A64_SFLOAT"},        {122, "VK_FORMAT_B10G11R11_UFLOAT_PACK32"},        {123, "VK_FORMAT_E5B9G9R9_UFLOAT_PACK32"},        {124, "VK_FORMAT_D16_UNORM"},        {125, "VK_FORMAT_X8_D24_UNORM_PACK32"},        {126, "VK_FORMAT_D32_SFLOAT"},        {127, "VK_FORMAT_S8_UINT"},        {128, "VK_FORMAT_D16_UNORM_S8_UINT"},        {129, "VK_FORMAT_D24_UNORM_S8_UINT"},        {130, "VK_FORMAT_D32_SFLOAT_S8_UINT"},        {131, "VK_FORMAT_BC1_RGB_UNORM_BLOCK"},        {132, "VK_FORMAT_BC1_RGB_SRGB_BLOCK"},        {133, "VK_FORMAT_BC1_RGBA_UNORM_BLOCK"},        {134, "VK_FORMAT_BC1_RGBA_SRGB_BLOCK"},        {135, "VK_FORMAT_BC2_UNORM_BLOCK"},        {136, "VK_FORMAT_BC2_SRGB_BLOCK"},        {137, "VK_FORMAT_BC3_UNORM_BLOCK"},        {138, "VK_FORMAT_BC3_SRGB_BLOCK"},        {139, "VK_FORMAT_BC4_UNORM_BLOCK"},        {140, "VK_FORMAT_BC4_SNORM_BLOCK"},        {141, "VK_FORMAT_BC5_UNORM_BLOCK"},        {142, "VK_FORMAT_BC5_SNORM_BLOCK"},        {143, "VK_FORMAT_BC6H_UFLOAT_BLOCK"},        {144, "VK_FORMAT_BC6H_SFLOAT_BLOCK"},        {145, "VK_FORMAT_BC7_UNORM_BLOCK"},        {146, "VK_FORMAT_BC7_SRGB_BLOCK"},        {147, "VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK"},        {148, "VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK"},        {149, "VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK"},        {150, "VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK"},        {151, "VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK"},        {152, "VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK"},        {153, "VK_FORMAT_EAC_R11_UNORM_BLOCK"},        {154, "VK_FORMAT_EAC_R11_SNORM_BLOCK"},        {155, "VK_FORMAT_EAC_R11G11_UNORM_BLOCK"},        {156, "VK_FORMAT_EAC_R11G11_SNORM_BLOCK"},        {157, "VK_FORMAT_ASTC_4x4_UNORM_BLOCK"},        {158, "VK_FORMAT_ASTC_4x4_SRGB_BLOCK"},        {159, "VK_FORMAT_ASTC_5x4_UNORM_BLOCK"},        {160, "VK_FORMAT_ASTC_5x4_SRGB_BLOCK"},        {161, "VK_FORMAT_ASTC_5x5_UNORM_BLOCK"},        {162, "VK_FORMAT_ASTC_5x5_SRGB_BLOCK"},        {163, "VK_FORMAT_ASTC_6x5_UNORM_BLOCK"},        {164, "VK_FORMAT_ASTC_6x5_SRGB_BLOCK"},        {165, "VK_FORMAT_ASTC_6x6_UNORM_BLOCK"},        {166, "VK_FORMAT_ASTC_6x6_SRGB_BLOCK"},        {167, "VK_FORMAT_ASTC_8x5_UNORM_BLOCK"},        {168, "VK_FORMAT_ASTC_8x5_SRGB_BLOCK"},        {169, "VK_FORMAT_ASTC_8x6_UNORM_BLOCK"},        {170, "VK_FORMAT_ASTC_8x6_SRGB_BLOCK"},        {171, "VK_FORMAT_ASTC_8x8_UNORM_BLOCK"},        {172, "VK_FORMAT_ASTC_8x8_SRGB_BLOCK"},        {173, "VK_FORMAT_ASTC_10x5_UNORM_BLOCK"},        {174, "VK_FORMAT_ASTC_10x5_SRGB_BLOCK"},        {175, "VK_FORMAT_ASTC_10x6_UNORM_BLOCK"},        {176, "VK_FORMAT_ASTC_10x6_SRGB_BLOCK"},        {177, "VK_FORMAT_ASTC_10x8_UNORM_BLOCK"},        {178, "VK_FORMAT_ASTC_10x8_SRGB_BLOCK"},        {179, "VK_FORMAT_ASTC_10x10_UNORM_BLOCK"},        {180, "VK_FORMAT_ASTC_10x10_SRGB_BLOCK"},        {181, "VK_FORMAT_ASTC_12x10_UNORM_BLOCK"},        {182, "VK_FORMAT_ASTC_12x10_SRGB_BLOCK"},        {183, "VK_FORMAT_ASTC_12x12_UNORM_BLOCK"},        {184, "VK_FORMAT_ASTC_12x12_SRGB_BLOCK"},        {1000156000, "VK_FORMAT_G8B8G8R8_422_UNORM"},        {1000156001, "VK_FORMAT_B8G8R8G8_422_UNORM"},        {1000156002, "VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM"},        {1000156003, "VK_FORMAT_G8_B8R8_2PLANE_420_UNORM"},        {1000156004, "VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM"},        {1000156005, "VK_FORMAT_G8_B8R8_2PLANE_422_UNORM"},        {1000156006, "VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM"},        {1000156007, "VK_FORMAT_R10X6_UNORM_PACK16"},        {1000156008, "VK_FORMAT_R10X6G10X6_UNORM_2PACK16"},        {1000156009, "VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16"},        {1000156010, "VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16"},        {1000156011, "VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16"},        {1000156012, "VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16"},        {1000156013, "VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16"},        {1000156014, "VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16"},        {1000156015, "VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16"},        {1000156016, "VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16"},        {1000156017, "VK_FORMAT_R12X4_UNORM_PACK16"},        {1000156018, "VK_FORMAT_R12X4G12X4_UNORM_2PACK16"},        {1000156019, "VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16"},        {1000156020, "VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16"},        {1000156021, "VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16"},        {1000156022, "VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16"},        {1000156023, "VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16"},        {1000156024, "VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16"},        {1000156025, "VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16"},        {1000156026, "VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16"},        {1000156027, "VK_FORMAT_G16B16G16R16_422_UNORM"},        {1000156028, "VK_FORMAT_B16G16R16G16_422_UNORM"},        {1000156029, "VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM"},        {1000156030, "VK_FORMAT_G16_B16R16_2PLANE_420_UNORM"},        {1000156031, "VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM"},        {1000156032, "VK_FORMAT_G16_B16R16_2PLANE_422_UNORM"},        {1000156033, "VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM"},        {1000054000, "VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG"},        {1000054001, "VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG"},        {1000054002, "VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG"},        {1000054003, "VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG"},        {1000054004, "VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG"},        {1000054005, "VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG"},        {1000054006, "VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG"},        {1000054007, "VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG"},        {1000066000, "VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK_EXT"},        {1000066001, "VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK_EXT"},        {1000066002, "VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK_EXT"},        {1000066003, "VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK_EXT"},        {1000066004, "VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK_EXT"},        {1000066005, "VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK_EXT"},        {1000066006, "VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK_EXT"},        {1000066007, "VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK_EXT"},        {1000066008, "VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK_EXT"},        {1000066009, "VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK_EXT"},        {1000066010, "VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK_EXT"},        {1000066011, "VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK_EXT"},        {1000066012, "VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK_EXT"},        {1000066013, "VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK_EXT"},        {1000330000, "VK_FORMAT_G8_B8R8_2PLANE_444_UNORM_EXT"},        {1000330001, "VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16_EXT"},        {1000330002, "VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16_EXT"},        {1000330003, "VK_FORMAT_G16_B16R16_2PLANE_444_UNORM_EXT"},        {1000340000, "VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT"},        {1000340001, "VK_FORMAT_A4B4G4R4_UNORM_PACK16_EXT"},        {VK_FORMAT_G8B8G8R8_422_UNORM, "VK_FORMAT_G8B8G8R8_422_UNORM_KHR"},        {VK_FORMAT_B8G8R8G8_422_UNORM, "VK_FORMAT_B8G8R8G8_422_UNORM_KHR"},        {VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM, "VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM_KHR"},        {VK_FORMAT_G8_B8R8_2PLANE_420_UNORM, "VK_FORMAT_G8_B8R8_2PLANE_420_UNORM_KHR"},        {VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM, "VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM_KHR"},        {VK_FORMAT_G8_B8R8_2PLANE_422_UNORM, "VK_FORMAT_G8_B8R8_2PLANE_422_UNORM_KHR"},        {VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM, "VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM_KHR"},        {VK_FORMAT_R10X6_UNORM_PACK16, "VK_FORMAT_R10X6_UNORM_PACK16_KHR"},        {VK_FORMAT_R10X6G10X6_UNORM_2PACK16, "VK_FORMAT_R10X6G10X6_UNORM_2PACK16_KHR"},        {VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16, "VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16_KHR"},        {VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16, "VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16_KHR"},        {VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16, "VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16_KHR"},        {VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16, "VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16_KHR"},        {VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16, "VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16_KHR"},        {VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16, "VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16_KHR"},        {VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16, "VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16_KHR"},        {VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16, "VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16_KHR"},        {VK_FORMAT_R12X4_UNORM_PACK16, "VK_FORMAT_R12X4_UNORM_PACK16_KHR"},        {VK_FORMAT_R12X4G12X4_UNORM_2PACK16, "VK_FORMAT_R12X4G12X4_UNORM_2PACK16_KHR"},        {VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16, "VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16_KHR"},        {VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16, "VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16_KHR"},        {VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16, "VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16_KHR"},        {VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16, "VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16_KHR"},        {VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16, "VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16_KHR"},        {VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16, "VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16_KHR"},        {VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16, "VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16_KHR"},        {VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16, "VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16_KHR"},        {VK_FORMAT_G16B16G16R16_422_UNORM, "VK_FORMAT_G16B16G16R16_422_UNORM_KHR"},        {VK_FORMAT_B16G16R16G16_422_UNORM, "VK_FORMAT_B16G16R16G16_422_UNORM_KHR"},        {VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM, "VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM_KHR"},        {VK_FORMAT_G16_B16R16_2PLANE_420_UNORM, "VK_FORMAT_G16_B16R16_2PLANE_420_UNORM_KHR"},        {VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM, "VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM_KHR"},        {VK_FORMAT_G16_B16R16_2PLANE_422_UNORM, "VK_FORMAT_G16_B16R16_2PLANE_422_UNORM_KHR"},        {VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM, "VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM_KHR"}    };}
#endif

namespace Engine
{
    namespace Window
    {
        namespace Wrapper
        {

            VulkanDriver::VulkanDriver() {}
            VulkanDriver::~VulkanDriver()
            {
                vkDestroyCommandPool(_device, _renderPool, nullptr);
                vkDestroyCommandPool(_device, _presentPool, nullptr);
                for(auto& img: _swapchain_images_views)
                {
                    vkDestroyImageView(_device, img, nullptr);
                }
                vkDestroySwapchainKHR(_device, _swapchain, nullptr);
                vkDestroyDevice(_device, nullptr);
                vkDestroySurfaceKHR(_instance, _surface, nullptr);
                vkDestroyInstance(_instance, nullptr);
            }

            void VulkanDriver::init(std::vector<const char *> req_ext, std::vector<const char *> deviceExtension, GLFWwindow *window)
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
                _appInfo.apiVersion = VK_API_VERSION_1_3;

                VkInstanceCreateInfo crInfo;
                ZeroMem(crInfo);
                crInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
                crInfo.ppEnabledExtensionNames = req_ext.data();
                crInfo.enabledExtensionCount = (uint32_t)req_ext.size();
                #ifdef DEBUG
                    static std::vector<const char*> validationLayers{"VK_LAYER_KHRONOS_validation"};
                    crInfo.enabledLayerCount = (uint32_t)validationLayers.size();
                    crInfo.ppEnabledLayerNames = validationLayers.data();
                #else 
                crInfo.enabledLayerCount = 0;
                crInfo.ppEnabledLayerNames = nullptr;
                #endif

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

                uint32_t idxFamilyRender = 0;
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
                        CHECK_VULKAN_CALLBACK(vkGetPhysicalDeviceSurfaceSupportKHR(dev, idxFamilyRender, _surface, &canPresent));
                        if (canPresent)
                        {
                            idxFamilyPresent = idxFamilyRender;
                        }
                        if (fprop.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                        {
                            _PhysicalDevice = dev;
                            DEB_LOG("Selected suitable device: " << prop.deviceName << " {" << prop.deviceID << "}\n");
                            if (!idxFamilyPresent.has_value())
                            {
                                uint32_t i = 1 + idxFamilyRender;
                                while (i < familyProp.size())
                                {
                                    CHECK_VULKAN_CALLBACK(vkGetPhysicalDeviceSurfaceSupportKHR(dev, idxFamilyRender, _surface, &canPresent));
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

                        ++idxFamilyRender;
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
                    std::set<uint32_t> _unique_family_queue = {idxFamilyRender, idxFamilyPresent.value()};
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
                devInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
                devInfo.pQueueCreateInfos = crQueue.data();
                devInfo.queueCreateInfoCount = (uint32_t)crQueue.size();
                devInfo.pEnabledFeatures = &deviceFeatures;
                devInfo.enabledExtensionCount = (uint32_t)deviceExtension.size(); // @DeviceExtension
                devInfo.ppEnabledExtensionNames = deviceExtension.data();
                /////////////////////////////////////////////////////////////////////////////
                CRITICAL_VULKAN_CALLBACK(vkCreateDevice(_PhysicalDevice, &devInfo, nullptr, &_device))
                /////////////////////////////////////////////////////////////////////////////
                vkGetDeviceQueue(_device, idxFamilyRender, 0, &_renderq);
                vkGetDeviceQueue(_device, idxFamilyPresent.value(), 0, &_presentq);
                /////////////////////////////////////////////////////////////////////////////
                /////////////////////////////////////////////////////////////////////////////

                _idxFamilyPresent = idxFamilyPresent.value();
                _idxFamilyRender = idxFamilyRender;
            }

            void VulkanDriver::initFrameBuffer(GLFWwindow* window)
            {
                VkPresentModeKHR presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;

                uint32_t size;

                VkSurfaceCapabilitiesKHR capabilities;
                vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_PhysicalDevice, _surface, &capabilities);

                vkGetPhysicalDeviceSurfacePresentModesKHR(_PhysicalDevice, _surface, &size, nullptr);
                { // Select optimal mode.
                    std::vector<VkPresentModeKHR> modes;
                    modes.resize(size);
                    //VK_PRESENT_MODE_IMMEDIATE_KHR - NO vsync
                    vkGetPhysicalDeviceSurfacePresentModesKHR(_PhysicalDevice, _surface, &size, modes.data());
                    for (const auto &m : modes)
                    {
                        if (m == VK_PRESENT_MODE_FIFO_RELAXED_KHR)
                        {
                            presentMode = VK_PRESENT_MODE_FIFO_RELAXED_KHR;
                            break;
                        }
                    }
                }
                presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;

                VkSwapchainCreateInfoKHR crsc; // create swapchain
                ZeroMem(crsc);
                crsc.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
                crsc.surface = _surface;
                crsc.minImageCount = (capabilities.minImageCount + 1);

                {
                    uint32_t formatCount;
                    vkGetPhysicalDeviceSurfaceFormatsKHR(_PhysicalDevice, _surface, &formatCount, nullptr);
                    if(formatCount > 1) 
                    {
                        std::vector<VkSurfaceFormatKHR> formats;
                        formats.resize(formatCount);
                        vkGetPhysicalDeviceSurfaceFormatsKHR(_PhysicalDevice, _surface, &formatCount, formats.data());
                        
                        _format = formats[0].format;
                        for(auto& form: formats)
                        {
                            if(form.format == VK_FORMAT_R8G8B8A8_SRGB && form.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
                            {
                                _format = form.format;
                                __BigEndian = true;
                                break;
                            } else if(form.format == VK_FORMAT_B8G8R8A8_SRGB && form.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
                            {
                                __BigEndian = false;
                                _format = form.format;
                                break;
                            }
                        }
                        DEB_LOG("Available formats: \n");
                        for(const auto& f: formats)
                        {
                            DEB_LOG("\t" << TranslateFormats[_format] << ": " << f.colorSpace << "\n");
                            // vkGetPhysicalDeviceImageFormatProperties(_PhysicalDevice,
                            //                                         f.format,
                            //                                         VK_IMAGE_TYPE_2D,
                            //                                         VK_IMAGE_TILING_OPTIMAL,
                            //                                         VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
                            //                                         0, nullptr);
                        }
                        DEB_LOG("Used format: " << TranslateFormats[_format] << "\n");
                    }
                    else 
                    {
                        CRITICAL_ERROR("Available formats is null.");
                    }
                }
                
                if(capabilities.currentExtent.width != UINT32_MAX) {
                    _extent = capabilities.currentExtent;
                } else {
                    int w, h;
                    glfwGetFramebufferSize(window, &w, &h);
                    _extent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, (uint32_t)w));
                    _extent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, (uint32_t)h));
                }


                crsc.imageFormat = _format;
                crsc.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
                crsc.imageExtent = _extent;
                crsc.imageArrayLayers = 1; ////////////////////////////// <.
                crsc.presentMode = presentMode;//                          |
                crsc.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT; // Пока у нас однослойный рендер.
                // Но это не значит, что он будет таким всегда. //@imageUsage //@option
                // press F intel gpu



                DEB_LOG(    "VkSwapchainCreateInfo.minImageCount: " <<
                            crsc.minImageCount <<
                            "\nVkSwapchainCreateInfo.imageUsage: " <<
                            crsc.imageUsage <<
                            "\ncrsc.presentMode: " <<
                            (presentMode == VK_PRESENT_MODE_IMMEDIATE_KHR ? "VK_PRESENT_MODE_IMMEDIATE_KHR\n" : "VK_PRESENT_MODE_FIFO_RELAXED_KHR\n"));

                uint32_t queueFamilyIndices[] = {_idxFamilyPresent, _idxFamilyRender};

                if (_idxFamilyPresent != _idxFamilyRender)
                {
                    crsc.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
                    crsc.queueFamilyIndexCount = 2;
                    crsc.pQueueFamilyIndices = queueFamilyIndices;
                }
                else
                {
                    crsc.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
                    crsc.queueFamilyIndexCount = 0;
                    crsc.pQueueFamilyIndices = nullptr;
                }
                crsc.preTransform = capabilities.currentTransform;

                crsc.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;//VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR;
                crsc.clipped = VK_TRUE;
                crsc.oldSwapchain = VK_NULL_HANDLE;
                

                CRITICAL_VULKAN_CALLBACK(vkCreateSwapchainKHR(_device, &crsc, nullptr, &_swapchain))
                ////////////////////////////////-- Init images in vector --/////////////////////////////////////////////
                vkGetSwapchainImagesKHR(_device, _swapchain, &size, nullptr);
                _swapchain_images.resize(size);
                _swapchain_images_views.resize(size);
                vkGetSwapchainImagesKHR(_device, _swapchain, &size, _swapchain_images.data());

                for(size_t i = 0; i < _swapchain_images.size(); ++i)
                {
                    VkImageViewCreateInfo crinfo;
                    ZeroMem(crinfo);
                    crinfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
                    crinfo.image = _swapchain_images[i];
                    crinfo.viewType = VK_IMAGE_VIEW_TYPE_2D; //@viewtype //@option
                    crinfo.format = _format;
                    
                    crinfo.components.a = VK_COMPONENT_SWIZZLE_A;
                    crinfo.components.r = VK_COMPONENT_SWIZZLE_R;
                    crinfo.components.g = VK_COMPONENT_SWIZZLE_G;
                    crinfo.components.b = VK_COMPONENT_SWIZZLE_B;

                    crinfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                    crinfo.subresourceRange.baseMipLevel = 0;
                    crinfo.subresourceRange.levelCount = 1;
                    crinfo.subresourceRange.baseArrayLayer = 0;
                    crinfo.subresourceRange.layerCount = 1;

                    CHECK_VULKAN_CALLBACK(vkCreateImageView(_device, &crinfo, nullptr, &_swapchain_images_views[i]));
                }
                
                _pipelines.emplace_back();
                
                auto& basePipeline = _pipelines.back();
                basePipeline.initPipeline(_device, _extent, _format);
                basePipeline.initMemType(_PhysicalDevice);
                basePipeline.initFramebuffers(_swapchain_images_views, _extent);

                VkCommandPoolCreateInfo renderInfo;
                VkCommandPoolCreateInfo presentInfo;
                ZeroMem(renderInfo); ZeroMem(presentInfo);

                presentInfo.sType = renderInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
                
                presentInfo.flags = 0;
                renderInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;

                // presentInfo.queueFamilyIndex = _idxFamilyPresent;
                renderInfo.queueFamilyIndex = _idxFamilyRender;

                CRITICAL_VULKAN_CALLBACK(vkCreateCommandPool(_device, &renderInfo, nullptr, &_renderPool));
                // CRITICAL_VULKAN_CALLBACK(vkCreateCommandPool(_device, &presentInfo, nullptr, &_presentPool));
                
                basePipeline.initCommandBuffers(_renderPool);
            }

            uint32_t VulkanDriver::getIndexImage(Engine::System::Graphics::Pipeline* pipeline) const
            {
                auto& pip = (pipeline == nullptr ? _pipelines.front() : *pipeline); 
                uint32_t idx;
                vkAcquireNextImageKHR(_device, _swapchain, UINT64_MAX, pip._imageAvailable, VK_NULL_HANDLE, &idx);
                return idx;
            }

            void VulkanDriver::qSumbit(Engine::System::Graphics::Pipeline* pipeline)
            {
                auto& pip = (pipeline == nullptr ? _pipelines.front() : *pipeline);

                VkSubmitInfo info;
                ZeroMem(info);

                info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
                static VkPipelineStageFlags flags[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT}; // относительно каждого семафора
                info.waitSemaphoreCount = 1;
                info.pWaitSemaphores = &pip._imageAvailable;
                info.pWaitDstStageMask = flags;
                info.commandBufferCount = 1;
                info.pCommandBuffers = &pip._commandBuffers[_indexImage = this->getIndexImage(&pip)];
                info.signalSemaphoreCount = 1;
                info.pSignalSemaphores = &pip._renderFinished;

                CHECK_VULKAN_CALLBACK(vkQueueSubmit(_renderq, 1, &info, VK_NULL_HANDLE));
            }

            void VulkanDriver::display(Engine::System::Graphics::Pipeline* pipeline)
            {
                auto& pip = (pipeline == nullptr ? _pipelines.front() : *pipeline);

                VkPresentInfoKHR presentInfo;
                ZeroMem(presentInfo);

                presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
                presentInfo.waitSemaphoreCount = 1;
                presentInfo.pWaitSemaphores = &pip._renderFinished;
                presentInfo.swapchainCount = 1;
                presentInfo.pSwapchains = &_swapchain;
                presentInfo.pImageIndices = &_indexImage;
                presentInfo.pResults = nullptr;

                CRITICAL_VULKAN_CALLBACK(vkQueuePresentKHR(_presentq, &presentInfo));
                CHECK_VULKAN_CALLBACK(vkQueueWaitIdle(_presentq));
                // CHECK_VULKAN_CALLBACK(vkDeviceWaitIdle(_device));
            }

            void VulkanDriver::addVertex(Engine::System::Graphics::Pipeline::Vertex vertex, Engine::System::Graphics::Pipeline* pipeline)
            {
                auto& p = (pipeline ? *pipeline : _pipelines.front());
                p.addVertex(vertex);
            }

            void VulkanDriver::clearVertex(Engine::System::Graphics::Pipeline* pipeline)
            {
                auto& p = (pipeline ? *pipeline : _pipelines.front());
                p.clearVertex();
            }

            void VulkanDriver::draw(Engine::System::Graphics::Pipeline* pipeline)
            {
                auto& p = (pipeline ? *pipeline : _pipelines.front());
                p.beginCommands();   
                p.draw();
                p.endCommands();
            }
        }
    }
}
