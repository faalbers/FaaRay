cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(FaaRay VERSION 0.1 LANGUAGES CXX)

file(GLOB MORE_TARGETS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */*.cpp )
#get_target_property(GFA_SOURCE_DIR GFA SOURCE_DIR)

#add_library(FaaRay ${MORE_TARGETS})
#target_link_libraries(FaaRay PRIVATE GFA)
#target_include_directories(FaaRay PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${GFA_SOURCE_DIR})
