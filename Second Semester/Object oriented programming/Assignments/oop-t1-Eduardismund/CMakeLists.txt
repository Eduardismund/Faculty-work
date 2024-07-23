cmake_minimum_required(VERSION 3.27)
project(t1_Eduardismund_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(t1_Eduardismund_1
        main.cpp
        player.h
        repo.h
        service.h
        ui.h
        player.cpp
        repo.cpp
        service.cpp
        ui.cpp
        tests.cpp)
