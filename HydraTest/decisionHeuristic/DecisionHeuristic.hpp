#pragma once

#include <memory>
#include <sstream>
#include <string>

#include "Hydra/decisionHeuristic/DecisionHeuristicAbstract.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/satSolver/SatSolverAbstract.hpp"
#include "Hydra/satSolver/cadical/CadicalSolver.hpp"
#include "Hydra/satSolver/glucose/GlucoseSolver.hpp"
#include "Hydra/satSolver/minisat/MiniSatSolver.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/satSolver/enums/SatSolverTypeEnum.hpp"

namespace HydraTest::DecisionHeuristic {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;
    using ClauseIdT = char8_t;

    using VariableSetType = typename Hydra::DecisionHeuristic::DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
    using SatSolverAbstractPtrType = typename Hydra::DecisionHeuristic::DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::SatSolverAbstractPtrType;
    using FormulaRepresentationAbstractPtrType = typename Hydra::DecisionHeuristic::DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    using CadicalSolverType = Hydra::SatSolver::Cadical::CadicalSolver<VarT, LiteralT, ClauseIdT>;
    using GlucoseSolverType = Hydra::SatSolver::Glucose::GlucoseSolver<VarT, LiteralT, ClauseIdT>;
    using MiniSatSolverType = Hydra::SatSolver::MiniSat::MiniSatSolver<VarT, LiteralT, ClauseIdT>;
    using SatSolverAbstractUniquePtrType = std::unique_ptr<Hydra::SatSolver::SatSolverAbstract<VarT, LiteralT, ClauseIdT>>;
    using DecisionHeuristicAbstractConstPtrType = const Hydra::DecisionHeuristic::DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>*;
    using DecisionHeuristicAbstractUniquePtrType = std::unique_ptr<Hydra::DecisionHeuristic::DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>>;
    using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

    using SatSolverTypeEnum = Hydra::SatSolver::SatSolverTypeEnum;
    using IgnorePureLiteralTypeEnum = Hydra::IgnorePureLiteralTypeEnum;
    //endregion

    inline SatSolverAbstractUniquePtrType createSatSolver(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                                          SatSolverTypeEnum satSolverType = SatSolverTypeEnum::MINISAT) {
        switch (satSolverType) {
                // MiniSat
            case SatSolverTypeEnum::MINISAT:
                return std::make_unique<MiniSatSolverType>(formulaRepresentationAbstractPtr, true);
                // Glucose
            case SatSolverTypeEnum::GLUCOSE:
                return std::make_unique<GlucoseSolverType>(formulaRepresentationAbstractPtr, true);
                // CaDiCaL
            case SatSolverTypeEnum::CADICAL:
                return std::make_unique<CadicalSolverType>(formulaRepresentationAbstractPtr);
            default:
                throw Hydra::Exception::SomethingIsWrongException();
        }
    }

    inline void printDecisionHeuristic(DecisionHeuristicAbstractConstPtrType decisionHeuristicAbstractPtr, std::stringstream& actualResult,
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

    inline void computeDecisionHeuristic(DecisionHeuristicAbstractConstPtrType decisionHeuristicAbstractPtr, const VariableSetType& selectedVariableSet,
                                         const VariableSetType& currentComponentVariableSet, std::stringstream& actualResult,
                                         bool printDecisionVariableAndSelectedVariableSet = true, bool removeIgnoredPureVariables = false) {
        if (printDecisionVariableAndSelectedVariableSet)
            printSelectedVariables(selectedVariableSet, actualResult);

        VarT decisionVariable = decisionHeuristicAbstractPtr->getDecisionVariable(selectedVariableSet, currentComponentVariableSet, removeIgnoredPureVariables);

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

    inline VariableSetType generateCurrentComponentVariableSet(VarT maxVariable) {
        VariableSetType currentComponentVariableSet(maxVariable);

        for (VarT var = 1; var <= maxVariable; ++var)
            currentComponentVariableSet.emplace(var);

        return currentComponentVariableSet;
    }
}   // namespace HydraTest::DecisionHeuristic
