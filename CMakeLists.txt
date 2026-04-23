cmake_minimum_required(VERSION 3.21.1)
project(untitled)

set(CMAKE_C_STANDARD 99)

add_executable(untitled
        main.c
        waveform.c
        io.c)