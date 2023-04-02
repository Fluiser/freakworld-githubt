project(freakWorld)
cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 /std:c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DDEBUG=TRUE /std:c++17")


#variables
set(INCLUDE_DIR "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/include")


add_executable(freakWorld
		Gameplay/Objects/Object.h 			Gameplay/Objects/Object.cpp
		Gameplay/Objects/Dynamic_Object.h 	Gameplay/Objects/Dynamic_Object.cpp
		Gameplay/Objects/Static_Object.h 	Gameplay/Objects/Static_Object.cpp 
											Gameplay/Objects/StaticObject_BoxForm.cpp
		Gameplay/Scene.hpp 					Gameplay/Scene.cpp
		Gameplay/Player.h					Gameplay/Player.cpp
		
		System/Graphics/TextAreas/BaseTextArea.h		System/Graphics/TextAreas/BaseTextArea.cpp
		System/Graphics/TextAreas/CompoundTextArea.h	System/Graphics/TextAreas/CompoundTextArea.cpp

		System/Handlers.h 		System/Handlers.cpp
		System/Window.h 		System/Window.cpp
		main.cpp
)

#libs
set(Boost_INCLUDE_DIR "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/include")
set(Boost_LIBRARIES_CMAKE ${Boost_INCLUDE_DIR}/stage/lib)
find_package(Boost 1.80.0 REQUIRED)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
link_directories(${Boost_LIBRARIES_CMAKE})

set(SFML_DIR "X:/SFML/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5.1 REQUIRED graphics audio window system)


target_link_libraries(freakWorld sfml-graphics sfml-audio sfml-window sfml-system ${Boost_LIBRARIES})

if (WIN32)
# Now not need.
endif(WIN32)

if (UNIX)
	add_compile_definitions(LINUX=TRUE)
endif(UNIX)

#///
include_directories(${INCLUDE_DIR} ./)