# CMake project for Bella
cmake_minimum_required(VERSION 3.14)

project("Bella"
        VERSION 9.10.0
        DESCRIPTION "knowledge compiler")

add_executable(BellaCompiler "Bella.cpp"
        "commandLineArguments/CommandLineArguments.cpp")

copy_shmetis_windows(BellaCompiler)

set_target_properties(BellaCompiler PROPERTIES OUTPUT_NAME "Bella")

target_link_libraries(BellaCompiler PRIVATE HydraLibrary)
