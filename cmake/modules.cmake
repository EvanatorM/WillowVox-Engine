include(FetchContent)

macro(_fetch_git_project NAME REPO COMMIT)
  message(STATUS "Module: ${NAME} @ ${COMMIT}")
  FetchContent_Declare(${NAME}
    GIT_REPOSITORY ${REPO}
    GIT_TAG        ${COMMIT}      # exact commit from lockfile
    GIT_SHALLOW    TRUE
    UPDATE_DISCONNECTED FALSE
  )
  FetchContent_MakeAvailable(${NAME})
endmacro()

# ----- Engine Modules -----
# Uncomment any modules you will be using for your project

# Core Module (Required)
_fetch_git_project(WVCore https://github.com/EvanatorM/WV-Core.git alpha-v0.2.3)
target_link_libraries(${PROJECT_NAME} PRIVATE WVCore)
target_include_directories(${PROJECT_NAME} PRIVATE ${wvcore_SOURCE_DIR}/include)

# Voxel Worlds Module
#_fetch_git_project(WVVoxelWorlds https://github.com/EvanatorM/WV-VoxelWorlds.git alpha-v0.1.0)
#target_link_libraries(${PROJECT_NAME} PRIVATE WVVoxelWorlds)
#target_include_directories(${PROJECT_NAME} PUBLIC ${wvvoxelworlds_SOURCE_DIR}/include)

# --------------------------