cmake_minimum_required(VERSION 3.10)

project(Observer VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(src/buffer)

add_subdirectory(src/socket)

add_subdirectory(src/ethr)

add_subdirectory(src/iphdr)

add_subdirectory(src/manager)

add_subdirectory(src/exceptions)

add_subdirectory(app)
