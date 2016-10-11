cmake_minimum_required(VERSION 3.5)
project(Informatica_Olympiade_2016_2017_C4)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp)

add_executable(Informatica_Olympiade_2016_2017_C4 ${SOURCE_FILES})
target_link_libraries(Informatica_Olympiade_2016_2017_C4 Informatica_Olympiade_2016_2017_CCore)