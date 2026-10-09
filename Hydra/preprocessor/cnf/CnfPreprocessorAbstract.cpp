#include "./CnfPreprocessorAbstract.hpp"

#include <cassert>
#include <string>

namespace Hydra::Preprocessor::Cnf {

    CnfPreprocessorAbstract::ParsedFormulaStruct CnfPreprocessorAbstract::preprocess(ParsedFormulaStruct&& parsedFormulaStruct) {
        assert(parsedFormulaStruct.checkConsistencyOfDataStructuresDebug(true,
                                                                         "Hydra::Preprocessor::Cnf::CnfPreprocessorAbstract::preprocess (before)"));

        // Empty formula
        if (parsedFormulaStruct.formula.empty())
            return std::move(parsedFormulaStruct);

        // Statistics
        if (cnfPreprocessorStatisticsPtr_)
            cnfPreprocessorStatisticsPtr_->preprocessTimer.startStopwatch();

        const Statistics::LargeFloatingNumberType numberOfOldVariables = parsedFormulaStruct.numberOfVariables;
        const Statistics::LargeFloatingNumberType numberOfOldClauses = parsedFormulaStruct.numberOfClauses;
        const Statistics::LargeFloatingNumberType oldFormulaSize = parsedFormulaStruct.formula.size();

        ParsedFormulaStruct preprocessedFormulaStruct = processPreprocess(std::move(parsedFormulaStruct));

        // Statistics
        if (cnfPreprocessorStatisticsPtr_) {
            cnfPreprocessorStatisticsPtr_->ratioOfNumberOfNewVariablesToNumberOfOldVariablesNumber.setNumber(static_cast<Statistics::LargeFloatingNumberType>(preprocessedFormulaStruct.numberOfVariables) / numberOfOldVariables);
            cnfPreprocessorStatisticsPtr_->ratioOfNumberOfNewClausesToNumberOfOldClausesNumber.setNumber(static_cast<Statistics::LargeFloatingNumberType>(preprocessedFormulaStruct.numberOfClauses) / numberOfOldClauses);
            cnfPreprocessorStatisticsPtr_->ratioOfNewFormulaSizeToOldFormulaSizeNumber.setNumber(static_cast<Statistics::LargeFloatingNumberType>(preprocessedFormulaStruct.formula.size()) / oldFormulaSize);

            cnfPreprocessorStatisticsPtr_->preprocessTimer.stopStopwatch();
        }

        assert(preprocessedFormulaStruct.checkConsistencyOfDataStructuresDebug(true,
                                                                               "Hydra::Preprocessor::Cnf::CnfPreprocessorAbstract::preprocess (after)"));

        return preprocessedFormulaStruct;
    }

    #ifndef NDEBUG
    void CnfPreprocessorAbstract::printCnfPreprocessorDebug(std::ostream& out) const {
        out << "CNF preprocessor" << std::endl;
        out << "Type: " << cnfPreprocessorTypeEnumToString(cnfPreprocessorType_) << std::endl;

        this->processPrintCnfPreprocessorDebug(out);

        out << std::endl;
    }
    #endif
}   // namespace Hydra::Preprocessor::Cnf
