cmake_minimum_required(VERSION 3.25)
project(untitled3)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp
        src/matrix.cpp
        src/utils.cpp
        src/order_statistic.cpp)

add_compile_definitions(LOCAL)
