include(FetchContent)

macro(_add_engine_git_module NAME REPO COMMIT)
  message(STATUS "Module: ${NAME} @ ${COMMIT}")
  FetchContent_Declare(${NAME}
    GIT_REPOSITORY ${REPO}
    GIT_TAG        ${COMMIT}      # exact commit from lockfile
    GIT_SHALLOW    TRUE
    UPDATE_DISCONNECTED FALSE
  )
  FetchContent_MakeAvailable(${NAME})

  target_link_libraries(${PROJECT_NAME} PRIVATE ${NAME})
  target_include_directories(${PROJECT_NAME} PRIVATE ${${NAME}_SOURCE_DIR}/include)
endmacro()

_add_engine_git_module(WVCore https://github.com/EvanatorM/WV-Core.git alpha-v0.2.2)