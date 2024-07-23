cmake_minimum_required(VERSION 3.27)
project(oop_a4_5_Eduardismund)

set(CMAKE_CXX_STANDARD 14)

add_executable(oop_a4_5_Eduardismund
        Dog.cpp
        Dog.h
        DynamicArray.h
        ShelterRepository.cpp
        ShelterRepository.h
        AdminService.h
        AdminService.cpp
        Exception.h
        ui.h
        ui.cpp
        main.cpp
        tests.h
        tests.cpp
        AdoptedRepo.cpp
        AdoptedRepo.h
        UserService.h
        UserService.cpp)
