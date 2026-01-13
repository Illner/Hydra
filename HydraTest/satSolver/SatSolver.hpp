#pragma once

#include <algorithm>
#include <memory>
#include <sstream>
#include <string>

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/satSolver/EquivalencePreprocessingStructure.hpp"
#include "Hydra/satSolver/SatSolverAbstract.hpp"

namespace HydraTest::SatSolver {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;
    using ClauseIdT = char8_t;

    using LiteralType = typename Hydra::SatSolver::SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
    using VariableSetType = typename Hydra::SatSolver::SatSolverAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
    using LiteralVectorType = typename Hydra::SatSolver::SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
    using VariableVectorType = typename Hydra::SatSolver::SatSolverAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;

    using SatSolverAbstractPtrType = Hydra::SatSolver::SatSolverAbstract<VarT, LiteralT, ClauseIdT>*;
    using EquivalencePreprocessingStruct = Hydra::SatSolver::EquivalencePreprocessingStruct<VarT, LiteralT>;
    using SatSolverAbstractConstPtrType = const Hydra::SatSolver::SatSolverAbstract<VarT, LiteralT, ClauseIdT>*;
    using SatSolverAbstractUniquePtrType = std::unique_ptr<Hydra::SatSolver::SatSolverAbstract<VarT, LiteralT, ClauseIdT>>;
    using FormulaRepresentationAbstractPtrType = const Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;
    using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;
    //endregion

    inline void printSatSolver(SatSolverAbstractConstPtrType satSolverAbstractPtr, std::stringstream& actualResult, bool printCoreSatSolver = true) {
        satSolverAbstractPtr->printSatSolverDebug(actualResult, printCoreSatSolver);
        actualResult << std::endl;
    }

    inline void printCurrentFormula(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, std::stringstream& actualResult) {
        actualResult << "Current formula: ";
        formulaRepresentationAbstractPtr->printCurrentFormulaDebug(actualResult);
        actualResult << std::endl
                     << std::endl;
    }

    inline void printAssumption(const LiteralVectorType& assumption, std::stringstream& actualResult) {
        actualResult << "Assumption:";
        for (const LiteralType& lit : assumption)
            actualResult << " " << lit;
        actualResult << std::endl;
    }

    inline void printRestrictedVariableSet(const VariableSetType& restrictedVariableSet, std::stringstream& actualResult) {
        actualResult << "Restricted variables:";
        for (VarT var : Hydra::Other::sortUnorderedSet(restrictedVariableSet))
            actualResult << " " << std::to_string(var);
        actualResult << std::endl;
    }

    inline void printSelectedVariableSet(const VariableSetType& selectedVariableSet, std::stringstream& actualResult) {
        actualResult << "Selected variables:";
        for (VarT var : Hydra::Other::sortUnorderedSet(selectedVariableSet))
            actualResult << " " << std::to_string(var);
        actualResult << std::endl;
    }

    inline void doUnitPropagation(SatSolverAbstractPtrType satSolverAbstractPtr, const VariableSetType& restrictedVariableSet,
                                  bool includeAssumptions, std::stringstream& actualResult) {
        // The current formula is not satisfiable
        if (!satSolverAbstractPtr->unitPropagation(restrictedVariableSet, includeAssumptions)) {
            actualResult << "Formula is not satisfiable" << std::endl;
            return;
        }

        actualResult << "Implied literals:";
        for (const LiteralType& lit : satSolverAbstractPtr->getImpliedLiteralVectorFromPreviousCallOfUnitPropagation(true))
            actualResult << " " << lit;
        actualResult << std::endl;
    }

    inline void printEquivalencePreprocessingStructure(EquivalencePreprocessingStruct& equivalencePreprocessingStruct, std::stringstream& actualResult) {
        // Implicit implied literals
        actualResult << "Implicit implied literals:";

        // Because of unassignment
        LiteralVectorType tmp(equivalencePreprocessingStruct.implicitImpliedLiteralVector.cbegin(), equivalencePreprocessingStruct.implicitImpliedLiteralVector.cend());
        std::sort(tmp.begin(), tmp.end());

        for (const LiteralType& lit : tmp)
            actualResult << " " << lit;
        actualResult << std::endl;

        // Equivalence preprocessing structure
        for (VariableVectorType& equivalence : equivalencePreprocessingStruct.equivalencePreprocessingStructure) {
            VarT representant = equivalence[0];

            std::sort(equivalence.begin(), equivalence.end());

            actualResult << std::to_string(representant) << ":";
            for (VarT var : equivalence)
                actualResult << " " << std::to_string(var);
            actualResult << std::endl;
        }
    }
}   // namespace HydraTest::SatSolver
