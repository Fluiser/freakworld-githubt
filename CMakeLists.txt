project(freakWorld)
cmake_minimum_required(VERSION 3.0.0)
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

set(SFML_DIR ${INCLUDE_DIR}/SFML/lib/cmake/SFML)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5.1 REQUIRED graphics audio window system)

if (WIN32)
	add_compile_definitions(WIN32=TRUE)
endif(WIN32)

if (UNIX)
	add_compile_definitions(LINUX=TRUE)
endif(UNIX)

#///
include_directories(${INCLUDE_DIR} ./)



if(WIN32)
	set(DiscordRPC "System/DiscordRPC")
	set(DISCORD_LNK "")

	add_library(DiscordRPCLIB STATIC IMPORTED)
	set_target_properties(DiscordRPCLIB PROPERTIES 
							Debug ${CMAKE_CURRENT_SOURCE_DIR}/System/DiscordRPC/lib/discord-rpc-debug.lib
							Release ${CMAKE_CURRENT_SOURCE_DIR}/System/DiscordRPC/lib/discord-rpc.lib)
else()

	set(DISCORD_LNK "")
	set(DISCORD_DLL "")

endif()

message(LNK: ${DISCORD_LNK}\n DLL LIB: ${DISCORD_DLL})

add_executable(freakWorld
		Gameplay/Objects/Object.h 						Gameplay/Objects/Object.cpp
		Gameplay/Objects/Dynamic_Object.h 				Gameplay/Objects/Dynamic_Object.cpp
		Gameplay/Objects/Static_Object.h 				Gameplay/Objects/Static_Object.cpp 
														Gameplay/Objects/StaticObject_BoxForm.cpp
		Gameplay/Scene.hpp 								Gameplay/Scene.cpp
		Gameplay/Player.h								Gameplay/Player.cpp
		System/Graphics/String.hpp						System/Graphics/String.cpp
		System/Handlers.h 		System/Handlers.cpp
		System/Window.h 		System/Window.cpp
		
		${DISCORD_LNK}

		main.cpp
)
target_link_libraries(freakWorld sfml-graphics sfml-audio sfml-window sfml-system ${Boost_LIBRARIES} ${DISCORD_DLL})
target_link_libraries(freakWorld debug ${CMAKE_CURRENT_SOURCE_DIR}/System/DiscordRPC/lib/discord-rpc-debug.lib)
target_link_libraries(freakWorld optimized ${CMAKE_CURRENT_SOURCE_DIR}/System/DiscordRPC/lib/discord-rpc.lib)
