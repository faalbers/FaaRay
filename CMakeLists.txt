cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(FaaRay VERSION 0.1 LANGUAGES CXX)

if(FALSE)
    find_package(Git QUIET)
    message(STATUS "Submodule update")
    message(STATUS ${GIT_EXECUTABLE})
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
endif()

add_subdirectory(extern/GFA)

file(GLOB MORE_TARGETS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */*.cpp )
add_library(FaaRay ${MORE_TARGETS})
target_link_libraries(FaaRay PRIVATE GFA)
target_include_directories(FaaRay PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
