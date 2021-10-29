cmake_minimum_required(VERSION 3.10)

set (TARGET_NAME openIMUdriver)

project(${TARGET_NAME})


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-D__DEBUG__)
endif()

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

#include (UrhoCommon)
#add_subdirectory (Hello)

file (GLOB SRC_CPP_FILES src/*.cpp)
file (GLOB SRC_H_FILES include/*.h)

include_directories(include)

add_executable(${TARGET_NAME} ${SRC_CPP_FILES})



message("CPP files      : " ${SRC_CPP_FILES})
message("H files        : " ${SRC_H_FILES})

message("System type     : " ${CMAKE_SYSTEM_NAME})
message("Target name     : " ${TARGET_NAME})
message("Build type      : " ${CMAKE_BUILD_TYPE})
message("Source dir      : " ${CMAKE_SOURCE_DIR})
message("C flags         : " ${CMAKE_C_FLAGS})
message("CPP flags       : " ${CMAKE_CXX_FLAGS})
