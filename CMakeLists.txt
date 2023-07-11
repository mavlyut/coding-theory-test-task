cmake_minimum_required(VERSION 3.25)
project(coding-theory-test-task)

set(CMAKE_CXX_STANDARD 17)

add_library(order_statistics STATIC
        src/matrix.cpp
        src/utils.cpp
        src/order_statistic.cpp
        src/include/matrix.h
        src/include/utils.h
        src/include/order_statistic.h
        )

add_executable(collect collect_statistics.cpp)
target_link_libraries(collect order_statistics)

add_executable(main main.cpp)
target_link_libraries(main order_statistics)
