#pragma once

#include "Hydra/preprocessor/cnf/CnfPreprocessorAbstract.hpp"

#include "Hydra/preprocessor/cnf/enums/CnfPreprocessorTypeEnum.hpp"

namespace Hydra::Preprocessor::Cnf::None {

    /**
     * None CNF preprocessor (final class)
     * Exceptions:
     */
    class NoneCnfPreprocessor final : public CnfPreprocessorAbstract {
    public:
        explicit NoneCnfPreprocessor(CnfPreprocessorStatisticsPtrType cnfPreprocessorStatisticsPtr) noexcept
            : CnfPreprocessorAbstract(CnfPreprocessorTypeEnum::NONE, cnfPreprocessorStatisticsPtr) { }

    private:
        ParsedFormulaStruct processPreprocess(ParsedFormulaStruct&& parsedFormulaStruct) override;

    #ifndef NDEBUG
    private:
        void processPrintCnfPreprocessorDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::Preprocessor::Cnf::None
