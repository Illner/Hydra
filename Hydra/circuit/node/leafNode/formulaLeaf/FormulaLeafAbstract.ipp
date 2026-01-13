#pragma once

#include "./FormulaLeafAbstract.hpp"

namespace Hydra::Circuit::Node {

    template <typename VarT, typename LiteralT>
    void FormulaLeafAbstract<VarT, LiteralT>::computeAndSetLeafSize(bool includeNumberOfClauses) noexcept {
        this->size_ = getFormulaSize();

        if (includeNumberOfClauses) {
            ClauseIdType numberOfClauses = getNumberOfClauses();

            if (numberOfClauses > 1)
                this->size_ += numberOfClauses;
        }
    }

    template <typename VarT, typename LiteralT>
    void FormulaLeafAbstract<VarT, LiteralT>::setUsedVariables(BoolVectorType& usedVariableVector, VarT& numberOfUsedVariables) const {
        for (const ClauseType& clause : formula_) {
            for (const LiteralType& lit : clause) {
                VarT var = lit.getVariable();

                assert(var < usedVariableVector.size());

                // New variable
                if (!usedVariableVector[var]) {
                    ++numberOfUsedVariables;
                    usedVariableVector[var] = true;
                }
            }
        }
    }

    template <typename VarT, typename LiteralT>
    bool FormulaLeafAbstract<VarT, LiteralT>::processIsCircuitSmooth(MappingFromIdNodeToVariableSetType& mappingFromIdNodeToVariableSet) const {
        mappingFromIdNodeToVariableSet[this->id_] = getVariableSet();

        return true;
    }

    template <typename VarT, typename LiteralT>
    typename FormulaLeafAbstract<VarT, LiteralT>::NumberOfModelsType
    FormulaLeafAbstract<VarT, LiteralT>::processModelCounting(const PartialAssignmentType& partialAssignment,
                                                              [[maybe_unused]] ModelCountingCacheType& cache) const {
        VariableSetType variableSet = getVariableSet();

        for (auto it = variableSet.begin(); it != variableSet.end();) {
            if (partialAssignment.variableExists(*it))
                it = variableSet.erase(it);
            else
                ++it;
        }

        VariableSortedVectorType variableSortedVector = Other::sortUnorderedSet(variableSet);

        NumberOfModelsType numberOfModels;   // 0
        PartialAssignmentType partialAssignmentTmp = partialAssignment;

        processModelCounting(static_cast<VarT>(0), partialAssignmentTmp, variableSortedVector, numberOfModels);

        return numberOfModels;
    }

    template <typename VarT, typename LiteralT>
    void FormulaLeafAbstract<VarT, LiteralT>::processModelCounting(VarT indexVariable, PartialAssignmentType& partialAssignment,
                                                                   const VariableSortedVectorType& variableSortedVector, NumberOfModelsType& numberOfModels) const {
        // Full assignment
        if (indexVariable == variableSortedVector.size()) {
            FormulaStatusEnum formulaStatus = getFormulaStatus(partialAssignment);

            // A model has been found
            if (formulaStatus == FormulaStatusEnum::SATISFIED)
                ++numberOfModels;

            return;
        }

        VarT var = variableSortedVector[indexVariable];
        ++indexVariable;

        // Positive literal
        LiteralType posLit(var, true);
        partialAssignment.addLiteral(posLit);
        processModelCounting(indexVariable, partialAssignment, variableSortedVector, numberOfModels);

        partialAssignment.removeLiteral(posLit);

        // Negative literal
        LiteralType negLit(var, false);
        partialAssignment.addLiteral(negLit);
        processModelCounting(indexVariable, partialAssignment, variableSortedVector, numberOfModels);

        partialAssignment.removeLiteral(negLit);
    }

    template <typename VarT, typename LiteralT>
    typename FormulaLeafAbstract<VarT, LiteralT>::FormulaSizeType
    FormulaLeafAbstract<VarT, LiteralT>::getFormulaSize() const noexcept {
        FormulaSizeType sizeTmp = 0;

        for (const ClauseType& clause : formula_) {
            sizeTmp += static_cast<FormulaSizeType>(clause.getClauseSize());
        }

        return sizeTmp;
    }

    template <typename VarT, typename LiteralT>
    typename FormulaLeafAbstract<VarT, LiteralT>::VariableSetType
    FormulaLeafAbstract<VarT, LiteralT>::getVariableSet() const noexcept {
        VariableSetType variableSet;

        for (const ClauseType& clause : formula_) {
            for (const LiteralType& lit : clause) {
                variableSet.emplace(lit.getVariable());
            }
        }

        return variableSet;
    }

    template <typename VarT, typename LiteralT>
    VarT FormulaLeafAbstract<VarT, LiteralT>::getNumberOfVariables() const noexcept {
        VariableSetType variableSet = getVariableSet();

        return static_cast<VarT>(variableSet.size());
    }

    template <typename VarT, typename LiteralT>
    typename FormulaLeafAbstract<VarT, LiteralT>::ClauseIdType
    FormulaLeafAbstract<VarT, LiteralT>::getNumberOfClauses() const noexcept {
        return static_cast<ClauseIdType>(formula_.size());
    }

    template <typename VarT, typename LiteralT>
    std::pair<typename FormulaLeafAbstract<VarT, LiteralT>::MappingFromVariableToVariableType, typename FormulaLeafAbstract<VarT, LiteralT>::MappingFromVariableToVariableType>
    FormulaLeafAbstract<VarT, LiteralT>::getVariableMapping() const noexcept {
        MappingFromVariableToVariableType mappingFromVarToIndex;
        MappingFromVariableToVariableType mappingFromIndexToVar;

        VarT index = 1;

        #ifndef NDEBUG
        VariableSortedVectorType variableStructure = Other::sortUnorderedSet(getVariableSet());
        #else
        VariableSetType variableStructure = getVariableSet();
        #endif

        for (VarT var : variableStructure) {
            mappingFromVarToIndex.insert({ var, index });
            mappingFromIndexToVar.insert({ index, var });

            ++index;
        }

        return { mappingFromVarToIndex, mappingFromIndexToVar };
    }

    template <typename VarT, typename LiteralT>
    void FormulaLeafAbstract<VarT, LiteralT>::printFormulaInDimacsCnfFormat(std::ostream& out,
                                                                            const MappingFromVariableToVariableType& mappingFromVarToIndex,
                                                                            VarT numberOfVariables,
                                                                            bool printProblemLine) const {
        // Problem line
        if (printProblemLine) {
            if (numberOfVariables == 0)
                numberOfVariables = getNumberOfVariables();

            out << Other::Parser::PROBLEM << " " << Other::Parser::CNF_HEADER_STRING << " " << std::to_string(numberOfVariables) << " " << std::to_string(getNumberOfClauses()) << std::endl;
        }

        // Formula
        for (const ClauseType& clause : formula_) {
            for (const LiteralType& lit : clause) {
                VarT varTmp = lit.getVariable();

                // Mapping function is used
                if (auto itTmp = mappingFromVarToIndex.find(varTmp); itTmp != mappingFromVarToIndex.end())
                    varTmp = itTmp->second;

                if (lit.isPositive())
                    out << std::to_string(varTmp) << " ";
                else
                    out << "-" << std::to_string(varTmp) << " ";
            }

            out << "0" << std::endl;   // end of the clause
        }
    }

    template <typename VarT, typename LiteralT>
    typename FormulaLeafAbstract<VarT, LiteralT>::FormulaStatusEnum
    FormulaLeafAbstract<VarT, LiteralT>::getFormulaStatus(const PartialAssignmentType& partialAssignment) const {
        bool unresolvedClauseExists = false;

        for (const ClauseType& clause : formula_) {
            ClauseStatusEnum clauseStatus = clause.getClauseStatus(partialAssignment);

            switch (clauseStatus) {
                case ClauseStatusEnum::EMPTY:
                    return FormulaStatusEnum::UNSATISFIED;
                case ClauseStatusEnum::UNRESOLVED:
                case ClauseStatusEnum::UNIT_CLAUSE:
                    unresolvedClauseExists = true;
                    break;
                case ClauseStatusEnum::SATISFIED:
                    break;
                default:
                    throw Exception::NotImplementedException(Formula::clauseStatusEnumToString(clauseStatus),
                                                             "Hydra::Circuit::Node::FormulaLeafAbstract::getFormulaStatus");
            }
        }

        if (unresolvedClauseExists)
            return FormulaStatusEnum::UNRESOLVED;

        return FormulaStatusEnum::SATISFIED;
    }

    template <typename VarT, typename LiteralT>
    bool FormulaLeafAbstract<VarT, LiteralT>::unitPropagation(PartialAssignmentType& partialAssignment) {
        Other::HashMap::MapType<LiteralType, ClauseIdVectorType> watchedLiterals(2 * S_ESTIMATED_NUMBER_OF_VARIABLES_);
        Other::HashMap::MapType<ClauseIdType, LiteralVectorType> clauseWatchedLiterals(formula_.size());
        Other::HashMap::SetType<ClauseIdType> clauseNeedToBeProcessedSet(formula_.size());

        // Initialization
        for (ClauseIdType i = 0; i < formula_.size(); ++i)
            clauseNeedToBeProcessedSet.emplace(i);

        while (!clauseNeedToBeProcessedSet.empty()) {
            auto tmp = clauseNeedToBeProcessedSet.begin();
            ClauseIdType clauseId = *tmp;
            clauseNeedToBeProcessedSet.erase(tmp);

            ClauseType& clause = formula_[clauseId];
            ClauseStatusWatchedLiteralEnum clauseStatusWatchedLiteral = clause.updateWatchedLiterals(partialAssignment);

            // Update structures
            if (clause.getFirstWatchedLiteralIndex().has_value() && clause.getSecondWatchedLiteralIndex().has_value()) {
                const LiteralType& firstWatchedLiteral = clause[*(clause.getFirstWatchedLiteralIndex())];
                const LiteralType& secondWatchedLiteral = clause[*(clause.getSecondWatchedLiteralIndex())];

                if (!Other::containInMap(watchedLiterals, firstWatchedLiteral)) {
                    watchedLiterals[firstWatchedLiteral] = {};
                    watchedLiterals[firstWatchedLiteral].reserve(formula_.size());
                }
                if (!Other::containInMap(watchedLiterals, secondWatchedLiteral)) {
                    watchedLiterals[secondWatchedLiteral] = {};
                    watchedLiterals[secondWatchedLiteral].reserve(formula_.size());
                }

                // First visit
                if (!Other::containInMap(clauseWatchedLiterals, clauseId)) {
                    watchedLiterals[firstWatchedLiteral].emplace_back(clauseId);
                    watchedLiterals[secondWatchedLiteral].emplace_back(clauseId);

                    clauseWatchedLiterals[clauseId] = {};
                    clauseWatchedLiterals[clauseId].reserve(2);
                    clauseWatchedLiterals[clauseId].emplace_back(firstWatchedLiteral.getVariable(), firstWatchedLiteral.isPositive());
                    clauseWatchedLiterals[clauseId].emplace_back(secondWatchedLiteral.getVariable(), secondWatchedLiteral.isPositive());
                }
                else {
                    const LiteralType& firstWatchedLiteralOld = clauseWatchedLiterals[clauseId][0];
                    // First watched literal has been changed
                    if (firstWatchedLiteral != firstWatchedLiteralOld) {
                        watchedLiterals[firstWatchedLiteral].emplace_back(clauseId);
                        Other::smartRemoveElementFromVector(watchedLiterals[firstWatchedLiteralOld], clauseId);

                        clauseWatchedLiterals[clauseId][0] = firstWatchedLiteral;
                    }

                    const LiteralType& secondWatchedLiteralOld = clauseWatchedLiterals[clauseId][1];
                    // Second watched literal has been changed
                    if (secondWatchedLiteral != secondWatchedLiteralOld) {
                        watchedLiterals[secondWatchedLiteral].emplace_back(clauseId);
                        Other::smartRemoveElementFromVector(watchedLiterals[secondWatchedLiteralOld], clauseId);

                        clauseWatchedLiterals[clauseId][1] = secondWatchedLiteral;
                    }
                }
            }

            switch (clauseStatusWatchedLiteral) {
                case ClauseStatusWatchedLiteralEnum::SATISFIED: {
                    // Note: the watched literals have not been changed
                    break;
                }
                case ClauseStatusWatchedLiteralEnum::EMPTY: {
                    partialAssignment.clear();
                    return false;
                }
                case ClauseStatusWatchedLiteralEnum::UNDEFINED: {
                    // Note: all the structures have already been updated
                    break;
                }
                case ClauseStatusWatchedLiteralEnum::UNIT_CLAUSE_1:
                case ClauseStatusWatchedLiteralEnum::UNIT_CLAUSE_2: {
                    const LiteralType& impliedLiteral = (clauseStatusWatchedLiteral == ClauseStatusWatchedLiteralEnum::UNIT_CLAUSE_1) ? clause[*(clause.getFirstWatchedLiteralIndex())] : clause[*(clause.getSecondWatchedLiteralIndex())];

                    partialAssignment.addLiteral(impliedLiteral);
                    LiteralType negatedImpliedLiteral = !impliedLiteral;

                    if (auto itTmp = watchedLiterals.find(negatedImpliedLiteral); itTmp != watchedLiterals.end()) {
                        for (ClauseIdType id : itTmp->second)
                            clauseNeedToBeProcessedSet.emplace(id);
                    }

                    break;
                }
            }
        }

        return true;
    }

    template <typename VarT, typename LiteralT>
    typename FormulaLeafAbstract<VarT, LiteralT>::ConstIteratorType FormulaLeafAbstract<VarT, LiteralT>::begin() const noexcept {
        return formula_.cbegin();
    }

    template <typename VarT, typename LiteralT>
    typename FormulaLeafAbstract<VarT, LiteralT>::ConstIteratorType FormulaLeafAbstract<VarT, LiteralT>::end() const noexcept {
        return formula_.cend();
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT>
    void FormulaLeafAbstract<VarT, LiteralT>::sortFormulaDebug() {
        // Formula is already sorted
        if (d_sortedFormula_)
            return;

        for (ClauseType& clause : formula_)
            clause.sortClauseDebug();

        std::sort(formula_.begin(), formula_.end());
        d_sortedFormula_ = true;
    }

    template <typename VarT, typename LiteralT>
    typename FormulaLeafAbstract<VarT, LiteralT>::LiteralSortedVectorType
    FormulaLeafAbstract<VarT, LiteralT>::computeAndReturnSortedLiteralsInCircuitDebug() const {
        LiteralSetType literalInCircuitSet;

        for (const ClauseType& clause : formula_) {
            for (const LiteralType& lit : clause) {
                literalInCircuitSet.emplace(lit.getVariable(), lit.isPositive());
            }
        }

        LiteralSortedVectorType literalInCircuitSortedVector = Other::sortUnorderedSet(literalInCircuitSet);

        return literalInCircuitSortedVector;
    }

    template <typename VarT, typename LiteralT>
    typename FormulaLeafAbstract<VarT, LiteralT>::VariableSortedVectorType
    FormulaLeafAbstract<VarT, LiteralT>::computeAndReturnSortedVariablesInCircuitDebug() const {
        VariableSetType variableInCircuitSet;

        for (const ClauseType& clause : formula_) {
            for (const LiteralType& lit : clause) {
                variableInCircuitSet.emplace(lit.getVariable());
            }
        }

        VariableSortedVectorType variableInCircuitSortedVector = Other::sortUnorderedSet(variableInCircuitSet);

        return variableInCircuitSortedVector;
    }

    template <typename VarT, typename LiteralT>
    void FormulaLeafAbstract<VarT, LiteralT>::printFormulaDebug(std::ostream& out) {
        sortFormulaDebug();   // deterministic output

        out << "Formula: ";

        for (ClauseType& clause : formula_) {
            clause.printClauseDebug(out);
            out << " ";
        }

        out << "00";
    }
    #endif
}   // namespace Hydra::Circuit::Node
