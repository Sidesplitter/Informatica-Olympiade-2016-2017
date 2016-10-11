cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Adds HUMAN_MESSAGES to the preprocessor
# Since the subbmitted version is just a plain .cpp file, this will be disabled by default. If you want to see what
# the final product looks like, comment out the next line.
add_definitions(-DHUMAN_MESSAGES)

add_subdirectory(src/CCore)
add_subdirectory(src/CPerformance)
add_subdirectory(src/C1)
add_subdirectory(src/C2)
add_subdirectory(src/C4)
add_subdirectory(lib/googletest)


# Tests
project(Informatica_Olympiade_2016_2017_Tests)
set(TEST_SOURCE_FILES test/main.cpp test/CCore/PrimalityTesterTest.cpp test/CCore/PathTest.cpp)


include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Informatica_Olympiade_2016_2017_Tests ${TEST_SOURCE_FILES} src/CCore/CCore.cpp src/CCore/CCore.h src/CCore/PrimalityTester.cpp src/CCore/PrimalityTester.h src/CCore/Point.cpp src/CCore/Point.h src/CCore/Path.cpp src/CCore/Path.h src/CCore/Directions.h)
include_directories(src)
target_link_libraries(Informatica_Olympiade_2016_2017_Tests gtest gtest_main Informatica_Olympiade_2016_2017_CCore)
add_test(runUnitTests runUnitTests)
