#define project configs
cmake_minimum_required(VERSION 3.10)
project(verletIntegration VERSION "0.1" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include cmake modules and libraries
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)
if(WIN32)
    set(LIB_DIR libraries/win)
    set(SHRD_EXT dll)
else()
    set(LIB_DIR libraries/unix)
    set(SHRD_EXT so)
endif(WIN32)

set(SOURCES
    src/box.cpp
    src/engine.cpp
    src/node.cpp
    src/particle.cpp
    src/renderer.cpp
)

#packages
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio network)
add_executable(${CMAKE_PROJECT_NAME} main.cpp ${SOURCES})

#include header files
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)

#include tests library in future#

if (UNIX)
   target_link_libraries(${PROJECT_NAME} pthread)
endif (UNIX)