#pragma once

#include <memory>

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

namespace HydraTest::Formula::StructuralRestrictedRepresentation {

    /**
     * Krom-C (none)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createKromCNone(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * Krom-C (no duplicate)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createKromCNoDuplicate(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * Krom-C (no subsumed)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createKromCNoSubsumed(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * Horn-C (none)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createHornCNone(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * Horn-C (no duplicate)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createHornCNoDuplicate(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * Horn-C (no subsumed)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createHornCNoSubsumed(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * anti-Horn-C (none)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createAntiHornCNone(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * anti-Horn-C (no duplicate)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createAntiHornCNoDuplicate(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * anti-Horn-C (no subsumed)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createAntiHornCNoSubsumed(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * renH-C (none)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCNone(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * renH-C (no duplicate)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCNoDuplicate(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * renH-C (no subsumed)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCNoSubsumed(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * Formula with connected components
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaWithConnectedComponents(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * Krom-C (partial assignment)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createKromCPartialAssignment(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * Horn-C (partial assignment)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createHornCPartialAssignment(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * anti-Horn-C (partial assignment)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createAntiHornCPartialAssignment(Hydra::Other::HashMap::SetType<VarT>& variableSet);

    /**
     * renH-C (partial assignment)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCPartialAssignment(Hydra::Other::HashMap::SetType<VarT>& variableSet);
}   // namespace HydraTest::Formula::StructuralRestrictedRepresentation

#include "./CreateFormula.ipp"
