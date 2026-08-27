#pragma once

#include <cassert>
#include <iostream>
#include <string>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"

namespace Hydra::Parser::Cnf {

    /**
     * Parsed formula structure
     * Copy methods are disabled! Move methods (default) are allowed!
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    struct ParsedFormulaStruct {
        static_assert(Formula::Literal<VarT, LiteralT>::isValidVarT::value, "Invalid VarT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidLiteralT::value, "Invalid LiteralT type!");
        static_assert(Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isValidClauseT::value, "Invalid ClauseIdT type!");

    public:
        using LiteralType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseSizeType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeType;
        using ClauseIdVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;

    public:
        ParsedFormulaStruct(VarT numberOfVariables, ClauseIdT numberOfClauses, FormulaType&& formula, ClauseIdVectorType&& literalNumberOfOccurrences)
            : formula(std::move(formula)), numberOfVariables(numberOfVariables), numberOfClauses(numberOfClauses),
              literalNumberOfOccurrences(std::move(literalNumberOfOccurrences)) {
            assert(checkConsistencyOfDataStructuresDebug(true));
        };

        ParsedFormulaStruct(const ParsedFormulaStruct&) = delete;
        ParsedFormulaStruct(ParsedFormulaStruct&&) noexcept = default;

        ParsedFormulaStruct& operator=(const ParsedFormulaStruct&) = delete;
        ParsedFormulaStruct& operator=(ParsedFormulaStruct&&) noexcept = default;

    public:
        FormulaType formula;
        VarT numberOfVariables;
        ClauseIdT numberOfClauses;

        ClauseIdVectorType literalNumberOfOccurrences;

    public:
        void printParsedFormulaStruct(std::ostream& out) const;

    #ifndef NDEBUG
    private:
        /**
         * Check if the data structures are consistent
         * @return true if the data structures are consistent. Otherwise, false is returned.
         * @throw InconsistentDataStructureException [throwException] if the data structures are inconsistent
         */
        bool checkConsistencyOfDataStructuresDebug(bool throwException = false) const;
    #endif
    };
}   // namespace Hydra::Parser::Cnf

#include "./ParsedFormulaStructure.ipp"
