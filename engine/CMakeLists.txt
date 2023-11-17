
cmake_minimum_required(VERSION 2.8)

project(Nova)

find_package(OpenGL REQUIRED)

set(SRC_LIST
    Nova.h
    Log.cpp
    Log.h
    Platform/glad.c
    Platform/Windows/WindowsWindow.cpp
    Platform/Windows/WindowsWindow.h
    Cores/Window.h
    Cores/Application.cpp
    Cores/Application.h
    )

file(GLOB EVENTS_HEADERS Events/*.h)

add_library(Nova STATIC
    ${SRC_LIST}
    ${EVENTS_HEADERS}
)

add_subdirectory(../misc/GLFW ../glfw)

target_link_libraries(${PROJECT_NAME} glfw)

target_include_directories(${PROJECT_NAME} PUBLIC 
    .
    ../misc/spdlog/include
    ../misc/GLFW/include
    Platform/include
    Events/
    Cores/
    )
