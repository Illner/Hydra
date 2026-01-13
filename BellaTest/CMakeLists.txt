# CMake project for BellaTest
cmake_minimum_required(VERSION 3.14)

project("BellaTest"
        DESCRIPTION "Tests for Bella")

add_executable(BellaCompilerTest "BellaTest.cpp"

        # (s)d-DNNF circuits
        "compiler/dDNNF/dDNNF_CompilerTest.cpp"
        "compiler/dDNNF/dDNNF_CompilerTestHidden.cpp"

        # wDNNF, pwDNNF and nwDNNF circuits
        "compiler/wDNNF/wDNNF_CompilerTest.cpp"
        "compiler/wDNNF/wDNNF_CompilerTestHidden.cpp")

copy_shmetis_windows(BellaCompilerTest)

set_target_properties(BellaCompilerTest PROPERTIES OUTPUT_NAME "BellaTest")

target_link_libraries(BellaCompilerTest PRIVATE HydraLibrary HydraTestLibrary)
