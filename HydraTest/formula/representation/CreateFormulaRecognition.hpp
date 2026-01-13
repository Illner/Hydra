#pragma once

#include <memory>

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.tpp"

namespace HydraTest::Formula::Representation::Recognition {

    /**
     * Formula with connected components
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaWithConnectedComponents(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                                          const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration);

    /**
     * Formula with connected components (partial assignment)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaWithConnectedComponentsPartialAssignment(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                                                           const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration);

    /**
     * Trivial formula
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createTrivialFormula(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                          const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration);

    /**
     * Formula with pure clauses
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaWithPureClauses(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                                  const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration);

    /**
     * Krom-C
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createKromC(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                 const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration);

    /**
     * Krom-C (partial assignment)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createKromCPartialAssignment(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                                  const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration);

    /**
     * Not Krom-C
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createNotKromC(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                    const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration);

    /**
     * Horn-C
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createHornC(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                 const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration);

    /**
     * Horn-C (partial assignment)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createHornCPartialAssignment(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                                  const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration);

    /**
     * Not Horn-C
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createNotHornC(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                    const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration);

    /**
     * Anti-Horn-C
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createAntiHornC(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                     const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration);

    /**
     * Anti-Horn-C (partial assignment)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createAntiHornCPartialAssignment(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                                      const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration);

    /**
     * Not Anti-Horn-C
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createNotAntiHornC(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                        const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration);
}   // namespace HydraTest::Formula::Representation::Recognition

#include "./CreateFormulaRecognition.ipp"
