cmake_minimum_required(VERSION 3.25)
project("swjungle-week-04-basic")

set(CMAKE_C_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)
set(EXPORT_COMPILE_COMMANDS)

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_EXECUTABLE_SUFFIX .out)
set(CMAKE_BINARY_DIR bin)

set(SRC_TARGET ${CMAKE_PROJECT_NAME})
set(LIB_TARGET lib${CMAKE_PROJECT_NAME})

add_compile_options(-Wall -fno-builtin -O0)
add_compile_definitions(DEBUG SENTINEL)

include_directories("include")
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "main.c")

add_custom_target(make_build
                  COMMAND make build
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})   

add_custom_target(test
                  COMMAND make test
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})   

add_subdirectory("basic/rbtree")

# ################################################
# compile source files
# ################################################
message("@@@@SOURCE_FILES:")
message("${SOURCE_FILES}")
message("@@@@CMAKE_BINARY_DIR : ${CMAKE_BINARY_DIR}")

foreach(SOURCE_PATH ${SOURCE_FILES})
    get_filename_component(EXEC_TARGET ${SOURCE_PATH} DIRECTORY)
    get_filename_component(EXEC_TARGET ${EXEC_TARGET} NAME)
    file(GLOB SOURCES "*.c")
    set(EXEC_TARGET ${EXEC_TARGET}_app)
    message("@@@@EXEC_TARGET: ${EXEC_TARGET}")

    add_executable(${EXEC_TARGET} ${SOURCE_PATH} ${SOURCES})
    target_link_libraries(${EXEC_TARGET} rbtree)
    set_target_properties(${EXEC_TARGET}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endforeach()