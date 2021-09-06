cmake_minimum_required(VERSION 3.10)

project(Observer VERSION 0.0.1 LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(src/buffer)

add_subdirectory(src/socket)

add_subdirectory(src/ethr)

add_subdirectory(src/iphdr)

add_subdirectory(src/manager)

add_subdirectory(src/exceptions)

add_subdirectory(app)
