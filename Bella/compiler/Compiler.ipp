#pragma once

#include "Hydra/compiler/Compiler.hpp"

namespace Hydra {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void Compiler<VarT, LiteralT, ClauseIdT>::initializeCircuit() {
        // The circuit type is not supported
        if (!Other::containInSet(Circuit::supportCompilationCircuitTypeSet, configuration_.circuitType))
            throw Exception::CompilingIntoCircuitTypeIsNotSupportedException(configuration_.circuitType);

        circuitUniquePtr_ = std::make_unique<CircuitType>(formulaRepresentationAbstractUniquePtr_->getNumberOfVariablesInOriginalFormula(), smoothness_,
                                                          MappingFromVariableToOriginalVariableType(), MappingFromOriginalVariableToVariableType(),
                                                          statisticsPtr_ ? statisticsPtr_->getCircuitStatisticsPtr() : nullptr);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    IdNodeType Compiler<VarT, LiteralT, ClauseIdT>::compilePureClauses(const VariableSetType& currentComponentVariableSet,
                                                                       const ClauseIdSetType& pureClauseSet) {
        // Statistics
        if (compilerStatisticsPtr_)
            compilerStatisticsPtr_->ratioOfNumberOfPureClausesToNumberOfClausesCounter.addCount(static_cast<Statistics::LargeFloatingNumberType>(pureClauseSet.size()) / static_cast<Statistics::LargeFloatingNumberType>(formulaRepresentationAbstractUniquePtr_->getNumberOfCurrentComponentClauses(currentComponentVariableSet)));

        if (pureClauseSet.empty()) {
            // Statistics
            if (compilerStatisticsPtr_)
                compilerStatisticsPtr_->ratioOfPureResidualFormulaSizeToResidualFormulaSizeCounter.addCount(static_cast<Statistics::LargeFloatingNumberType>(0));

            return trueLeafIdNode_;
        }

        IdNodeVectorType clauseIdNodeVector;
        clauseIdNodeVector.reserve(pureClauseSet.size());

        LiteralVectorType literalVector;
        literalVector.reserve(currentComponentVariableSet.size());

        LargeNumberType pureResidualFormulaSize = 0;

        #ifndef NDEBUG
        for (ClauseIdT clauseId : Other::sortUnorderedSet(pureClauseSet)) {
        #else
        for (ClauseIdT clauseId : pureClauseSet) {
        #endif
            literalVector.clear();

            for (auto clauseIt = formulaRepresentationAbstractUniquePtr_->beginClause(clauseId);
                 clauseIt != formulaRepresentationAbstractUniquePtr_->endClause(); ++clauseIt) {
                assert(formulaRepresentationAbstractUniquePtr_->isPureLiteralInCurrentFormula(clauseIt->getVariable(), ignorePureLiteralType_));   // ignored pure variable

                literalVector.emplace_back(clauseIt->getVariable(), clauseIt->isPositive());
            }

            assert(!literalVector.empty());   // at least one literal

            pureResidualFormulaSize += static_cast<LargeNumberType>(literalVector.size());

            clauseIdNodeVector.emplace_back(circuitUniquePtr_->createOrInnerNode(literalVector));
        }

        assert(clauseIdNodeVector.size() == pureClauseSet.size());

        // Statistics
        if (compilerStatisticsPtr_)
            compilerStatisticsPtr_->ratioOfPureResidualFormulaSizeToResidualFormulaSizeCounter.addCount(static_cast<Statistics::LargeFloatingNumberType>(pureResidualFormulaSize) / static_cast<Statistics::LargeFloatingNumberType>(formulaRepresentationAbstractUniquePtr_->getCurrentComponentFormulaSize(currentComponentVariableSet)));

        return circuitUniquePtr_->createAndInnerNode(clauseIdNodeVector, bellaFormulaDecomposabilityType_);
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
            MappingFromVariableToLiteralType componentCacheMapping = componentCacheUniquePtr_->createMapping(componentCacheSearchResult->second, componentCacheRecordStruct);

            return circuitUniquePtr_->copySubcircuit(*(componentCacheSearchResult->first), componentCacheMapping,
                                                     configuration_.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping,
                                                     currentComponentVariableSet, formulaRepresentationAbstractUniquePtr_.get());
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

            #ifndef NDEBUG
            // No ignored pure variable in the cached hypergraph cut
            for (VarT var : hypergraphCut)
                assert(!formulaRepresentationAbstractUniquePtr_->isPureLiteralInCurrentFormula(var, ignorePureLiteralType_));
            #endif
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

            // Statistics
            if (compilerStatisticsPtr_)
                compilerStatisticsPtr_->ratioOfNumberOfEmptyHypergraphCutsToNumberOfHypergraphCutsCounter.addCount(static_cast<Statistics::LargeNumberType>(hypergraphCut.empty()));
        }

        // Decision variable
        VarT decisionVariable = 0;

        // No hypergraph cut exists (can happen)
        if (hypergraphCut.empty())
            decisionVariable = decisionHeuristicAbstractUniquePtr_->getDecisionVariable(currentComponentVariableSet, true);
        else
            decisionVariable = decisionHeuristicAbstractUniquePtr_->getDecisionVariable(hypergraphCut, false);

        assert(decisionVariable != 0);   // decision variable has been set

        // Invalid hypergraph cut
        if (!validHypergraphCut)
            hypergraphCut.clear();

        // Statistics
        if (compilerStatisticsPtr_)
            compilerStatisticsPtr_->numberOfDecisionsIncrement.incrementNumber();

        // Positive literal
        LiteralType posLit(decisionVariable, true);
        VariableVectorType posFreeVariableVector = assignLiteralVectorInFormulaAndSatSolver({ posLit }, currentComponentVariableSet);
        IdNodeType posIdNode = compileMoreComponents(currentComponentVariableSet, hypergraphCut);
        unassignLiteralVectorInFormulaAndSatSolver({ posLit }, currentComponentVariableSet);

        // Negative literal
        LiteralType negLit(decisionVariable, false);
        VariableVectorType negFreeVariableVector = assignLiteralVectorInFormulaAndSatSolver({ negLit }, currentComponentVariableSet);
        IdNodeType negIdNode = compileMoreComponents(currentComponentVariableSet, hypergraphCut);
        unassignLiteralVectorInFormulaAndSatSolver({ negLit }, currentComponentVariableSet);

        IdNodeType idNode = circuitUniquePtr_->createDecisionInnerNode(decisionVariable,
                                                                       posIdNode, negIdNode,
                                                                       posFreeVariableVector, negFreeVariableVector);

        // Component cache
        componentCacheUniquePtr_->addCacheRecordToCache(std::move(componentCacheRecordStruct), std::move(idNode));

        // Hypergraph cut cache
        if (!hypergraphCutCacheSearchResult.has_value() && computeNewHypergraphCut && validHypergraphCut)
            hypergraphCutCacheUniquePtr_->addCacheRecordToCache(std::move(hypergraphCutCacheRecordStruct), VariableVectorType(hypergraphCut.cbegin(), hypergraphCut.cend()));

        return idNode;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    Compiler<VarT, LiteralT, ClauseIdT>::ComponentCacheValueType Compiler<VarT, LiteralT, ClauseIdT>::compileMoreComponents(VariableSetType& currentComponentVariableSet,
                                                                                                                            const VariableSetType& hypergraphCut,
                                                                                                                            EquivalencePreprocessingStructPtrType equivalencePreprocessingStructPtr,
                                                                                                                            bool firstCall) {
        // The timeout has expired
        if (killedByMainThread_ && killedByMainThread_->load(std::memory_order::relaxed))
            throw Exception::TimeoutException();

        // The current formula is a tautology
        if (currentComponentVariableSet.empty())
            return trueLeafIdNode_;

        if (!firstCall && equivalencePreprocessingStructPtr == nullptr) {
            // The current formula is not satisfiable
            if (!satSolverAbstractUniquePtr_->isSatisfiable(currentComponentVariableSet)) {
                // Statistics
                if (compilerStatisticsPtr_)
                    compilerStatisticsPtr_->numberOfUnsatisfiableResidualFormulaeIncrement.incrementNumber();

                return falseLeafIdNode_;
            }
        }

        VarT numberOfVariablesBeforeUnitPropagation = static_cast<VarT>(currentComponentVariableSet.size());

        [[maybe_unused]] bool isSatisfiable = satSolverAbstractUniquePtr_->unitPropagation(currentComponentVariableSet, false);
        assert(isSatisfiable);   // current formula is satisfiable

        // Get (sorted) implied literals
        LiteralVectorType impliedLiteralVector = satSolverAbstractUniquePtr_->getImpliedLiteralVectorFromPreviousCallOfUnitPropagation(true);

        VariableVectorType freeVariableVector = assignLiteralVectorInFormulaAndSatSolver(impliedLiteralVector, currentComponentVariableSet);

        VarT numberOfVariablesAfterUnitPropagation = static_cast<VarT>(currentComponentVariableSet.size());

        // Free variables
        IdNodeType freeVariablesIdNode = trueLeafIdNode_;
        if (!freeVariableVector.empty()) {
            IdNodeVectorType freeVariableIdNodeVectorTmp;
            freeVariableIdNodeVectorTmp.reserve(freeVariableVector.size());

            for (VarT var : freeVariableVector)
                freeVariableIdNodeVectorTmp.emplace_back(circuitUniquePtr_->createTrivialOrInnerNode(var));

            freeVariablesIdNode = circuitUniquePtr_->createAndInnerNode(freeVariableIdNodeVectorTmp, DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);
        }

        // Implied literals
        IdNodeType impliedLiteralsIdNode = trueLeafIdNode_;
        if (!impliedLiteralVector.empty())
            impliedLiteralsIdNode = circuitUniquePtr_->createAndInnerNode(impliedLiteralVector, true);

        // The current formula is a tautology
        if (currentComponentVariableSet.empty()) {
            unassignLiteralVectorInFormulaAndSatSolver(impliedLiteralVector, currentComponentVariableSet);

            // Statistics
            if (compilerStatisticsPtr_)
                compilerStatisticsPtr_->numberOfEmptyResidualFormulaeIncrement.incrementNumber();

            // No implied literals and free variables
            if ((impliedLiteralsIdNode == trueLeafIdNode_) && (freeVariablesIdNode == trueLeafIdNode_))
                return trueLeafIdNode_;

            // No implied literals
            if (impliedLiteralsIdNode == trueLeafIdNode_)
                return freeVariablesIdNode;

            // No free variables
            if (freeVariablesIdNode == trueLeafIdNode_)
                return impliedLiteralsIdNode;

            return circuitUniquePtr_->createAndInnerNode({ impliedLiteralsIdNode, freeVariablesIdNode },
                                                         DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);
        }

        ClauseIdSetType pureClauseSet;
        ConnectedComponentType connectedComponents;

        // Sharing variables is allowed
        if (sharingVariables_) {
            connectedComponents = formulaRepresentationAbstractUniquePtr_->computeConnectedComponents(currentComponentVariableSet, pureClauseSet,
                                                                                                      ignorePureLiteralType_);

            assert(connectedComponents.empty() || (pureClauseSet.size() != formulaRepresentationAbstractUniquePtr_->getNumberOfCurrentComponentClauses(currentComponentVariableSet)));
        }
        // Sharing variables is forbidden
        else {
            connectedComponents = formulaRepresentationAbstractUniquePtr_->computeConnectedComponents(currentComponentVariableSet);

            assert(!connectedComponents.empty());   // at least one component
        }

        // Statistics
        if (compilerStatisticsPtr_) {
            compilerStatisticsPtr_->numberOfConnectedComponentsCounter.addCount(static_cast<Statistics::LargeNumberType>(connectedComponents.size()));
            compilerStatisticsPtr_->numberOfSplitsIncrement.incrementNumber(static_cast<Statistics::LargeNumberType>(connectedComponents.size() > 1 ? connectedComponents.size() : 0));

            compilerStatisticsPtr_->ratioOfNumberOfMonotoneResidualFormulaeToNumberOfResidualFormulaeCounter.addCount(static_cast<Statistics::LargeNumberType>(connectedComponents.empty()));
            if (connectedComponents.empty())
                compilerStatisticsPtr_->monotoneResidualFormulaSizeCounter.addCount(static_cast<Statistics::LargeNumberType>(formulaRepresentationAbstractUniquePtr_->getCurrentComponentFormulaSize(currentComponentVariableSet)));
        }

        IdNodeVectorType idNodeConnectedComponents;
        idNodeConnectedComponents.reserve(static_cast<typename IdNodeVectorType::size_type>(3) + connectedComponents.size());   // plus 3 for the implied literals, free variables, and pure clauses

        // Pure clauses
        IdNodeType pureClausesIdNode = compilePureClauses(currentComponentVariableSet, pureClauseSet);
        formulaRepresentationAbstractUniquePtr_->removeClausesContainingOnlyPureLiteralsOfIgnoredType(pureClauseSet, ignorePureLiteralType_);

        for (ConnectedComponentStruct& newConnectedComponentStruct : connectedComponents) {
            PureVariableRemovedClausesVectorType pureVariableRemovedClausesVector = formulaRepresentationAbstractUniquePtr_->setNewComponent(newConnectedComponentStruct, ignorePureLiteralType_);

            // Restricted hypergraph cut
            VariableSetType restrictedHypergraphCut(hypergraphCut.size());

            if (equivalencePreprocessingStructPtr == nullptr) {
                for (VarT var : hypergraphCut) {
                    if (Other::containInSet(newConnectedComponentStruct.variableSet, var) &&
                        !this->formulaRepresentationAbstractUniquePtr_->isPureLiteralInCurrentFormula(var, ignorePureLiteralType_))
                        restrictedHypergraphCut.emplace(var);
                }
            }

            bool computeNewHypergraphCut = (equivalencePreprocessingStructPtr != nullptr) ||
                                           shouldHypergraphCutBeRecomputed(restrictedHypergraphCut, hypergraphCut, (connectedComponents.size() > 1),
                                                                           numberOfVariablesBeforeUnitPropagation, numberOfVariablesAfterUnitPropagation);

            // Statistics
            if (compilerStatisticsPtr_)
                compilerStatisticsPtr_->ratioOfRecomputedHypergraphCutsCounter.addCount(static_cast<Statistics::LargeNumberType>(computeNewHypergraphCut));

            if (equivalencePreprocessingStructPtr == nullptr) {
                // Do NOT use the equivalence simplification method
                if ((newConnectedComponentStruct.variableSet.size() <= configuration_.notEnoughVariablesForComputingHypergraphCut) ||
                    (newConnectedComponentStruct.variableSet.size() >= configuration_.tooManyVariablesForComputingHypergraphCut) ||
                    !computeNewHypergraphCut || (computeNewHypergraphCut && !configuration_.useEquivalenceSimplificationMethod)) {
                    IdNodeType idNodeTmp = compileOneComponent(newConnectedComponentStruct.variableSet, std::move(restrictedHypergraphCut),
                                                               nullptr, computeNewHypergraphCut);
                    idNodeConnectedComponents.emplace_back(idNodeTmp);
                }
                // Use the equivalence simplification method
                else {
                    assert(computeNewHypergraphCut);

                    EquivalencePreprocessingStruct equivalencePreprocessingStruct = satSolverAbstractUniquePtr_->createEquivalencePreprocessingStruct(newConnectedComponentStruct.variableSet,
                                                                                                                                                      configuration_.ignoreMultiOccurrentIgnoredVariables,
                                                                                                                                                      configuration_.implicitBcpVariableOrderType);

                    VariableVectorType implicitFreeVariableVector = assignLiteralVectorInFormulaAndSatSolver(equivalencePreprocessingStruct.implicitImpliedLiteralVector,
                                                                                                             newConnectedComponentStruct.variableSet, false);

                    IdNodeType idNodeTmp;

                    // No implicit implied literals
                    if (equivalencePreprocessingStruct.implicitImpliedLiteralVector.empty())
                        idNodeTmp = compileOneComponent(newConnectedComponentStruct.variableSet, {},
                                                        &equivalencePreprocessingStruct, computeNewHypergraphCut);
                    else
                        idNodeTmp = compileMoreComponents(newConnectedComponentStruct.variableSet, {}, &equivalencePreprocessingStruct);

                    unassignLiteralVectorInFormulaAndSatSolver(equivalencePreprocessingStruct.implicitImpliedLiteralVector, newConnectedComponentStruct.variableSet);

                    // Implicit implied literals
                    if (!equivalencePreprocessingStruct.implicitImpliedLiteralVector.empty()) {
                        IdNodeType implicitImpliedLiteralsIdNode = circuitUniquePtr_->createAndInnerNode(equivalencePreprocessingStruct.implicitImpliedLiteralVector, false);

                        idNodeTmp = circuitUniquePtr_->createAndInnerNode({ idNodeTmp, implicitImpliedLiteralsIdNode },
                                                                          DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);
                    }

                    // Implicit free variables
                    if (!implicitFreeVariableVector.empty()) {
                        IdNodeVectorType implicitFreeVariableIdNodeVectorTmp;
                        implicitFreeVariableIdNodeVectorTmp.reserve(implicitFreeVariableVector.size());

                        for (VarT var : implicitFreeVariableVector)
                            implicitFreeVariableIdNodeVectorTmp.emplace_back(circuitUniquePtr_->createTrivialOrInnerNode(var));

                        IdNodeType implicitFreeVariablesIdNode = circuitUniquePtr_->createAndInnerNode(implicitFreeVariableIdNodeVectorTmp,
                                                                                                       DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);

                        idNodeTmp = circuitUniquePtr_->createAndInnerNode({ idNodeTmp, implicitFreeVariablesIdNode },
                                                                          DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);
                    }

                    idNodeConnectedComponents.emplace_back(idNodeTmp);
                }
            }
            else {
                assert(computeNewHypergraphCut);

                IdNodeType idNodeTmp = compileOneComponent(newConnectedComponentStruct.variableSet, {},
                                                           equivalencePreprocessingStructPtr, computeNewHypergraphCut);
                idNodeConnectedComponents.emplace_back(idNodeTmp);
            }

            formulaRepresentationAbstractUniquePtr_->popPreviousComponent(newConnectedComponentStruct, pureVariableRemovedClausesVector);
        }

        assert(idNodeConnectedComponents.size() == connectedComponents.size());

        formulaRepresentationAbstractUniquePtr_->addClausesContainingOnlyPureLiteralsOfIgnoredType(pureClauseSet, ignorePureLiteralType_);

        // Implied literals
        if (impliedLiteralsIdNode != trueLeafIdNode_)
            idNodeConnectedComponents.emplace_back(impliedLiteralsIdNode);

        // Free variables
        if (freeVariablesIdNode != trueLeafIdNode_)
            idNodeConnectedComponents.emplace_back(freeVariablesIdNode);

        // Pure clauses
        if (!pureClauseSet.empty())
            idNodeConnectedComponents.emplace_back(pureClausesIdNode);

        unassignLiteralVectorInFormulaAndSatSolver(impliedLiteralVector, currentComponentVariableSet);

        // Sharing variables is allowed
        if (sharingVariables_)
            return circuitUniquePtr_->createAndInnerNode(idNodeConnectedComponents, bellaFormulaDecomposabilityType_);

        return circuitUniquePtr_->createAndInnerNode(idNodeConnectedComponents, DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool Compiler<VarT, LiteralT, ClauseIdT>::isCircuitCompiled() const noexcept {
        return isCompiled_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename Compiler<VarT, LiteralT, ClauseIdT>::CircuitPtrType
    Compiler<VarT, LiteralT, ClauseIdT>::getCompiledCircuitPtr() const {
        // The circuit has not yet been compiled
        if (!isCompiled_)
            throw Exception::CircuitHasNotYetBeenCompiledException();

        return circuitUniquePtr_.get();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void Compiler<VarT, LiteralT, ClauseIdT>::compile() {
        // The circuit has already been compiled
        if (isCompiled_)
            return;

        // Statistics
        if (compilerStatisticsPtr_)
            compilerStatisticsPtr_->compileTimer.startStopwatch();

        // Statistics
        formulaRepresentationAbstractUniquePtr_->setStatisticsBeforeCompilation();

        // Create the current component set
        VariableSetType currentComponentVariableSet(formulaRepresentationAbstractUniquePtr_->getNumberOfVariablesInOriginalFormula());
        for (VarT var = 1; var <= formulaRepresentationAbstractUniquePtr_->getNumberOfVariablesInOriginalFormula(); ++var) {
            // Free variables are ignored
            if (formulaRepresentationAbstractUniquePtr_->isVariableFree(var))
                continue;

            currentComponentVariableSet.emplace(var);
        }

        IdNodeType root = falseLeafIdNode_;
        LiteralVectorType initiallyImpliedLiterals;

        // The formula is satisfiable
        if (satSolverAbstractUniquePtr_->isSatisfiable()) {
            satSolverAbstractUniquePtr_->initialSimplification();

            initiallyImpliedLiterals = satSolverAbstractUniquePtr_->getInitiallyImpliedLiterals();
            std::sort(initiallyImpliedLiterals.begin(), initiallyImpliedLiterals.end());   // because of assignment

            // There is no need to consider the free variables since they will be treated as missing variables and added to the compiled circuit after the compilation
            assignLiteralVectorInFormulaAndSatSolver(initiallyImpliedLiterals, currentComponentVariableSet);

            // TODO: Aspvall since no unit clauses

            root = compileMoreComponents(currentComponentVariableSet, {}, nullptr, true);
        }

        // Add the initially implied literals to the compiled circuit
        if (!initiallyImpliedLiterals.empty()) {
            IdNodeType idNodeTmp = circuitUniquePtr_->createAndInnerNode(initiallyImpliedLiterals, true);
            root = circuitUniquePtr_->createAndInnerNode({ root, idNodeTmp }, DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);
        }

        // Unsatisfiable formula or tautology
        if ((root == falseLeafIdNode_) || (root == trueLeafIdNode_))
            circuitUniquePtr_->createAndInnerNode({ root, root }, DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);

        circuitUniquePtr_->setRoot();

        unassignLiteralVectorInFormulaAndSatSolver(initiallyImpliedLiterals, currentComponentVariableSet);

        isCompiled_ = true;

        // Statistics
        circuitUniquePtr_->setStatisticsAfterCompilation();
        componentCacheUniquePtr_->setStatisticsAfterCompilation();
        hypergraphCutCacheUniquePtr_->setStatisticsAfterCompilation();

        // Statistics
        if (compilerStatisticsPtr_)
            compilerStatisticsPtr_->compileTimer.stopStopwatch();
    }
}   // namespace Hydra
