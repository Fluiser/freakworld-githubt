project(freakWorld)
cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 /std:c++20")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DDEBUG=TRUE /std:c++20")


#variables
set(INCLUDE_DIR "D:/soft/VisualStudio/VC/Tools/MSVC/14.29.30133/include")


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
		main.cpp
)

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


target_link_libraries(freakWorld sfml-graphics sfml-audio sfml-window sfml-system ${Boost_LIBRARIES})

if (WIN32)
# Now not need.
endif(WIN32)

if (UNIX)
	add_compile_definitions(LINUX=TRUE)
endif(UNIX)

#///
include_directories(${INCLUDE_DIR} ./)