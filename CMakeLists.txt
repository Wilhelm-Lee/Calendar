cmake_minimum_required(VERSION 4.1)
project(Calendar C)

set(CMAKE_C_STANDARD 99)

add_executable(Calendar main.c
        write_event.c)
