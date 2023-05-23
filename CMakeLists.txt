set(CMAKE_TOOLCHAIN_FILE "F:/github/vcpkg/scripts/buildsystems/vcpkg.cmake")
cmake_minimum_required(VERSION 3.0.0)
project(freakWorld)
set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 /std:c++20")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DDEBUG=TRUE /std:c++20")

#variables
set(INCLUDE_DIR "D:/soft/VisualStudio/VC/Tools/MSVC/14.29.30133/include")

#libs
set(Boost_INCLUDE_DIR "D:/soft/VisualStudio/VC/Tools/MSVC/14.29.30133/include")
set(Boost_LIBRARIES_CMAKE ${Boost_INCLUDE_DIR}/stage/lib)
find_package(Boost 1.80.0 REQUIRED)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
link_directories(${Boost_LIBRARIES_CMAKE})

set(SFML_DIR ${INCLUDE_DIR}/SFML/lib/cmake/SFML)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5.1 REQUIRED graphics audio window system)

add_compile_definitions(NOMINMAX=TRUE)

if (WIN32)
	add_compile_definitions(WIN32=TRUE)
	set(OTHER_LIB "")
endif(WIN32)

if (UNIX)
	add_compile_definitions(LINUX=TRUE)
	set(OTHER_LIB "")
endif(UNIX)

include_directories(${INCLUDE_DIR} ./)

set(DiscordRPC "System/DiscordRPC")

if(WIN32)
	set(DISCORD_LNK System/DiscordRPC/achievement_manager.cpp System/DiscordRPC/achievement_manager.h System/DiscordRPC/activity_manager.cpp System/DiscordRPC/activity_manager.h System/DiscordRPC/application_manager.cpp System/DiscordRPC/application_manager.h System/DiscordRPC/core.cpp System/DiscordRPC/core.h System/DiscordRPC/image_manager.cpp System/DiscordRPC/image_manager.h System/DiscordRPC/lobby_manager.cpp System/DiscordRPC/lobby_manager.h System/DiscordRPC/network_manager.cpp System/DiscordRPC/network_manager.h System/DiscordRPC/overlay_manager.cpp System/DiscordRPC/overlay_manager.h System/DiscordRPC/relationship_manager.cpp System/DiscordRPC/relationship_manager.h System/DiscordRPC/storage_manager.cpp System/DiscordRPC/storage_manager.h System/DiscordRPC/store_manager.cpp System/DiscordRPC/store_manager.h System/DiscordRPC/types.cpp System/DiscordRPC/types.h System/DiscordRPC/user_manager.cpp System/DiscordRPC/user_manager.h System/DiscordRPC/voice_manager.cpp System/DiscordRPC/voice_manager.h)
	set(DISCORD_DLL ${CMAKE_CURRENT_SOURCE_DIR}/System/DiscordRPC/lib/discord_game_sdk.dll.lib)
else()

	set(DISCORD_LNK "")
	set(DISCORD_DLL "")

endif()

message(LNK: ${DISCORD_LNK}\n DLL LIB: ${DISCORD_DLL})

add_executable(freakWorld
		System/Window/Vulkan.hpp						System/Window/Vulkan.cpp
		System/Window/Window.hpp						System/Window/Window.cpp 
		System/IODevices/Event.hpp						System/IODevices/Event.cpp 

		System/Graphics/Shader.hpp						System/Graphics/Shader.cpp
		System/Graphics/GraphicsPipeline.hpp			System/Graphics/GraphicsPipeline.cpp

		main.cpp
)

find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
target_link_libraries(freakWorld sfml-graphics sfml-audio sfml-window sfml-system ${Boost_LIBRARIES} ${OTHER_LIB} glfw Vulkan::Vulkan)
