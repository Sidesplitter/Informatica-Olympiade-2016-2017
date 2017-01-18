cmake_minimum_required(VERSION 3.5)
project(Informatica_Olympiade_2016_2017_CCore)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Main project
set(SOURCE_FILES CCore.cpp CCore.h PrimalityTester.cpp PrimalityTester.h Point.cpp Point.h Path.cpp Path.h Directions.h Progress.cpp Progress.h Exporter.cpp Exporter.h WorkDivider.cpp WorkDivider.h)
add_library(Informatica_Olympiade_2016_2017_CCore SHARED ${SOURCE_FILES})
target_link_libraries(Informatica_Olympiade_2016_2017_CCore nlohmann_json)