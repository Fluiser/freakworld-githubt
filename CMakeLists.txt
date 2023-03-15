project(freakWorld)
cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 /std:c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DDEBUG=TRUE /std:c++17")


#variables
set(INCLUDE_DIR "D:/soft/VisualStudio/VC/Tools/MSVC/14.29.30133/include")


add_executable(freakWorld
		gameplay/Objects/Object.h 			gameplay/Objects/Object.cpp
		gameplay/Objects/Dynamic_Object.h 	gameplay/Objects/Dynamic_Object.cpp
		gameplay/Objects/Static_Object.h 	gameplay/Objects/Static_Object.cpp 
											gameplay/Objects/StaticObject_BoxForm.cpp
		gameplay/Scene.h 					gameplay/Scene.cpp
		gameplay/Player.h					gameplay/Player.cpp
		System/Window.h System/Window.cpp
		main.cpp)

#libs
set(Boost_INCLUDE_DIR "D:/soft/VisualStudio/VC/Tools/MSVC/14.29.30133/include")
set(Boost_LIBRARIES_CMAKE ${Boost_INCLUDE_DIR}/stage/lib)
link_directories(${Boost_LIBRARIES_CMAKE})
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost 1.80.0 REQUIRED)

set(SFML_DIR ${INCLUDE_DIR}/SFML/lib/cmake/SFML)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5.1 REQUIRED graphics audio window system)


target_link_libraries(freakWorld sfml-graphics sfml-audio sfml-window sfml-system ${Boost_LIBRARIES})

#///
include_directories(${INCLUDE_DIR} ./)
