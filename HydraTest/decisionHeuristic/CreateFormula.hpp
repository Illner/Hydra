#pragma once

#include <iterator>
#include <memory>
#include <sstream>

#include "HydraTest/decisionHeuristic/DecisionHeuristicFormula.hpp"

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.hpp"
#include "Hydra/formula/representation/contagious/parser/ContagiousFormulaParser.hpp"
#include "Hydra/other/parser/Parser.hpp"

namespace HydraTest::DecisionHeuristic {

    /**
     * Formula for literal count decision heuristic
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForLiteralCount();

    /**
     * Formula for literal count decision heuristic (ignore pure literals)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForLiteralCountIgnorePureLiterals();

    /**
     * Formula for Jeroslow-Wang decision heuristic
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForJeroslowWang();

    /**
     * Formula for Jeroslow-Wang decision heuristic (ignore pure literals)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForJeroslowWangIgnorePureLiterals();

    /**
     * Pigeon hole formula
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createPigeonHoleFormula();

    /**
     * Formula for UPC
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForUpc();

}   // namespace HydraTest::DecisionHeuristic

#include "./CreateFormula.ipp"
