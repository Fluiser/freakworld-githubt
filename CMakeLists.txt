set(CMAKE_TOOLCHAIN_FILE "F:/github/vcpkg/scripts/buildsystems/vcpkg.cmake")
cmake_minimum_required(VERSION 3.0.0)
project(freakWorld)
set(CMAKE_CXX_STANDARD 20)
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
target_link_libraries(freakWorld ${Boost_LIBRARIES} ${OTHER_LIB} glfw Vulkan::Vulkan)
