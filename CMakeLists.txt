cmake_minimum_required(VERSION 3.5.0)
project(mondelbrot VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL2 REQUIRED CONFIG)

add_executable(mondelbrot main.cpp)

target_link_libraries(mondelbrot PRIVATE SDL2::SDL2)
