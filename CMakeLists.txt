# CMakeLists.txt (root)
cmake_minimum_required(VERSION 3.15)
project(WillowVoxEngine
        LANGUAGES CXX
        VERSION 0.1.0
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add engine and test projects
add_subdirectory(engine)
add_subdirectory(test)