#pragma once

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/container/contiguousOccurrenceList/ContiguousOccurrenceList.hpp"

namespace Hydra::RenHCRecognition::Aspvall {

    using FormulaSizeType = Hydra::Formula::Representation::FormulaSizeType;

    /**
     * Aspvall renH-C recognition structure
     * Copy and move methods (default) are allowed!
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     * @tparam AspVarT type used for an Aspvall variable
     * @tparam AspLiteralT type used for an Aspvall literal
     * @tparam AspClauseIdT type used for an Aspvall clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename AspVarT, typename AspLiteralT, typename AspClauseIdT>
    struct AspvallRenHCRecognitionStruct {
    public:
        using ClauseIdVectorType = typename Container::ContiguousOccurrenceList::ContiguousOccurrenceList<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ClauseIdVectorAspType = typename Container::ContiguousOccurrenceList::ContiguousOccurrenceList<AspVarT, AspLiteralT, AspClauseIdT>::ClauseIdVectorType;

    public:
        AspVarT numberOfVariables;
        AspLiteralT numberOfLiterals;
        AspClauseIdT numberOfClauses;
        FormulaSizeType formulaSize;

        ClauseIdVectorType mappingFromAspvallClauseIdToOriginalClauseIdVector = ClauseIdVectorType();
        ClauseIdVectorAspType mappingFromOriginalClauseIdToFirstAspvallClauseIdVector = ClauseIdVectorAspType();
    };
}   // namespace Hydra::RenHCRecognition::Aspvall
