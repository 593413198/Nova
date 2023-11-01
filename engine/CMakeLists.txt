
cmake_minimum_required(VERSION 2.8)

project(Nova)

set(SRC_LIST
    Log.cpp
    Log.h
    Events/Event.h
    Events/KeyEvent.h
    Events/MouseEvent.h
    Events/WindowEvent.h
    )

add_library(Nova STATIC ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PUBLIC ../misc/spdlog/include)
