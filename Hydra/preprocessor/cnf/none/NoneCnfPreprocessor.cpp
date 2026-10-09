#include "./NoneCnfPreprocessor.hpp"

namespace Hydra::Preprocessor::Cnf::None {

    NoneCnfPreprocessor::ParsedFormulaStruct NoneCnfPreprocessor::processPreprocess(ParsedFormulaStruct&& parsedFormulaStruct) {
        return std::move(parsedFormulaStruct);
    }

    #ifndef NDEBUG
    void NoneCnfPreprocessor::processPrintCnfPreprocessorDebug([[maybe_unused]] std::ostream& out) const { }
    #endif
}   // namespace Hydra::Preprocessor::Cnf::None
