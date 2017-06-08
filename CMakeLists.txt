cmake_minimum_required(VERSION 3.7)
project(proyecto)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp cmake-build-debug/GenericUnit.cpp cmake-build-debug/GenericUnit.h)
add_executable(proyecto ${SOURCE_FILES})