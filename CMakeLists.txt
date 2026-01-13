# Top-Level CMakeLists.txt
cmake_minimum_required(VERSION 3.14)

project(Hydra)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET 14.0)

# Compile options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-class-memaccess -Wno-unknown-warning-option")  # MiniSat

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native")

# "file too big" (CYGWIN)
IF ((CMAKE_SYSTEM_NAME STREQUAL "CYGWIN") AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    message(STATUS "Optimization Level 1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
ENDIF ()

# Include the root directory
include_directories(${CMAKE_SOURCE_DIR})

# Boost (KaHyPar)
set(BOOST_KAHYPAR_HOME "${CMAKE_SOURCE_DIR}/Hydra/external/boost/")

# Partitioning hypergraph (PaToH, hMETIS, KaHyPar)
set(PATOH_HOME "${CMAKE_SOURCE_DIR}/Hydra/external/partitioningHypergraphs/PaToH/")
set(HMETIS_HOME "${CMAKE_SOURCE_DIR}/Hydra/external/partitioningHypergraphs/hMETIS/")
set(KAHYPAR_HOME "${CMAKE_SOURCE_DIR}/Hydra/external/partitioningHypergraphs/KaHyPar/")

# Global options
option(BUILD_BELLA "Build Bella" OFF)
option(BUILD_CARA "Build Cara" OFF)
option(BUILD_TEST "Build tests" OFF)

# Ensure that exactly one of the options is ON
IF ((BUILD_BELLA AND BUILD_CARA) OR (NOT BUILD_BELLA AND NOT BUILD_CARA))
    message(FATAL_ERROR "Exactly one of BUILD_BELLA or BUILD_CARA must be enabled!")
ENDIF ()

# Options
IF (BUILD_BELLA)
    add_compile_definitions(BELLA_COMPILER)
ENDIF ()
IF (BUILD_CARA)
    add_compile_definitions(CARA_SOLVER)
ENDIF ()
IF (BUILD_TEST)
    add_compile_definitions(TEST)
    IF (BUILD_BELLA)
        add_compile_definitions(BELLA_COMPILER_TEST)
    ENDIF ()
    IF (BUILD_CARA)
        add_compile_definitions(CARA_SOLVER_TEST)
    ENDIF ()
ENDIF ()

# Add Hydra
add_subdirectory(Hydra)

# Add Bella
IF (BUILD_BELLA)
    add_subdirectory(Bella)
ENDIF ()

# Add Cara
IF (BUILD_CARA)
    add_subdirectory(Cara)
ENDIF ()

# Add tests
IF (BUILD_TEST)
    add_subdirectory(HydraTest)

    # Add BellaTest
    IF (BUILD_BELLA)
        add_subdirectory(BellaTest)
    ENDIF ()

    # Add CaraTest
    IF (BUILD_CARA)
        add_subdirectory(CaraTest)
    ENDIF ()
ENDIF ()
