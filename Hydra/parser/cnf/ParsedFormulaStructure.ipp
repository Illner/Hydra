#pragma once

#include "./ParsedFormulaStructure.hpp"

#include <type_traits>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/vectorSet/VectorSet.hpp"
#include "Hydra/other/stdExt/InsertionOperator.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

namespace Hydra::Parser::Cnf {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    template <typename NewVarT, typename NewLiteralT, typename NewClauseIdT>
    ParsedFormulaStruct<NewVarT, NewLiteralT, NewClauseIdT> ParsedFormulaStruct<VarT, LiteralT, ClauseIdT>::convertTypes(ParsedFormulaStruct parsedFormulaStruct) {
        static_assert(Other::isValidVarT<NewVarT>, "Invalid NewVarT type!");
        static_assert(Other::isValidLiteralT<NewLiteralT>, "Invalid NewLiteralT type!");
        static_assert(Other::isValidClauseIdT<NewClauseIdT>, "Invalid NewClauseIdT type!");

        using NewParsedFormulaStruct = ParsedFormulaStruct<NewVarT, NewLiteralT, NewClauseIdT>;
        using NewLiteralType = NewParsedFormulaStruct::LiteralType;
        using NewFormulaType = NewParsedFormulaStruct::FormulaType;
        using NewClauseIdVectorType = NewParsedFormulaStruct::ClauseIdVectorType;

        assert(parsedFormulaStruct.checkConsistencyOfDataStructuresDebug(true, "Hydra::Parser::Cnf::ParsedFormulaStruct::convertTypes"));

        assert(Hydra::Other::variablesCanBeSavedAsTypeT<NewVarT>(parsedFormulaStruct.numberOfVariables));
        assert(Hydra::Other::literalsCanBeSavedAsTypeT<NewLiteralT>(parsedFormulaStruct.numberOfVariables));
        assert(Hydra::Other::clauseIdCanBeSavedAsTypeT<NewClauseIdT>(parsedFormulaStruct.numberOfClauses));

        // New formula
        NewFormulaType newFormula;
        if constexpr (std::is_same_v<FormulaType, NewFormulaType>)
            newFormula = std::move(parsedFormulaStruct.formula);
        else {
            newFormula.reserve(parsedFormulaStruct.formula.size());

            for (const LiteralType& lit : parsedFormulaStruct.formula) {
                // Zero literal
                if (lit.isZeroLiteral())
                    newFormula.emplace_back(Formula::createZeroLiteral<NewVarT, NewLiteralT>());
                else
                    newFormula.emplace_back(NewLiteralType(static_cast<NewVarT>(lit.getVariable()), lit.isPositive()));
            }
        }

        // New literalNumberOfOccurrences
        NewClauseIdVectorType newLiteralNumberOfOccurrences;
        if constexpr (std::is_same_v<ClauseIdVectorType, NewClauseIdVectorType>)
            newLiteralNumberOfOccurrences = std::move(parsedFormulaStruct.literalNumberOfOccurrences);
        else {
            newLiteralNumberOfOccurrences.reserve(parsedFormulaStruct.literalNumberOfOccurrences.size());

            for (ClauseIdT numberOfOccurrences : parsedFormulaStruct.literalNumberOfOccurrences)
                newLiteralNumberOfOccurrences.emplace_back(static_cast<NewClauseIdT>(numberOfOccurrences));
        }

        return NewParsedFormulaStruct(static_cast<NewVarT>(parsedFormulaStruct.numberOfVariables), static_cast<NewClauseIdT>(parsedFormulaStruct.numberOfClauses),
                                      std::move(newFormula), std::move(newLiteralNumberOfOccurrences));
    }

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
    bool ParsedFormulaStruct<VarT, LiteralT, ClauseIdT>::checkConsistencyOfDataStructuresDebug(bool throwException, const std::string& functionName) const {
        using VectorSetType = Container::VectorSet::VectorSet;

        assert((LiteralT(2) + LiteralT(2) * static_cast<LiteralT>(numberOfVariables)) == static_cast<LiteralT>(literalNumberOfOccurrences.size()));
        assert(literalNumberOfOccurrences[0] == 0);
        assert(literalNumberOfOccurrences[1] == 0);

        bool clauseIsEmpty = true;
        ClauseIdT numberOfClausesTmp = 0;
        ClauseIdVectorType literalNumberOfOccurrencesTmp = literalNumberOfOccurrences;

        // Data structures to detect complementary and duplicate literals in a clause
        VectorSetType positiveLiteralVectorSet(numberOfVariables + 1);
        VectorSetType negativeLiteralVectorSet(numberOfVariables + 1);

        for (const LiteralType& lit : formula) {
            // The end of the clause
            if (lit.isZeroLiteral()) {
                ++numberOfClausesTmp;

                // Empty clause
                if (clauseIsEmpty) {
                    if (throwException)
                        throw Exception::InconsistentDataStructureException("formula - empty clause", functionName);

                    return false;
                }

                // Clear data structures
                clauseIsEmpty = true;
                positiveLiteralVectorSet.clear();
                negativeLiteralVectorSet.clear();

                continue;
            }

            VarT var = lit.getVariable();

            clauseIsEmpty = false;
            bool duplicateLiterals = false;
            bool complementaryLiterals = false;

            // The number of variables is inconsistent
            if (numberOfVariables < var) {
                if (throwException)
                    throw Exception::InconsistentDataStructureException("numberOfVariables", functionName);

                return false;
            }

            // Positive literal
            if (lit.isPositive()) {
                // Duplicate literal
                if (positiveLiteralVectorSet.contains(var))
                    duplicateLiterals = true;

                // Complementary literal
                if (negativeLiteralVectorSet.contains(var))
                    complementaryLiterals = true;

                positiveLiteralVectorSet.emplace(var, false);
            }

            // Negative literal
            else {
                // Duplicate literal
                if (negativeLiteralVectorSet.contains(var))
                    duplicateLiterals = true;

                // Complementary literal
                if (positiveLiteralVectorSet.contains(var))
                    complementaryLiterals = true;

                negativeLiteralVectorSet.emplace(var, false);
            }

            // Duplicate literals
            if (duplicateLiterals) {
                if (throwException)
                    throw Exception::InconsistentDataStructureException("formula - duplicate literals in a clause", functionName);

                return false;
            }

            // Complementary literals
            if (complementaryLiterals) {
                if (throwException)
                    throw Exception::InconsistentDataStructureException("formula - complementary literals in a clause", functionName);

                return false;
            }

            assert(literalNumberOfOccurrencesTmp[lit.getLiteralT()] > 0);

            --literalNumberOfOccurrencesTmp[lit.getLiteralT()];
        }

        // The last clause does not end with a zero literal
        if (!clauseIsEmpty) {
            if (throwException)
                throw Exception::InconsistentDataStructureException("formula - missing a zero literal at the end of the last clause", functionName);

            return false;
        }

        // The number of clauses is inconsistent
        if (numberOfClauses != numberOfClausesTmp) {
            if (throwException)
                throw Exception::InconsistentDataStructureException("numberOfClauses", functionName);

            return false;
        }

        for (ClauseIdT numberOfOccurrences : literalNumberOfOccurrencesTmp) {
            if (numberOfOccurrences == 0)
                continue;

            if (throwException)
                throw Exception::InconsistentDataStructureException("literalNumberOfOccurrences", functionName);

            return false;
        }

        return true;
    }
    #endif
}   // namespace Hydra::Parser::Cnf
