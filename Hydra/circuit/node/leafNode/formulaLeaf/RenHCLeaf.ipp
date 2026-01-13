#pragma once

#include "./RenHCLeaf.hpp"

namespace Hydra::Circuit::Node {

    template <typename VarT, typename LiteralT>
    bool RenHCLeaf<VarT, LiteralT>::processConsistencyCheck(const PartialAssignmentType& partialAssignment,
                                                            const VariableSetType& forgottenVariableSet,
                                                            [[maybe_unused]] ConsistencyCheckCacheType& cache) {
        // Forgetting is not supported
        if (forgottenVariableSet.size() > 0)
            throw Exception::NotImplementedException("forgetting - consistency check",
                                                     "Hydra::Circuit::Node::RenHCLeaf::processConsistencyCheck");

        PartialAssignmentType partialAssignmentCopy = partialAssignment;
        bool isConsistent = this->unitPropagation(partialAssignmentCopy);

        return isConsistent;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType RenHCLeaf<VarT, LiteralT>::copySubcircuit(Circuit<VarT, LiteralT>* circuit, const MappingFromVariableToLiteralType& mapping,
                                                         CopySubcircuitCacheType& cache, [[maybe_unused]] bool isVariableToLiteralMapping) {
        // The leaf has already been processed
        if (auto itTmp = cache.find(this->id_); itTmp != cache.end())
            return itTmp->second;

        VariableSetType newSwitchedVariables(mapping.size());

        FormulaType newRenamableHornFormula;
        newRenamableHornFormula.reserve(this->formula_.size());

        for (const ClauseType& clause : this->formula_) {
            newRenamableHornFormula.push_back(std::move(clause.copyClause(mapping)));

            // Switched variables
            for (const LiteralType& lit : clause) {
                const LiteralType& mappedLit = mapping.at(lit.getVariable());
                bool isSwitched = Other::containInSet(switchedVariables_, lit.getVariable());

                if ((isSwitched && mappedLit.isPositive()) || (!isSwitched && mappedLit.isNegative()))
                    newSwitchedVariables.emplace(mappedLit.getVariable());
            }
        }

        // newSwitchedVariables.shrink_to_fit();

        IdNodeType mappedNodeId = circuit->createRenHCLeaf(std::move(newRenamableHornFormula), std::move(newSwitchedVariables));

        // Cache
        cache[this->id_] = mappedNodeId;

        return mappedNodeId;
    }

    template <typename VarT, typename LiteralT>
    void RenHCLeaf<VarT, LiteralT>::printNode(std::ostream& out,
                                              const MappingFromVariableToOriginalVariableType& mapping) const {
        std::pair<MappingFromVariableToVariableType, MappingFromVariableToVariableType> mappingTmp = this->getVariableMapping();
        MappingFromVariableToVariableType& mappingFromVarToIndex = std::get<0>(mappingTmp);
        MappingFromVariableToVariableType& mappingFromIndexToVar = std::get<1>(mappingTmp);

        VarT numberOfVariables = static_cast<VarT>(mappingFromVarToIndex.size());

        // R number_of_rows number_of_variables lit1 lit2 ... litN
        out << RENH_C_LEAF << " " << std::to_string(this->getNumberOfClauses() + 1) << " " << std::to_string(numberOfVariables);

        for (VarT i = 1; i <= mappingFromIndexToVar.size(); ++i) {
            VarT var = mappingFromIndexToVar[i];
            bool isSwitched = Other::containInSet(switchedVariables_, var);

            // Mapping is used
            if (auto itTmp = mapping.find(var); itTmp != mapping.end()) {
                auto mappedVariableTmp = itTmp->second;

                if (isSwitched)
                    out << " -" << std::to_string(mappedVariableTmp);
                else
                    out << " " << std::to_string(mappedVariableTmp);
            }
            // Mapping is NOT used
            else {
                if (isSwitched)
                    out << " -" << std::to_string(var);
                else
                    out << " " << std::to_string(var);
            }
        }

        out << std::endl;

        this->printFormulaInDimacsCnfFormat(out, mappingFromVarToIndex, numberOfVariables, true);
    }

    template <typename VarT, typename LiteralT>
    bool RenHCLeaf<VarT, LiteralT>::isRenamableHorn(bool throwException) const {
        for (const ClauseType& clause : this->formula_) {
            if (!clause.clauseIsRenamableHorn(switchedVariables_)) {
                if (throwException)
                    throw Exception::Circuit::Node::FormulaIsNotRenHCException(this);

                return false;
            }
        }

        return true;
    }

    template <typename VarT, typename LiteralT>
    void RenHCLeaf<VarT, LiteralT>::printSwitchedVariables(std::ostream& out) const {
        for (VarT var : switchedVariables_)
            out << var << " ";

        out << std::endl;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT>
    void RenHCLeaf<VarT, LiteralT>::printSortedSwitchedVariablesDebug(std::ostream& out) const {
        VariableSortedVectorType switchedVariableSortedVector = Other::sortUnorderedSet(switchedVariables_);

        out << "Switched variables:";

        for (VarT var : switchedVariableSortedVector)
            out << " " << std::to_string(var);
    }

    template <typename VarT, typename LiteralT>
    void RenHCLeaf<VarT, LiteralT>::printNodeDebug(std::ostream& out) {
        out << "RenH-C leaf - ID: " << std::to_string(this->getId()) << " "
            << "Size: " << std::to_string(this->getSize()) << " "
            << "Formula size: " << std::to_string(this->getFormulaSize()) << " "
            << "Number of clauses: " << std::to_string(this->getNumberOfClauses()) << " "
            << "Number of variables: " << std::to_string(this->getNumberOfVariables()) << " ";

        this->printSortedSwitchedVariablesDebug(out);
        out << " ";
        this->printVariablesInCircuitDebug(out);
        out << " ";
        this->printLiteralsInCircuitDebug(out);
        out << " ";
        this->printFormulaDebug(out);
        out << std::endl;
    }
    #endif
}   // namespace Hydra::Circuit::Node
