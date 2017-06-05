cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

# Adds HUMAN_MESSAGES to the preprocessor
# Since the subbmitted version is just a plain .cpp file, this will be disabled by default. If you want to see what
# the final product looks like, comment out the next line.
option(HUMAN_MESSAGES "Print ouput other than the required output. Turn this off when handing in." ON)
if(HUMAN_MESSAGES)
    add_definitions(-DHUMAN_MESSAGES)
endif()

option(MULTI_THREADING "Enable multithreading support." ON)
if(MULTI_THREADING)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    add_definitions(-DMULTI_THREADING)
endif()

#Output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Dependencies
#include(conanbuildinfo.cmake)
#conan_basic_setup()

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}/lib/sfml/cmake/Modules")

#Libraries
# SFML
include_directories(lib/sfml/include)
add_subdirectory(lib/sfml)
# JSON
add_subdirectory(lib/json )

#C-Exercises related projects
add_subdirectory(src/CCore)
add_subdirectory(src/CPerformance)
add_subdirectory(src/CExport)
add_subdirectory(src/CRender)

#Exercises
add_subdirectory(src/C1)
add_subdirectory(src/C2)
add_subdirectory(src/C3)
add_subdirectory(src/C4)