cmake_minimum_required(VERSION 2.6)

project(sun-sensor)
set(CMAKE_BUILD_TYPE Debug)

include_directories(
    libs/veml6075-uv-sensor/include
    )

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

file(GLOB veml6075 libs/veml6075-uv-sensor/src/*.c)
file(GLOB_RECURSE tests tests/*.cpp)

add_executable(
    tests
    ${veml6075}
    ${tests}
    )

target_link_libraries(
    tests
    m
    CppUTest
    CppUTestExt
    )

# Run unit tests
add_custom_target(check ./tests -c DEPENDS tests)


