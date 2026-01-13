#pragma once

#include "./ContagiousFormulaRepresentation.hpp"

namespace Hydra::Formula::Representation::Contagious {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::clauseVariableSubsumesWithMappingClause(ClauseIdT clauseId1, ClauseIdT clauseId2,
                                                                                                             const VariableVectorMapType& variableVectorMap,
                                                                                                             IgnorePureLiteralTypeEnum ignorePureLiteralType) const {
        assert(clauseId1 < this->numberOfOriginalClauses_);
        assert(clauseId2 < this->numberOfOriginalClauses_);
        assert(this->isClauseUnresolved(clauseId1));   // clause is unresolved
        assert(this->isClauseUnresolved(clauseId2));   // clause is unresolved

        ClauseSizeType clause2Size = getCurrentClauseSize(clauseId2);

        // Clause_2 has fewer literals than Clause_1
        if ((ignorePureLiteralType == IgnorePureLiteralTypeEnum::NONE) &&
            (clause2Size < getCurrentClauseSize(clauseId1)))
            return false;

        VariableSetType clause2MappedVariableSet(clause2Size);

        // Remap the variables in Clause_2
        for (auto clauseIt = beginClause(clauseId2); clauseIt != this->endClause(); ++clauseIt) {
            VarT var = clauseIt->getVariable();

            // The mapping contains the variable
            if (variableVectorMap.contains(var))
                var = variableVectorMap.find(var);

            clause2MappedVariableSet.emplace(var);
        }

        // Check variable subsumption with mapping
        for (auto clauseIt = beginClause(clauseId1); clauseIt != this->endClause(); ++clauseIt) {
            VarT var = clauseIt->getVariable();

            // Pure literal of the ignored type
            if (this->isPureLiteralInCurrentFormula(var, ignorePureLiteralType)) {
                assert(!variableVectorMap.contains(var));   // pure literal does not exist in the mapping

                continue;
            }

            // The mapping contains the variable
            if (variableVectorMap.contains(var))
                var = variableVectorMap.find(var);

            if (!Other::containInSet(clause2MappedVariableSet, var))
                return false;
        }

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::forwardVariableSubsumptionWithMappingDetection(VectorSetType& clauseThatVariableSubsumesSomeClauseVectorSet,
                                                                                                                    const VariableVectorMapType& variableVectorMap,
                                                                                                                    IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                                                                                                    VertexWeightTypeEnum vertexWeightType,
                                                                                                                    VertexWeightVectorType& vertexWeightVector) const {
        assert(clauseThatVariableSubsumesSomeClauseVectorSet.empty());

        for (ClauseIdT clauseId1 : currentComponentClausesFixedVector_) {
            assert(this->isClauseUnresolved(clauseId1));   // clause is unresolved

            assert(!PartitioningHypergraph::isVertexWeightUsed(vertexWeightType) || (clauseId1 < vertexWeightVector.size()));
            assert(!PartitioningHypergraph::isVertexWeightUsed(vertexWeightType) || vertexWeightVector[clauseId1] > 0);

            // Transitivity
            if (clauseThatVariableSubsumesSomeClauseVectorSet.contains(clauseId1))
                continue;

            // The clause contains only pure literals of the ignored type
            if (this->doesClauseContainOnlyPureLiteralsOfIgnoredType(clauseId1, ignorePureLiteralType)) {
                clauseThatVariableSubsumesSomeClauseVectorSet.emplace(clauseId1);
                continue;
            }

            for (ClauseIdT clauseId2 : currentComponentClausesFixedVector_) {
                assert(this->isClauseUnresolved(clauseId2));   // clause is unresolved

                assert(!PartitioningHypergraph::isVertexWeightUsed(vertexWeightType) || (clauseId2 < vertexWeightVector.size()));
                assert(!PartitioningHypergraph::isVertexWeightUsed(vertexWeightType) || vertexWeightVector[clauseId2] > 0);

                if (clauseId1 == clauseId2)
                    continue;

                // The clause has already been detected that variable subsumes some clause
                if (clauseThatVariableSubsumesSomeClauseVectorSet.contains(clauseId2))
                    continue;

                // The clause contains only pure literals of the ignored type
                if (this->doesClauseContainOnlyPureLiteralsOfIgnoredType(clauseId2, ignorePureLiteralType)) {
                    clauseThatVariableSubsumesSomeClauseVectorSet.emplace(clauseId2);
                    continue;
                }

                if (clauseVariableSubsumesWithMappingClause(clauseId2, clauseId1, variableVectorMap, ignorePureLiteralType)) {
                    clauseThatVariableSubsumesSomeClauseVectorSet.emplace(clauseId2);

                    // Vertex weights
                    if (PartitioningHypergraph::isVertexWeightUsed(vertexWeightType))
                        vertexWeightVector[clauseId1] = this->combineVertexWeights(vertexWeightVector[clauseId2], vertexWeightVector[clauseId1],
                                                                                   vertexWeightType);
                }
            }
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::oneLiteralWatchingAlgorithmVariableSubsumptionWithMapping(VectorSetType& clauseThatVariableSubsumesSomeClauseVectorSet,
                                                                                                                               const VariableVectorMapType& variableVectorMap,
                                                                                                                               IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                                                                                                               VertexWeightTypeEnum vertexWeightType,
                                                                                                                               VertexWeightVectorType& vertexWeightVector) const {
        assert(clauseThatVariableSubsumesSomeClauseVectorSet.empty());

        // Initialize local auxiliary data structures
        if (l_firstCall_oneLiteralWatchingAlgorithmSubsumption_) {
            l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_ = VectorSetType(this->getNumberOfOriginalClauses());
            l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_ = ClauseSizeVectorType(this->getNumberOfOriginalClauses(), 0);

            l_firstCall_oneLiteralWatchingAlgorithmSubsumption_ = false;
        }

        // Initialize local auxiliary data structures
        if (l_firstCall_oneLiteralWatchingAlgorithmVariableSubsumption_) {
            l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_ = VariableSetType(maxOriginalClauseSize_);
            l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_ = VectorSetType(this->getNumberOfVariablesInOriginalFormulaUsedForIndexing());
            l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_ = SubsumptionWatcherVectorType(this->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), ClauseIdVectorType());

            // Reserve the variable watcher
            for (ClauseIdVectorType& clauseIdVector : l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_)
                clauseIdVector.reserve(S_ESTIMATED_NUMBER_OF_WATCHED_CLAUSES_FOR_SUBSUMPTION_);

            l_firstCall_oneLiteralWatchingAlgorithmVariableSubsumption_ = false;
        }

        // Clear the variable watcher
        for (std::size_t index : l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_.getAddedElementVector())
            l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_[index].clear();
        l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_.clear();

        #ifndef NDEBUG
        // Check the variable watcher is empty
        for (const ClauseIdVectorType& clauseIdVector : l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_)
            assert(clauseIdVector.empty());
        #endif

        // Initialize the watcher
        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            ClauseSizeType indexTmp = getIndexOfUnassignedLiteralInClause(clauseId, ignorePureLiteralType);
            VarT variable = getLiteralAtPositionInClause(clauseId, indexTmp).getVariable();

            // The clause contains only pure literals of the ignored type
            if (this->isPureLiteralInCurrentFormula(variable, ignorePureLiteralType)) {
                clauseThatVariableSubsumesSomeClauseVectorSet.emplace(clauseId);
                continue;
            }

            // The mapping contains the variable
            if (variableVectorMap.contains(variable))
                variable = variableVectorMap.find(variable);

            // Index watcher
            l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_[clauseId] = indexTmp;

            // Variable watcher
            l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_[variable].emplace_back(clauseId);
            l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_.emplace(variable, false);
        }

        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            assert(!PartitioningHypergraph::isVertexWeightUsed(vertexWeightType) || (clauseId < vertexWeightVector.size()));
            assert(!PartitioningHypergraph::isVertexWeightUsed(vertexWeightType) || vertexWeightVector[clauseId] > 0);

            // Transitivity
            if (clauseThatVariableSubsumesSomeClauseVectorSet.contains(clauseId))
                continue;

            processClauseOneLiteralWatchingAlgorithmVariableSubsumptionWithMapping(clauseId, clauseThatVariableSubsumesSomeClauseVectorSet, variableVectorMap,
                                                                                   ignorePureLiteralType, vertexWeightType, vertexWeightVector);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::processClauseOneLiteralWatchingAlgorithmVariableSubsumptionWithMapping(ClauseIdT clauseId,
                                                                                                                                            VectorSetType& clauseThatVariableSubsumesSomeClauseVectorSet,
                                                                                                                                            const VariableVectorMapType& variableVectorMap,
                                                                                                                                            IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                                                                                                                            VertexWeightTypeEnum vertexWeightType,
                                                                                                                                            VertexWeightVectorType& vertexWeightVector) const {
        ClauseSizeType clauseSize = getCurrentClauseSize(clauseId);
        l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_.clear();

        for (auto clauseIt = beginClause(clauseId); clauseIt != this->endClause(); ++clauseIt) {
            VarT variable = clauseIt->getVariable();

            // Pure literal of the ignored type
            if (this->isPureLiteralInCurrentFormula(variable, ignorePureLiteralType)) {
                assert(!variableVectorMap.contains(variable));   // pure literal does not exist in the mapping

                continue;
            }

            // The mapping contains the variable
            if (variableVectorMap.contains(variable))
                variable = variableVectorMap.find(variable);

            l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_.emplace(variable);

            // No update needed
            if (l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_[variable].empty())
                continue;

            l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_.clear();

            for (ClauseIdT clauseIdTmp : l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_[variable]) {
                assert(!PartitioningHypergraph::isVertexWeightUsed(vertexWeightType) || (clauseIdTmp < vertexWeightVector.size()));
                assert(!PartitioningHypergraph::isVertexWeightUsed(vertexWeightType) || vertexWeightVector[clauseIdTmp] > 0);

                if (clauseId == clauseIdTmp)
                    continue;

                if ((ignorePureLiteralType == IgnorePureLiteralTypeEnum::NONE) &&
                    (getCurrentClauseSize(clauseIdTmp) > clauseSize))
                    continue;

                // The clause has already been detected that variable subsumes some clause
                if (clauseThatVariableSubsumesSomeClauseVectorSet.contains(clauseIdTmp))
                    continue;

                // The watcher cannot be updated
                if (!updateWatcherOneLiteralWatchingAlgorithmVariableSubsumptionWithMapping(clauseIdTmp, variableVectorMap, ignorePureLiteralType)) {
                    clauseThatVariableSubsumesSomeClauseVectorSet.emplace(clauseIdTmp);

                    // Vertex weights
                    if (PartitioningHypergraph::isVertexWeightUsed(vertexWeightType))
                        vertexWeightVector[clauseId] = this->combineVertexWeights(vertexWeightVector[clauseIdTmp], vertexWeightVector[clauseId],
                                                                                  vertexWeightType);
                }
                // The watcher has been updated
                else {
                    l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_.emplace(clauseIdTmp);
                }
            }

            Other::smartRemoveElementsFromVector(l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_[variable],
                                                 l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::updateWatcherOneLiteralWatchingAlgorithmVariableSubsumptionWithMapping(ClauseIdT clauseId,
                                                                                                                                            const VariableVectorMapType& variableVectorMap,
                                                                                                                                            IgnorePureLiteralTypeEnum ignorePureLiteralType) const {
        ClauseSizeType index = l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_[clauseId];
        VarT oldVariable = getLiteralAtPositionInClause(clauseId, index).getVariable();

        // The mapping contains the variable
        if (variableVectorMap.contains(oldVariable))
            oldVariable = variableVectorMap.find(oldVariable);

        VarT newVariable = oldVariable;

        assert(Other::containInVector(l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_[oldVariable], clauseId));

        // (index + 1, endClause)
        for (ClauseSizeType i = index + 1; i < originalClauseSize_[clauseId]; ++i) {
            VarT variable = getLiteralAtPositionInClause(clauseId, i).getVariable();

            // The variable is assigned
            if (this->isVariableAssigned(variable))
                continue;

            // Pure literal of the ignored type
            if (this->isPureLiteralInCurrentFormula(variable, ignorePureLiteralType)) {
                assert(!variableVectorMap.contains(variable));   // pure literal does not exist in the mapping

                continue;
            }

            // The mapping contains the variable
            if (variableVectorMap.contains(variable))
                variable = variableVectorMap.find(variable);

            // New watcher has been found
            if (!l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_.contains(variable)) {
                newVariable = variable;
                l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_[clauseId] = i;

                break;
            }
        }

        // (0, index - 1)
        if (oldVariable == newVariable) {
            for (ClauseSizeType i = 0; i < index; ++i) {
                VarT variable = getLiteralAtPositionInClause(clauseId, i).getVariable();

                // The variable is assigned
                if (this->isVariableAssigned(variable))
                    continue;

                // Pure literal of the ignored type
                if (this->isPureLiteralInCurrentFormula(variable, ignorePureLiteralType)) {
                    assert(!variableVectorMap.contains(variable));   // pure literal does not exist in the mapping

                    continue;
                }

                // The mapping contains the variable
                if (variableVectorMap.contains(variable))
                    variable = variableVectorMap.find(variable);

                // New watcher has been found
                if (!l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_.contains(variable)) {
                    newVariable = variable;
                    l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_[clauseId] = i;

                    break;
                }
            }
        }

        // No variable can be used as a watcher
        if (oldVariable == newVariable)
            return false;

        // Variable watcher
        l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_[newVariable].emplace_back(clauseId);
        l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_.emplace(newVariable, false);

        return true;
    }
}   // namespace Hydra::Formula::Representation::Contagious
