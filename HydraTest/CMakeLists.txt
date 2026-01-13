# CMake project for HydraTest
cmake_minimum_required(VERSION 3.14)

project("HydraTest"
        DESCRIPTION "Tests for Hydra")

add_library(HydraTestLibrary STATIC "TemplateTest.cpp")

add_executable(HydraTest "HydraTest.cpp"

        # Node
        "circuit/node/NodeTest.cpp"

        # Circuit
        "circuit/CircuitTest.cpp"
        "circuit/query/CircuitQueryTest.cpp"
        "circuit/parser/CircuitParserTest.cpp"
        "circuit/copySubcircuit/CircuitCopySubcircuitTest.cpp"

        # Formula
        "formula/FormulaTest.cpp"
        "formula/partialAssignment/PartialAssignmentTest.cpp"

        # Formula representation
        "formula/representation/contagious/ContagiousFormulaRepresentationTest.cpp"
        "formula/representation/contagious/parser/ContagiousFormulaRepresentationParserTest.cpp"
        "formula/representation/contagious/recognition/ContagiousFormulaRepresentationRecognitionTest.cpp"
        "formula/representation/contagious/subsumption/ContagiousFormulaRepresentationSubsumptionTest.cpp"
        "formula/representation/contagious/subsumption/ContagiousFormulaRepresentationUnsortedSubsumptionTest.cpp"
        "formula/representation/contagious/variableSubsumptionWithMapping/ContagiousFormulaRepresentationVariableSubsumptionWithMappingTest.cpp"

        # Structural restricted formula representation
        "formula/structuralRestrictedRepresentation/StructuralRestrictedFormulaRepresentationTest.cpp"

        # RenH-C recognition
        "renHCRecognition/aspvall/AspvallRenHCRecognitionTest.cpp"

        # Other
        "other/MergeSortTest.cpp"

        # Container
        "other/container/vectorMap/VectorMapTest.cpp"
        "other/container/vectorSet/VectorSetTest.cpp"
        "other/container/fixedVector/FixedVectorTest.cpp"
        "other/container/reusableVector/ReusableVectorTest.cpp"
        "other/container/stackWithLevels/StackWithLevelsTest.cpp"
        "other/container/variableStateVector/VariableStateVectorTest.cpp"
        "other/container/contagiousOccurrenceList/ContagiousOccurrenceListTest.cpp"
        "other/container/computeConnectedComponents/ComputeConnectedComponentsTest.cpp"

        # Type
        "other/type/arbitraryPrecisionInteger/custom/CustomArbitraryPrecisionIntegerTest.cpp"

        # Partitioning hypergraph
        "partitioningHypergraph/PartitioningHypergraphTest.cpp"

        # SAT solver
        "satSolver/minisat/MiniSatSolverTest.cpp"

        # Decision heuristic
        "decisionHeuristic/jeroslowWang/JeroslowWangDecisionHeuristicTest.cpp"
        "decisionHeuristic/literalCount/LiteralCountDecisionHeuristicTest.cpp"
        "decisionHeuristic/random/RandomDecisionHeuristicTest.cpp"
        "decisionHeuristic/upc/UpcDecisionHeuristicTest.cpp"
        "decisionHeuristic/vsads/VsadsDecisionHeuristicTest.cpp"
        "decisionHeuristic/vsids/VsidsDecisionHeuristicTest.cpp"

        # Cache
        "cache/CacheTest.cpp"

        # Caching scheme
        "cache/cachingScheme/CachingSchemeTest.cpp"
        "cache/cachingScheme/basic/BasicCachingSchemeTest.cpp"
        "cache/cachingScheme/cara/CaraCachingSchemeTest.cpp"
        "cache/cachingScheme/hybrid/HybridCachingSchemeTest.cpp"
        "cache/cachingScheme/none/NoneCachingSchemeTest.cpp"
        "cache/cachingScheme/standard/StandardCachingSchemeTest.cpp"

        # Cache cleaning strategy
        "cache/cacheCleaningStrategy/none/NoneCacheCleaningStrategyTest.cpp"
        "cache/cacheCleaningStrategy/sharpSat/SharpSatCacheCleaningStrategyTest.cpp"

        # Statistics
        "statistics/StatisticsTest.cpp")

copy_shmetis_windows(HydraTest)

set_target_properties(HydraTest PROPERTIES OUTPUT_NAME "HydraTest")

target_link_libraries(HydraTest PRIVATE HydraLibrary HydraTestLibrary)
