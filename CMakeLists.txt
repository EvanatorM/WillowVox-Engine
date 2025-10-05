cmake_minimum_required(VERSION 3.24)
project(WVTest LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(WVTest main.cpp)

set_target_properties(WVTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

include(${CMAKE_SOURCE_DIR}/cmake/modules.cmake OPTIONAL)