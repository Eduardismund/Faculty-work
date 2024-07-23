cmake_minimum_required(VERSION 3.27)
project(a2_3_Eduardismund C)


set(CMAKE_C_STANDARD 11)
include_directories(ui)
include_directories(domain)
include_directories(repo)
include_directories(service)
include_directories(dynamicArray)



# Set the WIN32 option to specify that this is a console application
add_executable(a2_3_Eduardismund
        dynamicArray/DynamicArray.h
        ui/UI.c
        ui/UI.h
        repo/Repo.c
        repo/Repo.h
        dynamicArray/DynamicArray.c
        domain/RealEstateAgency.c
        domain/RealEstateAgency.h
        service/Service.c
        service/Service.h
        main.c
        domain/Operation.c
        repo/UndoRedoRepository.h
        repo/UndoRedoRepository.c
        tests/testDynamicArray.h
        tests/testDynamicArray.c
        tests/testEstate.c
        tests/testEstate.h
        tests/testService.h
        tests/testService.c
)
