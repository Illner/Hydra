# CMake project for CaraTest
cmake_minimum_required(VERSION 3.14)

project("CaraTest"
        DESCRIPTION "Tests for Cara")

add_executable(CaraSolverTest "CaraTest.cpp"

        # #Solver
        "sharpSolver/SharpSolverTest.cpp"
        "sharpSolver/SharpSolverTestHidden.cpp")

copy_shmetis_windows(CaraSolverTest)

set_target_properties(CaraSolverTest PROPERTIES OUTPUT_NAME "CaraTest")

target_link_libraries(CaraSolverTest PRIVATE HydraLibrary HydraTestLibrary)
