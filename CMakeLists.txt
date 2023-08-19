cmake_minimum_required(VERSION 3.26)
project(MathParser)

set(CMAKE_CXX_STANDARD 20)

add_executable(MathParser main.cpp
        mp/parser.cpp
        mp/lexer.cpp
        mp/evaluate.cpp
        mp/lexer.h
        mp/parser.h
        mp/evaluate.h)
