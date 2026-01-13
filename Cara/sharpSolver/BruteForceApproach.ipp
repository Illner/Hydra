#pragma once

#include "Hydra/compiler/Compiler.hpp"

namespace Hydra {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    Compiler<VarT, LiteralT, ClauseIdT>::NumberOfModelsType
    Compiler<VarT, LiteralT, ClauseIdT>::computeNumberOfModelsUsingBruteForceApproach(const VariableSetType& currentComponentVariableSet) const {
        assert(currentComponentVariableSet.size() <= S_MAX_NUMBER_OF_VARIABLES_FOR_BRUTE_FORCE_APPROACH_);   // valid number of variables

        // Initialize local auxiliary data structures
        if (l_firstCall_computeNumberOfModelsUsingBruteForceApproach_) {
            l_clauseIdReusableVector_computeNumberOfModelsUsingBruteForceApproach_ = ClauseIdReusableVectorType(formulaRepresentationAbstractUniquePtr_->getNumberOfOriginalClauses());
            l_variableToIndexVectorMapping_computeNumberOfModelsUsingBruteForceApproach_ = VariableVectorType(formulaRepresentationAbstractUniquePtr_->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), 0);

            l_firstCall_computeNumberOfModelsUsingBruteForceApproach_ = false;
        }

        // Create a mapping used for assignments
        VarT index = 0;
        for (VarT var : currentComponentVariableSet) {
            l_variableToIndexVectorMapping_computeNumberOfModelsUsingBruteForceApproach_[var] = index;
            ++index;
        }

        // Get the clauses
        formulaRepresentationAbstractUniquePtr_->getCurrentComponentClauses(currentComponentVariableSet,
                                                                            l_clauseIdReusableVector_computeNumberOfModelsUsingBruteForceApproach_);

        assert(l_clauseIdReusableVector_computeNumberOfModelsUsingBruteForceApproach_.size() <= S_MAX_NUMBER_OF_CLAUSES_FOR_BRUTE_FORCE_APPROACH_);   // valid number of clauses

        NumberOfModelsType numberOfModels = 0;
        std::size_t maxNumberOfAssignments = static_cast<std::size_t>(1) << currentComponentVariableSet.size();   // 2^|V|

        // Iterate assignments
        for (std::size_t assignment = 0; assignment < maxNumberOfAssignments; ++assignment) {
            bool isSatisfied = true;

            // Iterate clauses
            for (ClauseIdT clauseId : l_clauseIdReusableVector_computeNumberOfModelsUsingBruteForceApproach_) {
                bool isClauseSatisfied = false;

                // Iterate literals
                for (auto clauseIt = formulaRepresentationAbstractUniquePtr_->beginClause(clauseId);
                     clauseIt != formulaRepresentationAbstractUniquePtr_->endClause(); ++clauseIt) {
                    assert(Other::containInSet(currentComponentVariableSet, clauseIt->getVariable()));

                    bool value = (assignment >> static_cast<std::size_t>(l_variableToIndexVectorMapping_computeNumberOfModelsUsingBruteForceApproach_[clauseIt->getVariable()])) & 1;

                    // The clause is satisfied
                    if ((clauseIt->isPositive() && value) || (clauseIt->isNegative() && !value)) {
                        isClauseSatisfied = true;

                        break;
                    }
                }

                if (!isClauseSatisfied) {
                    isSatisfied = false;

                    break;
                }
            }

            if (isSatisfied)
                ++numberOfModels;
        }

        return numberOfModels;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    Compiler<VarT, LiteralT, ClauseIdT>::NumberOfModelsType
    Compiler<VarT, LiteralT, ClauseIdT>::computeNumberOfModelsUsingBruteForceApproachAndSingletonAwareMethod(const VariableSetType& currentComponentVariableSet) const {
        // Initialize local auxiliary data structures
        if (l_firstCall_computeNumberOfModelsUsingBruteForceApproach_) {
            l_clauseIdReusableVector_computeNumberOfModelsUsingBruteForceApproach_ = ClauseIdReusableVectorType(formulaRepresentationAbstractUniquePtr_->getNumberOfOriginalClauses());
            l_variableToIndexVectorMapping_computeNumberOfModelsUsingBruteForceApproach_ = VariableVectorType(formulaRepresentationAbstractUniquePtr_->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), 0);

            l_firstCall_computeNumberOfModelsUsingBruteForceApproach_ = false;
        }

        // Initialize local auxiliary data structures
        if (l_firstCall_computeNumberOfModelsUsingBruteForceApproachAndSingletonAwareMethod_) {
            l_numberOfSingletonVariablesInClauseReusableVector_computeNumberOfModelsUsingBruteForceApproachAndSingletonAwareMethod_ = VariableReusableVectorType(S_MAX_NUMBER_OF_CLAUSES_FOR_BRUTE_FORCE_APPROACH_);

            l_firstCall_computeNumberOfModelsUsingBruteForceApproachAndSingletonAwareMethod_ = false;
        }

        // Create a mapping used for assignments
        VarT varIndex = 0;
        VarT numberOfSingletonVariables = 0;
        VarT indexOfSingletonVariables = static_cast<VarT>(currentComponentVariableSet.size());
        for (VarT var : currentComponentVariableSet) {
            // Singleton variable
            if (formulaRepresentationAbstractUniquePtr_->isVariableSingleton(var)) {
                ++numberOfSingletonVariables;
                l_variableToIndexVectorMapping_computeNumberOfModelsUsingBruteForceApproach_[var] = indexOfSingletonVariables;

                continue;
            }

            l_variableToIndexVectorMapping_computeNumberOfModelsUsingBruteForceApproach_[var] = varIndex;
            ++varIndex;
        }

        assert(varIndex <= S_MAX_NUMBER_OF_VARIABLES_FOR_BRUTE_FORCE_APPROACH_);   // valid number of non-singleton variables

        // Get the clauses
        formulaRepresentationAbstractUniquePtr_->getCurrentComponentClauses(currentComponentVariableSet,
                                                                            l_clauseIdReusableVector_computeNumberOfModelsUsingBruteForceApproach_);

        assert(l_clauseIdReusableVector_computeNumberOfModelsUsingBruteForceApproach_.size() <= S_MAX_NUMBER_OF_CLAUSES_FOR_BRUTE_FORCE_APPROACH_);   // valid number of clauses

        l_numberOfSingletonVariablesInClauseReusableVector_computeNumberOfModelsUsingBruteForceApproachAndSingletonAwareMethod_.clear();

        // Precompute the number of singleton variables for each clause
        VarT remainingNumberOfSingletonVariables = numberOfSingletonVariables;
        for (ClauseIdT clauseId : l_clauseIdReusableVector_computeNumberOfModelsUsingBruteForceApproach_) {
            // All the singleton variables have been processed
            if (remainingNumberOfSingletonVariables == 0) {
                l_numberOfSingletonVariablesInClauseReusableVector_computeNumberOfModelsUsingBruteForceApproachAndSingletonAwareMethod_.emplace_back(0);

                continue;
            }

            VarT numberOfSingletonVariablesInClause = 0;

            for (auto clauseIt = formulaRepresentationAbstractUniquePtr_->beginClause(clauseId);
                 clauseIt != formulaRepresentationAbstractUniquePtr_->endClause(); ++clauseIt) {
                // Singleton variable
                if (l_variableToIndexVectorMapping_computeNumberOfModelsUsingBruteForceApproach_[clauseIt->getVariable()] == indexOfSingletonVariables) {
                    ++numberOfSingletonVariablesInClause;
                    --remainingNumberOfSingletonVariables;
                }
            }

            l_numberOfSingletonVariablesInClauseReusableVector_computeNumberOfModelsUsingBruteForceApproachAndSingletonAwareMethod_.emplace_back(numberOfSingletonVariablesInClause);
        }

        NumberOfModelsType numberOfModels = 0;
        std::size_t maxNumberOfAssignments = static_cast<std::size_t>(1) << (currentComponentVariableSet.size() - static_cast<std::size_t>(numberOfSingletonVariables));   // 2^|non-singleton variable|

        // Iterate assignments
        for (std::size_t assignment = 0; assignment < maxNumberOfAssignments; ++assignment) {
            bool isSatisfied = true;
            NumberOfModelsType numberOfModelsForAssignment = 1;

            // Iterate clauses
            ClauseIdT clauseIndex = 0;
            for (ClauseIdT clauseId : l_clauseIdReusableVector_computeNumberOfModelsUsingBruteForceApproach_) {
                bool isClauseSatisfiedByNonSingletonVariable = false;

                // Iterate literals
                for (auto clauseIt = formulaRepresentationAbstractUniquePtr_->beginClause(clauseId);
                     clauseIt != formulaRepresentationAbstractUniquePtr_->endClause(); ++clauseIt) {
                    VarT var = clauseIt->getVariable();

                    assert(Other::containInSet(currentComponentVariableSet, var));

                    // Singleton variable
                    if (l_variableToIndexVectorMapping_computeNumberOfModelsUsingBruteForceApproach_[var] == indexOfSingletonVariables)
                        continue;

                    bool value = (assignment >> static_cast<std::size_t>(l_variableToIndexVectorMapping_computeNumberOfModelsUsingBruteForceApproach_[var])) & 1;

                    // The clause is satisfied
                    if ((clauseIt->isPositive() && value) || (clauseIt->isNegative() && !value)) {
                        isClauseSatisfiedByNonSingletonVariable = true;

                        break;
                    }
                }

                assert(clauseIndex < l_numberOfSingletonVariablesInClauseReusableVector_computeNumberOfModelsUsingBruteForceApproachAndSingletonAwareMethod_.size());

                VarT numberOfSingletonVariablesInClause = l_numberOfSingletonVariablesInClauseReusableVector_computeNumberOfModelsUsingBruteForceApproachAndSingletonAwareMethod_[clauseIndex];

                // No singleton variables
                if (numberOfSingletonVariablesInClause == 0) {
                    // The clause is NOT satisfied
                    if (!isClauseSatisfiedByNonSingletonVariable) {
                        isSatisfied = false;

                        break;
                    }
                }
                // There are singleton variables in the clause
                else {
                    NumberOfModelsType numberOfModelsTmp = computePowerOfTwo(static_cast<std::size_t>(numberOfSingletonVariablesInClause));   // 2^|singleton variable in clause|

                    // The singleton variables must satisfy the clause; there are 2^|singleton variable in clause| - 1 possible assignments
                    if (!isClauseSatisfiedByNonSingletonVariable)
                        --numberOfModelsTmp;

                    numberOfModelsForAssignment *= numberOfModelsTmp;
                }

                ++clauseIndex;
            }

            if (isSatisfied)
                numberOfModels += numberOfModelsForAssignment;
        }

        return numberOfModels;
    }
}   // namespace Hydra
