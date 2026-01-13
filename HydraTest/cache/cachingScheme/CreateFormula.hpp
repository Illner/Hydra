#pragma once

#include "HydraTest/cache/cachingScheme/CachingScheme.hpp"

namespace HydraTest::Cache::CachingScheme {

    /**
     * Variable - char8
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>
    createFormulaVariableChar8(VariableSetType& variableSet);

    /**
     * Variable - char16 (low)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>
    createFormulaVariableChar16Low(VariableSetType& variableSet);

    /**
     * Variable - char16 (high)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>
    createFormulaVariableChar16High(VariableSetType& variableSet);

    /**
     * Variable - char32
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>
    createFormulaVariableChar32(VariableSetType& variableSet);

    /**
     * Literal - char8
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>
    createFormulaLiteralChar8(VariableSetType& variableSet);

    /**
     * Literal - char16 (low)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>
    createFormulaLiteralChar16Low(VariableSetType& variableSet);

    /**
     * Literal - char16 (high)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>
    createFormulaLiteralChar16High(VariableSetType& variableSet);

    /**
     * Literal - char32
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>
    createFormulaLiteralChar32(VariableSetType& variableSet);

    /**
     * Formula
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormula();

    /**
     * Formula for omitting clauses
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForOmittingClauses();

    /**
     * Formula for multi-occurrent clauses
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForMultiOccurrentClauses();

    /**
     * Formula (unit clauses)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaUnitClauses();
}   // namespace HydraTest::Cache::CachingScheme

#include "./CreateFormula.ipp"
