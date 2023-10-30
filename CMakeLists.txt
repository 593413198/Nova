
cmake_minimum_required(VERSION 2.8)

project(Game)

set(SRC_LIST game/Application.cpp)

add_subdirectory(engine)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} Nova)
