cmake_minimum_required(VERSION 3.24)
project(MyApp LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MyApp main.cpp)


include(${CMAKE_SOURCE_DIR}/cmake/modules.cmake OPTIONAL)