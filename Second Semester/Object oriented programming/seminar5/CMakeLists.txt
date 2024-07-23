cmake_minimum_required(VERSION 3.27)
project(seminar5)

set(CMAKE_CXX_STANDARD 17)

add_executable(seminar5 CSVPlaylist.cpp
CSVPlaylist.h
FilePlaylist.cpp
FilePlaylist.h
        main.cpp
PlayList.cpp
PlayList.h
Repository.cpp
Repository.h
RepositoryExceptions.cpp
RepositoryExceptions.h
Service.cpp
Service.h
Song.cpp
Song.h
SongValidator.cpp
SongValidator.h
UI.cpp
UI.h
Utils.cpp
Utils.h
        Action.h)
