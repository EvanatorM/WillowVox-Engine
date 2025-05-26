# CMakeLists.txt (root)
cmake_minimum_required(VERSION 3.15)
project(WillowVox
    LANGUAGES CXX C
    VERSION 0.1.0
)
set(CMAKE_GENERATOR_PLATFORM x64)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add engine and test projects
add_subdirectory(external/imgui)
add_subdirectory(engine)
add_subdirectory(test_game)

# Copy assets folder to build folder
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/test_game/assets
    $<TARGET_FILE_DIR:TestGame>/assets
    COMMENT "Copying assets"
)