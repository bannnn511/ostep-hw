cmake_minimum_required(VERSION 3.28)
project(cpu_api C)

set(CMAKE_C_STANDARD 11)

add_executable(cpu_api 1.c
        2.c
        3.c
        3-nowait.c)
