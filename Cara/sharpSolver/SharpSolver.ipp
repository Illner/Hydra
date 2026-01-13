#pragma once

#include "Hydra/compiler/Compiler.hpp"

namespace Hydra {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    Compiler<VarT, LiteralT, ClauseIdT>::NumberOfModelsType Compiler<VarT, LiteralT, ClauseIdT>::computePowerOfTwo(std::size_t exponent) const {
        return (NumberOfModelsType("1") << exponent);   // 2^exponent
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    Compiler<VarT, LiteralT, ClauseIdT>::ComponentCacheValueType Compiler<VarT, LiteralT, ClauseIdT>::compileOneComponent(VariableSetType& currentComponentVariableSet,
                                                                                                                          VariableSetType&& hypergraphCut,
                                                                                                                          EquivalencePreprocessingStructPtrType equivalencePreprocessingStructPtr,
                                                                                                                          bool computeNewHypergraphCut) {
        assert(satSolverAbstractUniquePtr_->isSatisfiable(currentComponentVariableSet));   // current formula is satisfiable
        assert(equivalencePreprocessingStructPtr == nullptr || computeNewHypergraphCut);
        assert(formulaRepresentationAbstractUniquePtr_->computeConnectedComponents(currentComponentVariableSet).size() == 1);   // only one component

        bool validHypergraphCut = true;

        // Component cache
        CacheRecordStruct componentCacheRecordStruct = componentCacheUniquePtr_->createCacheRecordStruct(currentComponentVariableSet);
        CacheValuePtrAndIdPairOptionalComponentCachingType componentCacheSearchResult = componentCacheUniquePtr_->searchInCache(componentCacheRecordStruct);

        // Component cache - positive hit
        if (componentCacheSearchResult.has_value()) {
            // No removed variables
            if (componentCacheRecordStruct.numberOfRemovedVariables == 0)
                return *(componentCacheSearchResult->first);
            // There are some removed variables
            else
                return *(componentCacheSearchResult->first) << static_cast<std::size_t>(componentCacheRecordStruct.numberOfRemovedVariables);   // models * 2^|removed variable|
        }

        // Checking if the (singleton-aware) brute-force approach can be used
        if (formulaRepresentationAbstractUniquePtr_->getNumberOfCurrentComponentClauses(currentComponentVariableSet) <= configuration_.numberOfClausesThresholdForBruteForceApproach) {
            VarT numberOfVariables = static_cast<VarT>(currentComponentVariableSet.size());
            VarT numberOfSingletonVariables = formulaRepresentationAbstractUniquePtr_->getNumberOfSingletonVariables(currentComponentVariableSet);
            VarT numberOfNonSingletonVariables = numberOfVariables - numberOfSingletonVariables;

            // Brute-force approach
            if (numberOfNonSingletonVariables <= configuration_.numberOfVariablesThresholdForBruteForceApproach) {
                NumberOfModelsType numberOfModels;

                // Brute-force approach
                if (numberOfVariables <= configuration_.numberOfVariablesThresholdForBruteForceApproach)
                    numberOfModels = computeNumberOfModelsUsingBruteForceApproach(currentComponentVariableSet);
                // Singleton-aware brute-force approach
                else
                    numberOfModels = computeNumberOfModelsUsingBruteForceApproachAndSingletonAwareMethod(currentComponentVariableSet);

                // Component cache
                // No removed variables
                if (componentCacheRecordStruct.numberOfRemovedVariables == 0)
                    componentCacheUniquePtr_->addCacheRecordToCache(std::move(componentCacheRecordStruct), NumberOfModelsType(numberOfModels));
                // There are some removed variables
                else {
                    assert((numberOfModels & (1 << static_cast<std::size_t>(componentCacheRecordStruct.numberOfRemovedVariables - 1))) == 0);   // the number of models is divisible by 2^|removed variable|

                    NumberOfModelsType numberOfModelsWithoutRemovedVariables = numberOfModels >> static_cast<std::size_t>(componentCacheRecordStruct.numberOfRemovedVariables);
                    componentCacheUniquePtr_->addCacheRecordToCache(std::move(componentCacheRecordStruct), std::move(numberOfModelsWithoutRemovedVariables));
                }

                return numberOfModels;
            }
        }

        // Hypergraph cut cache
        CacheRecordStruct hypergraphCutCacheRecordStruct = hypergraphCutCacheUniquePtr_->createCacheRecordStruct(currentComponentVariableSet);
        CacheValuePtrAndIdPairOptionalHypergraphCutCachingType hypergraphCutCacheSearchResult = hypergraphCutCacheUniquePtr_->searchInCache(hypergraphCutCacheRecordStruct);

        // Hypergraph cut cache - positive hit
        if (hypergraphCutCacheSearchResult.has_value()) {
            MappingFromVariableToLiteralType hypergraphCutCacheMapping = hypergraphCutCacheUniquePtr_->createMapping(hypergraphCutCacheSearchResult->second, hypergraphCutCacheRecordStruct);

            hypergraphCut = VariableSetType(hypergraphCutCacheSearchResult->first->size());

            // Identity
            if (hypergraphCutCacheMapping.empty()) {
                for (VarT var : *(hypergraphCutCacheSearchResult->first))
                    hypergraphCut.emplace(var);
            }
            // Non-identity
            else {
                for (VarT var : *(hypergraphCutCacheSearchResult->first)) {
                    assert(Other::containInMap(hypergraphCutCacheMapping, var));   // variable exists in the mapping
                    assert(hypergraphCutCacheMapping.at(var).isPositive());        // variable to variable mapping

                    hypergraphCut.emplace(hypergraphCutCacheMapping.at(var).getVariable());
                }
            }
        }
        // Compute a new hypergraph cut
        else if (computeNewHypergraphCut) {
            // Not enough variables or too many variables
            if ((currentComponentVariableSet.size() <= configuration_.notEnoughVariablesForComputingHypergraphCut) ||
                (currentComponentVariableSet.size() >= configuration_.tooManyVariablesForComputingHypergraphCut))
                hypergraphCut.clear();
            // The equivalence simplification method is NOT applied
            else if (equivalencePreprocessingStructPtr == nullptr)
                hypergraphCut = partitioningHypergraphAbstractUniquePtr_->computeCut(currentComponentVariableSet, validHypergraphCut);
            // The equivalence simplification method is applied
            else
                hypergraphCut = partitioningHypergraphAbstractUniquePtr_->computeCut(currentComponentVariableSet, validHypergraphCut,
                                                                                     *equivalencePreprocessingStructPtr);
        }

        // Decision variable
        VarT decisionVariable = 0;

        // No hypergraph cut exists (can happen)
        if (hypergraphCut.empty())
            decisionVariable = decisionHeuristicAbstractUniquePtr_->getDecisionVariable(currentComponentVariableSet, false);
        else
            decisionVariable = decisionHeuristicAbstractUniquePtr_->getDecisionVariable(hypergraphCut, false);

        assert(decisionVariable != 0);   // decision variable has been set

        // Invalid hypergraph cut
        if (!validHypergraphCut)
            hypergraphCut.clear();

        // Positive literal
        LiteralType posLit(decisionVariable, true);
        VariableVectorType posFreeVariableVector = assignLiteralVectorInFormulaAndSatSolver({ posLit }, currentComponentVariableSet);
        NumberOfModelsType posNumberOfModels = compileMoreComponents(currentComponentVariableSet, hypergraphCut);
        unassignLiteralVectorInFormulaAndSatSolver({ posLit }, currentComponentVariableSet);

        // Negative literal
        LiteralType negLit(decisionVariable, false);
        VariableVectorType negFreeVariableVector = assignLiteralVectorInFormulaAndSatSolver({ negLit }, currentComponentVariableSet);
        NumberOfModelsType negNumberOfModels = compileMoreComponents(currentComponentVariableSet, hypergraphCut);
        unassignLiteralVectorInFormulaAndSatSolver({ negLit }, currentComponentVariableSet);

        NumberOfModelsType numberOfModels = (computePowerOfTwo(static_cast<std::size_t>(posFreeVariableVector.size())) * posNumberOfModels) +   // 2^|posFreeVariableVector| * posNumberOfModels
                                            (computePowerOfTwo(static_cast<std::size_t>(negFreeVariableVector.size())) * negNumberOfModels);    // 2^|negFreeVariableVector| * negNumberOfModels

        // Component cache
        // No removed variables
        if (componentCacheRecordStruct.numberOfRemovedVariables == 0)
            componentCacheUniquePtr_->addCacheRecordToCache(std::move(componentCacheRecordStruct), NumberOfModelsType(numberOfModels));
        // There are some removed variables
        else {
            assert((numberOfModels & (1 << static_cast<std::size_t>(componentCacheRecordStruct.numberOfRemovedVariables - 1))) == 0);   // the number of models is divisible by 2^|removed variable|

            NumberOfModelsType numberOfModelsWithoutRemovedVariables = numberOfModels >> static_cast<std::size_t>(componentCacheRecordStruct.numberOfRemovedVariables);
            componentCacheUniquePtr_->addCacheRecordToCache(std::move(componentCacheRecordStruct), std::move(numberOfModelsWithoutRemovedVariables));
        }

        // Hypergraph cut cache
        if (!hypergraphCutCacheSearchResult.has_value() && computeNewHypergraphCut && validHypergraphCut)
            hypergraphCutCacheUniquePtr_->addCacheRecordToCache(std::move(hypergraphCutCacheRecordStruct), VariableVectorType(hypergraphCut.cbegin(), hypergraphCut.cend()));

        return numberOfModels;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    Compiler<VarT, LiteralT, ClauseIdT>::ComponentCacheValueType Compiler<VarT, LiteralT, ClauseIdT>::compileMoreComponents(VariableSetType& currentComponentVariableSet,
                                                                                                                            const VariableSetType& hypergraphCut,
                                                                                                                            EquivalencePreprocessingStructPtrType equivalencePreprocessingStructPtr,
                                                                                                                            bool firstCall) {
        // The current formula is a tautology
        if (currentComponentVariableSet.empty())
            return ONE_MODEL_;

        if (!firstCall && equivalencePreprocessingStructPtr == nullptr) {
            // The current formula is not satisfiable
            if (!satSolverAbstractUniquePtr_->isSatisfiable(currentComponentVariableSet))
                return ZERO_MODELS_;
        }

        VarT numberOfVariablesBeforeUnitPropagation = static_cast<VarT>(currentComponentVariableSet.size());

        [[maybe_unused]] bool isSatisfiable = satSolverAbstractUniquePtr_->unitPropagation(currentComponentVariableSet, false);
        assert(isSatisfiable);   // current formula is satisfiable

        // Get (unsorted) implied literals
        LiteralVectorType impliedLiteralVector = satSolverAbstractUniquePtr_->getImpliedLiteralVectorFromPreviousCallOfUnitPropagation(false);

        VariableVectorType freeVariableVector = assignLiteralVectorInFormulaAndSatSolver(impliedLiteralVector, currentComponentVariableSet);

        VarT numberOfVariablesAfterUnitPropagation = static_cast<VarT>(currentComponentVariableSet.size());

        // The current formula is a tautology
        if (currentComponentVariableSet.empty()) {
            unassignLiteralVectorInFormulaAndSatSolver(impliedLiteralVector, currentComponentVariableSet);

            return computePowerOfTwo(static_cast<std::size_t>(freeVariableVector.size()));   // 2^|freeVariableVector|
        }

        ConnectedComponentType connectedComponents = formulaRepresentationAbstractUniquePtr_->computeConnectedComponents(currentComponentVariableSet);

        assert(!connectedComponents.empty());   // at least one component

        NumberOfModelsType numberOfModels = computePowerOfTwo(static_cast<std::size_t>(freeVariableVector.size()));   // 2^|freeVariableVector|

        for (ConnectedComponentStruct& newConnectedComponentStruct : connectedComponents) {
            PureVariableRemovedClausesVectorType pureVariableRemovedClausesVector = formulaRepresentationAbstractUniquePtr_->setNewComponent(newConnectedComponentStruct, ignorePureLiteralType_);

            assert(pureVariableRemovedClausesVector.empty());

            // Restricted hypergraph cut
            VariableSetType restrictedHypergraphCut(hypergraphCut.size());

            if (equivalencePreprocessingStructPtr == nullptr) {
                for (VarT var : hypergraphCut) {
                    if (Other::containInSet(newConnectedComponentStruct.variableSet, var))
                        restrictedHypergraphCut.emplace(var);
                }
            }

            bool computeNewHypergraphCut = (equivalencePreprocessingStructPtr != nullptr) ||
                                           shouldHypergraphCutBeRecomputed(restrictedHypergraphCut, hypergraphCut, (connectedComponents.size() > 1),
                                                                           numberOfVariablesBeforeUnitPropagation, numberOfVariablesAfterUnitPropagation);

            if (equivalencePreprocessingStructPtr == nullptr) {
                // Do NOT use the equivalence simplification method
                if ((newConnectedComponentStruct.variableSet.size() <= configuration_.notEnoughVariablesForComputingHypergraphCut) ||
                    (newConnectedComponentStruct.variableSet.size() >= configuration_.tooManyVariablesForComputingHypergraphCut) ||
                    !computeNewHypergraphCut || (computeNewHypergraphCut && !configuration_.useEquivalenceSimplificationMethod)) {
                    numberOfModels *= compileOneComponent(newConnectedComponentStruct.variableSet, std::move(restrictedHypergraphCut),
                                                          nullptr, computeNewHypergraphCut);
                }
                // Use the equivalence simplification method
                else {
                    assert(computeNewHypergraphCut);

                    EquivalencePreprocessingStruct equivalencePreprocessingStruct = satSolverAbstractUniquePtr_->createEquivalencePreprocessingStruct(newConnectedComponentStruct.variableSet,
                                                                                                                                                      configuration_.ignoreMultiOccurrentIgnoredVariables,
                                                                                                                                                      configuration_.implicitBcpVariableOrderType);

                    VariableVectorType implicitFreeVariableVector = assignLiteralVectorInFormulaAndSatSolver(equivalencePreprocessingStruct.implicitImpliedLiteralVector,
                                                                                                             newConnectedComponentStruct.variableSet, false);

                    // No implicit implied literals
                    if (equivalencePreprocessingStruct.implicitImpliedLiteralVector.empty())
                        numberOfModels *= compileOneComponent(newConnectedComponentStruct.variableSet, {},
                                                              &equivalencePreprocessingStruct, computeNewHypergraphCut);
                    else
                        numberOfModels *= compileMoreComponents(newConnectedComponentStruct.variableSet, {}, &equivalencePreprocessingStruct);

                    unassignLiteralVectorInFormulaAndSatSolver(equivalencePreprocessingStruct.implicitImpliedLiteralVector, newConnectedComponentStruct.variableSet);

                    // Implicit free variables
                    numberOfModels *= computePowerOfTwo(static_cast<std::size_t>(implicitFreeVariableVector.size()));   // 2^|implicitFreeVariableVector|
                }
            }
            else {
                assert(computeNewHypergraphCut);

                numberOfModels *= compileOneComponent(newConnectedComponentStruct.variableSet, {},
                                                      equivalencePreprocessingStructPtr, computeNewHypergraphCut);
            }

            formulaRepresentationAbstractUniquePtr_->popPreviousComponent(newConnectedComponentStruct, pureVariableRemovedClausesVector);
        }

        unassignLiteralVectorInFormulaAndSatSolver(impliedLiteralVector, currentComponentVariableSet);

        return numberOfModels;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool Compiler<VarT, LiteralT, ClauseIdT>::isNumberOfModelsComputed() const noexcept {
        return isNumberOfModelsComputed_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    const Compiler<VarT, LiteralT, ClauseIdT>::NumberOfModelsType& Compiler<VarT, LiteralT, ClauseIdT>::getComputedNumberOfModels() const {
        // The number of models has not yet been computed
        if (!isNumberOfModelsComputed_)
            throw Exception::NumberOfModelsHasNotYetBeenComputedException();

        return numberOfModels_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void Compiler<VarT, LiteralT, ClauseIdT>::computeNumberOfModels() {
        // The number of models has already been computed
        if (isNumberOfModelsComputed_)
            return;

        VarT numberOfMissingVariables = 0;

        // Create the current component set
        VariableSetType currentComponentVariableSet(formulaRepresentationAbstractUniquePtr_->getNumberOfVariablesInOriginalFormula());
        for (VarT var = 1; var <= formulaRepresentationAbstractUniquePtr_->getNumberOfVariablesInOriginalFormula(); ++var) {
            // Free variables are ignored
            if (formulaRepresentationAbstractUniquePtr_->isVariableFree(var)) {
                ++numberOfMissingVariables;

                continue;
            }

            currentComponentVariableSet.emplace(var);
        }

        LiteralVectorType initiallyImpliedLiterals;

        // The formula is satisfiable
        if (satSolverAbstractUniquePtr_->isSatisfiable()) {
            satSolverAbstractUniquePtr_->initialSimplification();

            initiallyImpliedLiterals = satSolverAbstractUniquePtr_->getInitiallyImpliedLiterals();
            // std::sort(initiallyImpliedLiterals.begin(), initiallyImpliedLiterals.end());   // because of assignment

            VariableVectorType freeVariableVector = assignLiteralVectorInFormulaAndSatSolver(initiallyImpliedLiterals, currentComponentVariableSet);

            numberOfMissingVariables += static_cast<VarT>(freeVariableVector.size());                  // take the free variables into account
            numberOfModels_ = computePowerOfTwo(static_cast<std::size_t>(numberOfMissingVariables));   // 2^numberOfMissingVariables

            numberOfModels_ *= compileMoreComponents(currentComponentVariableSet, {}, nullptr, true);
        }

        unassignLiteralVectorInFormulaAndSatSolver(initiallyImpliedLiterals, currentComponentVariableSet);

        isNumberOfModelsComputed_ = true;
    }
}   // namespace Hydra
