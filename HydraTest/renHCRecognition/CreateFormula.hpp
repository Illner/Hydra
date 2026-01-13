#pragma once

#include <memory>

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

namespace HydraTest::RenHCRecognition {

    /**
     * Formula
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormula(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                           bool assignLitNeg4);

    /**
     * Monotone formula
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createMonotoneFormula(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                                   bool assignLitPos1);

    /**
     * Current component formula
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createCurrentComponentFormula(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                                           bool assignLitPos1AndLitPos6);

    /**
     * RenH-C (ignored pure literals: positive)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCPositive(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * No renH-C (ignored pure literals: positive)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createNoRenHCPositive(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * RenH-C - partial assignment (ignored pure literals: positive)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCPartialAssignmentPositive(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * RenH-C (ignored pure literals: negative)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCNegative(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * No renH-C (ignored pure literals: negative)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createNoRenHCNegative(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * RenH-C - partial assignment (ignored pure literals: negative)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCPartialAssignmentNegative(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * RenH-C (ignored pure literals: both positive and negative)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCBothPositiveAndNegative(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * No renH-C (ignored pure literals: both positive and negative)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createNoRenHCBothPositiveAndNegative(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * RenH-C - partial assignment (ignored pure literals: both positive and negative)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCPartialAssignmentBothPositiveAndNegative(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * RenH-C
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHC(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * RenH-C - partial assignment
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCPartialAssignment(Hydra::Other::HashMap::SetType<VarT>& variableSet);
}   // namespace HydraTest::RenHCRecognition

#include "./CreateFormula.ipp"
