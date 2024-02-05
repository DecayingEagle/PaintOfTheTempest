cmake_minimum_required(VERSION 3.28)
project(paintofthetempest VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenGL REQUIRED)

add_executable(paintofthetempest src/main.cpp
        src/config.h
        src/glad.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)

target_link_libraries(paintofthetempest glfw OpenGL::GL)
