#pragma once

#include <vector>

#include "Hydra/formula/Literal.hpp"

namespace Hydra::SatSolver {

    /**
     * Equivalence preprocessing structure
     * Copy and move methods (default) are allowed!
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    struct EquivalencePreprocessingStruct {
    private:
        using LiteralVectorType = typename Formula::Literal<VarT, LiteralT>::LiteralVectorType;
        using VariableVectorType = typename Formula::Literal<VarT, LiteralT>::VariableVectorType;

    public:
        using EquivalencePreprocessingStructureType = std::vector<VariableVectorType>;

    public:
        bool ignoreMultiOccurrentIgnoredVariables;
        LiteralVectorType implicitImpliedLiteralVector = {};
        EquivalencePreprocessingStructureType equivalencePreprocessingStructure = {};   // [[representant, dominated_1, ...], ...]
    };
}   // namespace Hydra::SatSolver
