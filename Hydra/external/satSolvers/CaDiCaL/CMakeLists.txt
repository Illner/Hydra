# CMake project for CaDiCaL
cmake_minimum_required(VERSION 3.14)

# Collect all .cpp files from the CaDiCaL source directory
file(GLOB CADICAL_SRC_FILES "src/*.cpp")

add_library(CaDiCaLLibrary STATIC ${CADICAL_SRC_FILES})

target_include_directories(CaDiCaLLibrary PUBLIC src)

target_compile_definitions(CaDiCaLLibrary PRIVATE NBUILD)
target_compile_definitions(CaDiCaLLibrary PRIVATE NCLOSEFROM)
