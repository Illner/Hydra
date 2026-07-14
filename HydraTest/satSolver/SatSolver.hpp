#pragma once

#include <algorithm>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/satSolver/EquivalencePreprocessingStructure.hpp"
#include "Hydra/satSolver/SatSolverAbstract.hpp"

#include "Hydra/satSolver/exceptions/SatSolverException.hpp"

#include "Hydra/satSolver/enums/ImplicitBcpVariableOrderTypeEnum.hpp"

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
    using FormulaRepresentationAbstractPtrType = Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;
    using FormulaRepresentationAbstractConstPtrType = const Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;
    using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

    using ImplicitBcpVariableOrderTypeEnum = Hydra::SatSolver::ImplicitBcpVariableOrderTypeEnum;
    //endregion

    inline void printSatSolver(SatSolverAbstractConstPtrType satSolverAbstractPtr, std::stringstream& actualResult, bool printCoreSatSolver = true) {
        satSolverAbstractPtr->printSatSolverDebug(actualResult, printCoreSatSolver);
        actualResult << std::endl;
    }

    inline void printCurrentFormula(FormulaRepresentationAbstractConstPtrType formulaRepresentationAbstractPtr, std::stringstream& actualResult) {
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

    inline VariableSetType generateSelectedVariableSet(VarT maxVariable) {
        VariableSetType selectedVariableSet(maxVariable);

        for (VarT var = 1; var <= maxVariable; ++var)
            selectedVariableSet.emplace(var);

        return selectedVariableSet;
    }

    inline void isSatisfiableAssumptions(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, SatSolverAbstractPtrType satSolverAbstractPtr,
                                         std::stringstream& actualResult) {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg6(6, false);
        LiteralType litPos8(8, true);
        //endregion

        VariableVectorType tmp;
        VariableSetType variableSet = generateSelectedVariableSet(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormula());
        std::vector<LiteralVectorType> assumptionsVector { {}, { litPos1 }, { litPos3 }, { litPos1, litNeg3 }, { litPos2 }, { litNeg2 }, { litNeg4, litPos5 }, { litNeg6, litPos8 }, {} };

        for (const LiteralVectorType& assumptions : assumptionsVector) {
            actualResult << "--------------------------------------------------" << std::endl;
            printAssumption(assumptions, actualResult);
            actualResult << "--------------------------------------------------" << std::endl;

            for (const LiteralType& lit : assumptions)
                variableSet.erase(lit.getVariable());

            try {
                formulaRepresentationAbstractPtr->addLiteralVectorToPartialAssignment(assumptions, tmp);
                satSolverAbstractPtr->assignLiteralVector(assumptions);

                printSatSolver(satSolverAbstractPtr, actualResult, false);

                bool isSatisfiable = satSolverAbstractPtr->isSatisfiable(variableSet);
                actualResult << "------------------------------" << std::endl;
                actualResult << "Is satisfiable: " << std::to_string(isSatisfiable) << std::endl;
                actualResult << "------------------------------" << std::endl;

                satSolverAbstractPtr->unassignLiteralVector(assumptions, true);
                formulaRepresentationAbstractPtr->removeLiteralVectorFromPartialAssignment(assumptions, tmp, true);

                printSatSolver(satSolverAbstractPtr, actualResult, false);
            }
            catch (const Hydra::Exception::SatSolver::SatSolverException& e) {
                actualResult << e.what() << std::endl;
            }

            for (const LiteralType& lit : assumptions)
                variableSet.emplace(lit.getVariable());
        }
    }

    inline void processUnitPropagation(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, SatSolverAbstractPtrType satSolverAbstractPtr,
                                       std::stringstream& actualResult) {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litNeg3(3, false);
        LiteralType litNeg4(4, false);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        //endregion

        VariableVectorType tmp;
        VariableSetType restrictedVariableSet = generateSelectedVariableSet(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormula());
        std::vector<LiteralVectorType> assumptionsVector { {}, { litNeg2 }, { litNeg5 }, { litPos6 }, { litNeg5, litPos6 }, { litPos1, litPos2, litNeg3, litNeg4, litNeg5 }, { litPos1, litPos2, litNeg3, litNeg4, litPos6 }, { litPos1, litPos2, litNeg3, litNeg4, litNeg5, litPos6 } };

        for (const LiteralVectorType& assumptions : assumptionsVector) {
            for (bool includeAssumptions : { true, false }) {
                actualResult << "------------------------------" << std::endl;
                printAssumption(assumptions, actualResult);
                actualResult << "Include assumptions: " << std::to_string(includeAssumptions) << std::endl;
                actualResult << "------------------------------" << std::endl;

                try {
                    formulaRepresentationAbstractPtr->addLiteralVectorToPartialAssignment(assumptions, tmp);
                    satSolverAbstractPtr->assignLiteralVector(assumptions);

                    doUnitPropagation(satSolverAbstractPtr, restrictedVariableSet, includeAssumptions, actualResult);

                    satSolverAbstractPtr->unassignLiteralVector(assumptions, true);
                    formulaRepresentationAbstractPtr->removeLiteralVectorFromPartialAssignment(assumptions, tmp, true);
                }
                catch (const Hydra::Exception::SatSolver::SatSolverException& e) {
                    actualResult << e.what() << std::endl;
                }

                actualResult << std::endl;
            }
        }
    }

    inline void processUnitPropagationRestrictions(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                                   SatSolverAbstractPtrType satSolverAbstractPtr, std::stringstream& actualResult) {
        //region Literals
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        //endregion

        VariableVectorType tmp;
        std::vector<VariableSetType> restrictedVariableSetVector { {}, { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, { 1, 2, 3, 4 }, { 5, 6, 7, 8, 9 }, { 6, 7, 8 }, { 9 } };
        std::vector<LiteralVectorType> assumptionsVector { {}, { litNeg5 }, { litPos6 }, { litNeg5, litPos6 } };

        for (const VariableSetType& restrictedVariableSet : restrictedVariableSetVector) {
            for (const LiteralVectorType& assumptions : assumptionsVector) {
                for (bool includeAssumptions : { true, false }) {
                    actualResult << "------------------------------" << std::endl;
                    printAssumption(assumptions, actualResult);
                    actualResult << "Include assumptions: " << std::to_string(includeAssumptions) << std::endl;
                    actualResult << "Restricted variables:";
                    for (VarT var : Hydra::Other::sortUnorderedSet(restrictedVariableSet))
                        actualResult << " " << std::to_string(var);
                    actualResult << std::endl;
                    actualResult << "------------------------------" << std::endl;

                    try {
                        formulaRepresentationAbstractPtr->addLiteralVectorToPartialAssignment(assumptions, tmp);
                        satSolverAbstractPtr->assignLiteralVector(assumptions);

                        doUnitPropagation(satSolverAbstractPtr, restrictedVariableSet, includeAssumptions, actualResult);

                        satSolverAbstractPtr->unassignLiteralVector(assumptions, true);
                        formulaRepresentationAbstractPtr->removeLiteralVectorFromPartialAssignment(assumptions, tmp, true);
                    }
                    catch (const Hydra::Exception::SatSolver::SatSolverException& e) {
                        actualResult << e.what() << std::endl;
                    }

                    actualResult << std::endl;
                }
            }
        }
    }

    inline void processEquivalencePreprocessingStructureSelectedVariables(SatSolverAbstractPtrType satSolverAbstractPtr, std::stringstream& actualResult) {
        std::vector<VariableSetType> selectedVariablesVector { {}, { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }, { 10, 11, 12 }, { 7, 8, 9, 10, 11, 12, 13, 14, 15 }, { 16, 17, 18 }, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 } };

        for (const VariableSetType& selectedVariables : selectedVariablesVector) {
            actualResult << "------------------------------" << std::endl;
            printSelectedVariableSet(selectedVariables, actualResult);
            actualResult << "------------------------------" << std::endl;

            EquivalencePreprocessingStruct equivalencePreprocessingStruct = satSolverAbstractPtr->createEquivalencePreprocessingStruct(selectedVariables,
                                                                                                                                       false,
                                                                                                                                       ImplicitBcpVariableOrderTypeEnum::VARIABLE_INDEX);

            satSolverAbstractPtr->unassignLiteralVector(equivalencePreprocessingStruct.implicitImpliedLiteralVector, true);

            printEquivalencePreprocessingStructure(equivalencePreprocessingStruct, actualResult);
        }
    }
}   // namespace HydraTest::SatSolver
