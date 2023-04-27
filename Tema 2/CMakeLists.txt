cmake_minimum_required(VERSION 3.21)
project(untitled3)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled3 main.cpp Animal.cpp)

target_include_directories(untitled3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
