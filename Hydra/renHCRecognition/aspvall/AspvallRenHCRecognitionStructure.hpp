#pragma once

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/container/contagiousOccurrenceList/ContagiousOccurrenceList.hpp"

namespace Hydra::RenHCRecognition::Aspvall {

    using FormulaSizeType = Hydra::Formula::Representation::FormulaSizeType;

    /**
     * Aspvall renH-C recognition structure
     * Copy and move methods (default) are allowed!
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     * @tparam VarAspT type used for an Aspvall variable
     * @tparam LiteralAspT type used for an Aspvall literal
     * @tparam ClauseIdAspT type used for an Aspvall clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    struct AspvallRenHCRecognitionStruct {
    public:
        using ClauseIdVectorType = typename Container::ContagiousOccurrenceList::ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ClauseIdVectorAspType = typename Container::ContagiousOccurrenceList::ContagiousOccurrenceList<VarAspT, LiteralAspT, ClauseIdAspT>::ClauseIdVectorType;

    public:
        VarAspT numberOfVariables;
        LiteralAspT numberOfLiterals;
        ClauseIdAspT numberOfClauses;
        FormulaSizeType formulaSize;

        ClauseIdVectorType mappingFromAspvallClauseIdToOriginalClauseIdVector = ClauseIdVectorType();
        ClauseIdVectorAspType mappingFromOriginalClauseIdToFirstAspvallClauseIdVector = ClauseIdVectorAspType();
    };
}   // namespace Hydra::RenHCRecognition::Aspvall
