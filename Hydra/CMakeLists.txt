# CMake project for Hydra
cmake_minimum_required(VERSION 3.14)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

add_library(HydraLibrary STATIC
        "other/parser/CommandLineArgumentsParser.cpp"
        "statistics/StatisticsAbstract.cpp" "statistics/Statistics.cpp" "other/version/Version.cpp"
        "other/operatingSystem/OperatingSystem.cpp" "other/memory/Memory.cpp" "other/container/vectorSet/VectorSet.cpp"
        "other/type/arbitraryPrecisionInteger/custom/CustomArbitraryPrecisionInteger.cpp" "external/satSolvers/MiniSat_d4/Solver.cpp"

        # Statistics
        "cache/Cache.cxx"
        "circuit/Circuit.cxx"
        "compiler/Compiler.cxx"
        "satSolver/SatSolverAbstract.cxx"
        "renHCRecognition/RenHCRecognitionAbstract.cxx"
        "decisionHeuristic/DecisionHeuristicAbstract.cxx"
        "formula/representation/FormulaRepresentationAbstract.cxx"
        "partitioningHypergraph/PartitioningHypergraphAbstract.cxx")

# Hydra version
target_compile_definitions(HydraLibrary PRIVATE
        HYDRA_VERSION="${PROJECT_VERSION}"
        HYDRA_VERSION_MAJOR="${PROJECT_VERSION_MAJOR}"
        HYDRA_VERSION_MINOR="${PROJECT_VERSION_MINOR}"
        HYDRA_VERSION_PATCH="${PROJECT_VERSION_PATCH}"
)

# Boost (header-only)
IF (CMAKE_SYSTEM_NAME STREQUAL "CYGWIN")
    find_package(Boost REQUIRED)
ELSE ()
    find_package(Boost REQUIRED CONFIG)
ENDIF ()
target_include_directories(HydraLibrary PUBLIC ${Boost_INCLUDE_DIRS})

# GMP
find_library(GMPLibrary NAMES gmp)
# GMP was NOT found
IF (NOT GMPLibrary)
    message(FATAL_ERROR "GMP was NOT found! Please install GMP!")
ENDIF ()
target_link_libraries(HydraLibrary PRIVATE ${GMPLibrary})

# Custom function to copy shmetis.exe (Windows/CYGWIN)
FUNCTION(copy_shmetis_windows TARGET_NAME)
    IF ((${CMAKE_SYSTEM_NAME} STREQUAL "Windows") OR (CMAKE_SYSTEM_NAME STREQUAL "CYGWIN"))
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${HMETIS_HOME}/Windows/shmetis.exe"
                "$<TARGET_FILE_DIR:${TARGET_NAME}>/shmetis.exe")
    ENDIF ()
ENDFUNCTION()

# Custom function to find the library and check if it was found
FUNCTION(find_and_check_library LIBRARY_VAR LIBRARY_NAME LIBRARY_PATH)
    find_library(${LIBRARY_VAR} ${LIBRARY_NAME} PATHS ${LIBRARY_PATH} NO_SYSTEM_ENVIRONMENT_PATH NO_DEFAULT_PATH)

    # The library was NOT found
    IF (NOT ${LIBRARY_VAR})
        message(FATAL_ERROR "${LIBRARY_NAME} was NOT found in ${LIBRARY_PATH}!")
    # The library was found
    ELSE ()
        target_link_libraries(HydraLibrary PRIVATE ${${LIBRARY_VAR}})
    ENDIF ()
ENDFUNCTION()

# macOS
IF (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    # Apple Silicon
    IF (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm64")
        # PaToH
        find_and_check_library(PaToHLibrary "libpatoh.a" "${PATOH_HOME}/macOS/Apple Silicon/")

        # KaHyPar
        find_and_check_library(KaHyParLibrary "libkahypar.a" "${KAHYPAR_HOME}/macOS/Apple Silicon/")

        # Boost (KaHyPar)
        find_and_check_library(BoostKaHyParLibrary "libmini_boost.a" "${BOOST_KAHYPAR_HOME}/macOS/Apple Silicon/")
    # Intel
    ELSE ()
        # PaToH
        find_and_check_library(PaToHLibrary "libpatoh.a" "${PATOH_HOME}/macOS/Intel/")

        # KaHyPar
        find_and_check_library(KaHyParLibrary "libkahypar.a" "${KAHYPAR_HOME}/macOS/Intel/")

        # Boost (KaHyPar)
        find_and_check_library(BoostKaHyParLibrary "libmini_boost.a" "${BOOST_KAHYPAR_HOME}/macOS/Intel/")
    ENDIF ()
# Windows
ELSEIF ((${CMAKE_SYSTEM_NAME} STREQUAL "Windows") OR (CMAKE_SYSTEM_NAME STREQUAL "CYGWIN"))
    # KaHyPar
    find_and_check_library(KaHyParLibrary "libkahypar.a" "${KAHYPAR_HOME}/Windows/")

    # Boost (KaHyPar)
    find_and_check_library(BoostKaHyParLibrary "libmini_boost.a" "${BOOST_KAHYPAR_HOME}/Windows/")
# Linux
ELSEIF (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    # PaToH
    find_and_check_library(PaToHLibrary "libpatoh.a" "${PATOH_HOME}/Linux/")

    # KaHyPar
    find_and_check_library(KaHyParLibrary "libkahypar.a" "${KAHYPAR_HOME}/Linux/")

    # Boost (KaHyPar)
    find_and_check_library(BoostKaHyParLibrary "libmini_boost.a" "${BOOST_KAHYPAR_HOME}/Linux/")
# Not supported
ELSE ()
    message(FATAL_ERROR "Your operating system (${CMAKE_SYSTEM_NAME}) is NOT supported!")
ENDIF ()
