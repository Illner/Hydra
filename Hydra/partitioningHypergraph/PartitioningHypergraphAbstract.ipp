#pragma once

#include "./PartitioningHypergraphAbstract.hpp"

namespace Hydra::PartitioningHypergraph {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    const PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VertexWeightVectorType&
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::getClauseVertexWeightVector() const noexcept {
        return (module_ ? *(modulePointersStruct_.clauseVertexWeightVectorPtr) : clauseVertexWeightVector_);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VertexWeightVectorType&
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::getVertexWeightVector() noexcept {
        return (module_ ? *(modulePointersStruct_.vertexWeightVectorPtr) : vertexWeightVector_);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::PartitionNumberVectorMapType&
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::getPartitionNumberVectorMap() noexcept {
        return (module_ ? *(modulePointersStruct_.partitionNumberVectorMapPtr) : partitionNumberVectorMap_);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::createEquivalenceStruct(const VariableSetType& currentComponentVariableSet,
                                                                                            const EquivalencePreprocessingStruct& equivalencePreprocessingStruct) const {
        assert(!module_);
        assert(computeConnectedComponents_.isEmpty());   // data structure is empty

        // Statistics
        if (partitioningHypergraphStatisticsPtr_)
            partitioningHypergraphStatisticsPtr_->createEquivalenceStructTimer.startStopwatch();

        // Initialize local auxiliary data structures
        if (l_firstCall_createEquivalenceStruct_) {
            l_equivalenceVectorMap_equivalenceStruct_ = VariableVectorMapType(formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), 0);
            l_equivalenceStructureVector_equivalenceStruct_ = EquivalenceStructureVectorType(formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula(), VariableVectorType());

            // Reserve the equivalence structure
            for (VariableVectorType& variableVector : l_equivalenceStructureVector_equivalenceStruct_)
                variableVector.reserve(S_ESTIMATED_NUMBER_OF_VARIABLES_FOR_EQUIVALENCE_STRUCTURE_);

            l_firstCall_createEquivalenceStruct_ = false;
        }

        VariableSetType ignoredPureVariableSet(currentComponentVariableSet.size());
        if (ignorePureLiteralType_ != IgnorePureLiteralTypeEnum::NONE) {
            for (VarT var : currentComponentVariableSet) {
                if (formulaRepresentationAbstractPtr_->isPureLiteralInCurrentFormula(var, ignorePureLiteralType_))
                    ignoredPureVariableSet.emplace(var);
            }
        }

        MappingFromVariableToVariableType mappingFromRepresentantToPriority(currentComponentVariableSet.size());

        VarT position = 0;

        for (const VariableVectorType& variableVector : equivalencePreprocessingStruct.equivalencePreprocessingStructure) {
            assert(variableVector.size() > 1);   // at least two variables

            VarT representant = variableVector[0];

            // The representant is out of the component
            if (!Other::containInSet(currentComponentVariableSet, representant))
                continue;

            // The representant is ignored pure
            if (Other::containInSet(ignoredPureVariableSet, representant))
                continue;

            assert(!formulaRepresentationAbstractPtr_->isVariableAssigned(representant));   // representant is not assigned

            ++position;
            VarT priority = 0;

            for (VarT var : variableVector) {
                // The variable is out of the component
                if (!Other::containInSet(currentComponentVariableSet, var))
                    continue;

                // The variable is ignored pure
                if (Other::containInSet(ignoredPureVariableSet, var))
                    continue;

                assert(!formulaRepresentationAbstractPtr_->isVariableAssigned(var));   // variable is not assigned

                ++priority;
                computeConnectedComponents_.addConnection(representant, var);
            }

            assert(!Other::containInMap(mappingFromRepresentantToPriority, representant));

            // Singleton
            if (priority == 1)
                continue;

            if (equivalencePreprocessingStruct.ignoreMultiOccurrentIgnoredVariables)
                mappingFromRepresentantToPriority[representant] = position;
            else
                mappingFromRepresentantToPriority[representant] = priority;
        }

        // Equivalence structure
        l_equivalenceVectorMap_equivalenceStruct_.clear();
        l_variableOrderReusableVector_equivalenceStruct_.clear();

        ConnectedComponentType connectedComponent = computeConnectedComponents_.computeConnectedComponents(currentComponentVariableSet, ignoredPureVariableSet);

        std::size_t currentIndex = 0;

        for (const ConnectedComponentStruct& connectedComponentStruct : connectedComponent) {
            VarT representant = 0;

            // Singleton
            if (connectedComponentStruct.variableSet.size() == 1) {
                representant = *(connectedComponentStruct.variableSet.cbegin());
            }
            else {
                VarT maxPriority = 0;

                for (VarT var : connectedComponentStruct.variableSet) {
                    if (auto itTmp = mappingFromRepresentantToPriority.find(var); itTmp != mappingFromRepresentantToPriority.end()) {
                        if (maxPriority < itTmp->second) {
                            maxPriority = itTmp->second;
                            representant = itTmp->first;
                        }
                    }
                }

                assert(maxPriority > 0);   // max priority is set
            }

            assert(representant > 0);   // representant is set

            l_equivalenceStructureVector_equivalenceStruct_[currentIndex].clear();
            l_variableOrderReusableVector_equivalenceStruct_.emplace_back(representant);

            for (VarT var : connectedComponentStruct.variableSet) {
                assert(!l_equivalenceVectorMap_equivalenceStruct_.contains(var));

                l_equivalenceStructureVector_equivalenceStruct_[currentIndex].emplace_back(var);

                if (var != representant)
                    l_equivalenceVectorMap_equivalenceStruct_.emplace(var, representant);
            }

            #ifndef NDEBUG
            std::sort(l_equivalenceStructureVector_equivalenceStruct_[currentIndex].begin(), l_equivalenceStructureVector_equivalenceStruct_[currentIndex].end());
            #endif

            ++currentIndex;
        }

        assert(l_variableOrderReusableVector_equivalenceStruct_.size() == currentIndex);
        assert(l_equivalenceVectorMap_equivalenceStruct_.size() == (currentComponentVariableSet.size() - ignoredPureVariableSet.size() - l_variableOrderReusableVector_equivalenceStruct_.size()));

        // Statistics
        if (partitioningHypergraphStatisticsPtr_)
            partitioningHypergraphStatisticsPtr_->createEquivalenceStructTimer.stopStopwatch();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::createOccurrenceListStruct(const VariableReusableVectorType& variableOrderReusableVector,
                                                                                               const VariableSetType& currentComponentVariableSet,
                                                                                               const VariableVectorMapType& equivalenceVectorMap,
                                                                                               const EquivalenceStructureVectorType& equivalenceStructureVector) const {
        assert(!module_);

        // Statistics
        if (partitioningHypergraphStatisticsPtr_)
            partitioningHypergraphStatisticsPtr_->createOccurrenceListStructTimer.startStopwatch();

        // Clear the occurrence list structure
        l_occurrenceListStruct_.occurrenceListSize = 0;
        l_occurrenceListStruct_.variableOrderReusableVector.clear();
        l_occurrenceListStruct_.fromClauseIdToIndexVectorMap.clear();
        l_occurrenceListStruct_.variablePlusSingletonVariableReusableVector.clear();

        ClauseIdT freeIndexForClauseId = 0;
        l_clauseAddedToOccurrenceListVectorSet_createOccurrenceListStruct_.clear();

        formulaRepresentationAbstractPtr_->getCurrentComponentClausesThatVariableSubsumeSomeClause(currentComponentVariableSet,
                                                                                                   l_clauseThatVariableSubsumesSomeClauseVectorSet_createOccurrenceListStruct_,
                                                                                                   equivalenceVectorMap,
                                                                                                   ignorePureLiteralType_, vertexWeightType_, clauseVertexWeightVector_);

        // Mark the variables (singleton hyperedge)
        // VariableSetType markedVariableSet;
        // if (!allowSingletonHyperedge_ && !l_clauseThatVariableSubsumesSomeClauseVectorSet_createOccurrenceListStruct_.empty()) {
        //     markedVariableSet = VariableSetType(currentComponentVariableSet.size());
        //
        //     for (ClauseIdT clauseId : l_clauseThatVariableSubsumesSomeClauseVectorSet_createOccurrenceListStruct_) {
        //         for (auto clauseIt = formulaRepresentationAbstractPtr_->beginClause(clauseId);
        //              clauseIt != formulaRepresentationAbstractPtr_->endClause(); ++clauseIt) {
        //             VarT var = clauseIt->getVariable();
        //
        //             // Pure literal of the ignored type
        //             if (formulaRepresentationAbstractPtr_->isPureLiteralInCurrentFormula(var, ignorePureLiteralType_))
        //                 continue;
        //
        //             // The mapping contains the variable
        //             if (equivalenceVectorMap.contains(var))
        //                 var = equivalenceVectorMap.find(var);
        //
        //             // Mark the variable
        //             if (!Other::containInSet(markedVariableSet, var))
        //                 markedVariableSet.emplace(var);
        //         }
        //     }
        // }

        #ifndef NDEBUG
        // Sort variableOrder
        MappingFromVariableToVariableType mappingFromVarToIndexDebug(variableOrderReusableVector.size());

        // The equivalence simplification method is applied
        if (!equivalenceVectorMap.empty()) {
            for (VarT i = 0; i < variableOrderReusableVector.size(); ++i)
                mappingFromVarToIndexDebug[variableOrderReusableVector[i]] = i;
        }

        VariableSortedVectorType variableOrderDebug(variableOrderReusableVector.cbegin(), variableOrderReusableVector.cend());
        std::sort(variableOrderDebug.begin(), variableOrderDebug.end());

        // Create the mapping from clause IDs to indices
        formulaRepresentationAbstractPtr_->getCurrentComponentClauses(currentComponentVariableSet, l_clauseIdReusableVector_createOccurrenceListStruct_, true);

        for (ClauseIdT clauseIdTmp : l_clauseIdReusableVector_createOccurrenceListStruct_) {
            // The clause variable subsumes some clause
            if (l_clauseThatVariableSubsumesSomeClauseVectorSet_createOccurrenceListStruct_.contains(clauseIdTmp))
                continue;

            bool clauseIsUsedTmp = false;

            if (ignorePureLiteralType_ == IgnorePureLiteralTypeEnum::NONE) {
                clauseIsUsedTmp = true;
            }
            else {
                for (auto clauseItTmp = formulaRepresentationAbstractPtr_->beginClause(clauseIdTmp); clauseItTmp != this->formulaRepresentationAbstractPtr_->endClause(); ++clauseItTmp) {
                    VarT varTmp = clauseItTmp->getVariable();

                    switch (ignorePureLiteralType_) {
                        case IgnorePureLiteralTypeEnum::ONLY_POSITIVE:
                            if (!formulaRepresentationAbstractPtr_->isPositivePureLiteralInCurrentFormula(varTmp))
                                clauseIsUsedTmp = true;
                            break;
                        case IgnorePureLiteralTypeEnum::ONLY_NEGATIVE:
                            if (!formulaRepresentationAbstractPtr_->isNegativePureLiteralInCurrentFormula(varTmp))
                                clauseIsUsedTmp = true;
                            break;
                        case IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE:
                            if (!formulaRepresentationAbstractPtr_->isPureLiteralInCurrentFormula(varTmp))
                                clauseIsUsedTmp = true;
                            break;
                        default:
                            throw Exception::NotImplementedException(ignorePureLiteralTypeEnumToString(ignorePureLiteralType_),
                                                                     "Hydra::PartitioningHypergraph::PartitioningHypergraphAbstract::createOccurrenceListStruct (debug)");
                    }

                    if (clauseIsUsedTmp)
                        break;
                }
            }

            if (clauseIsUsedTmp) {
                l_occurrenceListStruct_.fromClauseIdToIndexVectorMap.emplace(clauseIdTmp, freeIndexForClauseId);
                ++freeIndexForClauseId;
            }
        }
        #endif

        std::size_t currentIndex = 0;

        for (VarT i = 0; i < variableOrderReusableVector.size(); ++i) {
            #ifndef NDEBUG
            VarT var = variableOrderDebug[i];
            #else
            VarT var = variableOrderReusableVector[i];
            #endif

            // The variable is dominated (because of tests)
            if (equivalenceVectorMap.contains(var))
                continue;

            // Ignore pure literals
            if (formulaRepresentationAbstractPtr_->isPureLiteralInCurrentFormula(var, ignorePureLiteralType_))
                continue;

            // The equivalence simplification method is applied
            if (!equivalenceVectorMap.empty()) {
                #ifndef NDEBUG
                VarT iTmp = mappingFromVarToIndexDebug[var];

                assert(Other::containInVector(equivalenceStructureVector[iTmp], var));   // variable is self-contained in its dominated vector

                formulaRepresentationAbstractPtr_->getCurrentClauses(currentComponentVariableSet, equivalenceStructureVector[iTmp],
                                                                     l_clauseIdReusableVector_createOccurrenceListStruct_,
                                                                     l_clauseThatVariableSubsumesSomeClauseVectorSet_createOccurrenceListStruct_);
                #else
                formulaRepresentationAbstractPtr_->getCurrentClauses(currentComponentVariableSet, equivalenceStructureVector[i],
                                                                     l_clauseIdReusableVector_createOccurrenceListStruct_,
                                                                     l_clauseThatVariableSubsumesSomeClauseVectorSet_createOccurrenceListStruct_);
                #endif
            }
            // The equivalence simplification method is NOT applied
            else {
                formulaRepresentationAbstractPtr_->getCurrentClauses(currentComponentVariableSet, var, l_clauseIdReusableVector_createOccurrenceListStruct_,
                                                                     l_clauseThatVariableSubsumesSomeClauseVectorSet_createOccurrenceListStruct_);
            }

            l_occurrenceListStruct_.variablePlusSingletonVariableReusableVector.emplace_back(var);

            // Singleton hyperedge
            if (!allowSingletonHyperedge_ && l_clauseIdReusableVector_createOccurrenceListStruct_.size() == 1)   // && !Other::containInSet(markedVariableSet, var))
                continue;

            l_occurrenceListStruct_.occurrenceListVector[currentIndex].clear();
            l_occurrenceListStruct_.variableOrderReusableVector.emplace_back(var);

            for (ClauseIdT clauseId : l_clauseIdReusableVector_createOccurrenceListStruct_) {
                // The clause variable subsumes some clause
                if (l_clauseThatVariableSubsumesSomeClauseVectorSet_createOccurrenceListStruct_.contains(clauseId))
                    continue;

                // The clause is NOT in the mapping
                if (!l_occurrenceListStruct_.fromClauseIdToIndexVectorMap.contains(clauseId)) {
                    l_occurrenceListStruct_.fromClauseIdToIndexVectorMap.emplace(clauseId, freeIndexForClauseId);
                    ++freeIndexForClauseId;
                }

                ClauseIdT mappedClauseId = l_occurrenceListStruct_.fromClauseIdToIndexVectorMap[clauseId];

                ++l_occurrenceListStruct_.occurrenceListSize;
                l_occurrenceListStruct_.occurrenceListVector[currentIndex].emplace_back(mappedClauseId);

                // We have seen this clause
                l_clauseAddedToOccurrenceListVectorSet_createOccurrenceListStruct_.emplace(mappedClauseId, false);
            }

            assert(!l_occurrenceListStruct_.occurrenceListVector[currentIndex].empty());   // variable is not free

            #ifndef NDEBUG
            std::sort(l_occurrenceListStruct_.occurrenceListVector[currentIndex].begin(), l_occurrenceListStruct_.occurrenceListVector[currentIndex].end());
            #endif

            ++currentIndex;
        }

        l_occurrenceListStruct_.numberOfDifferentClausesInOccurrenceList = static_cast<ClauseIdT>(l_clauseAddedToOccurrenceListVectorSet_createOccurrenceListStruct_.size());

        assert(l_occurrenceListStruct_.variableOrderReusableVector.size() == currentIndex);

        #ifndef NDEBUG
        if (allowSingletonHyperedge_)
            assert(l_occurrenceListStruct_.variableOrderReusableVector.size() == l_occurrenceListStruct_.variablePlusSingletonVariableReusableVector.size());
        else
            assert(l_occurrenceListStruct_.variableOrderReusableVector.size() <= l_occurrenceListStruct_.variablePlusSingletonVariableReusableVector.size());
        #endif

        // Statistics
        if (partitioningHypergraphStatisticsPtr_) {
            // Vertices
            partitioningHypergraphStatisticsPtr_->numberOfVerticesCounter.addCount(static_cast<Statistics::LargeNumberType>(l_occurrenceListStruct_.numberOfDifferentClausesInOccurrenceList));
            partitioningHypergraphStatisticsPtr_->ratioOfNumberOfVerticesToNumberOfClausesCounter.addCount(static_cast<Statistics::LargeFloatingNumberType>(l_occurrenceListStruct_.numberOfDifferentClausesInOccurrenceList) / static_cast<Statistics::LargeFloatingNumberType>(formulaRepresentationAbstractPtr_->getNumberOfCurrentComponentClauses(currentComponentVariableSet)));

            // Hyperedges
            partitioningHypergraphStatisticsPtr_->numberOfHyperedgesCounter.addCount(static_cast<Statistics::LargeNumberType>(l_occurrenceListStruct_.variableOrderReusableVector.size()));
            partitioningHypergraphStatisticsPtr_->ratioOfNumberOfHyperedgesToNumberOfVariablesCounter.addCount(static_cast<Statistics::LargeFloatingNumberType>(l_occurrenceListStruct_.variableOrderReusableVector.size()) / static_cast<Statistics::LargeFloatingNumberType>(currentComponentVariableSet.size()));

            // Hypergraph
            partitioningHypergraphStatisticsPtr_->hypergraphSizeCounter.addCount(static_cast<Statistics::LargeNumberType>(l_occurrenceListStruct_.occurrenceListSize));
            partitioningHypergraphStatisticsPtr_->ratioOfHypergraphSizeToFormulaSizeCounter.addCount(static_cast<Statistics::LargeFloatingNumberType>(l_occurrenceListStruct_.occurrenceListSize) / static_cast<Statistics::LargeFloatingNumberType>(formulaRepresentationAbstractPtr_->getCurrentComponentFormulaSize(currentComponentVariableSet)));

            partitioningHypergraphStatisticsPtr_->createOccurrenceListStructTimer.stopStopwatch();
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    template <typename XpinT, typename PinT>
    void PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::fillXpinsAndPins(const OccurrenceListStruct& occurrenceListStruct,
                                                                                     std::vector<XpinT>& xpins, std::vector<PinT>& pins) {
        assert(!wrapper_);

        pins.resize(occurrenceListStruct.occurrenceListSize);
        xpins.resize(occurrenceListStruct.variableOrderReusableVector.size() + 1);

        xpins[0] = 0;

        std::size_t pinIndex = 0;
        std::size_t xpinIndex = 1;
        for (std::size_t i = 0; i < occurrenceListStruct.variableOrderReusableVector.size(); ++i) {
            const ClauseIdVectorType& clauseIdVector = occurrenceListStruct.occurrenceListVector[i];

            for (ClauseIdT clauseId : clauseIdVector) {
                pins[pinIndex] = static_cast<PinT>(clauseId);
                ++pinIndex;
            }

            xpins[xpinIndex] = static_cast<XpinT>(pinIndex);
            ++xpinIndex;
        }

        assert(static_cast<std::size_t>(occurrenceListStruct.occurrenceListSize) == pinIndex);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    const typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::PartitionNumberVectorMapType&
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::createPreassignmentOfClauseIndices([[maybe_unused]] const OccurrenceListStruct& occurrenceListStruct,
                                                                                                  [[maybe_unused]] PartitionNumberType numberOfPartitions) {
        assert(!wrapper_);

        PartitionNumberVectorMapType& partitionNumberVectorMap = getPartitionNumberVectorMap();

        // TODO
        assert(partitionNumberVectorMap.empty());

        return partitionNumberVectorMap;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VertexWeightVectorType&
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::createVertexWeightVector(const OccurrenceListStruct& occurrenceListStruct) {
        assert(!wrapper_);

        VertexWeightVectorType& vertexWeightVector = getVertexWeightVector();
        const VertexWeightVectorType& clauseVertexWeightVector = getClauseVertexWeightVector();

        // Vertex weights are not supported
        if (clauseVertexWeightVector.empty()) {
            assert(vertexWeightVector.empty());

            return vertexWeightVector;
        }

        vertexWeightVector.resize(occurrenceListStruct.numberOfDifferentClausesInOccurrenceList);

        for (std::size_t clauseId : occurrenceListStruct.fromClauseIdToIndexVectorMap.getAddedKeyVector()) {
            assert(occurrenceListStruct.fromClauseIdToIndexVectorMap[clauseId] < vertexWeightVector.size());
            assert(clauseId < clauseVertexWeightVector.size());
            assert(clauseVertexWeightVector[clauseId] > 0);

            vertexWeightVector[occurrenceListStruct.fromClauseIdToIndexVectorMap[clauseId]] = clauseVertexWeightVector[clauseId];
        }

        #ifndef NDEBUG
        // Check if all the vertices have a weight
        for (VertexWeightType weight : vertexWeightVector)
            assert(weight > 0);
        #endif

        return vertexWeightVector;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::extractCut(const OccurrenceListStruct& occurrenceListStruct, const PartvecType& partvec) const {
        assert(!wrapper_);

        VariableSetType cut(occurrenceListStruct.variableOrderReusableVector.size());

        for (VarT i = 0; i < occurrenceListStruct.variableOrderReusableVector.size(); ++i) {
            const ClauseIdVectorType& clauseIdVector = occurrenceListStruct.occurrenceListVector[i];

            assert(!clauseIdVector.empty());   // variable is not free

            for (ClauseIdT clauseId : clauseIdVector) {
                // The variable is in the cut
                if (partvec[clauseId] != partvec[clauseIdVector[0]]) {
                    cut.emplace(occurrenceListStruct.variableOrderReusableVector[i]);
                    break;
                }
            }
        }

        return cut;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::computeCut(const VariableSetType& currentComponentVariableSet) {
        assert(!module_);
        assert(allowEmptyHypergraphCut_);   // empty cuts are allowed

        bool validCut = true;

        return computeCut(currentComponentVariableSet, validCut);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::computeCut(const VariableSetType& currentComponentVariableSet, bool& validCut) {
        assert(!module_);

        validCut = true;
        l_variableOrderReusableVector_equivalenceStruct_.copySet(currentComponentVariableSet);

        // Create the occurrence list structure
        createOccurrenceListStruct(l_variableOrderReusableVector_equivalenceStruct_, currentComponentVariableSet);

        assert(!allowSingletonHyperedge_ || !l_occurrenceListStruct_.variableOrderReusableVector.empty());   // at least one variable

        // Empty occurrence list (can happen since !allowSingletonHyperedge_)
        if (l_occurrenceListStruct_.variableOrderReusableVector.empty()) {
            validCut = false;
            return l_occurrenceListStruct_.variablePlusSingletonVariableReusableVector.createSetUsingEmplace();
        }

        // Only one variable
        if (l_occurrenceListStruct_.variableOrderReusableVector.size() == 1)
            return { l_occurrenceListStruct_.variableOrderReusableVector[0] };

        // Only one clause
        // if (l_occurrenceListStruct_.numberOfDifferentClausesInOccurrenceList == 1)
        //    return l_occurrenceListStruct_.variableOrderReusableVector.createSetUsingEmplace();

        // Statistics
        if (partitioningHypergraphStatisticsPtr_)
            partitioningHypergraphStatisticsPtr_->computeCutTimer.startStopwatch();

        VariableSetType cut = computeCut(l_occurrenceListStruct_);

        // Statistics
        if (partitioningHypergraphStatisticsPtr_) {
            partitioningHypergraphStatisticsPtr_->cutSizeCounter.addCount(static_cast<Statistics::LargeNumberType>(cut.size()));
            partitioningHypergraphStatisticsPtr_->ratioOfCutSizeToNumberOfVariablesCounter.addCount(static_cast<Statistics::LargeFloatingNumberType>(cut.size()) / static_cast<Statistics::LargeFloatingNumberType>(currentComponentVariableSet.size()));

            partitioningHypergraphStatisticsPtr_->computeCutTimer.stopStopwatch();
        }

        // Empty cut
        if (!allowEmptyHypergraphCut_ && cut.empty()) {
            validCut = false;
            return l_occurrenceListStruct_.variablePlusSingletonVariableReusableVector.createSetUsingEmplace();
        }

        return cut;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::computeCut(const VariableSetType& currentComponentVariableSet,
                                                                          const EquivalencePreprocessingStruct& equivalencePreprocessingStruct) {
        assert(!module_);
        assert(allowEmptyHypergraphCut_);   // empty cuts are allowed

        bool validCut = true;

        return computeCut(currentComponentVariableSet, validCut, equivalencePreprocessingStruct);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::computeCut(const VariableSetType& currentComponentVariableSet, bool& validCut,
                                                                          const EquivalencePreprocessingStruct& equivalencePreprocessingStruct) {
        assert(!module_);

        validCut = true;

        // Create the equivalence structure
        createEquivalenceStruct(currentComponentVariableSet, equivalencePreprocessingStruct);

        // Create the occurrence list structure
        createOccurrenceListStruct(l_variableOrderReusableVector_equivalenceStruct_, currentComponentVariableSet,
                                   l_equivalenceVectorMap_equivalenceStruct_, l_equivalenceStructureVector_equivalenceStruct_);

        assert(!allowSingletonHyperedge_ || !l_occurrenceListStruct_.variableOrderReusableVector.empty());   // at least one variable

        // Empty occurrence list (can happen since !allowSingletonHyperedge_)
        if (l_occurrenceListStruct_.variableOrderReusableVector.empty()) {
            validCut = false;
            return l_occurrenceListStruct_.variablePlusSingletonVariableReusableVector.createSetUsingEmplace();
        }

        // Only one variable
        if (l_occurrenceListStruct_.variableOrderReusableVector.size() == 1)
            return { l_occurrenceListStruct_.variableOrderReusableVector[0] };

        // Only one clause
        // if (l_occurrenceListStruct_.numberOfDifferentClausesInOccurrenceList == 1)
        //    return l_occurrenceListStruct_.variableOrderReusableVector.createSetUsingEmplace();

        // Statistics
        if (partitioningHypergraphStatisticsPtr_)
            partitioningHypergraphStatisticsPtr_->computeCutTimer.startStopwatch();

        VariableSetType cut = computeCut(l_occurrenceListStruct_);

        // Statistics
        if (partitioningHypergraphStatisticsPtr_) {
            partitioningHypergraphStatisticsPtr_->cutSizeCounter.addCount(static_cast<Statistics::LargeNumberType>(cut.size()));
            partitioningHypergraphStatisticsPtr_->ratioOfCutSizeToNumberOfVariablesCounter.addCount(static_cast<Statistics::LargeFloatingNumberType>(cut.size()) / static_cast<Statistics::LargeFloatingNumberType>(currentComponentVariableSet.size()));

            partitioningHypergraphStatisticsPtr_->computeCutTimer.stopStopwatch();
        }

        if (!allowEmptyHypergraphCut_ && cut.empty()) {
            validCut = false;
            return l_occurrenceListStruct_.variablePlusSingletonVariableReusableVector.createSetUsingEmplace();
        }

        return cut;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::printVertexWeightVectorDebug(std::ostream& out) const {
        out << "Vertex weights:";
        for (VertexWeightType weight : getClauseVertexWeightVector())
            out << " " << std::to_string(weight);
        out << std::endl;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::printPartitioningHypergraphDebug(std::ostream& out, bool printCurrentFormula) const {
        out << "Partitioning hypergraph" << std::endl;
        out << "Software: " << partitioningHypergraphSoftwareEnumToString(partitioningHypergraphSoftware_) << std::endl;
        out << "Ignoring pure literals: " << ignorePureLiteralTypeEnumToString(ignorePureLiteralType_) << std::endl;
        out << "Allow empty cuts: " << std::to_string(allowEmptyHypergraphCut_) << std::endl;

        // Vertex weights
        if (isVertexWeightUsed(vertexWeightType_))
            printVertexWeightVectorDebug(out);

        if (printCurrentFormula) {
            out << "Current formula: ";
            formulaRepresentationAbstractPtr_->printCurrentFormulaDebug(out);
            out << std::endl;
        }

        this->processPrintPartitioningHypergraphDebug(out);

        out << std::endl;
    }
    #endif

    #if defined(TEST)
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorMapType&
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::getEquivalenceVectorMap() const noexcept {
        return l_equivalenceVectorMap_equivalenceStruct_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VariableReusableVectorType&
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::getVariableOrderReusableVector() const noexcept {
        return l_variableOrderReusableVector_equivalenceStruct_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::EquivalenceStructureVectorType&
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::getEquivalenceStructureVector() const noexcept {
        return l_equivalenceStructureVector_equivalenceStruct_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::OccurrenceListStruct&
    PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::getOccurrenceListStruct() const noexcept {
        return l_occurrenceListStruct_;
    }
    #endif
}   // namespace Hydra::PartitioningHypergraph
