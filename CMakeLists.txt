cmake_minimum_required(VERSION 4.1)
project(Laboratorio3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Laboratorio3
        ast.cpp
        ast.h
        main.cpp
        parser.cpp
        parser.h
        scanner.cpp
        scanner.h
        token.cpp
        token.h
        visitor.cpp
        visitor.h)
