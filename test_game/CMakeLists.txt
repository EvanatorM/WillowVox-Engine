# CMakeLists.txt (engine)
project(TestGame)

# Define the library target
add_executable(TestGame
    main.cpp
)

# Link the engine library
target_link_libraries(TestGame PRIVATE WillowVoxEngine)

# Include directories
target_include_directories(TestGame PUBLIC ${CMAKE_SOURCE_DIR}/engine/include)
target_include_directories(TestGame PUBLIC ${CMAKE_SOURCE_DIR}/external)

# Set output properties for the library
set_target_properties(TestGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Add platform-specific preprocessor definitions
if(WIN32)
    target_compile_definitions(TestGame PUBLIC PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(TestGame PUBLIC PLATFORM_MACOS)
elseif(UNIX)
    target_compile_definitions(TestGame PUBLIC PLATFORM_LINUX)
else()
    message(FATAL_ERROR "Unknown platform!")
endif()

# Add export macros for cross-platform compatibility
target_compile_definitions(TestGame PUBLIC TESTGAME_EXPORT)