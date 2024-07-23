cmake_minimum_required(VERSION 3.27)
project(oop_a6_7_Eduardismund)

set(CMAKE_CXX_STANDARD 14)
#SET(GCC_FLAGS "-lsqlite3")
#INCLUDE_DIRECTORIES(.)
#
#SET(CMAKE_EXE_LINKER_FLAGS "${GCC_FLAGS}")
add_executable(oop_a6_7_Eduardismund
        Dog.cpp
        Dog.h
        RepoShelterDogs.cpp
        RepoShelterDogs.h
        ServiceAdmin.h
        ServiceAdmin.cpp
        Exception.h
        UserInterface.h
        UserInterface.cpp
        main.cpp
        tests.h
        tests.cpp
        RepoAdoptedDogs.cpp
        RepoAdoptedDogs.h
        ServiceUser.h
        ServiceUser.cpp
        sqlite3.c
        sqlite3.h
        sqlite3.def
        sqlite3.dll
        sqlite3ext.h
        DBRepository.cpp
        DBRepository.cpp)

find_package (SQLite3)

if (SQLITE3_FOUND)
    include_directories(${SQLITE3_INCLUDE_DIRS})
    target_link_libraries (tutorial ${SQLITE3_LIBRARIES})
endif (SQLITE3_FOUND)