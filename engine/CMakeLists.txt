
cmake_minimum_required(VERSION 2.8)

project(Nova)

set(SRC_LIST test.cpp)

add_library(Nova STATIC ${SRC_LIST})
