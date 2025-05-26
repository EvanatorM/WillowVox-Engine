# CMakeLists.txt (engine)
project(WillowVoxEngine)

# Define the library target
add_library(WillowVoxEngine SHARED

    # dependencies
    dependencies/include/glad/src/glad.c
)

# Include directories
target_include_directories(WillowVoxEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(WillowVoxEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include)
target_include_directories(WillowVoxEngine PUBLIC ${CMAKE_SOURCE_DIR}/external)

# Link libraries
target_link_libraries(WillowVoxEngine PRIVATE ${CMAKE_SOURCE_DIR}/external/glfw3.lib)
target_link_libraries(WillowVoxEngine PUBLIC imgui)

# Set output properties for the library
set_target_properties(WillowVoxEngine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Add platform-specific preprocessor definitions
if(WIN32)
    target_compile_definitions(WillowVoxEngine PUBLIC PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(WillowVoxEngine PUBLIC PLATFORM_MACOS)
elseif(UNIX)
    target_compile_definitions(WillowVoxEngine PUBLIC PLATFORM_LINUX)
else()
    message(FATAL_ERROR "Unknown platform!")
endif()

# Add export macros for cross-platform compatibility
target_compile_definitions(WillowVoxEngine PUBLIC WILLOWVOX_EXPORT)