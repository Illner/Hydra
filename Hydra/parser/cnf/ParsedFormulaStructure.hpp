#pragma once

#include <cassert>
#include <iostream>
#include <string>

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/TemplateType.hpp"

namespace Hydra::Parser::Cnf {

    /**
     * Parsed formula structure
     * Copy methods are disabled! Move methods (default) are allowed!
     * Invariant: every clause MUST end with a zero literal
     * Invariant: every clause MUST contain at least one literal
     * Invariant: every variable can appear in a clause AT MOST ONCE
     * Exception:
     *      InconsistentDataStructureException (debug)
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    struct ParsedFormulaStruct {
        static_assert(Other::isValidVarT<VarT>, "Invalid VarT type!");
        static_assert(Other::isValidLiteralT<LiteralT>, "Invalid LiteralT type!");
        static_assert(Other::isValidClauseIdT<ClauseIdT>, "Invalid ClauseIdT type!");

    public:
        using LiteralType = Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseSizeType = Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeType;
        using ClauseIdVectorType = Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;

    public:
        ParsedFormulaStruct(VarT numberOfVariables, ClauseIdT numberOfClauses, FormulaType&& formula, ClauseIdVectorType&& literalNumberOfOccurrences)
            : formula(std::move(formula)), numberOfVariables(numberOfVariables), numberOfClauses(numberOfClauses),
              literalNumberOfOccurrences(std::move(literalNumberOfOccurrences)) {
            assert(checkConsistencyOfDataStructuresDebug(true, "Hydra::Parser::Cnf::ParsedFormulaStruct::constructor"));
        }

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
        /**
         * Convert parsedFormulaStruct to different types
         * Assert: the number of variables MUST be savable as NewVarT
         * Assert: the number of literals MUST be savable as NewLiteralT
         * Assert: the number of clauses MUST be savable as NewClauseIdT
         * Assert: parsedFormulaStruct MUST have consistent data structures
         * @tparam NewVarT type used for a new variable
         * @tparam NewLiteralT type used for a new literal
         * @tparam NewClauseIdT type used for a new clause identifier
         * @param parsedFormulaStruct the parsed formula structure to convert
         * @return the converted parsed formula structure
         * @throw InconsistentDataStructureException (debug) if parsedFormulaStruct has inconsistent data structures
         */
        template <typename NewVarT, typename NewLiteralT, typename NewClauseIdT>
        static ParsedFormulaStruct<NewVarT, NewLiteralT, NewClauseIdT> convertTypes(ParsedFormulaStruct parsedFormulaStruct);

        void printParsedFormulaStruct(std::ostream& out) const;

    #ifndef NDEBUG
    public:
        /**
         * Check if the data structures are consistent
         * @param functionName [throwException] the name of the calling function that is used in the exception message
         * @return true if the data structures are consistent. Otherwise, false is returned.
         * @throw InconsistentDataStructureException [throwException] if the data structures are inconsistent
         */
        bool checkConsistencyOfDataStructuresDebug(bool throwException = false,
                                                   const std::string& functionName = "Hydra::Parser::Cnf::ParsedFormulaStruct::checkConsistencyOfDataStructuresDebug") const;
    #endif
    };
}   // namespace Hydra::Parser::Cnf

#include "./ParsedFormulaStructure.ipp"
