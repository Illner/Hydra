#pragma once

#include <memory>
#include <sstream>
#include <string>

#include "Hydra/decisionHeuristic/DecisionHeuristicAbstract.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/satSolver/SatSolverAbstract.hpp"
#include "Hydra/satSolver/minisat/MiniSatSolver.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"

namespace HydraTest::DecisionHeuristic {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;
    using ClauseIdT = char8_t;

    using VariableSetType = typename Hydra::DecisionHeuristic::DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
    using SatSolverAbstractPtrType = typename Hydra::DecisionHeuristic::DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::SatSolverAbstractPtrType;
    using FormulaRepresentationAbstractPtrType = typename Hydra::DecisionHeuristic::DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    using MiniSatSolverType = Hydra::SatSolver::MiniSat::MiniSatSolver<VarT, LiteralT, ClauseIdT>;
    using SatSolverAbstractUniquePtrType = std::unique_ptr<Hydra::SatSolver::SatSolverAbstract<VarT, LiteralT, ClauseIdT>>;
    using DecisionHeuristicAbstractPtrType = const Hydra::DecisionHeuristic::DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>*;
    using DecisionHeuristicAbstractUniquePtrType = std::unique_ptr<Hydra::DecisionHeuristic::DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>>;
    using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

    using IgnorePureLiteralTypeEnum = Hydra::IgnorePureLiteralTypeEnum;
    //endregion

    inline SatSolverAbstractUniquePtrType createSatSolver(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr) {
        return std::make_unique<MiniSatSolverType>(formulaRepresentationAbstractPtr, true);
    }

    inline void printDecisionHeuristic(DecisionHeuristicAbstractPtrType decisionHeuristicAbstractPtr, std::stringstream& actualResult,
                                       bool printCurrentFormula = true) {
        decisionHeuristicAbstractPtr->printDecisionHeuristicDebug(actualResult, printCurrentFormula);
        actualResult << std::endl;
    }

    inline void printSelectedVariables(const VariableSetType& selectedVariableSet, std::stringstream& actualResult) {
        actualResult << "Selected variables:";
        for (VarT var : Hydra::Other::sortUnorderedSet(selectedVariableSet))
            actualResult << " " << std::to_string(var);
        actualResult << std::endl;
    }

    inline void computeDecisionHeuristic(DecisionHeuristicAbstractPtrType decisionHeuristicAbstractPtr, const VariableSetType& selectedVariableSet,
                                         std::stringstream& actualResult, bool printDecisionVariableAndSelectedVariableSet = true,
                                         bool removeIgnoredPureVariables = false) {
        if (printDecisionVariableAndSelectedVariableSet)
            printSelectedVariables(selectedVariableSet, actualResult);

        VarT decisionVariable = decisionHeuristicAbstractPtr->getDecisionVariable(selectedVariableSet, removeIgnoredPureVariables);

        actualResult << "Decision variable: ";
        if (printDecisionVariableAndSelectedVariableSet)
            actualResult << std::to_string(decisionVariable) << std::endl;
        else {
            if (Hydra::Other::containInSet(selectedVariableSet, decisionVariable))
                actualResult << "correct";
            else
                actualResult << "incorrect";
        }
        actualResult << std::endl;
    }

    inline VariableSetType generateSelectedVariableSet(VarT maxVariable) {
        VariableSetType selectedVariableSet(maxVariable);

        for (VarT i = 1; i <= maxVariable; ++i)
            selectedVariableSet.emplace(i);

        return selectedVariableSet;
    }
}   // namespace HydraTest::DecisionHeuristic
