#pragma once

#include "./KromCLeaf.hpp"

namespace Hydra::Circuit::Node {

    template <typename VarT, typename LiteralT>
    bool KromCLeaf<VarT, LiteralT>::processConsistencyCheck(const PartialAssignmentType& partialAssignment,
                                                            const VariableSetType& forgottenVariableSet,
                                                            [[maybe_unused]] ConsistencyCheckCacheType& cache) {
        // Forgetting is not supported
        if (forgottenVariableSet.size() > 0)
            throw Exception::NotImplementedException("forgetting - consistency check",
                                                     "Hydra::Circuit::Node::KromCLeaf::processConsistencyCheck");

        VariableSetType variableSet = this->getVariableSet();
        PartialAssignmentType partialAssignmentCopy = partialAssignment;

        // Initial unit propagation (full assignment)
        bool result = this->unitPropagation(partialAssignmentCopy);
        if (!result)
            return false;

        for (VarT var : variableSet) {
            // The variable is already assigned
            if (partialAssignmentCopy.variableExists(var))
                continue;

            // Try positive literal
            LiteralType litPos(var, true);
            PartialAssignmentType partialAssignmentCopyTmp = partialAssignmentCopy;
            partialAssignmentCopyTmp.addLiteral(litPos);
            result = this->unitPropagation(partialAssignmentCopyTmp);

            if (result) {
                partialAssignmentCopy = std::move(partialAssignmentCopyTmp);
                continue;
            }

            // Try negative literal
            LiteralType litNeg(var, false);
            partialAssignmentCopyTmp = partialAssignmentCopy;
            partialAssignmentCopyTmp.addLiteral(litNeg);
            result = this->unitPropagation(partialAssignmentCopyTmp);

            if (result) {
                partialAssignmentCopy = std::move(partialAssignmentCopyTmp);
                continue;
            }

            return false;
        }

        return true;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType KromCLeaf<VarT, LiteralT>::copySubcircuit(Circuit<VarT, LiteralT>* circuit, const MappingFromVariableToLiteralType& mapping,
                                                         CopySubcircuitCacheType& cache, [[maybe_unused]] bool isVariableToLiteralMapping) {
        // The leaf has already been processed
        if (auto itTmp = cache.find(this->id_); itTmp != cache.end())
            return itTmp->second;

        FormulaType newKromFormula;
        newKromFormula.reserve(this->formula_.size());

        for (const ClauseType& clause : this->formula_)
            newKromFormula.push_back(std::move(clause.copyClause(mapping)));

        IdNodeType mappedNodeId = circuit->createKromCLeaf(std::move(newKromFormula));

        // Cache
        cache[this->id_] = mappedNodeId;

        return mappedNodeId;
    }

    template <typename VarT, typename LiteralT>
    void KromCLeaf<VarT, LiteralT>::printNode(std::ostream& out,
                                              const MappingFromVariableToOriginalVariableType& mapping) const {
        std::pair<MappingFromVariableToVariableType, MappingFromVariableToVariableType> mappingTmp = this->getVariableMapping();
        MappingFromVariableToVariableType& mappingFromVarToIndex = std::get<0>(mappingTmp);
        MappingFromVariableToVariableType& mappingFromIndexToVar = std::get<1>(mappingTmp);

        VarT numberOfVariables = static_cast<VarT>(mappingFromVarToIndex.size());

        // K number_of_rows number_of_variables var1 var2 ... varN
        out << KROM_C_LEAF << " " << std::to_string(this->getNumberOfClauses() + 1) << " " << std::to_string(numberOfVariables);

        for (VarT i = 1; i <= mappingFromIndexToVar.size(); ++i) {
            VarT var = mappingFromIndexToVar[i];

            // Mapping is used
            if (auto itTmp = mapping.find(var); itTmp != mapping.end()) {
                auto mappedVariableTmp = itTmp->second;
                out << " " << std::to_string(mappedVariableTmp);
            }
            // Mapping is NOT used
            else {
                out << " " << std::to_string(var);
            }
        }

        out << std::endl;

        this->printFormulaInDimacsCnfFormat(out, mappingFromVarToIndex, numberOfVariables, true);
    }

    template <typename VarT, typename LiteralT>
    bool KromCLeaf<VarT, LiteralT>::isKrom(bool throwException) const {
        for (const ClauseType& clause : this->formula_) {
            if (!clause.clauseHasAtMostTwoLiterals()) {
                if (throwException)
                    throw Exception::Circuit::Node::FormulaIsNotKromCException<VarT, LiteralT>(this);

                return false;
            }
        }

        return true;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT>
    void KromCLeaf<VarT, LiteralT>::printNodeDebug(std::ostream& out) {
        out << "Krom-C leaf - ID: " << std::to_string(this->getId()) << " "
            << "Size: " << std::to_string(this->getSize()) << " "
            << "Formula size: " << std::to_string(this->getFormulaSize()) << " "
            << "Number of clauses: " << std::to_string(this->getNumberOfClauses()) << " "
            << "Number of variables: " << std::to_string(this->getNumberOfVariables()) << " ";

        this->printVariablesInCircuitDebug(out);
        out << " ";
        this->printLiteralsInCircuitDebug(out);
        out << " ";
        this->printFormulaDebug(out);
        out << std::endl;
    }
    #endif
}   // namespace Hydra::Circuit::Node
