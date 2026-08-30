#pragma once

#include "./ContiguousFormulaRepresentation.hpp"

namespace Hydra::Formula::Representation::Contiguous {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::ClauseSizeComparator::operator()(ClauseIdT clauseId1, ClauseIdT clauseId2) const {
        ClauseSizeType clause1Size = contiguousFormulaRepresentationPtr_->getCurrentClauseSize(clauseId1);
        ClauseSizeType clause2Size = contiguousFormulaRepresentationPtr_->getCurrentClauseSize(clauseId2);

        return clause1Size < clause2Size;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    template <bool EqualityT, bool SameSizeT>
    bool ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::ClauseComparator<EqualityT, SameSizeT>::operator()(ClauseIdT clauseId1, ClauseIdT clauseId2) const {
        // The clauses can have different sizes
        if constexpr (!SameSizeT) {
            ClauseSizeType clause1Size = contiguousFormulaRepresentationPtr_->getCurrentClauseSize(clauseId1);
            ClauseSizeType clause2Size = contiguousFormulaRepresentationPtr_->getCurrentClauseSize(clauseId2);

            if (clause1Size != clause2Size) {
                if constexpr (EqualityT)
                    return false;
                else
                    return clause1Size < clause2Size;
            }
        }
        #ifndef NDEBUG
        // The clauses have the same size
        else
            assert(contiguousFormulaRepresentationPtr_->getCurrentClauseSize(clauseId1) == contiguousFormulaRepresentationPtr_->getCurrentClauseSize(clauseId2));   // the clauses MUST have the same size
        #endif

        auto clause1It = contiguousFormulaRepresentationPtr_->beginSortedClause(clauseId1);
        auto clause2It = contiguousFormulaRepresentationPtr_->beginSortedClause(clauseId2);
        auto clauseEndIt = contiguousFormulaRepresentationPtr_->endSortedClause();

        for (; clause1It != clauseEndIt; ++clause1It, ++clause2It) {
            const LiteralType& lit1 = *clause1It;
            const LiteralType& lit2 = *clause2It;

            if (lit1 != lit2) {
                if constexpr (EqualityT)
                    return false;
                else
                    return lit1 < lit2;
            }
        }

        if constexpr (EqualityT)
            return true;
        else
            return (clauseId1 < clauseId2);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    template <bool EqualityT, bool SameSizeT>
    bool ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::ClauseVariableComparator<EqualityT, SameSizeT>::operator()(ClauseIdT clauseId1, ClauseIdT clauseId2) const {
        // The clauses can have different sizes
        if constexpr (!SameSizeT) {
            ClauseSizeType clause1Size = contiguousFormulaRepresentationPtr_->getCurrentClauseSize(clauseId1);
            ClauseSizeType clause2Size = contiguousFormulaRepresentationPtr_->getCurrentClauseSize(clauseId2);

            if (clause1Size != clause2Size) {
                if constexpr (EqualityT)
                    return false;
                else
                    return clause1Size < clause2Size;
            }
        }
        #ifndef NDEBUG
        // The clauses have the same size
        else
            assert(contiguousFormulaRepresentationPtr_->getCurrentClauseSize(clauseId1) == contiguousFormulaRepresentationPtr_->getCurrentClauseSize(clauseId2));   // the clauses MUST have the same size
        #endif

        auto clause1It = contiguousFormulaRepresentationPtr_->beginSortedClause(clauseId1);
        auto clause2It = contiguousFormulaRepresentationPtr_->beginSortedClause(clauseId2);
        auto clauseEndIt = contiguousFormulaRepresentationPtr_->endSortedClause();

        for (; clause1It != clauseEndIt; ++clause1It, ++clause2It) {
            VarT var1 = clause1It->getVariable();
            VarT var2 = clause2It->getVariable();

            if (var1 != var2) {
                if constexpr (EqualityT)
                    return false;
                else
                    return var1 < var2;
            }
        }

        if constexpr (EqualityT)
            return true;
        else
            return (clauseId1 < clauseId2);
    }
}   // namespace Hydra::Formula::Representation::Contiguous
