cmake_minimum_required(VERSION 3.27)
project(oop-a10-Eduardismund)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.5.5\\mingw_64\\lib\\cmake\\")

find_package(Qt6 COMPONENTS Widgets Core Gui
        REQUIRED)

add_executable(oop-a10-Eduardismund
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
        DBRepository.cpp
        GUI.h
        GUI.cpp
        GUIUser.cpp
        Action.h
        TabelList.h
        TabelList.cpp
)

target_link_libraries(oop-a10-Eduardismund Qt::Widgets)

target_link_libraries(oop-a10-Eduardismund Qt::Widgets Qt::Core Qt::Gui)

if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()