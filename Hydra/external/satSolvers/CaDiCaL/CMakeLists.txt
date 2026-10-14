# CMake project for CaDiCaL (Hydra version)
cmake_minimum_required(VERSION 3.14)

# Sources of the library
file(GLOB CADICAL_SOURCE_FILES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")     # kitten.c

# Exclude the command-line tools 'cadical' and 'mobical'
list(REMOVE_ITEM CADICAL_SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cadical.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/mobical.cpp")

add_library(CaDiCaLLibrary OBJECT ${CADICAL_SOURCE_FILES})

# No warnings
target_compile_options(CaDiCaLLibrary PRIVATE -w)

target_compile_definitions(CaDiCaLLibrary PRIVATE NBUILD)

IF (CMAKE_SYSTEM_NAME STREQUAL "CYGWIN")
    target_compile_definitions(CaDiCaLLibrary PRIVATE _GNU_SOURCE NCLOSEFROM)
ENDIF ()

IF (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    target_compile_definitions(CaDiCaLLibrary PRIVATE NCLOSEFROM)
ENDIF ()

target_compile_definitions(CaDiCaLLibrary PUBLIC CaDiCaL=CaDiCaL_Hydra)
