cmake_minimum_required(VERSION 2.6)

project(sun-sensor)
set(CMAKE_BUILD_TYPE Debug)

include_directories(dependencies/)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(
    tests
    cpputest_runner.cpp
    sun_sensor_driver_test.cpp
    veml6075.c
    )

target_link_libraries(
    tests
    m
    CppUTest
    CppUTestExt
    )

# Run unit tests
add_custom_target(check ./tests -c DEPENDS tests)


