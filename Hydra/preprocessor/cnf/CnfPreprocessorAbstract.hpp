#pragma once

#include <iostream>

#include "Hydra/parser/cnf/ParsedFormulaStructure.hpp"

#include "Hydra/preprocessor/cnf/enums/CnfPreprocessorTypeEnum.hpp"

#include "Hydra/preprocessor/cnf/CnfPreprocessorAbstract.hxx"

namespace Hydra::Preprocessor::Cnf {

    /**
     * CNF preprocessor representation (abstract class)
     * Copy and move methods are disabled!
     * Exception:
     *      InconsistentDataStructureException (debug)
     */
    class CnfPreprocessorAbstract {
    public:
        using VarT = char32_t;
        using LiteralT = char32_t;
        using ClauseIdT = char32_t;

    public:
        using CnfPreprocessorStatisticsPtrType = CnfPreprocessorStatistics::CnfPreprocessorStatisticsPtrType;

    public:
        using ParsedFormulaStruct = Parser::Cnf::ParsedFormulaStruct<VarT, LiteralT, ClauseIdT>;

    public:
        CnfPreprocessorAbstract(CnfPreprocessorTypeEnum cnfPreprocessorType, CnfPreprocessorStatisticsPtrType cnfPreprocessorStatisticsPtr) noexcept
            : cnfPreprocessorType_(cnfPreprocessorType), cnfPreprocessorStatisticsPtr_(cnfPreprocessorStatisticsPtr) { }

        CnfPreprocessorAbstract(const CnfPreprocessorAbstract&) = delete;
        CnfPreprocessorAbstract(CnfPreprocessorAbstract&&) noexcept = delete;

        CnfPreprocessorAbstract& operator=(const CnfPreprocessorAbstract&) = delete;
        CnfPreprocessorAbstract& operator=(CnfPreprocessorAbstract&&) noexcept = delete;

        virtual ~CnfPreprocessorAbstract() noexcept = default;

    private:
        [[maybe_unused]] CnfPreprocessorTypeEnum cnfPreprocessorType_;

    protected:
        CnfPreprocessorStatisticsPtrType cnfPreprocessorStatisticsPtr_;

    protected:
        virtual ParsedFormulaStruct processPreprocess(ParsedFormulaStruct&& parsedFormulaStruct) = 0;

    public:
        /**
         * Preprocess the CNF formula
         * Assert: parsedFormulaStruct MUST have consistent data structures
         * Note: if the formula is empty, nothing happens
         * @param parsedFormulaStruct a CNF formula structure
         * @return the preprocessed CNF formula structure
         * @throw InconsistentDataStructureException (debug) if parsedFormulaStruct has inconsistent data structures
         */
        ParsedFormulaStruct preprocess(ParsedFormulaStruct&& parsedFormulaStruct);

    #ifndef NDEBUG
    public:
        void printCnfPreprocessorDebug(std::ostream& out) const;

    protected:
        virtual void processPrintCnfPreprocessorDebug(std::ostream& out) const = 0;
    #endif
    };
}   // namespace Hydra::Preprocessor::Cnf
