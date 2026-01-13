# CMake project for Cara
cmake_minimum_required(VERSION 3.14)

project("Cara"
        VERSION 12.8.0
        DESCRIPTION "#SAT solver")

add_executable(CaraSolver "Cara.cpp"
        "commandLineArguments/CommandLineArguments.cpp")

copy_shmetis_windows(CaraSolver)

set_target_properties(CaraSolver PROPERTIES OUTPUT_NAME "Cara")

target_link_libraries(CaraSolver PRIVATE HydraLibrary)
