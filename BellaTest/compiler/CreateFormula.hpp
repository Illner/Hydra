#pragma once

#include <iterator>
#include <memory>

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.hpp"
#include "Hydra/formula/representation/contagious/parser/ContagiousFormulaParser.hpp"
#include "Hydra/other/parser/Parser.hpp"

namespace BellaTest::Compiler {

    /**
     * Formula for wDNNF
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForWDnnf();

    /**
     * Formula for wDNNF (cut)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForWDnnfCut();

    /**
     * Formula for pwDNNF (cut)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForPWDnnfCut();

    /**
     * Formula for nwDNNF (cut)
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForNWDnnfCut();

    /**
     * Formula for singletons
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForSingletons();
}   // namespace BellaTest::Compiler

#include "./CreateFormula.ipp"
