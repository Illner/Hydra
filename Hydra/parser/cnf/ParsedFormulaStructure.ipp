#pragma once

#include "./ParsedFormulaStructure.hpp"

#include "Hydra/other/stdExt/InsertionOperator.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

namespace Hydra::Parser::Cnf {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ParsedFormulaStruct<VarT, LiteralT, ClauseIdT>::printParsedFormulaStruct(std::ostream& out) const {
        using namespace Hydra::Other::StdExt::InsertionOperator;

        out << "Parsed formula structure" << std::endl;

        out << "Number of variables: " << numberOfVariables << std::endl;
        out << "Number of clauses: " << numberOfClauses << std::endl;

        // Parsed formula
        out << "Parsed formula:";
        for (const LiteralType& lit : formula)
            out << " " << lit;
        out << std::endl;

        // Number of occurrences of literals
        out << "Number of occurrences of literals:";
        for (ClauseIdT numberOfOccurrences : literalNumberOfOccurrences)
            out << " " << numberOfOccurrences;
        out << std::endl;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ParsedFormulaStruct<VarT, LiteralT, ClauseIdT>::checkConsistencyOfDataStructuresDebug(bool throwException) const {
        assert((LiteralT(2) + LiteralT(2) * static_cast<LiteralT>(numberOfVariables)) == static_cast<LiteralT>(literalNumberOfOccurrences.size()));
        assert(literalNumberOfOccurrences[0] == 0);
        assert(literalNumberOfOccurrences[1] == 0);

        VarT maxVariableIndexTmp = 0;
        ClauseIdT numberOfClausesTmp = 0;
        ClauseIdVectorType literalNumberOfOccurrencesTmp = literalNumberOfOccurrences;

        for (const LiteralType& lit : formula) {
            // The end of the clause
            if (lit.isZeroLiteral()) {
                ++numberOfClausesTmp;
                continue;
            }

            if (maxVariableIndexTmp < lit.getVariable())
                maxVariableIndexTmp = lit.getVariable();

            assert(literalNumberOfOccurrencesTmp[lit.getLiteralT()] > 0);

            --literalNumberOfOccurrencesTmp[lit.getLiteralT()];
        }

        // The number of variables is inconsistent
        if (numberOfVariables < maxVariableIndexTmp) {
            if (throwException)
                throw Exception::InconsistentDataStructureException("numberOfVariables", "Hydra::Parser::Cnf::ParsedFormulaStruct::checkConsistencyOfDataStructuresDebug");

            return false;
        }

        // The number of clauses is inconsistent
        if (numberOfClauses != numberOfClausesTmp) {
            if (throwException)
                throw Exception::InconsistentDataStructureException("numberOfClauses", "Hydra::Parser::Cnf::ParsedFormulaStruct::checkConsistencyOfDataStructuresDebug");

            return false;
        }

        for (ClauseIdT numberOfOccurrences : literalNumberOfOccurrencesTmp) {
            if (numberOfOccurrences == 0)
                continue;

            if (throwException)
                throw Exception::InconsistentDataStructureException("literalNumberOfOccurrences", "Hydra::Parser::Cnf::ParsedFormulaStruct::checkConsistencyOfDataStructuresDebug");

            return false;
        }

        return true;
    }
    #endif
}   // namespace Hydra::Parser::Cnf
