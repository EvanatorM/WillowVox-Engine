cmake_minimum_required(VERSION 3.24)
project(MyApp LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MyApp main.cpp)

set_target_properties(MyApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

include(${CMAKE_SOURCE_DIR}/cmake/modules.cmake OPTIONAL)

# Copy assets folder to build folder
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Coping assets..."
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:MyApp>/assets
)