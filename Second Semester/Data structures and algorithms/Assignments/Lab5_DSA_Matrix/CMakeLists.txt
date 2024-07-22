cmake_minimum_required(VERSION 3.27)
project(Lab5_DSA_Matrix)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab5_DSA_Matrix App.cpp
                ExtendedTest.cpp
                ExtendedTest.h
                ShortTest.cpp
                ShortTest.h
                Matrix.cpp
        Matrix.h
)
