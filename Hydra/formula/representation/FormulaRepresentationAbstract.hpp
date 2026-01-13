#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/partialAssignment/PartialAssignment.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/computeConnectedComponents/ComputeConnectedComponents.hpp"
#include "Hydra/other/container/reusableVector/ReusableVector.hpp"
#include "Hydra/other/container/vectorMap/VectorMap.hpp"
#include "Hydra/other/container/vectorSet/VectorSet.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/formula/exceptions/FormulaRepresentationException.hpp"

#include "Cara/sharpSolver/enums/ModelCountingTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/OmitClauseTypeEnum.hpp"
#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/formula/enums/ClauseStatusEnum.hpp"
#include "Hydra/formula/enums/FormulaRepresentationTypeEnum.hpp"
#include "Hydra/formula/enums/RecognitionTypeEnum.hpp"
#include "Hydra/partitioningHypergraph/enums/VertexWeightTypeEnum.hpp"

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hxx"

#ifndef NDEBUG
    #include <sstream>
#endif

namespace Hydra::Formula::Representation {

    using FormulaSizeType = unsigned long int;               // at least 32 bits
    using ClauseReductionHeuristicScoreType = long double;   // 128 bits

    /**
     * Formula representation (abstract class)
     * Copy methods are disabled! Move methods (default) are allowed!
     * Invariant: non-empty formula
     * Invariant: variables MUST be indexed from 1 to N
     * Invariant: every clause MUST end with a zero literal
     * Invariant: clauses MUST be indexed from 0 to (#clauses - 1)
     * Invariant: every variable can appear in a clause AT MOST ONCE
     * Invariant (iterator): every clause MUST end with a zero literal
     * Invariant (iterator): the literals of a clause MUST be stored contiguously
     * Exception:
     *      FormulaIsEmptyException
     *      ...PartialAssignmentException (debug)
     *      SomethingCannotBeSavedAsStdSizeTException
     *      IteratingOverSatisfiedClauseException (debug)
     *      RecognitionOfSomethingIsNotSupportedException
     *      IthElementOfPartialAssignmentDoesNotExistException (debug)
     *      AttemptRemoveNotLastAssignedLiteralFromAssignmentStackException (debug)
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class FormulaRepresentationAbstract {
    public:
        using LiteralType = typename Literal<VarT, LiteralT>::LiteralType;
        using LiteralSetType = typename Literal<VarT, LiteralT>::LiteralSetType;
        using VariableSetType = typename Literal<VarT, LiteralT>::VariableSetType;
        using LiteralTSetType = typename Literal<VarT, LiteralT>::LiteralTSetType;
        using LiteralVectorType = typename Literal<VarT, LiteralT>::LiteralVectorType;
        using VariableVectorType = typename Literal<VarT, LiteralT>::VariableVectorType;
        using LiteralSortedVectorType = typename Literal<VarT, LiteralT>::LiteralSortedVectorType;
        using VariableSortedVectorType = typename Literal<VarT, LiteralT>::VariableSortedVectorType;
        using MappingFromVariableToVariableType = typename Literal<VarT, LiteralT>::MappingFromVariableToVariableType;
        using FormulaRepresentationStatisticsPtrType = typename FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType;
        using ConnectedComponentType = typename Container::ComputeConnectedComponents::ComputeConnectedComponents<VarT, LiteralT>::ConnectedComponentType;

    public:
        using ConnectedComponentStruct = typename Container::ComputeConnectedComponents::ComputeConnectedComponents<VarT, LiteralT>::ConnectedComponentStruct;

    public:
        using ClauseSizeType = VarT;
        using VertexWeightType = int;
        using ClauseIdVectorType = std::vector<ClauseIdT>;
        using ClauseStringType = std::basic_string<LiteralT>;
        using VectorSetType = Container::VectorSet::VectorSet;
        using ClauseIdSortedVectorType = std::vector<ClauseIdT>;
        using ClauseIdSetType = Other::HashMap::SetType<ClauseIdT>;
        using ClauseOffsetVectorType = std::vector<FormulaSizeType>;
        using VertexWeightVectorType = std::vector<VertexWeightType>;
        using VariableVectorMapType = Container::VectorMap::VectorMap<VarT>;
        using PureVariableRemovedClausesVectorType = std::vector<ClauseIdVectorType>;
        using ClauseSizeCounterType = Other::HashMap::MapType<ClauseSizeType, ClauseIdT>;
        using PartialAssignmentType = PartialAssignment::PartialAssignment<VarT, LiteralT>;
        using VariableReusableVectorType = Container::ReusableVector::ReusableVector<VarT>;
        using MappingFromClauseIdToClauseIdType = Other::HashMap::MapType<ClauseIdT, ClauseIdT>;
        using ClauseIdReusableVectorType = Container::ReusableVector::ReusableVector<ClauseIdT>;

    private:
        using ClauseReductionHeuristicScoreVectorType = std::vector<ClauseReductionHeuristicScoreType>;
        using FormulaRepresentationAbstractPtrType = const FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;

    public:
        using ModelCountingTypeEnum = Cara::ModelCountingTypeEnum;
        using IgnorePureLiteralTypeEnum = Hydra::IgnorePureLiteralTypeEnum;
        using OmitClauseTypeEnum = Cache::CachingScheme::OmitClauseTypeEnum;
        using VertexWeightTypeEnum = PartitioningHypergraph::VertexWeightTypeEnum;

    public:
        using isValidClauseT = std::bool_constant<(std::is_same<ClauseIdT, char8_t>::value ||
                                                   std::is_same<ClauseIdT, char16_t>::value ||
                                                   std::is_same<ClauseIdT, char32_t>::value)>;

        static_assert(isValidClauseT::value, "Invalid ClauseIdT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidVarT::value, "Invalid VarT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidLiteralT::value, "Invalid LiteralT type!");

    public:
        #ifndef NDEBUG
        FormulaRepresentationAbstract(FormulaRepresentationTypeEnum formulaRepresentationType,
                                      FormulaSizeType originalFormulaSize,
                                      VarT totalNumberOfVariables, ClauseIdT numberOfOriginalClauses,
                                      FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr)
            : formulaRepresentationType_(formulaRepresentationType), l_firstCall_sortVariablesBasedOnClauseReductionHeuristic_(true),
              l_variableClauseReductionHeuristicScoreVector_sortVariablesBasedOnClauseReductionHeuristic_(),
              numberOfOriginalClauses_(numberOfOriginalClauses), originalFormulaSize_(originalFormulaSize), partialAssignment_(totalNumberOfVariables),
              formulaRepresentationStatisticsPtr_(formulaRepresentationStatisticsPtr),
              d_assignmentStack_() {
            assert(S_ESTIMATED_PERCENTAGE_OF_DUPLICATE_CLAUSES_ >= 0 && S_ESTIMATED_PERCENTAGE_OF_DUPLICATE_CLAUSES_ <= 100);

            // The formula is empty
            if (originalFormulaSize_ == 0)
                throw Exception::Formula::Representation::FormulaIsEmptyException();

            // The literals cannot be saved as std::size_t
            LiteralT totalNumberOfLiterals = LiteralT(2) + LiteralT(2) * static_cast<LiteralT>(totalNumberOfVariables);
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<LiteralT>(totalNumberOfLiterals))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("literals", totalNumberOfLiterals);

            // The clauses cannot be saved as std::size_t
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<ClauseIdT>(numberOfOriginalClauses))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("clauses", numberOfOriginalClauses);

            // The formula size cannot be saved as std::size_t (need for ContagiousOccurrenceList)
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<FormulaSizeType>(originalFormulaSize))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("formula size", originalFormulaSize);

            d_assignmentStack_.reserve(totalNumberOfVariables);
        }
        #else
        FormulaRepresentationAbstract(FormulaRepresentationTypeEnum formulaRepresentationType,
                                      FormulaSizeType originalFormulaSize,
                                      VarT totalNumberOfVariables, ClauseIdT numberOfOriginalClauses,
                                      FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr)
            : formulaRepresentationType_(formulaRepresentationType), l_firstCall_sortVariablesBasedOnClauseReductionHeuristic_(true),
              l_variableClauseReductionHeuristicScoreVector_sortVariablesBasedOnClauseReductionHeuristic_(),
              numberOfOriginalClauses_(numberOfOriginalClauses), originalFormulaSize_(originalFormulaSize), partialAssignment_(totalNumberOfVariables),
              formulaRepresentationStatisticsPtr_(formulaRepresentationStatisticsPtr) {
            // The formula is empty
            if (originalFormulaSize_ == 0)
                throw Exception::Formula::Representation::FormulaIsEmptyException();

            // The literals cannot be saved as int (need for size_type)
            LiteralT totalNumberOfLiterals = LiteralT(2) + LiteralT(2) * static_cast<LiteralT>(totalNumberOfVariables);
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<LiteralT>(totalNumberOfLiterals))
                throw Exception::SomethingCannotBeSavedAsIntException("literals", totalNumberOfLiterals);

            // The clauses cannot be saved as int
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<ClauseIdT>(numberOfOriginalClauses))
                throw Exception::SomethingCannotBeSavedAsIntException("clauses", numberOfOriginalClauses);

            // The formula size cannot be saved as int (need for ContagiousOccurrenceList)
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<FormulaSizeType>(originalFormulaSize))
                throw Exception::SomethingCannotBeSavedAsIntException("formula size", originalFormulaSize);
        }
        #endif

        FormulaRepresentationAbstract(const FormulaRepresentationAbstract&) = delete;
        FormulaRepresentationAbstract(FormulaRepresentationAbstract&&) noexcept = default;

        FormulaRepresentationAbstract& operator=(const FormulaRepresentationAbstract&) = delete;
        FormulaRepresentationAbstract& operator=(FormulaRepresentationAbstract&&) noexcept = default;

        virtual ~FormulaRepresentationAbstract() noexcept = default;

    private:
        FormulaRepresentationTypeEnum formulaRepresentationType_;

        // Local auxiliary data structures for sortVariablesBasedOnClauseReductionHeuristic
        mutable bool l_firstCall_sortVariablesBasedOnClauseReductionHeuristic_;
        mutable ClauseReductionHeuristicScoreVectorType l_variableClauseReductionHeuristicScoreVector_sortVariablesBasedOnClauseReductionHeuristic_;

    protected:
        ClauseIdT numberOfOriginalClauses_;
        FormulaSizeType originalFormulaSize_;
        PartialAssignmentType partialAssignment_;

        FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr_;

        inline static constexpr int S_ESTIMATED_PERCENTAGE_OF_DUPLICATE_CLAUSES_ = 10;
        inline static constexpr ClauseSizeType S_ESTIMATED_NUMBER_OF_CLAUSE_SIZES_ = 4;

    protected:
        virtual void processAddLiteralToPartialAssignment(const LiteralType& lit, VariableVectorType& freeVariableVector,
                                                          bool firstAssignment, bool lastAssignment) = 0;

        virtual void processRemoveLiteralFromPartialAssignment(const LiteralType& lit, VariableVectorType& unfreeVariableVector) = 0;

        virtual void processAddClausesContainingOnlyPureLiteralsOfIgnoredType(const ClauseIdSetType& pureClauseSet) = 0;

        virtual void processRemoveClausesContainingOnlyPureLiteralsOfIgnoredType(const ClauseIdSetType& pureClauseSet) = 0;

        virtual ConnectedComponentType processComputeConnectedComponents(const VariableSetType& currentComponentVariableSet) const = 0;

        virtual ConnectedComponentType processComputeConnectedComponents(const VariableSetType& currentComponentVariableSet,
                                                                         ClauseIdSetType& pureClauseSet,
                                                                         IgnorePureLiteralTypeEnum ignorePureLiteralType) = 0;

        virtual bool processIsCurrentComponentFormulaKromC(const VariableSetType& currentComponentVariableSet) const;

        virtual bool processIsCurrentComponentFormulaHornC(const VariableSetType& currentComponentVariableSet) const;

        virtual bool processIsCurrentComponentFormulaAntiHornC(const VariableSetType& currentComponentVariableSet) const;

        virtual void processSaveCurrentComponentFormulaToVector(const VariableSetType& currentComponentVariableSet,
                                                                LiteralVectorType& formula, ClauseOffsetVectorType& clauseOffsetVector, bool sort) const = 0;

        /**
         * Combine two vertex weights
         * Clause_1 with vertexWeight_1 variable subsumes clause_2 with vertexWeight_2
         * Note: mainly used by PartitioningHypergraph
         * @param vertexWeight1 first vertex weight
         * @param vertexWeight2 second vertex weight
         * @param vertexWeightType a type of vertex weight
         * @return the new vertex weight
         */
        VertexWeightType combineVertexWeights(VertexWeightType vertexWeight1, VertexWeightType vertexWeight2,
                                              VertexWeightTypeEnum vertexWeightType) const;

    public:
        /**
         * Getter
         * @return the type of the formula representation
         */
        FormulaRepresentationTypeEnum getFormulaRepresentationType() const noexcept;

        /**
         * Getter
         * @return the number of variables in the original formula
         */
        VarT getNumberOfVariablesInOriginalFormula() const noexcept;

        /**
         * Note: used for indexing
         * @return the number of variables in the original formula INCREASED BY ONE (due to the zero index)
         */
        VarT getNumberOfVariablesInOriginalFormulaUsedForIndexing() const noexcept;

        /**
         * Getter
         * @return the number of literals in the original formula
         */
        LiteralT getNumberOfLiteralsInOriginalFormula() const noexcept;

        /**
         * Getter
         * @return the number of clauses in the original formula
         */
        ClauseIdT getNumberOfOriginalClauses() const noexcept;

        /**
         * Getter
         * @return the size of the original formula
         */
        FormulaSizeType getOriginalFormulaSize() const noexcept;

        /**
         * @return the maximum clause size in the original formula
         */
        virtual ClauseSizeType getMaxOriginalClauseSize() const noexcept = 0;

        /**
         * Check if the variable is assigned
         * Time complexity: O(1)
         * @param var a variable
         * @return true if the variable is assigned. Otherwise, false is returned.
         */
        bool isVariableAssigned(VarT var) const noexcept;

        /**
         * Check if the literal is set to true
         * Time complexity: O(1)
         * @param lit a literal
         * @return true if the literal is set to true. Otherwise, false is returned.
         */
        bool isLiteralSetToTrue(const LiteralType& lit) const noexcept;

        /**
         * Check if the literal is set to false
         * Time complexity: O(1)
         * @param lit a literal
         * @return true if the literal is set to false. Otherwise, false is returned.
         */
        bool isLiteralSetToFalse(const LiteralType& lit) const noexcept;

        /**
         * Check if the clause is satisfied
         * @param clauseId a clause ID
         * @return true if the clause is satisfied. Otherwise, false is returned.
         */
        bool isClauseSatisfied(ClauseIdT clauseId) const;

        /**
         * Check if the clause is empty
         * @param clauseId a clause ID
         * @return true if the clause is empty. Otherwise, false is returned.
         */
        bool isClauseEmpty(ClauseIdT clauseId) const;

        /**
         * Check if the clause is unresolved
         * @param clauseId a clause ID
         * @return true if the clause is unresolved. Otherwise, false is returned.
         */
        bool isClauseUnresolved(ClauseIdT clauseId) const;

        /**
         * Check if the clause is unit
         * @param clauseId a clause ID
         * @return true if the clause is unit. Otherwise, false is returned.
         */
        bool isClauseUnit(ClauseIdT clauseId) const;

        /**
         * Assert: the clauses MUST NOT be satisfied
         * @param clauseId1 first clause ID
         * @param clauseId2 second clause ID
         * @return
         *      -1 - clause_1 < clause_2
         *       0 - clause_1 = clause_2
         *       1 - clause_1 > clause_2
         */
        int compareClauses(ClauseIdT clauseId1, ClauseIdT clauseId2) const;

        /**
         * Add the literal (lit) to the partial assignment
         * @param lit a literal
         * @param freeVariableVector [output] a vector of variables that became free
         * @throw ...PartialAssignmentException (debug) if something is wrong with the partial assignment
         */
        void addLiteralToPartialAssignment(const LiteralType& lit, VariableVectorType& freeVariableVector);
        void addLiteralVectorToPartialAssignment(const LiteralVectorType& literalVector, VariableVectorType& freeVariableVector);

        /**
         * Remove the literal (lit) from the partial assignment
         * @param lit a literal
         * @param unfreeVariableVector [output] a vector of variables that became unfree
         * @throw ...PartialAssignmentException (debug) if something is wrong with the partial assignment
         * @throw AttemptRemoveNotLastAssignedLiteralFromAssignmentStackException (debug) if the literal is not the last assigned literal
         */
        void removeLiteralFromPartialAssignment(const LiteralType& lit, VariableVectorType& unfreeVariableVector);
        void removeLiteralVectorFromPartialAssignment(const LiteralVectorType& literalVector, VariableVectorType& unfreeVariableVector, bool reverse = true);

        /**
         * @param clauseId a clause ID
         * @param position a position in the clause
         * @return the literal occurring at the position in the clause
         */
        virtual const LiteralType& getLiteralAtPositionInClause(ClauseIdT clauseId, ClauseSizeType position) const = 0;

        /**
         * @param clauseId a clause ID
         * @return the current clause status (with respect to the partial assignment)
         */
        virtual ClauseStatusEnum getCurrentClauseStatus(ClauseIdT clauseId) const = 0;

        /**
         * Assert: the clause MUST NOT be satisfied
         * @param clauseId a clause ID
         * @return the size of the current clause (with respect to the partial assignment)
         */
        virtual ClauseSizeType getCurrentClauseSize(ClauseIdT clauseId) const = 0;

        /**
         * Time complexity: O(|C|)
         * Assert: the clause MUST NOT be satisfied
         * @param clauseId a clause ID
         * @param considerOnlyVariables should be considered only variables, not literals
         * @return a string representing the clause
         */
        ClauseStringType getClauseString(ClauseIdT clauseId, bool considerOnlyVariables = false) const;

        /**
         * @param clauseId a clause ID
         * @return true if the clause is untouched. Otherwise, false is returned.
         */
        virtual bool isClauseUntouched(ClauseIdT clauseId) const = 0;

        /**
         * @param clauseId a clause ID
         * @return true if the clause is untouched and binary. Otherwise, false is returned.
         */
        bool isClauseUntouchedAndBinary(ClauseIdT clauseId) const;

        /**
         * Time complexity: O(#occurrences)
         * Assert: the variable MUST NOT be assigned
         * Assert: the variable MUST be in the current component
         * @param lit a literal
         * @return true if the literal is in a unit clause. Otherwise, false is returned.
         */
        virtual bool isLiteralInUnitClause(const LiteralType& lit) const = 0;

        /**
         * Assert: the variable MUST NOT be assigned
         * Assert: the variable MUST be in the current component
         * @param var a variable
         * @return true if the variable is free (=does not occur in the current formula). Otherwise, false is returned.
         */
        virtual bool isVariableFree(VarT var) const = 0;

        /**
         * Assert: the variable MUST NOT be free
         * Assert: the variable MUST NOT be assigned
         * Assert: the variable MUST be in the current component
         * @param var a variable
         * @return true if the variable is a singleton. Otherwise, false is returned.
         */
        virtual bool isVariableSingleton(VarT var) const = 0;

        /**
         * Assert: the variable MUST NOT be free
         * Assert: the variable MUST NOT be assigned
         * Assert: the variable MUST be in the current component
         * @param var a variable
         * @return true if +var or -var is a pure literal in the current formula. Otherwise, false is returned.
         */
        bool isPureLiteralInCurrentFormula(VarT var) const;

        /**
         * Assert: the variable MUST NOT be free
         * Assert: the variable MUST NOT be assigned
         * Assert: the variable MUST be in the current component
         * @param var a variable
         * @return true if +var is a pure literal in the current formula. Otherwise, false is returned.
         */
        bool isPositivePureLiteralInCurrentFormula(VarT var) const;

        /**
         * Assert: the variable MUST NOT be free
         * Assert: the variable MUST NOT be assigned
         * Assert: the variable MUST be in the current component
         * @param var a variable
         * @return true if -var is a pure literal in the current formula. Otherwise, false is returned.
         */
        bool isNegativePureLiteralInCurrentFormula(VarT var) const;

        /**
         * Assert: the variable MUST NOT be free
         * Assert: the variable MUST NOT be assigned
         * Assert: the variable MUST be in the current component
         * Note: mainly used by variable subsumption with mapping
         * @param var a variable
         * @param ignorePureLiteralType a type of ignored pure literals
         * @return true if
         *      +var is a pure literal in the current formula (ONLY_POSITIVE)
         *      -var is a pure literal in the current formula (ONLY_NEGATIVE)
         *      +var or -var is a pure literal in the current formula (BOTH_POSITIVE_AND_NEGATIVE).
         * Otherwise, false is returned.
         */
        bool isPureLiteralInCurrentFormula(VarT var, IgnorePureLiteralTypeEnum ignorePureLiteralType) const;

        /**
         * Assert: the variables MUST NOT be free
         * Assert: the variables MUST NOT be assigned
         * Assert: the variables MUST be in the current component
         * Note: mainly used by compiler
         * @param variableSet a set of variables
         * @param ignorePureLiteralType a type of ignored pure literals
         * @return true if all variables are pure regarding the type of ignored pure literals. Otherwise, false is returned.
         */
        bool arePureLiteralsInCurrentFormula(const VariableSetType& variableSet, IgnorePureLiteralTypeEnum ignorePureLiteralType) const;

        /**
         * Time complexity: O(|C|)
         * Assert: the clause MUST NOT be satisfied
         * @param clauseId a clause ID
         * @param ignorePureLiteralType a type of ignored pure literals
         * @return true if the clause contains only pure literals of the ignored type. Otherwise, false is returned.
         */
        bool doesClauseContainOnlyPureLiteralsOfIgnoredType(ClauseIdT clauseId, IgnorePureLiteralTypeEnum ignorePureLiteralType) const;

        /**
         * Add the pure clauses
         * Assert: the clauses MUST be unresolved
         * Assert: the clauses MUST contain only pure literals
         * @param pureClauseSet a set of pure clauses
         * @param ignorePureLiteralType a type of ignored pure literals
         */
        void addClausesContainingOnlyPureLiteralsOfIgnoredType(const ClauseIdSetType& pureClauseSet, IgnorePureLiteralTypeEnum ignorePureLiteralType);

        /**
         * Remove the pure clauses
         * Assert: the clauses MUST be unresolved
         * Assert: the clauses MUST contain only pure literals
         * @param pureClauseSet a set of pure clauses
         * @param ignorePureLiteralType a type of ignored pure literals
         */
        void removeClausesContainingOnlyPureLiteralsOfIgnoredType(const ClauseIdSetType& pureClauseSet, IgnorePureLiteralTypeEnum ignorePureLiteralType);

        /**
         * Assert: the variable MUST NOT be assigned
         * Assert: the variable MUST be in the current component
         * @param lit a literal
         * @return the number of current (=unresolved) clauses containing the literal
         */
        ClauseIdT getNumberOfCurrentClauses(const LiteralType& lit) const;
        virtual ClauseIdT getNumberOfCurrentClauses(LiteralT literalT) const = 0;

        /**
         * Assert: the variable MUST NOT be assigned
         * Assert: the variable MUST be in the current component
         * @param lit a literal
         * @return a mapping where a key is a (clause) size, and the value is the number of current (=unresolved) clauses with the particular size containing the literal
         */
        ClauseSizeCounterType getCurrentClauseSizeCounter(const LiteralType& lit) const;
        virtual ClauseSizeCounterType getCurrentClauseSizeCounter(LiteralT literalT) const = 0;

        /**
         * Assert: the variable MUST NOT be assigned
         * Assert: the variable MUST be in the current component
         * @param lit a literal
         * @return the number of current (=unresolved) binary clauses containing the literal
         */
        ClauseIdT getNumberOfCurrentBinaryClauses(const LiteralType& lit) const;
        virtual ClauseIdT getNumberOfCurrentBinaryClauses(LiteralT literalT) const = 0;

        /**
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @return the size of the current formula (with respect to the partial assignment and the current component)
         */
        virtual FormulaSizeType getCurrentComponentFormulaSize(const VariableSetType& currentComponentVariableSet) const noexcept = 0;

        /**
         * Compute the connected components for the variables in the current component (currentComponentVariableSet)
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @return a structure containing the connected components
         */
        ConnectedComponentType computeConnectedComponents(const VariableSetType& currentComponentVariableSet) const;

        /**
         * Compute the connected components concerning ignored pure literals for the variables in the current component (currentComponentVariableSet)
         * Assert: pureClauseSet MUST be empty
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param pureClauseSet [output] a set of pure clauses
         * @param ignorePureLiteralType a type of ignored pure literals
         * @return a structure containing the connected components
         */
        ConnectedComponentType computeConnectedComponents(const VariableSetType& currentComponentVariableSet, ClauseIdSetType& pureClauseSet,
                                                          IgnorePureLiteralTypeEnum ignorePureLiteralType);

        /**
         * Set a new component based on the variables
         * Assert: the variables MUST be in the current component
         * @param newConnectedComponentStruct a new connected component
         * @param ignorePureLiteralType a type of ignored pure literals
         * @return the removed clauses related to the ignored pure variables
         */
        virtual PureVariableRemovedClausesVectorType setNewComponent(const ConnectedComponentStruct& newConnectedComponentStruct,
                                                                     IgnorePureLiteralTypeEnum ignorePureLiteralType) = 0;

        /**
         * Pop the previous component
         * @param currentConnectedComponentStruct a current connected component that we want to pop
         * @param pureVariableRemovedClausesVector the removed clauses related to the ignored pure variables that must be added
         */
        virtual void popPreviousComponent(const ConnectedComponentStruct& currentConnectedComponentStruct,
                                          const PureVariableRemovedClausesVectorType& pureVariableRemovedClausesVector) = 0;

        /**
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @return the number of current (=unresolved) clauses in which at least one variable from currentComponentVariableSet appears
         */
        virtual ClauseIdT getNumberOfCurrentComponentClauses(const VariableSetType& currentComponentVariableSet) const noexcept = 0;

        /**
         * Note: the clauses are not sorted concerning literals
         * Note: clauseIdReusableVector will be cleared at the beginning
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param clauseIdReusableVector [output] a reusable vector that will be filled by current (=unresolved) clauses in which at least one variable from currentComponentVariableSet appears
         * @param sortIds sort the clause IDs
         */
        virtual void getCurrentComponentClauses(const VariableSetType& currentComponentVariableSet,
                                                ClauseIdReusableVectorType& clauseIdReusableVector, bool sortIds = false) const = 0;

        /**
         * Note: the clauses are not sorted concerning literals/variables
         * Note: clauseIdReusableVector will be cleared at the beginning
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param clauseIdReusableVector [output] a reusable vector that will be filled by current (=unresolved) NOT DUPLICATE clauses in which at least one variable from currentComponentVariableSet appears
         * @param considerOnlyVariables should be considered only variables, not literals
         * @param sortIds sort the clause IDs
         */
        virtual void getCurrentComponentNotDuplicateClauses(const VariableSetType& currentComponentVariableSet,
                                                            ClauseIdReusableVectorType& clauseIdReusableVector,
                                                            bool considerOnlyVariables = false, bool sortIds = false) const = 0;

        /**
         * Note: clauseIdReusableVector will be cleared at the beginning
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param clauseIdReusableVector [output] a reusable vector that will be filled by SORTED current (=unresolved) clauses in which at least one variable from currentComponentVariableSet appears
         * @param removeDuplicateClauses should the duplicate clauses be removed
         * @param considerOnlyVariables should be considered only variables, not literals
         * @param omitClauseType what clause type should be omitted
         */
        virtual void getSortedCurrentComponentClauses(const VariableSetType& currentComponentVariableSet,
                                                      ClauseIdReusableVectorType& clauseIdReusableVector,
                                                      bool removeDuplicateClauses, bool considerOnlyVariables = false,
                                                      OmitClauseTypeEnum omitClauseType = OmitClauseTypeEnum::NONE) const = 0;

        /**
         * Note: the duplicate clauses are removed as well
         * Note: the clauses are not sorted concerning literals/variables
         * Note: clauseIdReusableVector and usedVariableVectorSet will be cleared at the beginning
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param clauseIdReusableVector [output] a reusable vector that will be filled by current (=unresolved) NOT SUBSUMED clauses in which at least one variable from currentComponentVariableSet appears
         * @param usedVariableVectorSet [output] a subset of currentComponentVariableSet. For each variable in the set, a not subsumed clause containing that variable exists.
         * @param fillUsedVariables should usedVariableVectorSet be filled
         * @param considerOnlyVariables should be considered only variables, not literals
         * @param sortIds sort the clause IDs
         */
        virtual void getCurrentComponentNotSubsumedClauses(const VariableSetType& currentComponentVariableSet,
                                                           ClauseIdReusableVectorType& clauseIdReusableVector,
                                                           VectorSetType& usedVariableVectorSet, bool fillUsedVariables,
                                                           bool considerOnlyVariables = false, bool sortIds = false) const = 0;

        /**
         * Note: the duplicate clauses are removed as well
         * Note: clauseIdReusableVector will be cleared at the beginning
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param clauseIdReusableVector [output] a reusable vector that will be filled by SORTED current (=unresolved) NOT SUBSUMED clauses in which at least one variable from currentComponentVariableSet appears
         */
        virtual void getSortedCurrentComponentNotSubsumedClauses(const VariableSetType& currentComponentVariableSet,
                                                                 ClauseIdReusableVectorType& clauseIdReusableVector) const = 0;

        /**
         * Variable subsumption is subsumption that considers only variables, not literals
         * Note: mainly used by PartitioningHypergraph
         * Note: the mapping is applied before checking variable subsumption
         * Note: clauseThatVariableSubsumesSomeClauseVectorSet will be cleared at the beginning
         * Note: the corresponding vertex weights MUST be initially set if vertex weights are used
         * Note: the duplicate clauses (considering only variables, not literals) are removed as well
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param clauseThatVariableSubsumesSomeClauseVectorSet [output] a vector set that will be filled by current (=unresolved) clauses in which at least one variable from currentComponentVariableSet appears. In addition to that, every clause variable subsumes some clause (i. g., (-x_1 v x_2), (x_1 v -x_2 v x_3), (x_4, -x_5) -> only (-x_1 v x_2) is returned).
         * @param variableVectorMap a variable vector map. If a variable does not exist in the vector map, no mapping will be applied to the variable.
         * @param ignorePureLiteralType a type of ignored pure literals
         * @param vertexWeightType a type of vertex weight
         * @param vertexWeightVector a vector of vertex weights
         */
        virtual void getCurrentComponentClausesThatVariableSubsumeSomeClause(const VariableSetType& currentComponentVariableSet,
                                                                             VectorSetType& clauseThatVariableSubsumesSomeClauseVectorSet,
                                                                             const VariableVectorMapType& variableVectorMap,
                                                                             IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                                                             VertexWeightTypeEnum vertexWeightType,
                                                                             VertexWeightVectorType& vertexWeightVector) const = 0;

        /**
         * Assert: the variable MUST NOT be assigned
         * Assert: the variable MUST be in the current component
         * Note: clauseIdReusableVector will be cleared at the beginning
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param var a variable
         * @param clauseIdReusableVector [output] a reusable vector that will be filled by current (=unresolved), non-ignored clauses that contain the variable
         * @param ignoredClauseVectorSet a vector set of ignored clauses. If the capacity of the vector set is zero, no clause is ignored.
         */
        virtual void getCurrentClauses(const VariableSetType& currentComponentVariableSet,
                                       VarT var, ClauseIdReusableVectorType& clauseIdReusableVector,
                                       const VectorSetType& ignoredClauseVectorSet) const = 0;

        /**
         * Assert: the variables MUST NOT be assigned
         * Assert: the variables MUST be in the current component
         * Note: clauseIdReusableVector will be cleared at the beginning
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param variableVector a vector of variables
         * @param clauseIdReusableVector [output] a reusable vector that will be filled by current (=unresolved), non-ignored clauses that contain at least one variable from variableVector
         * @param ignoredClauseVectorSet a vector set of ignored clauses. If the capacity of the vector set is zero, no clause is ignored.
         */
        virtual void getCurrentClauses(const VariableSetType& currentComponentVariableSet,
                                       const VariableVectorType& variableVector, ClauseIdReusableVectorType& clauseIdReusableVector,
                                       const VectorSetType& ignoredClauseVectorSet) const = 0;

        /**
         * Assert: the clause MUST NOT be satisfied
         * @param clauseId a clause ID
         * @return a set of unassigned variables contained in the clause (with respect to the partial assignment)
         */
        virtual VariableSetType getUnassignedVariablesInClause(ClauseIdT clauseId) const = 0;

        /**
         * Print the current formula in the DIMACS CNF format
         * Note: the number of variables in the Problem line will be the number of variables in the original formula
         * @param printProblemLine should the Problem line be printed
         * @param modelCountingType [!UNDEFINED] print the model counting header
         */
        virtual void printCurrentFormulaInDimacsCnfFormat(std::ostream& out, bool printProblemLine = true,
                                                          ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED) const = 0;

        /**
         * Print the SORTED current formula in the DIMACS CNF format
         * Note: removeSubsumedClauses => removeDuplicateClauses
         * Note: the number of variables in the Problem line will be the number of variables in the original formula
         * @param removeDuplicateClauses should the duplicate clauses be removed
         * @param removeSubsumedClauses should the subsumed clauses be removed
         * @param printProblemLine should the Problem line be printed
         * @param modelCountingType [!UNDEFINED] print the model counting header
         */
        virtual void printSortedCurrentFormulaInDimacsCnfFormat(std::ostream& out,
                                                                bool removeDuplicateClauses = false, bool removeSubsumedClauses = false,
                                                                bool printProblemLine = true,
                                                                ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED) const = 0;

        /**
         * Set statistics before the compilation
         * Statistics: all
         */
        void setStatisticsBeforeCompilation() const;

        /**
         * Sort the variables in the reusable vector based on the clause reduction heuristic
         * Assert: the variables in the reusable vector MUST NOT be assigned
         * Assert: the variables in the reusable vector MUST be in the current component
         * Local auxiliary data structures:
         *      l_firstCall_sortVariablesBasedOnClauseReductionHeuristic_
         *      l_variableClauseReductionHeuristicScoreVector_sortVariablesBasedOnClauseReductionHeuristic_
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param variableReusableVector a variable reusable vector that will be sorted
         * @param ascendingOrder ascending order or descending order
         */
        void sortVariablesBasedOnClauseReductionHeuristic(const VariableSetType& currentComponentVariableSet,
                                                          VariableReusableVectorType& variableReusableVector, bool ascendingOrder) const;

        /**
         * Check if the current formula (with respect to the partial assignment and the current component) is Krom-C
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @return true if the current formula is Krom-C. Otherwise, false is returned.
         * @throw RecognitionOfSomethingIsNotSupportedException if the recognition is not supported
         */
        bool isCurrentComponentFormulaKromC(const VariableSetType& currentComponentVariableSet) const;

        /**
         * Check if the current formula (with respect to the partial assignment and the current component) is Horn-C
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @return true if the current formula is Horn-C. Otherwise, false is returned.
         * @throw RecognitionOfSomethingIsNotSupportedException if the recognition is not supported
         */
        bool isCurrentComponentFormulaHornC(const VariableSetType& currentComponentVariableSet) const;

        /**
         * Check if the current formula (with respect to the partial assignment and the current component) is anti-Horn-C
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @return true if the current formula is anti-Horn-C. Otherwise, false is returned.
         * @throw RecognitionOfSomethingIsNotSupportedException if the recognition is not supported
         */
        bool isCurrentComponentFormulaAntiHornC(const VariableSetType& currentComponentVariableSet) const;

        /**
         * Save the current formula (with respect to the partial assignment and the current component) to a vector
         * Assert: formula MUST be empty
         * Assert: clauseOffsetVector MUST be empty
         * Note: every clause ends with a zero literal
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param formula [output] a vector where the current formula will be saved
         * @param clauseOffsetVector [output] a vector containing the clause offsets
         * @param sort should the literals in a clause be sorted
         */
        void saveCurrentComponentFormulaToVector(const VariableSetType& currentComponentVariableSet,
                                                 LiteralVectorType& formula, ClauseOffsetVectorType& clauseOffsetVector, bool sort = false) const;

        /**
         * Save the formula defined by clauses to a vector
         * Assert: formula MUST be empty
         * Assert: the clauses MUST be unresolved
         * Assert: clauseOffsetVector MUST be empty
         * @param clauseIdReusableVector a reusable vector of clauses
         * @param formula [output] a vector where the formula will be saved
         * @param clauseOffsetVector [output] a vector containing the clause offsets
         * @param sort should the literals in a clause be sorted
         */
        void saveFormulaDefinedByClausesToVector(const ClauseIdReusableVectorType& clauseIdReusableVector,
                                                 LiteralVectorType& formula, ClauseOffsetVectorType& clauseOffsetVector, bool sort = false) const;

        /**
         * Assert: the variables MUST NOT be free
         * Assert: the variables MUST NOT be assigned
         * Assert: the variables MUST be in the current component
         * @param variableSet a set of variables
         * @return the number of singleton variables in the set
         */
        VarT getNumberOfSingletonVariables(const VariableSetType& variableSet) const;

    public:
        class ClauseIterator {
        public:
            using iterator_category = std::input_iterator_tag;

        private:
            using PointerType = const LiteralType*;
            using ReferenceType = const LiteralType&;
            using FormulaRepresentationAbstractPtrType = const FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;

        public:
            // end
            ClauseIterator()
                : ptr_(nullptr), formulaRepresentationAbstractPtr_(nullptr) { }

            // begin
            ClauseIterator(PointerType ptr, FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr)
                : ptr_(ptr), formulaRepresentationAbstractPtr_(formulaRepresentationAbstractPtr) {
                // Pointer has to be changed
                if (formulaRepresentationAbstractPtr_->isVariableAssigned(ptr->getVariable()))
                    initialize();
            }

            #ifndef NDEBUG
            // begin
            ClauseIterator(PointerType ptr, FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                           ClauseIdT clauseId, bool checkSat)
                : ptr_(ptr), formulaRepresentationAbstractPtr_(formulaRepresentationAbstractPtr),
                  d_checkSat_(checkSat), d_clauseId_(clauseId) {
                // Pointer has to be changed
                if (formulaRepresentationAbstractPtr_->isVariableAssigned(ptr->getVariable()))
                    initialize();
            }
            #endif

        private:
            PointerType ptr_;
            FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr_;

        private:
            /**
             * @throw IteratingOverSatisfiedClauseException (debug) (d_checkSat_) if the clause is satisfied
             */
            void next();
            void initialize();

        public:
            ReferenceType operator*() const;

            PointerType operator->() const;

            ClauseIterator& operator++();

            friend bool operator==(const ClauseIterator& clauseIterator1, const ClauseIterator& clauseIterator2) {
                return clauseIterator1.ptr_ == clauseIterator2.ptr_;
            }

            friend bool operator!=(const ClauseIterator& clauseIterator1, const ClauseIterator& clauseIterator2) {
                return clauseIterator1.ptr_ != clauseIterator2.ptr_;
            };

        #ifndef NDEBUG
        private:
            bool d_checkSat_ = true;
            ClauseIdT d_clauseId_ = 0;
        #endif
        };

    public:
        /**
          * Invariant: every clause MUST end with a zero literal
          * Invariant: the literals of the clause MUST be stored contiguously
          * @param clauseId a clause ID
          * @param checkSat if the clause is satisfied, then an exception is thrown
          * @return an iterator
          * @throw IteratingOverSatisfiedClauseException (debug) (checkSat) if the clause is satisfied
          */
        virtual ClauseIterator beginClause(ClauseIdT clauseId, bool checkSat = true) const = 0;
        virtual ClauseIterator beginSortedClause(ClauseIdT clauseId, bool checkSat = true) const = 0;

        /**
         * Wrapped nullptr
         * @return an iterator
         */
        ClauseIterator endClause() const noexcept;
        ClauseIterator endSortedClause() const noexcept;

    #ifndef NDEBUG
    private:
        LiteralVectorType d_assignmentStack_;

    public:
        void printFormulaRepresentationDebug(std::ostream& out) const;

        virtual void printCurrentClauseDebug(std::ostream& out, ClauseIdT clauseId, bool considerOnlyVariables = false) const = 0;

        virtual void printCurrentFormulaDebug(std::ostream& out, bool removeDuplicateClauses = false, bool removeSubsumedClauses = false) const = 0;

        /**
         * Time complexity: O(1)
         * @param i an index
         * @return the i-th element of the partial assignment
         * @throw IthElementOfPartialAssignmentDoesNotExistException if the i-th element of the partial assignment does not exist
         */
        const LiteralType& getIthElementOfPartialAssignmentDebug(VarT i) const;

    protected:
        virtual void processPrintFormulaRepresentationDebug(std::ostream& out) const = 0;
    #endif
    };
}   // namespace Hydra::Formula::Representation

#include "./FormulaRepresentationAbstract.ipp"
