
cmake_minimum_required(VERSION 2.8)

project(Nova)

find_package(OpenGL REQUIRED)

set(SRC_LIST
    Log.cpp
    Log.h
    Events/Event.h
    Events/KeyEvent.h
    Events/MouseEvent.h
    Events/WindowEvent.h
    Platform/glad.c
    )

add_library(Nova STATIC ${SRC_LIST})

add_subdirectory(../misc/GLFW ../glfw)

target_link_libraries(${PROJECT_NAME} glfw)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ...
    ../misc/spdlog/include
    ../misc/GLFW/include
    Platform/include
    )
