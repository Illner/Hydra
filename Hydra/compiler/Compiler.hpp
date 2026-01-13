#pragma once

#include <algorithm>
#include <atomic>
#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <utility>

#include "Hydra/cache/Cache.hpp"
#include "Hydra/cache/CacheRecordStructure.hpp"
#include "Hydra/cache/cacheCleaningStrategy/CacheCleaningStrategyAbstract.hpp"
#include "Hydra/cache/cacheCleaningStrategy/cara/CaraCacheCleaningStrategy.hpp"
#include "Hydra/cache/cacheCleaningStrategy/none/NoneCacheCleaningStrategy.hpp"
#include "Hydra/cache/cacheCleaningStrategy/sharpSat/SharpSatCacheCleaningStrategy.hpp"
#include "Hydra/cache/cachingScheme/CachingSchemeAbstract.hpp"
#include "Hydra/cache/cachingScheme/basic/BasicCachingScheme.hpp"
#include "Hydra/cache/cachingScheme/cara/CaraCachingScheme.hpp"
#include "Hydra/cache/cachingScheme/hybrid/HybridCachingScheme.hpp"
#include "Hydra/cache/cachingScheme/none/NoneCachingScheme.hpp"
#include "Hydra/cache/cachingScheme/standard/StandardCachingScheme.hpp"
#include "Hydra/circuit/Circuit.hpp"
#include "Hydra/decisionHeuristic/DecisionHeuristicAbstract.hpp"
#include "Hydra/decisionHeuristic/jeroslowWang/JeroslowWangDecisionHeuristic.hpp"
#include "Hydra/decisionHeuristic/literalCount/LiteralCountDecisionHeuristic.hpp"
#include "Hydra/decisionHeuristic/random/RandomDecisionHeuristic.hpp"
#include "Hydra/decisionHeuristic/upc/UpcDecisionHeuristic.hpp"
#include "Hydra/decisionHeuristic/vsads/VsadsDecisionHeuristic.hpp"
#include "Hydra/decisionHeuristic/vsids/VsidsDecisionHeuristic.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/computeConnectedComponents/ConnectedComponentStructure.hpp"
#include "Hydra/other/operatingSystem/OperatingSystem.hpp"
#include "Hydra/partitioningHypergraph/PartitioningHypergraphAbstract.hpp"
#include "Hydra/partitioningHypergraph/cara/CaraPartitioningHypergraph.hpp"
#include "Hydra/partitioningHypergraph/hmetis/HmetisPartitioningHypergraph.hpp"
#include "Hydra/partitioningHypergraph/kahypar/KahyparPartitioningHypergraph.hpp"
#include "Hydra/partitioningHypergraph/patoh/PatohPartitioningHypergraph.hpp"
#include "Hydra/satSolver/EquivalencePreprocessingStructure.hpp"
#include "Hydra/satSolver/SatSolverAbstract.hpp"
#include "Hydra/satSolver/cadical/CadicalSolver.hpp"
#include "Hydra/satSolver/minisat/MiniSatSolver.hpp"
#include "Hydra/statistics/Statistics.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/cache/cacheCleaningStrategy/enums/CacheCleaningStrategyTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/CachingSchemeTypeEnum.hpp"
#include "Hydra/cache/enums/CacheTypeEnum.hpp"
#include "Hydra/circuit/enums/CircuitTypeEnum.hpp"
#include "Hydra/circuit/node/enums/DecomposabilityTypeEnum.hpp"
#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/compiler/enums/PartitioningHypergraphTypeEnum.hpp"
#include "Hydra/compiler/enums/RecomputingHypergraphCutTypeEnum.hpp"
#include "Hydra/decisionHeuristic/enums/DecisionHeuristicTypeEnum.hpp"
#include "Hydra/satSolver/enums/SatSolverTypeEnum.hpp"

#include "Hydra/compiler/Compiler.hxx"
#include "Hydra/compiler/Compiler.tpp"

namespace Hydra {

    using IdNodeType = Hydra::Circuit::IdNodeType;
    using LargeNumberType = Hydra::Circuit::LargeNumberType;

    /**
     * Compiler representation
     * Copy methods are disabled! Move methods (default) are allowed!
     * Exception:
     *      TimeoutException
     *      CircuitHasNotYetBeenCompiledException
     *      OperatingSystemIsNotSupportedException
     *      CompilingIntoCircuitTypeIsNotSupportedException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class Compiler {
        static_assert(Formula::Literal<VarT, LiteralT>::isValidVarT::value, "Invalid VarT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidLiteralT::value, "Invalid LiteralT type!");
        static_assert(Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isValidClauseT::value, "Invalid ClauseIdT type!");

    public:
        using NumberOfModelsType = typename Circuit::Circuit<VarT, LiteralT>::NumberOfModelsType;

    private:
        #if defined(BELLA_COMPILER)
        using ComponentCacheValueType = IdNodeType;
        #elif defined(CARA_SOLVER)
        using ComponentCacheValueType = NumberOfModelsType;
        #endif

    private:
        using HypergraphCutCacheValueType = typename Formula::Literal<VarT, LiteralT>::VariableVectorType;

    private:
        using FormulaType = typename Circuit::Circuit<VarT, LiteralT>::FormulaType;
        using LiteralType = typename Formula::Literal<VarT, LiteralT>::LiteralType;
        using StatisticsPtrType = typename Statistics::Statistics::StatisticsPtrType;
        using LiteralSetType = typename Formula::Literal<VarT, LiteralT>::LiteralSetType;
        using VariableSetType = typename Formula::Literal<VarT, LiteralT>::VariableSetType;
        using IdNodeVectorType = typename Circuit::Circuit<VarT, LiteralT>::IdNodeVectorType;
        using LiteralVectorType = typename Formula::Literal<VarT, LiteralT>::LiteralVectorType;
        using VariableVectorType = typename Formula::Literal<VarT, LiteralT>::VariableVectorType;
        using CompilerStatisticsPtrType = typename CompilerStatistics::CompilerStatisticsPtrType;
        using OriginalLiteralSetType = typename Formula::Literal<VarT, LiteralT>::OriginalLiteralSetType;
        using OriginalVariableSetType = typename Formula::Literal<VarT, LiteralT>::OriginalVariableSetType;
        using LiteralSortedVectorType = typename Formula::Literal<VarT, LiteralT>::LiteralSortedVectorType;
        using VariableSortedVectorType = typename Formula::Literal<VarT, LiteralT>::VariableSortedVectorType;
        using MappingFromVariableToLiteralType = typename Formula::Literal<VarT, LiteralT>::MappingFromVariableToLiteralType;
        using MappingFromVariableToVariableType = typename Formula::Literal<VarT, LiteralT>::MappingFromVariableToVariableType;
        using ClauseIdSetType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdSetType;
        using MappingFromVariableToOriginalVariableType = typename Formula::Literal<VarT, LiteralT>::MappingFromVariableToOriginalVariableType;
        using MappingFromOriginalVariableToVariableType = typename Formula::Literal<VarT, LiteralT>::MappingFromOriginalVariableToVariableType;
        using ClauseIdVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using FormulaRepresentationAbstractPtrType = typename Cache::CacheRecordStruct<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;
        using ConnectedComponentType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ConnectedComponentType;
        using ClauseIdReusableVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdReusableVectorType;
        using VariableReusableVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableReusableVectorType;
        using CacheValuePtrAndIdPairOptionalComponentCachingType = typename Cache::Cache<VarT, LiteralT, ClauseIdT, ComponentCacheValueType>::CacheValuePtrAndIdPairOptionalType;
        using PureVariableRemovedClausesVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::PureVariableRemovedClausesVectorType;
        using CacheValuePtrAndIdPairOptionalHypergraphCutCachingType = typename Cache::Cache<VarT, LiteralT, ClauseIdT, HypergraphCutCacheValueType>::CacheValuePtrAndIdPairOptionalType;

    private:
        using CacheRecordStruct = Cache::CacheRecordStruct<VarT, LiteralT, ClauseIdT>;
        using EquivalencePreprocessingStruct = typename SatSolver::SatSolverAbstract<VarT, LiteralT, ClauseIdT>::EquivalencePreprocessingStruct;
        using ConnectedComponentStruct = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ConnectedComponentStruct;

    private:
        using AtomicBoolPtrType = const std::atomic<bool>*;
        using EquivalencePreprocessingStructPtrType = const EquivalencePreprocessingStruct*;

    public:
        using CircuitPtrType = Circuit::Circuit<VarT, LiteralT>*;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        // Cache
    private:
        using ComponentCacheType = Cache::Cache<VarT, LiteralT, ClauseIdT, ComponentCacheValueType>;
        using ComponentCacheUniquePtrType = std::unique_ptr<ComponentCacheType>;
        using HypergraphCutCacheType = Cache::Cache<VarT, LiteralT, ClauseIdT, HypergraphCutCacheValueType>;
        using HypergraphCutCacheUniquePtrType = std::unique_ptr<HypergraphCutCacheType>;

        // Cache cleaning strategy
    private:
        template <typename CacheValueT>
        using NoneCacheCleaningStrategyType = Cache::CacheCleaningStrategy::None::NoneCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>;
        template <typename CacheValueT>
        using CaraCacheCleaningStrategyType = Cache::CacheCleaningStrategy::Cara::CaraCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>;
        template <typename CacheValueT>
        using SharpSatCacheCleaningStrategyType = Cache::CacheCleaningStrategy::SharpSat::SharpSatCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>;
        template <typename CacheValueT>
        using CacheCleaningStrategyAbstractUniquePtrType = std::unique_ptr<Cache::CacheCleaningStrategy::CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>>;

        // Caching scheme
    private:
        using NoneCachingSchemeType = Cache::CachingScheme::None::NoneCachingScheme<VarT, LiteralT, ClauseIdT>;
        using CaraCachingSchemeType = Cache::CachingScheme::Cara::CaraCachingScheme<VarT, LiteralT, ClauseIdT>;
        using BasicCachingSchemeType = Cache::CachingScheme::Basic::BasicCachingScheme<VarT, LiteralT, ClauseIdT>;
        using HybridCachingSchemeType = Cache::CachingScheme::Hybrid::HybridCachingScheme<VarT, LiteralT, ClauseIdT>;
        using StandardCachingSchemeType = Cache::CachingScheme::Standard::StandardCachingScheme<VarT, LiteralT, ClauseIdT>;
        using CachingSchemeAbstractUniquePtrType = std::unique_ptr<Cache::CachingScheme::CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>>;

        // Circuit
    private:
        using CircuitType = Circuit::Circuit<VarT, LiteralT>;
        using CircuitUniquePtrType = std::unique_ptr<CircuitType>;

        // SAT solver
    private:
        using MiniSatSolverType = SatSolver::MiniSat::MiniSatSolver<VarT, LiteralT, ClauseIdT>;
        using CadicalSolverType = SatSolver::Cadical::CadicalSolver<VarT, LiteralT, ClauseIdT>;
        using SatSolverAbstractUniquePtrType = std::unique_ptr<SatSolver::SatSolverAbstract<VarT, LiteralT, ClauseIdT>>;

        // Decision heuristic
    private:
        using UpcDecisionHeuristicType = DecisionHeuristic::Upc::UpcDecisionHeuristic<VarT, LiteralT, ClauseIdT>;
        using VsadsDecisionHeuristicType = DecisionHeuristic::Vsads::VsadsDecisionHeuristic<VarT, LiteralT, ClauseIdT>;
        using VsidsDecisionHeuristicType = DecisionHeuristic::Vsids::VsidsDecisionHeuristic<VarT, LiteralT, ClauseIdT>;
        using RandomDecisionHeuristicType = DecisionHeuristic::Random::RandomDecisionHeuristic<VarT, LiteralT, ClauseIdT>;
        using JeroslowWangDecisionHeuristicType = DecisionHeuristic::JeroslowWang::JeroslowWangDecisionHeuristic<VarT, LiteralT, ClauseIdT>;
        using LiteralCountDecisionHeuristicType = DecisionHeuristic::LiteralCount::LiteralCountDecisionHeuristic<VarT, LiteralT, ClauseIdT>;
        using DecisionHeuristicAbstractUniquePtrType = std::unique_ptr<DecisionHeuristic::DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>>;

        // Partitioning hypergraph
    private:
        using PatohPartitioningHypergraphType = PartitioningHypergraph::Patoh::PatohPartitioningHypergraph<VarT, LiteralT, ClauseIdT>;
        using HmetisPartitioningHypergraphType = PartitioningHypergraph::Hmetis::HmetisPartitioningHypergraph<VarT, LiteralT, ClauseIdT>;
        using KahyparPartitioningHypergraphType = PartitioningHypergraph::Kahypar::KahyparPartitioningHypergraph<VarT, LiteralT, ClauseIdT>;
        using CaraPartitioningHypergraphType = PartitioningHypergraph::Cara::CaraPartitioningHypergraph<VarT, LiteralT, ClauseIdT, ComponentCacheValueType>;
        using PartitioningHypergraphAbstractUniquePtrType = std::unique_ptr<PartitioningHypergraph::PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>>;

    private:
        using CacheTypeEnum = Cache::CacheTypeEnum;
        using CircuitTypeEnum = Circuit::CircuitTypeEnum;
        using SatSolverTypeEnum = SatSolver::SatSolverTypeEnum;
        using DecomposabilityTypeEnum = Circuit::Node::DecomposabilityTypeEnum;
        using CachingSchemeTypeEnum = Cache::CachingScheme::CachingSchemeTypeEnum;
        using DecisionHeuristicTypeEnum = DecisionHeuristic::DecisionHeuristicTypeEnum;
        using CacheCleaningStrategyTypeEnum = Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum;

    public:
        Compiler(FormulaRepresentationAbstractUniquePtrType&& formulaRepresentationAbstractUniquePtr, const CompilerConfiguration& configuration,
                 StatisticsPtrType statisticsPtr = nullptr, AtomicBoolPtrType killedByMainThread = nullptr)
            : configuration_(configuration), ignorePureLiteralType_(IgnorePureLiteralTypeEnum::NONE),
              componentCacheUniquePtr_(nullptr), satSolverAbstractUniquePtr_(nullptr), hypergraphCutCacheUniquePtr_(nullptr),
              decisionHeuristicAbstractUniquePtr_(nullptr), formulaRepresentationAbstractUniquePtr_(std::move(formulaRepresentationAbstractUniquePtr)),
              partitioningHypergraphAbstractUniquePtr_(nullptr),
              statisticsPtr_(statisticsPtr), compilerStatisticsPtr_(statisticsPtr ? statisticsPtr->getCompilerStatisticsPtr() : nullptr),
              killedByMainThread_(killedByMainThread) {
            #if defined(CARA_SOLVER)
            assert(statisticsPtr == nullptr);        // no statistics
            assert(killedByMainThread == nullptr);   // no threads

            // Brute-force approach
            assert(configuration_.numberOfClausesThresholdForBruteForceApproach <= S_MAX_NUMBER_OF_CLAUSES_FOR_BRUTE_FORCE_APPROACH_);
            assert(configuration_.numberOfVariablesThresholdForBruteForceApproach <= S_MAX_NUMBER_OF_VARIABLES_FOR_BRUTE_FORCE_APPROACH_);
            #endif

            assert(configuration_.percentageThresholdOfImmenseUnitPropagationRecomputingHypergraphCut >= 0 && configuration_.percentageThresholdOfImmenseUnitPropagationRecomputingHypergraphCut <= 1);

            // Statistics
            if (compilerStatisticsPtr_)
                compilerStatisticsPtr_->initializeTimer.startStopwatch();

            // Ignore upper bound limit for computing hypergraph cut
            if (configuration_.tooManyVariablesForComputingHypergraphCut == 0) {
                VarT numberOfVariablesInOriginalFormula = formulaRepresentationAbstractUniquePtr_->getNumberOfVariablesInOriginalFormula();

                if (!Other::unsignedValueCanBeSavedAsStdSizeT<VarT>(numberOfVariablesInOriginalFormula))
                    configuration_.tooManyVariablesForComputingHypergraphCut = std::numeric_limits<std::size_t>::max();
                else
                    configuration_.tooManyVariablesForComputingHypergraphCut = static_cast<std::size_t>(numberOfVariablesInOriginalFormula);
            }

            #if defined(BELLA_COMPILER)
            // Set smoothness
            if (Other::containInSet(Circuit::smoothCircuitTypeSet, configuration_.circuitType))
                smoothness_ = true;

            // Sharing variables is allowed
            if (Other::containInSet(Circuit::sharingVariablesCircuitTypeSet, configuration_.circuitType)) {
                sharingVariables_ = true;

                switch (configuration_.circuitType) {
                    case CircuitTypeEnum::wDNNF:
                    case CircuitTypeEnum::Bella:
                    case CircuitTypeEnum::Krom_Bella:
                        ignorePureLiteralType_ = IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE;
                        bellaFormulaDecomposabilityType_ = DecomposabilityTypeEnum::BELLA_DECOMPOSABILITY;
                        break;
                    case CircuitTypeEnum::pwDNNF:
                    case CircuitTypeEnum::posBella:
                        ignorePureLiteralType_ = IgnorePureLiteralTypeEnum::ONLY_POSITIVE;
                        bellaFormulaDecomposabilityType_ = DecomposabilityTypeEnum::posBELLA_DECOMPOSABILITY;
                        break;
                    case CircuitTypeEnum::nwDNNF:
                    case CircuitTypeEnum::negBella:
                        ignorePureLiteralType_ = IgnorePureLiteralTypeEnum::ONLY_NEGATIVE;
                        bellaFormulaDecomposabilityType_ = DecomposabilityTypeEnum::negBELLA_DECOMPOSABILITY;
                        break;
                    default:
                        throw Exception::NotImplementedException(Circuit::circuitTypeEnumToString(configuration_.circuitType),
                                                                 "Hydra::Compiler::constructor");
                }
            }
            #endif

            #if defined(BELLA_COMPILER)
            // Circuit
            initializeCircuit();
            assert(circuitUniquePtr_);   // circuit pointer is set

            trueLeafIdNode_ = circuitUniquePtr_->createConstantLeaf(true);
            falseLeafIdNode_ = circuitUniquePtr_->createConstantLeaf(false);
            #endif

            // Component cache
            initializeComponentCache();
            assert(componentCacheUniquePtr_);   // component cache pointer is set

            // Hypergraph cut cache
            initializeHypergraphCutCache();
            assert(hypergraphCutCacheUniquePtr_);   // hypergraph cut cache pointer is set

            // SAT solver
            initializeSatSolver();
            assert(satSolverAbstractUniquePtr_);   // SAT solver pointer is set

            // Decision heuristic
            initializeDecisionHeuristic();
            assert(decisionHeuristicAbstractUniquePtr_);   // decision heuristic pointer is set

            // Partitioning hypergraph
            initializePartitioningHypergraph();
            assert(partitioningHypergraphAbstractUniquePtr_);   // partitioning hypergraph pointer is set

            // Statistics - initialization
            if (compilerStatisticsPtr_) {
                compilerStatisticsPtr_->numberOfSplitsIncrement.setNumber(static_cast<Statistics::LargeNumberType>(0));
                compilerStatisticsPtr_->numberOfDecisionsIncrement.setNumber(static_cast<Statistics::LargeNumberType>(0));
                compilerStatisticsPtr_->numberOfEmptyResidualFormulaeIncrement.setNumber(static_cast<Statistics::LargeNumberType>(0));
                compilerStatisticsPtr_->numberOfUnsatisfiableResidualFormulaeIncrement.setNumber(static_cast<Statistics::LargeNumberType>(0));
            }

            // Statistics
            if (compilerStatisticsPtr_)
                compilerStatisticsPtr_->initializeTimer.stopStopwatch();
        }

        Compiler(const Compiler&) = delete;
        Compiler(Compiler&&) noexcept = default;

        Compiler& operator=(const Compiler&) = delete;
        Compiler& operator=(Compiler&&) noexcept = default;

    #if defined(BELLA_COMPILER)
    private:
        bool isCompiled_ = false;
        bool smoothness_ = false;         // because of free variables
        bool sharingVariables_ = false;   // sharing variables is allowed/forbidden
        DecomposabilityTypeEnum bellaFormulaDecomposabilityType_ = DecomposabilityTypeEnum::NONE;

        IdNodeType trueLeafIdNode_;
        IdNodeType falseLeafIdNode_;
        CircuitUniquePtrType circuitUniquePtr_ = nullptr;
    #endif

    #if defined(CARA_SOLVER)
    private:
        bool isNumberOfModelsComputed_ = false;

        NumberOfModelsType numberOfModels_ = NumberOfModelsType("0");

        // Local auxiliary data structures for computeNumberOfModelsUsingBruteForceApproach(AndSingletonAwareMethod)
        mutable bool l_firstCall_computeNumberOfModelsUsingBruteForceApproach_ = true;
        mutable VariableVectorType l_variableToIndexVectorMapping_computeNumberOfModelsUsingBruteForceApproach_;
        mutable ClauseIdReusableVectorType l_clauseIdReusableVector_computeNumberOfModelsUsingBruteForceApproach_;

        // Local auxiliary data structures for computeNumberOfModelsUsingBruteForceApproachAndSingletonAwareMethod
        mutable bool l_firstCall_computeNumberOfModelsUsingBruteForceApproachAndSingletonAwareMethod_ = true;
        mutable VariableReusableVectorType l_numberOfSingletonVariablesInClauseReusableVector_computeNumberOfModelsUsingBruteForceApproachAndSingletonAwareMethod_;

        inline static const NumberOfModelsType ONE_MODEL_ = NumberOfModelsType("1");
        inline static const NumberOfModelsType ZERO_MODELS_ = NumberOfModelsType("0");
        inline static constexpr VarT S_MAX_NUMBER_OF_VARIABLES_FOR_BRUTE_FORCE_APPROACH_ = 20;
        inline static constexpr ClauseIdT S_MAX_NUMBER_OF_CLAUSES_FOR_BRUTE_FORCE_APPROACH_ = 20;
    #endif

    private:
        CompilerConfiguration configuration_;
        IgnorePureLiteralTypeEnum ignorePureLiteralType_;

    private:
        ComponentCacheUniquePtrType componentCacheUniquePtr_;
        SatSolverAbstractUniquePtrType satSolverAbstractUniquePtr_;
        HypergraphCutCacheUniquePtrType hypergraphCutCacheUniquePtr_;
        DecisionHeuristicAbstractUniquePtrType decisionHeuristicAbstractUniquePtr_;
        FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr_;
        PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphAbstractUniquePtr_;

        StatisticsPtrType statisticsPtr_;
        CompilerStatisticsPtrType compilerStatisticsPtr_;

    private:
        AtomicBoolPtrType killedByMainThread_;   // true if the timeout has expired

    #if defined(BELLA_COMPILER)
    private:
        /**
         * Initialize the circuit
         * The supported circuit types are defined in supportCompilationCircuitTypeSet
         * @throw CompilingIntoCircuitTypeIsNotSupportedException if the circuit type is not supported
         */
        void initializeCircuit();

        /**
         * Compile the pure clauses
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param pureClauseSet a set of pure clauses
         * @return the identifier of a root representing the conjunction of the compiled pure clauses
         */
        IdNodeType compilePureClauses(const VariableSetType& currentComponentVariableSet, const ClauseIdSetType& pureClauseSet);
    #endif

    #if defined(CARA_SOLVER)
    private:
        /**
         * Compute 2 raised to the given exponent (that is, 2^exponent)
         * Note: used for free variables and missing variables
         * @param exponent an exponent
         * @return 2^exponent
         */
        NumberOfModelsType computePowerOfTwo(std::size_t exponent) const;
    #endif

    private:
        /**
         * Initialize the component cache
         */
        void initializeComponentCache();

        /**
         * Initialize the hypergraph cut cache
         */
        void initializeHypergraphCutCache();

        /**
         * Initialize the SAT solver
         */
        void initializeSatSolver();

        /**
         * Initialize the decision heuristic
         */
        void initializeDecisionHeuristic();

        /**
         * Initialize the partitioning hypergraph
         * Supported operating systems: Linux, macOS, and Windows
         * @throw OperatingSystemIsNotSupportedException if this operating system is not supported
         */
        void initializePartitioningHypergraph();

        /**
         * Check if a new hypergraph cut should be computed
         * @param restrictedHypergraphCut the current RESTRICTED hypergraph cut
         * @param unrestrictedHypergraphCut the current UNRESTRICTED hypergraph cut
         * @param split is the current formula split
         * @param numberOfVariablesBeforeUnitPropagation the number of variables before the unit propagation was performed
         * @param numberOfVariablesAfterUnitPropagation the number of variables after the unit propagation was performed
         * @return true if a new hypergraph cut should be computed. Otherwise, false is returned.
         */
        bool shouldHypergraphCutBeRecomputed(const VariableSetType& restrictedHypergraphCut, const VariableSetType& unrestrictedHypergraphCut,
                                             bool split, VarT numberOfVariablesBeforeUnitPropagation, VarT numberOfVariablesAfterUnitPropagation) const;

        /**
         * Compile the current formula as a single component
         * Assert: the current formula MUST be satisfiable
         * Assert: the current formula MUST have only one component
         * Note: DECLARED BUT NOT DEFINED FUNCTION
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param hypergraphCut the current hypergraph cut
         * @param equivalencePreprocessingStructPtr a pointer to an equivalence preprocessing structure (can be nullptr)
         * @param computeNewHypergraphCut should a new hypergraph cut be computed
         * @return
         *      Bella: the identifier of a root representing the current formula
         *      Cara: the number of models of the current formula
         */
        ComponentCacheValueType compileOneComponent(VariableSetType& currentComponentVariableSet, VariableSetType&& hypergraphCut,
                                                    EquivalencePreprocessingStructPtrType equivalencePreprocessingStructPtr, bool computeNewHypergraphCut);

        /**
         * Compile the current formula
         *      1) check satisfiability
         *      2) get implied literals
         *      3) get connected components
         *      4) for each connected component, calls compileOneComponent
         * Note: DECLARED BUT NOT DEFINED FUNCTION
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param hypergraphCut the current hypergraph cut
         * @return
         *      Bella: the identifier of a root representing the current formula
         *      Cara: the number of models of the current formula
         * @throw TimeoutException if the timeout has expired
         */
        ComponentCacheValueType compileMoreComponents(VariableSetType& currentComponentVariableSet, const VariableSetType& hypergraphCut,
                                                      EquivalencePreprocessingStructPtrType equivalencePreprocessingStructPtr = nullptr, bool firstCall = false);

        /**
         * Assign the literals in the formula representation and SAT solver
         * Assert: the variables MUST NOT be free
         * Assert: the variables MUST NOT be assigned
         * Assert: the variables MUST be in the current component
         * @param literalVector literals that will be assigned
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param setLiteralsInSatSolver set the literals in the SAT solver
         * @return a vector of free variables
         */
        VariableVectorType assignLiteralVectorInFormulaAndSatSolver(const LiteralVectorType& literalVector, VariableSetType& currentComponentVariableSet,
                                                                    bool setLiteralsInSatSolver = true);

        /**
         * Unassign the literals in the formula representation and SAT solver
         * Assert: the variables MUST be assigned
         * Assert: the variables MUST NOT be in the current component
         * @param literalVector literals that will be unassigned
         * @param currentComponentVariableSet a set of variables appearing in the current component
         */
        void unassignLiteralVectorInFormulaAndSatSolver(const LiteralVectorType& literalVector, VariableSetType& currentComponentVariableSet);

    #if defined(BELLA_COMPILER)
    public:
        /**
         * Getter
         * @return true if the circuit has been compiled. Otherwise, false is returned.
         */
        bool isCircuitCompiled() const noexcept;

        /**
         * @return a pointer to the compiled circuit
         * @throw CircuitHasNotYetBeenCompiledException if the circuit has not yet been compiled
         */
        CircuitPtrType getCompiledCircuitPtr() const;

        /**
         * Compile the formula into a circuit of the particular circuit type
         */
        void compile();
    #endif

    #if defined(CARA_SOLVER)
    public:
        /**
         * Getter
         * @return true if the number of models has been computed. Otherwise, false is returned.
         */
        bool isNumberOfModelsComputed() const noexcept;

        /**
         * @return the number of models of the formula
         * @throw NumberOfModelsHasNotYetBeenComputedException if the number of models has not yet been computed
         */
        const NumberOfModelsType& getComputedNumberOfModels() const;

        /**
         * Compute the number of models of the formula
         */
        void computeNumberOfModels();

        /**
         * Use the brute-force approach to compute the number of models
         * Assert: the number of clauses MUST NOT be more than S_MAX_NUMBER_OF_CLAUSES_FOR_BRUTE_FORCE_APPROACH_
         * Assert: the number of variables MUST NOT be more than S_MAX_NUMBER_OF_VARIABLES_FOR_BRUTE_FORCE_APPROACH_
         * Local auxiliary data structures:
         *      l_firstCall_computeNumberOfModelsUsingBruteForceApproach_
         *      l_clauseIdReusableVector_computeNumberOfModelsUsingBruteForceApproach_
         *      l_variableToIndexVectorMapping_computeNumberOfModelsUsingBruteForceApproach_
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @return the number of models
         */
        NumberOfModelsType computeNumberOfModelsUsingBruteForceApproach(const VariableSetType& currentComponentVariableSet) const;

        /**
         * Use the brute-force approach with the singleton-aware method to compute the number of models
         * Assert: the number of clauses MUST NOT be more than S_MAX_NUMBER_OF_CLAUSES_FOR_BRUTE_FORCE_APPROACH_
         * Assert: the number of non-singleton variables MUST NOT be more than S_MAX_NUMBER_OF_VARIABLES_FOR_BRUTE_FORCE_APPROACH_
         * Local auxiliary data structures:
         *      l_firstCall_computeNumberOfModelsUsingBruteForceApproach_
         *      l_clauseIdReusableVector_computeNumberOfModelsUsingBruteForceApproach_
         *      l_variableToIndexVectorMapping_computeNumberOfModelsUsingBruteForceApproach_
         *      l_firstCall_computeNumberOfModelsUsingBruteForceApproachAndSingletonAwareMethod_
         *      l_numberOfSingletonVariablesInClauseReusableVector_computeNumberOfModelsUsingBruteForceApproachAndSingletonAwareMethod_
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @return the number of models
         */
        NumberOfModelsType computeNumberOfModelsUsingBruteForceApproachAndSingletonAwareMethod(const VariableSetType& currentComponentVariableSet) const;
    #endif

    public:
        /**
         * @return a pointer to the formula representation
         */
        FormulaRepresentationAbstractPtrType getFormulaPtr() const noexcept;

        /**
         * Note: nullptr is returned if statistics are not used
         * @return a pointer to the statistics
         */
        StatisticsPtrType getStatisticsPtr() const noexcept;

    #ifndef NDEBUG
    public:
        void printCompilerDebug(std::ostream& out);
    #endif
    };
}   // namespace Hydra

#include "./Compiler.ipp"

#if defined(BELLA_COMPILER)
    #include "Bella/compiler/Compiler.ipp"
#elif defined(CARA_SOLVER)
    #include "Cara/sharpSolver/BruteForceApproach.ipp"
    #include "Cara/sharpSolver/SharpSolver.ipp"
#endif
