cmake_minimum_required(VERSION 3.22)
project(calculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(calculator main.cpp src/Node.cpp src/Node.hpp src/Token.cpp src/Token.hpp src/Lexer.cpp src/Lexer.hpp src/Parser.cpp src/Parser.hpp)
