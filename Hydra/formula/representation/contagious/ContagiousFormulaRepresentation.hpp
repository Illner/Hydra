#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>
#include <string>
#include <vector>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/computeConnectedComponents/ComputeConnectedComponents.hpp"
#include "Hydra/other/container/contagiousOccurrenceList/ContagiousOccurrenceList.hpp"
#include "Hydra/other/container/fixedVector/FixedVector.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"
#include "Hydra/other/parser/Parser.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/cache/cachingScheme/enums/OmitClauseTypeEnum.hpp"
#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/formula/enums/ClauseStatusEnum.hpp"
#include "Hydra/formula/enums/FormulaRepresentationTypeEnum.hpp"
#include "Hydra/partitioningHypergraph/enums/VertexWeightTypeEnum.hpp"

#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.tpp"

namespace Hydra::Formula::Representation::Contagious {

    /**
     * Note: used for tests
     * @return literalNumberOfOccurrences for the formula
     */
    template <typename VarT2, typename LiteralT2, typename ClauseIdT2>
    inline std::vector<ClauseIdT2> createLiteralNumberOfOccurrences(VarT2 numberOfVariables,
                                                                    const std::vector<Literal<VarT2, LiteralT2>>& formula) noexcept;

    /**
     * Note: used for tests
     * @return the number of clauses in the formula
     */
    template <typename VarT2, typename LiteralT2, typename ClauseIdT2>
    inline ClauseIdT2 getNumberOfClauses(const std::vector<Literal<VarT2, LiteralT2>>& formula) noexcept;

    /**
     * Contagious formula representation (final class)
     * Note: every clause will be sorted
     * Invariant: every clause MUST end with a zero literal
     * Invariant: every clause MUST contain at least one literal
     * Exceptions:
     *      AttemptToAddDuplicateOccurrenceException (debug)
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class ContagiousFormulaRepresentation final : public FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using LiteralType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using VectorSetType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VectorSetType;
        using ClauseSizeType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeType;
        using VariableSetType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using LiteralTSetType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralTSetType;
        using ClauseIdSetType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdSetType;
        using VertexWeightType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VertexWeightType;
        using LiteralVectorType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
        using VariableVectorType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
        using ClauseIdVectorType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using VariableVectorMapType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorMapType;
        using ClauseSizeCounterType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeCounterType;
        using ConnectedComponentType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ConnectedComponentType;
        using VertexWeightVectorType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VertexWeightVectorType;
        using ClauseOffsetVectorType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseOffsetVectorType;
        using VariableSortedVectorType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableSortedVectorType;
        using ClauseIdReusableVectorType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdReusableVectorType;
        using PureVariableRemovedClausesVectorType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::PureVariableRemovedClausesVectorType;
        using FormulaRepresentationStatisticsPtrType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationStatisticsPtrType;

    private:
        using ConnectedComponentStruct = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ConnectedComponentStruct;

    private:
        using ClauseSizeVectorType = std::vector<ClauseSizeType>;
        using VariableSetVectorType = std::vector<VariableSetType>;
        using ClauseIdWatcherVectorType = std::vector<ClauseSizeType>;
        using SubsumptionWatcherVectorType = std::vector<ClauseIdVectorType>;
        using FixedVectorType = Container::FixedVector::FixedVector<ClauseIdT>;
        using MappingFromVariableToVariableSetType = Other::HashMap::MapType<VarT, VariableSetType>;
        using ContagiousFormulaRepresentationPtrType = const ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>*;
        using ComputeConnectedComponentsType = Container::ComputeConnectedComponents::ComputeConnectedComponents<VarT, LiteralT>;
        using ContagiousOccurrenceListType = Container::ContagiousOccurrenceList::ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>;

    public:
        using FormulaType = std::vector<LiteralType>;

    private:
        using OmitClauseTypeEnum = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::OmitClauseTypeEnum;
        using VertexWeightTypeEnum = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VertexWeightTypeEnum;
        using ModelCountingTypeEnum = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ModelCountingTypeEnum;
        using IgnorePureLiteralTypeEnum = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::IgnorePureLiteralTypeEnum;

    private:
        struct ClauseSizeComparator {
        public:
            explicit ClauseSizeComparator(ContagiousFormulaRepresentationPtrType contagiousFormulaRepresentationPtr)
                : contagiousFormulaRepresentationPtr_(contagiousFormulaRepresentationPtr) { }

        private:
            ContagiousFormulaRepresentationPtrType contagiousFormulaRepresentationPtr_;

        public:
            /**
             * Clause size comparator
             * @param clauseId1 first clause ID
             * @param clauseId2 second clause ID
             * @return true if the size of clauseId1 < the size of clauseId2. Otherwise, false is returned.
             */
            bool operator()(ClauseIdT clauseId1, ClauseIdT clauseId2) const;
        };

        template <bool EqualityT, bool SameSizeT>
        struct ClauseComparator {
        public:
            explicit ClauseComparator(ContagiousFormulaRepresentationPtrType contagiousFormulaRepresentationPtr)
                : contagiousFormulaRepresentationPtr_(contagiousFormulaRepresentationPtr) { }

        private:
            ContagiousFormulaRepresentationPtrType contagiousFormulaRepresentationPtr_;

        public:
            /**
             * Clause (equal) comparator
             * Assert: if SameSizeT, the clauses MUST have the same size
             * @param clauseId1 first clause ID
             * @param clauseId2 second clause ID
             * @return
             *      EqualityT: true if the clauses are identical. Otherwise, false is returned.
             *      !EqualityT: true if clauseId1 < clauseId2. Otherwise, false is returned.
             */
            bool operator()(ClauseIdT clauseId1, ClauseIdT clauseId2) const;
        };

        template <bool EqualityT, bool SameSizeT>
        struct ClauseVariableComparator {
        public:
            explicit ClauseVariableComparator(ContagiousFormulaRepresentationPtrType contagiousFormulaRepresentationPtr)
                : contagiousFormulaRepresentationPtr_(contagiousFormulaRepresentationPtr) { }

        private:
            ContagiousFormulaRepresentationPtrType contagiousFormulaRepresentationPtr_;

        public:
            /**
             * Clause (equal) variable comparator
             * Assert: if SameSizeT, the clauses MUST have the same size
             * Note: only variables are considered, not literals
             * @param clauseId1 first clause ID
             * @param clauseId2 second clause ID
             * @return
             *      EqualityT: true if the clauses are identical. Otherwise, false is returned.
             *      !EqualityT: true if clauseId1 < clauseId2. Otherwise, false is returned.
             */
            bool operator()(ClauseIdT clauseId1, ClauseIdT clauseId2) const;
        };

    public:
        using ClauseComparatorFunctor = ClauseComparator<false, false>;
        using ClauseEqualComparatorFunctor = ClauseComparator<true, false>;
        using ClauseVariableComparatorFunctor = ClauseVariableComparator<false, false>;
        using ClauseEqualVariableComparatorFunctor = ClauseVariableComparator<true, false>;

        using SameClauseSizeComparatorFunctor = ClauseComparator<false, true>;
        using SameClauseSizeEqualComparatorFunctor = ClauseComparator<true, true>;
        using SameClauseSizeVariableComparatorFunctor = ClauseVariableComparator<false, true>;
        using SameClauseSizeEqualVariableComparatorFunctor = ClauseVariableComparator<true, true>;

    public:
        #ifndef NDEBUG
        ContagiousFormulaRepresentation(FormulaType&& formula, VarT numberOfVariables, ClauseIdT numberOfClauses,
                                        const ClauseIdVectorType& literalNumberOfOccurrences,
                                        const ContagiousFormulaRepresentationConfiguration& configuration = ContagiousFormulaRepresentationConfiguration(),
                                        FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr = nullptr)
            : FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>(FormulaRepresentationTypeEnum::CONTAGIOUS,
                                                                       static_cast<FormulaSizeType>(formula.size() - numberOfClauses),
                                                                       numberOfVariables, numberOfClauses,
                                                                       formulaRepresentationStatisticsPtr),
              originalFormula_(std::move(formula)), originalClauseSize_(), originalClauseOffset_(),
              l_clauseNeedsToBeDeactivatedVectorSet_processAddLiteralToPartialAssignment_(numberOfClauses),
              l_watchedVariableVector_processComputeConnectedComponents_(numberOfClauses, 0), l_computeConnectedComponents_processComputeConnectedComponents_(numberOfVariables),
              l_firstCall_getCurrentClauses_(true), l_addedClauseVectorSet_getCurrentClauses_(),
              l_firstCall_getCurrentComponentNotSubsumedClauses_(true), l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_(),
              l_firstCall_oneLiteralWatchingAlgorithmSubsumption_(true), l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_(),
              l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_(), l_firstCall_oneLiteralWatchingAlgorithmLiteralSubsumption_(true),
              l_forbiddenLiteralTSet_oneLiteralWatchingAlgorithmLiteralSubsumption_(), l_removeLiteralTSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmLiteralSubsumption_(),
              l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_(), l_firstCall_oneLiteralWatchingAlgorithmVariableSubsumption_(true),
              l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_(), l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_(),
              l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_(), configuration_(configuration), clauseIdWatcher_(),
              currentComponentClausesStack_(), currentComponentClausesFixedVector_(0, numberOfClauses), clauseNumberOfSatisfiedLiterals_(),
              clauseNumberOfUnsatisfiedLiterals_(), contagiousOccurrenceList_(numberOfClauses, literalNumberOfOccurrences),
              numberOfPositiveLiteralsInClauseVector_(), numberOfNegativeLiteralsInClauseVector_(),
              d_currentComponentVariableSetStack_() {
            assert(originalFormula_.size() > 1);
            assert((LiteralT(2) + LiteralT(2) * static_cast<LiteralT>(numberOfVariables)) == static_cast<LiteralT>(literalNumberOfOccurrences.size()));

            initializeDataStructures();

            // d_currentComponentVariableSetStack_
            d_currentComponentVariableSetStack_.reserve(numberOfVariables);
            d_currentComponentVariableSetStack_.emplace_back(numberOfVariables);
            for (VarT var = 1; var <= numberOfVariables; ++var)
                d_currentComponentVariableSetStack_.back().emplace(var);
        }

        ContagiousFormulaRepresentation(const FormulaType& formula, VarT numberOfVariables, ClauseIdT numberOfClauses,
                                        const ClauseIdVectorType& literalNumberOfOccurrences,
                                        const ContagiousFormulaRepresentationConfiguration& configuration = ContagiousFormulaRepresentationConfiguration(),
                                        FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr = nullptr)
            : FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>(FormulaRepresentationTypeEnum::CONTAGIOUS,
                                                                       static_cast<FormulaSizeType>(formula.size() - numberOfClauses),
                                                                       numberOfVariables, numberOfClauses,
                                                                       formulaRepresentationStatisticsPtr),
              originalFormula_(formula), originalClauseSize_(), originalClauseOffset_(),
              l_clauseNeedsToBeDeactivatedVectorSet_processAddLiteralToPartialAssignment_(numberOfClauses),
              l_watchedVariableVector_processComputeConnectedComponents_(numberOfClauses, 0), l_computeConnectedComponents_processComputeConnectedComponents_(numberOfVariables),
              l_firstCall_getCurrentClauses_(true), l_addedClauseVectorSet_getCurrentClauses_(),
              l_firstCall_getCurrentComponentNotSubsumedClauses_(true), l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_(),
              l_firstCall_oneLiteralWatchingAlgorithmSubsumption_(true), l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_(),
              l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_(), l_firstCall_oneLiteralWatchingAlgorithmLiteralSubsumption_(true),
              l_forbiddenLiteralTSet_oneLiteralWatchingAlgorithmLiteralSubsumption_(), l_removeLiteralTSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmLiteralSubsumption_(),
              l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_(), l_firstCall_oneLiteralWatchingAlgorithmVariableSubsumption_(true),
              l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_(), l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_(),
              l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_(), configuration_(configuration), clauseIdWatcher_(),
              currentComponentClausesStack_(), currentComponentClausesFixedVector_(0, numberOfClauses), clauseNumberOfSatisfiedLiterals_(),
              clauseNumberOfUnsatisfiedLiterals_(), contagiousOccurrenceList_(numberOfClauses, literalNumberOfOccurrences),
              numberOfPositiveLiteralsInClauseVector_(), numberOfNegativeLiteralsInClauseVector_(),
              d_currentComponentVariableSetStack_() {
            assert(originalFormula_.size() > 1);
            assert((LiteralT(2) + LiteralT(2) * static_cast<LiteralT>(numberOfVariables)) == static_cast<LiteralT>(literalNumberOfOccurrences.size()));

            initializeDataStructures();

            // d_currentComponentVariableSetStack_
            d_currentComponentVariableSetStack_.reserve(numberOfVariables);
            d_currentComponentVariableSetStack_.emplace_back(numberOfVariables);
            for (VarT var = 1; var <= numberOfVariables; ++var)
                d_currentComponentVariableSetStack_.back().emplace(var);
        }
        #else
        ContagiousFormulaRepresentation(FormulaType&& formula, VarT numberOfVariables, ClauseIdT numberOfClauses,
                                        const ClauseIdVectorType& literalNumberOfOccurrences,
                                        const ContagiousFormulaRepresentationConfiguration& configuration = ContagiousFormulaRepresentationConfiguration(),
                                        FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr = nullptr)
            : FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>(FormulaRepresentationTypeEnum::CONTAGIOUS,
                                                                       static_cast<FormulaSizeType>(formula.size() - numberOfClauses),
                                                                       numberOfVariables, numberOfClauses,
                                                                       formulaRepresentationStatisticsPtr),
              originalFormula_(std::move(formula)), originalClauseSize_(), originalClauseOffset_(),
              l_clauseNeedsToBeDeactivatedVectorSet_processAddLiteralToPartialAssignment_(numberOfClauses),
              l_watchedVariableVector_processComputeConnectedComponents_(numberOfClauses, 0), l_computeConnectedComponents_processComputeConnectedComponents_(numberOfVariables),
              l_firstCall_getCurrentClauses_(true), l_addedClauseVectorSet_getCurrentClauses_(),
              l_firstCall_getCurrentComponentNotSubsumedClauses_(true), l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_(),
              l_firstCall_oneLiteralWatchingAlgorithmSubsumption_(true), l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_(),
              l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_(), l_firstCall_oneLiteralWatchingAlgorithmLiteralSubsumption_(true),
              l_forbiddenLiteralTSet_oneLiteralWatchingAlgorithmLiteralSubsumption_(), l_removeLiteralTSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmLiteralSubsumption_(),
              l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_(), l_firstCall_oneLiteralWatchingAlgorithmVariableSubsumption_(true),
              l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_(), l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_(),
              l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_(), configuration_(configuration), clauseIdWatcher_(),
              currentComponentClausesStack_(), currentComponentClausesFixedVector_(0, numberOfClauses), clauseNumberOfSatisfiedLiterals_(),
              clauseNumberOfUnsatisfiedLiterals_(), contagiousOccurrenceList_(numberOfClauses, literalNumberOfOccurrences),
              numberOfPositiveLiteralsInClauseVector_(), numberOfNegativeLiteralsInClauseVector_() {
            initializeDataStructures();
        }

        ContagiousFormulaRepresentation(const FormulaType& formula, VarT numberOfVariables, ClauseIdT numberOfClauses,
                                        const ClauseIdVectorType& literalNumberOfOccurrences,
                                        const ContagiousFormulaRepresentationConfiguration& configuration = ContagiousFormulaRepresentationConfiguration(),
                                        FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr = nullptr)
            : FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>(FormulaRepresentationTypeEnum::CONTAGIOUS,
                                                                       static_cast<FormulaSizeType>(formula.size() - numberOfClauses),
                                                                       numberOfVariables, numberOfClauses,
                                                                       formulaRepresentationStatisticsPtr),
              originalFormula_(formula), originalClauseSize_(), originalClauseOffset_(),
              l_clauseNeedsToBeDeactivatedVectorSet_processAddLiteralToPartialAssignment_(numberOfClauses),
              l_watchedVariableVector_processComputeConnectedComponents_(numberOfClauses, 0), l_computeConnectedComponents_processComputeConnectedComponents_(numberOfVariables),
              l_firstCall_getCurrentClauses_(true), l_addedClauseVectorSet_getCurrentClauses_(),
              l_firstCall_getCurrentComponentNotSubsumedClauses_(true), l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_(),
              l_firstCall_oneLiteralWatchingAlgorithmSubsumption_(true), l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_(),
              l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_(), l_firstCall_oneLiteralWatchingAlgorithmLiteralSubsumption_(true),
              l_forbiddenLiteralTSet_oneLiteralWatchingAlgorithmLiteralSubsumption_(), l_removeLiteralTSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmLiteralSubsumption_(),
              l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_(), l_firstCall_oneLiteralWatchingAlgorithmVariableSubsumption_(true),
              l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_(), l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_(),
              l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_(), configuration_(configuration), clauseIdWatcher_(),
              currentComponentClausesStack_(), currentComponentClausesFixedVector_(0, numberOfClauses), clauseNumberOfSatisfiedLiterals_(),
              clauseNumberOfUnsatisfiedLiterals_(), contagiousOccurrenceList_(numberOfClauses, literalNumberOfOccurrences),
              numberOfPositiveLiteralsInClauseVector_(), numberOfNegativeLiteralsInClauseVector_() {
            initializeDataStructures();
        }
        #endif

    private:
        FormulaType originalFormula_;
        ClauseSizeType maxOriginalClauseSize_ = 0;
        ClauseSizeVectorType originalClauseSize_;
        ClauseOffsetVectorType originalClauseOffset_;

        // Local auxiliary data structures for processAddLiteralToPartialAssignment
        VectorSetType l_clauseNeedsToBeDeactivatedVectorSet_processAddLiteralToPartialAssignment_;

        // Local auxiliary data structures for processComputeConnectedComponents
        mutable VariableVectorType l_watchedVariableVector_processComputeConnectedComponents_;
        mutable ComputeConnectedComponentsType l_computeConnectedComponents_processComputeConnectedComponents_;

        // Local auxiliary data structures for getCurrentClauses
        mutable bool l_firstCall_getCurrentClauses_;
        mutable VectorSetType l_addedClauseVectorSet_getCurrentClauses_;

        // Local auxiliary data structures for get(Sorted)CurrentComponentNotSubsumedClauses
        mutable bool l_firstCall_getCurrentComponentNotSubsumedClauses_;
        mutable VectorSetType l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_;

        // Local auxiliary data structures for oneLiteralWatchingAlgorithm(Variable)Subsumption(WithMapping)
        mutable bool l_firstCall_oneLiteralWatchingAlgorithmSubsumption_;
        mutable VectorSetType l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_;
        mutable ClauseSizeVectorType l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_;

        // Local auxiliary data structures for oneLiteralWatchingAlgorithmSubsumption
        mutable bool l_firstCall_oneLiteralWatchingAlgorithmLiteralSubsumption_;
        mutable LiteralTSetType l_forbiddenLiteralTSet_oneLiteralWatchingAlgorithmLiteralSubsumption_;
        mutable VectorSetType l_removeLiteralTSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmLiteralSubsumption_;
        mutable SubsumptionWatcherVectorType l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_;

        // Local auxiliary data structures for oneLiteralWatchingAlgorithmVariableSubsumption(WithMapping)
        mutable bool l_firstCall_oneLiteralWatchingAlgorithmVariableSubsumption_;
        mutable VariableSetType l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_;
        mutable VectorSetType l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_;
        mutable SubsumptionWatcherVectorType l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_;

        ContagiousFormulaRepresentationConfiguration configuration_;

        // MUST BE MODIFIED WHILE MODIFYING THE FORMULA
        ClauseIdWatcherVectorType clauseIdWatcher_;   // used for components
        FormulaSizeType currentComponentFormulaSize_;
        ClauseIdVectorType currentComponentClausesStack_;
        FixedVectorType currentComponentClausesFixedVector_;
        ClauseSizeVectorType clauseNumberOfSatisfiedLiterals_;
        ClauseSizeVectorType clauseNumberOfUnsatisfiedLiterals_;
        ContagiousOccurrenceListType contagiousOccurrenceList_;
        ClauseSizeVectorType numberOfPositiveLiteralsInClauseVector_;
        ClauseSizeVectorType numberOfNegativeLiteralsInClauseVector_;

        inline static constexpr ClauseIdT S_ESTIMATED_NUMBER_OF_WATCHED_CLAUSES_FOR_SUBSUMPTION_ = 10;

    private:
        /**
         * Assert: the clauses MUST NOT be empty
         * Initialize the data structures:
         *      clauseIdWatcher_
         *      originalClauseSize_
         *      maxOriginalClauseSize_
         *      currentComponentFormulaSize_
         *      currentComponentClausesStack_
         *      clauseNumberOfSatisfiedLiterals_, clauseNumberOfUnsatisfiedLiterals_
         *      numberOfPositiveLiteralsInClauseVector_, numberOfNegativeLiteralsInClauseVector_
         *      originalClauseOffset_ - initialize the formula offsets based on the zero literals in the formula (originalFormula_)
         */
        void initializeDataStructures();

        /**
         * Sort the clauses in the reusable vector
         * Note: clauseIdReusableVector MUST be already filled
         * Note: first, the clauses are grouped by their sizes, and then, for each group, the clauses are sorted by their literals/variables
         * @param clauseIdReusableVector a reusable vector of clauses that will be sorted
         * @param considerOnlyVariables should be considered only variables, not literals
         */
        void sortClauseIdReusableVectorWithGroupingBySizes(ClauseIdReusableVectorType& clauseIdReusableVector, bool considerOnlyVariables) const;

        /**
         * Remove the duplicate clauses from the reusable vector
         * Note: clauseIdReusableVector MUST be already filled
         * Side effect: clauseIdReusableVector will be sorted if it has not already been sorted (!alreadySorted)
         * @param clauseIdReusableVector a reusable vector of clauses from which the duplicate clauses will be removed
         * @param considerOnlyVariables should be considered only variables, not literals
         * @param alreadySorted is clauseIdReusableVector already sorted
         */
        void removeDuplicateClausesFromClauseIdReusableVector(ClauseIdReusableVectorType& clauseIdReusableVector,
                                                              bool considerOnlyVariables, bool alreadySorted) const;

        /**
         * Note: clauseIdReusableVector will be cleared at the beginning
         * @param clauseIdReusableVector [output] a reusable vector that will be filled by SORTED current component clauses (currentComponentClausesFixedVector_) satisfying the requirements
         * @param removeDuplicateClauses should the duplicate clauses be removed
         * @param ignoredClauseVectorSet a vector set of clauses that are ignored. If the capacity of the vector set is zero, no clause is ignored.
         * @param considerOnlyVariables should be considered only variables, not literals
         * @param omitClauseType what clause type should be omitted
         */
        void sortClauses(ClauseIdReusableVectorType& clauseIdReusableVector, bool removeDuplicateClauses, const VectorSetType& ignoredClauseVectorSet,
                         bool considerOnlyVariables, OmitClauseTypeEnum omitClauseType) const;

        /**
         * Time complexity: O(|C|)
         * Assert: the clause MUST be unresolved
         * @param clauseId a clause ID
         * @param ignorePureLiteralType a type of ignored pure literals
         * @return the index of an unassigned literal in the clause.
         * If the clause contains only pure literals of the ignored type, the index of a random pure literal will be returned.
         */
        ClauseSizeType getIndexOfUnassignedLiteralInClause(ClauseIdT clauseId,
                                                           IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::NONE) const;

        /**
         * Try to update the watcher
         * Note: the new watcher MUST NOT be either assigned or ignored
         * Assert: the clause MUST be unresolved
         * @param clauseId a clause ID
         * @param ignorePureLiteralType a type of ignored pure literals
         * @return true if the watcher has been changed. Otherwise, false is returned.
         */
        bool updateClauseWatcher(ClauseIdT clauseId, IgnorePureLiteralTypeEnum ignorePureLiteralType);

        /**
         * Local auxiliary data structures:
         *      l_clauseNeedsToBeDeactivatedVectorSet_processAddLiteralToPartialAssignment_
         */
        void processAddLiteralToPartialAssignment(const LiteralType& lit, VariableVectorType& freeVariableVector,
                                                  bool firstAssignment, bool lastAssignment) override;

        void processRemoveLiteralFromPartialAssignment(const LiteralType& lit, VariableVectorType& unfreeVariableVector) override;

        void processAddClausesContainingOnlyPureLiteralsOfIgnoredType(const ClauseIdSetType& pureClauseSet) override;

        void processRemoveClausesContainingOnlyPureLiteralsOfIgnoredType(const ClauseIdSetType& pureClauseSet) override;

        /**
         * Local auxiliary data structures:
         *      l_watchedVariableVector_processComputeConnectedComponents_
         *      l_computeConnectedComponents_processComputeConnectedComponents_
         */
        ConnectedComponentType processComputeConnectedComponents(const VariableSetType& currentComponentVariableSet) const override;

        /**
         * Local auxiliary data structures:
         *      l_computeConnectedComponents_processComputeConnectedComponents_
         */
        ConnectedComponentType processComputeConnectedComponents(const VariableSetType& currentComponentVariableSet, ClauseIdSetType& pureClauseSet,
                                                                 IgnorePureLiteralTypeEnum ignorePureLiteralType) override;

        bool processIsCurrentComponentFormulaKromC(const VariableSetType& currentComponentVariableSet) const override;

        bool processIsCurrentComponentFormulaHornC(const VariableSetType& currentComponentVariableSet) const override;

        bool processIsCurrentComponentFormulaAntiHornC(const VariableSetType& currentComponentVariableSet) const override;

        void processSaveCurrentComponentFormulaToVector(const VariableSetType& currentComponentVariableSet,
                                                        LiteralVectorType& formula, ClauseOffsetVectorType& clauseOffsetVector, bool sort) const override;

    public:
        ClauseSizeType getMaxOriginalClauseSize() const noexcept override;

        const LiteralType& getLiteralAtPositionInClause(ClauseIdT clauseId, ClauseSizeType position) const override;

        ClauseStatusEnum getCurrentClauseStatus(ClauseIdT clauseId) const override;

        ClauseSizeType getCurrentClauseSize(ClauseIdT clauseId) const override;

        bool isClauseUntouched(ClauseIdT clauseId) const override;

        bool isLiteralInUnitClause(const LiteralType& lit) const override;

        bool isVariableFree(VarT var) const override;

        bool isVariableSingleton(VarT var) const override;

        ClauseIdT getNumberOfCurrentClauses(LiteralT literalT) const override;

        ClauseSizeCounterType getCurrentClauseSizeCounter(LiteralT literalT) const override;

        ClauseIdT getNumberOfCurrentBinaryClauses(LiteralT literalT) const override;

        FormulaSizeType getCurrentComponentFormulaSize(const VariableSetType& currentComponentVariableSet) const noexcept override;

        PureVariableRemovedClausesVectorType setNewComponent(const ConnectedComponentStruct& newConnectedComponentStruct,
                                                             IgnorePureLiteralTypeEnum ignorePureLiteralType) override;

        void popPreviousComponent(const ConnectedComponentStruct& currentConnectedComponentStruct,
                                  const PureVariableRemovedClausesVectorType& pureVariableRemovedClausesVector) override;

        ClauseIdT getNumberOfCurrentComponentClauses(const VariableSetType& currentComponentVariableSet) const noexcept override;

        void getCurrentComponentClauses(const VariableSetType& currentComponentVariableSet,
                                        ClauseIdReusableVectorType& clauseIdReusableVector, bool sortIds = false) const override;

        void getCurrentComponentNotDuplicateClauses(const VariableSetType& currentComponentVariableSet,
                                                    ClauseIdReusableVectorType& clauseIdReusableVector,
                                                    bool considerOnlyVariables = false, bool sortIds = false) const override;

        void getSortedCurrentComponentClauses(const VariableSetType& currentComponentVariableSet, ClauseIdReusableVectorType& clauseIdReusableVector,
                                              bool removeDuplicateClauses, bool considerOnlyVariables = false,
                                              OmitClauseTypeEnum omitClauseType = OmitClauseTypeEnum::NONE) const override;

        /**
         * Local auxiliary data structures:
         *      l_firstCall_getCurrentComponentNotSubsumedClauses_
         *      l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_
         */
        void getCurrentComponentNotSubsumedClauses(const VariableSetType& currentComponentVariableSet, ClauseIdReusableVectorType& clauseIdReusableVector,
                                                   VectorSetType& usedVariableVectorSet, bool fillUsedVariables,
                                                   bool considerOnlyVariables = false, bool sortIds = false) const override;

        /**
         * Local auxiliary data structures:
         *      l_firstCall_getCurrentComponentNotSubsumedClauses_
         *      l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_
         */
        void getSortedCurrentComponentNotSubsumedClauses(const VariableSetType& currentComponentVariableSet,
                                                         ClauseIdReusableVectorType& clauseIdReusableVector) const override;

        void getCurrentComponentClausesThatVariableSubsumeSomeClause(const VariableSetType& currentComponentVariableSet,
                                                                     VectorSetType& clauseThatVariableSubsumesSomeClauseVectorSet,
                                                                     const VariableVectorMapType& variableVectorMap,
                                                                     IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                                                     VertexWeightTypeEnum vertexWeightType,
                                                                     VertexWeightVectorType& vertexWeightVector) const override;

        void getCurrentClauses(const VariableSetType& currentComponentVariableSet, VarT var,
                               ClauseIdReusableVectorType& clauseIdReusableVector, const VectorSetType& ignoredClauseVectorSet) const override;

        /**
         * Local auxiliary data structures:
         *      l_firstCall_getCurrentClauses_
         *      l_addedClauseVectorSet_getCurrentClauses_
         */
        void getCurrentClauses(const VariableSetType& currentComponentVariableSet, const VariableVectorType& variableVector,
                               ClauseIdReusableVectorType& clauseIdReusableVector, const VectorSetType& ignoredClauseVectorSet) const override;

        VariableSetType getUnassignedVariablesInClause(ClauseIdT clauseId) const override;

        void printCurrentFormulaInDimacsCnfFormat(std::ostream& out, bool printProblemLine = true,
                                                  ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED) const override;

        void printSortedCurrentFormulaInDimacsCnfFormat(std::ostream& out,
                                                        bool removeDuplicateClauses = false, bool removeSubsumedClauses = false,
                                                        bool printProblemLine = true,
                                                        ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED) const override;

    private:
        /**
         * Time complexity: O(|C_2|)
         * Assert: the clauses MUST be unresolved
         * Note: if Clause_1 and Clause_2 are identical, then Clause_1 subsumes Clause_2
         * @param clauseId1 first clause ID
         * @param clauseId2 second clause ID
         * @return true if Clause_1 subsumes Clause_2 (that is, Clause_2 is subsumed by Clause_1). Otherwise, false is returned.
         */
        bool clauseSubsumesClause(ClauseIdT clauseId1, ClauseIdT clauseId2) const;

        /**
         * Time complexity: O(|C_2|)
         * Assert: the clauses MUST be unresolved
         * Note: if Clause_1 and Clause_2 are identical, then Clause_1 variable subsumes Clause_2
         * @param clauseId1 first clause ID
         * @param clauseId2 second clause ID
         * @return true if Clause_1 variable subsumes Clause_2 (that is, Clause_2 is variable subsumed by Clause_1). Otherwise, false is returned.
         */
        bool clauseVariableSubsumesClause(ClauseIdT clauseId1, ClauseIdT clauseId2) const;

        /**
         * Assert: subsumedClauseVectorSet MUST be empty
         * Note: the duplicate clauses are removed as well
         * Note: the current component clauses (currentComponentClausesFixedVector_) are taken into account
         * Algorithm 1: ZHANG, Lintao. On subsumption removal and on-the-fly CNF simplification. In: International conference on theory and applications of satisfiability testing. Springer, Berlin, Heidelberg, 2005. p. 482-489.
         * @param subsumedClauseVectorSet [output] a vector set of subsumed clauses
         * @param considerOnlyVariables should be considered only variables, not literals
         */
        void backwardSubsumptionDetectionIntersection(VectorSetType& subsumedClauseVectorSet, bool considerOnlyVariables) const;

        /**
         * Heuristic: a literal/variable with the smallest number of occurrences is used
         * Assert: subsumedClauseVectorSet MUST be empty
         * Note: the duplicate clauses are removed as well
         * Note: the current component clauses (currentComponentClausesFixedVector_) are taken into account
         * @param subsumedClauseVectorSet [output] a vector set of subsumed clauses
         * @param considerOnlyVariables should be considered only variables, not literals
         */
        void backwardSubsumptionDetection(VectorSetType& subsumedClauseVectorSet, bool considerOnlyVariables) const;

        /**
         * Assert: subsumedClauseVectorSet MUST be empty
         * Note: the duplicate clauses are removed as well
         * Note: the current component clauses (currentComponentClausesFixedVector_) are taken into account
         * @param subsumedClauseVectorSet [output] a vector set of subsumed clauses
         * @param considerOnlyVariables should be considered only variables, not literals
         */
        void forwardSubsumptionDetection(VectorSetType& subsumedClauseVectorSet, bool considerOnlyVariables) const;

        /**
         * Assert: subsumedClauseVectorSet MUST be empty
         * Note: the duplicate clauses are removed as well
         * Note: the current component clauses (currentComponentClausesFixedVector_) are taken into account
         * Algorithm 2: ZHANG, Lintao. On subsumption removal and on-the-fly CNF simplification. In: International conference on theory and applications of satisfiability testing. Springer, Berlin, Heidelberg, 2005. p. 482-489.
         * Local auxiliary data structures:
         *      l_firstCall_oneLiteralWatchingAlgorithmSubsumption_
         *      l_firstCall_oneLiteralWatchingAlgorithmLiteralSubsumption_
         *      l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_
         *      l_forbiddenLiteralTSet_oneLiteralWatchingAlgorithmLiteralSubsumption_
         *      l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_
         *      l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_
         *      l_removeLiteralTSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmLiteralSubsumption_
         * @param subsumedClauseVectorSet [output] a vector set of subsumed clauses
         */
        void oneLiteralWatchingAlgorithmSubsumption(VectorSetType& subsumedClauseVectorSet) const;

        /**
         * Local auxiliary data structures:
         *      l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_
         *      l_forbiddenLiteralTSet_oneLiteralWatchingAlgorithmLiteralSubsumption_
         *      l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_
         * @param clauseId a clause ID
         * @param subsumedClauseVectorSet a vector set of currently detected subsumed clauses
         * @return true if the clause is subsumed. Otherwise, false is returned.
         */
        bool isClauseSubsumedOneLiteralWatchingAlgorithmSubsumption(ClauseIdT clauseId, const VectorSetType& subsumedClauseVectorSet) const;

        /**
         * Local auxiliary data structures:
         *      l_forbiddenLiteralTSet_oneLiteralWatchingAlgorithmLiteralSubsumption_
         *      l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_
         *      l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_
         *      l_removeLiteralTSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmLiteralSubsumption_
         * @param clauseId a clause ID
         * @return true if the watcher has been successfully updated. If no literal can be used as a watcher, false is returned.
         */
        bool updateWatcherOneLiteralWatchingAlgorithmSubsumption(ClauseIdT clauseId) const;

        /**
         * Assert: variableSubsumedClauseVectorSet MUST be empty
         * Note: the duplicate clauses are removed as well
         * Note: the current component clauses (currentComponentClausesFixedVector_) are taken into account
         * Algorithm 2: ZHANG, Lintao. On subsumption removal and on-the-fly CNF simplification. In: International conference on theory and applications of satisfiability testing. Springer, Berlin, Heidelberg, 2005. p. 482-489.
         * Local auxiliary data structures:
         *      l_firstCall_oneLiteralWatchingAlgorithmSubsumption_
         *      l_firstCall_oneLiteralWatchingAlgorithmVariableSubsumption_
         *      l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_
         *      l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_
         *      l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_
         *      l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_
         *      l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_
         * @param variableSubsumedClauseVectorSet [output] a vector set of variable subsumed clauses
         */
        void oneLiteralWatchingAlgorithmVariableSubsumption(VectorSetType& variableSubsumedClauseVectorSet) const;

        /**
         * Local auxiliary data structures:
         *      l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_
         *      l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_
         *      l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_
         * @param clauseId a clause ID
         * @param variableSubsumedClauseVectorSet a vector set of currently detected variable subsumed clauses
         * @return true if the clause is variable subsumed. Otherwise, false is returned.
         */
        bool isClauseVariableSubsumedOneLiteralWatchingAlgorithmVariableSubsumption(ClauseIdT clauseId, const VectorSetType& variableSubsumedClauseVectorSet) const;

        /**
         * Local auxiliary data structures:
         *      l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_
         *      l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_
         *      l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_
         *      l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_
         * @param clauseId a clause ID
         * @return true if the watcher has been successfully updated. If no variable can be used as a watcher, false is returned.
         */
        bool updateWatcherOneLiteralWatchingAlgorithmVariableSubsumption(ClauseIdT clauseId) const;

    private:
        /**
         * Time complexity: O(|C_1| + |C_2|)
         * Assert: the clauses MUST be unresolved
         * Assert: the mapping MUST NOT contain ignored pure literals
         * Note: if Clause_1 and Clause_2 are identical, then Clause_1 variable subsumes Clause_2
         * @param clauseId1 first clause ID
         * @param clauseId2 second clause ID
         * @param variableVectorMap a variable vector map. If a variable does not exist in the vector map, no mapping will be applied to the variable.
         * @param ignorePureLiteralType a type of ignored pure literals
         * @return true if Clause_1 variable subsumes Clause_2 (that is, Clause_2 is variable subsumed by Clause_1). Otherwise, false is returned.
         */
        bool clauseVariableSubsumesWithMappingClause(ClauseIdT clauseId1, ClauseIdT clauseId2, const VariableVectorMapType& variableVectorMap,
                                                     IgnorePureLiteralTypeEnum ignorePureLiteralType) const;

        /**
         * Assert: the mapping MUST NOT contain ignored pure literals
         * Assert: clauseThatVariableSubsumesSomeClauseVectorSet MUST be empty
         * Note: the duplicate clauses are removed as well
         * Note: the current component clauses (currentComponentClausesFixedVector_) are taken into account
         * Note: the clauses containing only pure literals of the ignored type are also included in the returned set
         * @param clauseThatVariableSubsumesSomeClauseVectorSet [output] a vector set of clauses such that every clause variable subsumes some clause
         * @param variableVectorMap a variable vector map. If a variable does not exist in the vector map, no mapping will be applied to the variable.
         * @param ignorePureLiteralType a type of ignored pure literals
         * @param vertexWeightType a type of vertex weight
         * @param vertexWeightVector a vector of vertex weights
         */
        void forwardVariableSubsumptionWithMappingDetection(VectorSetType& clauseThatVariableSubsumesSomeClauseVectorSet,
                                                            const VariableVectorMapType& variableVectorMap,
                                                            IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                                            VertexWeightTypeEnum vertexWeightType,
                                                            VertexWeightVectorType& vertexWeightVector) const;

        /**
         * Assert: the mapping MUST NOT contain ignored pure literals
         * Assert: clauseThatVariableSubsumesSomeClauseVectorSet MUST be empty
         * Note: the duplicate clauses are removed as well
         * Note: the current component clauses (currentComponentClausesFixedVector_) are taken into account
         * Note: the clauses containing only pure literals of the ignored type are also included in the returned set
         * Algorithm 2: ZHANG, Lintao. On subsumption removal and on-the-fly CNF simplification. In: International conference on theory and applications of satisfiability testing. Springer, Berlin, Heidelberg, 2005. p. 482-489.
         * Local auxiliary data structures:
         *      l_firstCall_oneLiteralWatchingAlgorithmSubsumption_
         *      l_firstCall_oneLiteralWatchingAlgorithmVariableSubsumption_
         *      l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_
         *      l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_
         *      l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_
         *      l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_
         *      l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_
         * @param clauseThatVariableSubsumesSomeClauseVectorSet [output] a vector set of clauses such that every clause variable subsumes some clause
         * @param variableVectorMap a variable vector map. If a variable does not exist in the vector map, no mapping will be applied to the variable.
         * @param ignorePureLiteralType a type of ignored pure literals
         * @param vertexWeightType a type of vertex weight
         * @param vertexWeightVector a vector of vertex weights
         */
        void oneLiteralWatchingAlgorithmVariableSubsumptionWithMapping(VectorSetType& clauseThatVariableSubsumesSomeClauseVectorSet,
                                                                       const VariableVectorMapType& variableVectorMap,
                                                                       IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                                                       VertexWeightTypeEnum vertexWeightType,
                                                                       VertexWeightVectorType& vertexWeightVector) const;

        /**
         * All the clauses that variable subsume the clause are found and added to clauseThatVariableSubsumesSomeClauseVectorSet
         * Local auxiliary data structures:
         *      l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_
         *      l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_
         *      l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_
         * @param clauseId a clause ID
         * @param clauseThatVariableSubsumesSomeClauseVectorSet [input/output] a vector set of clauses such that every clause variable subsumes some clause
         * @param variableVectorMap a variable vector map. If a variable does not exist in the vector map, no mapping will be applied to the variable.
         * @param ignorePureLiteralType a type of ignored pure literals
         * @param vertexWeightType a type of vertex weight
         * @param vertexWeightVector a vector of vertex weights
         */
        void processClauseOneLiteralWatchingAlgorithmVariableSubsumptionWithMapping(ClauseIdT clauseId,
                                                                                    VectorSetType& clauseThatVariableSubsumesSomeClauseVectorSet,
                                                                                    const VariableVectorMapType& variableVectorMap,
                                                                                    IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                                                                    VertexWeightTypeEnum vertexWeightType,
                                                                                    VertexWeightVectorType& vertexWeightVector) const;

        /**
         * Local auxiliary data structures:
         *      l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_
         *      l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_
         *      l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_
         *      l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_
         * @param clauseId a clause ID
         * @param variableVectorMap a variable vector map. If a variable does not exist in the vector map, no mapping will be applied to the variable.
         * @param ignorePureLiteralType a type of ignored pure literals
         * @return true if the watcher has been successfully updated. If no variable can be used as a watcher, false is returned.
         */
        bool updateWatcherOneLiteralWatchingAlgorithmVariableSubsumptionWithMapping(ClauseIdT clauseId, const VariableVectorMapType& variableVectorMap,
                                                                                    IgnorePureLiteralTypeEnum ignorePureLiteralType) const;

    public:
        typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator beginClause(ClauseIdT clauseId, bool checkSat = true) const override;

        typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator beginSortedClause(ClauseIdT clauseId, bool checkSat = true) const override;

    #ifndef NDEBUG
    private:
        VariableSetVectorType d_currentComponentVariableSetStack_;

    private:
        void processPrintFormulaRepresentationDebug(std::ostream& out) const override;

        bool isVariableInCurrentComponentDebug(VarT var) const;

    public:
        void printCurrentClauseDebug(std::ostream& out, ClauseIdT clauseId, bool considerOnlyVariables = false) const override;

        /**
         * Note: removeSubsumedClauses => removeDuplicateClauses
         */
        void printCurrentFormulaDebug(std::ostream& out, bool removeDuplicateClauses = false, bool removeSubsumedClauses = false) const override;
    #endif
    };
}   // namespace Hydra::Formula::Representation::Contagious

#include "./ContagiousFormulaRepresentation.ipp"
#include "./ContagiousFormulaRepresentationComparator.ipp"
#include "./ContagiousFormulaRepresentationSubsumption.ipp"
#include "./ContagiousFormulaRepresentationVariableSubsumptionWithMapping.ipp"
