cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(bankCardNumber VERSION 1.0.0)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(bankCardNumberChecker main.cpp)