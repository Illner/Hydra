#pragma once

#include <cassert>
#include <memory>
#include <sstream>
#include <string>

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/renHCRecognition/RenHCRecognitionAbstract.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"

namespace HydraTest::RenHCRecognition {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;
    using ClauseIdT = char8_t;

    using LiteralType = typename Hydra::RenHCRecognition::RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
    using ClauseIdSetType = typename Hydra::RenHCRecognition::RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdSetType;
    using VariableSetType = typename Hydra::RenHCRecognition::RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
    using VariableSetOptionalType = typename Hydra::RenHCRecognition::RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::VariableSetOptionalType;
    using LiteralVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
    using VariableVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
    using ConnectedComponentType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ConnectedComponentType;
    using ConnectedComponentStruct = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ConnectedComponentStruct;
    using PureVariableRemovedClausesVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::PureVariableRemovedClausesVectorType;

    using RenHCRecognitionAbstractPtrType = Hydra::RenHCRecognition::RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>*;
    using RenHCRecognitionAbstractConstPtrType = const Hydra::RenHCRecognition::RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>*;
    using FormulaRepresentationAbstractPtrType = Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;
    using RenHCRecognitionAbstractUniquePtrType = std::unique_ptr<Hydra::RenHCRecognition::RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>>;
    using FormulaRepresentationAbstractConstPtrType = const Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;
    using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

    using IgnorePureLiteralTypeEnum = Hydra::RenHCRecognition::RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::IgnorePureLiteralTypeEnum;
    //endregion

    inline void printRenHCRecognition(RenHCRecognitionAbstractConstPtrType renHCRecognitionAbstractPtr, std::stringstream& actualResult) {
        renHCRecognitionAbstractPtr->printRenHCRecognitionDebug(actualResult);
        actualResult << std::endl;
    }

    inline void printCurrentFormula(FormulaRepresentationAbstractConstPtrType formulaRepresentationAbstractPtr, std::stringstream& actualResult) {
        actualResult << "Current formula: ";
        formulaRepresentationAbstractPtr->printCurrentFormulaDebug(actualResult);
        actualResult << std::endl
                     << std::endl;
    }

    inline void printClauses(const ClauseIdSetType& clauseSet, std::stringstream& actualResult) {
        actualResult << "Clauses:";
        for (ClauseIdT clauseId : Hydra::Other::sortUnorderedSet(clauseSet))
            actualResult << " " << std::to_string(clauseId);
        actualResult << std::endl;
    }

    inline void printPureClauses(const ClauseIdSetType& clauseSet, std::stringstream& actualResult) {
        actualResult << "Pure clauses:";
        for (ClauseIdT clauseId : Hydra::Other::sortUnorderedSet(clauseSet))
            actualResult << " " << std::to_string(clauseId);
        actualResult << std::endl;
    }

    inline void printCurrentComponentVariables(const VariableSetType& currentComponentVariableSet, std::stringstream& actualResult) {
        actualResult << "Current component variables:";
        for (VarT var : Hydra::Other::sortUnorderedSet(currentComponentVariableSet))
            actualResult << " " << std::to_string(var);
        actualResult << std::endl;
    }

    inline void printIsRenHC(const VariableSetOptionalType& switchedVariableSet, std::stringstream& actualResult) {
        // No renH-C
        if (!switchedVariableSet.has_value()) {
            actualResult << "no renH-C" << std::endl;
            return;
        }

        // RenH-C
        actualResult << "Switched variables:";
        for (VarT var : Hydra::Other::sortUnorderedSet(*switchedVariableSet))
            actualResult << " " << std::to_string(var);
        actualResult << std::endl;
    }

    inline void printConnectedComponents(const ConnectedComponentType& connectedComponents, bool printPureVariables, std::stringstream& actualResult) {
        actualResult << "Connected components:" << std::endl;

        for (const ConnectedComponentStruct& connectedComponentStruct : connectedComponents) {
            actualResult << "\t";

            for (VarT var : Hydra::Other::sortUnorderedSet(connectedComponentStruct.variableSet))
                actualResult << " " << std::to_string(var);

            if (printPureVariables) {
                // Pure literals
                actualResult << " |";
                for (const LiteralType& lit : connectedComponentStruct.pureLiteralVector)
                    actualResult << " " << lit;
            }

            actualResult << std::endl;
        }

        actualResult << std::endl;
    }

    inline void printSetNewConnectedComponent(const ConnectedComponentStruct& newConnectedComponent, std::stringstream& actualResult) {
        actualResult << "----------------------------------------" << std::endl;
        actualResult << "Set connected component:";
        for (VarT var : Hydra::Other::sortUnorderedSet(newConnectedComponent.variableSet))
            actualResult << " " << std::to_string(var);
        actualResult << std::endl;
        actualResult << "----------------------------------------" << std::endl;
    }

    inline void printPopPreviousConnectedComponent(const ConnectedComponentStruct& newConnectedComponent, std::stringstream& actualResult) {
        actualResult << "----------------------------------------" << std::endl;
        actualResult << "Pop connected component:";
        for (VarT var : Hydra::Other::sortUnorderedSet(newConnectedComponent.variableSet))
            actualResult << " " << std::to_string(var);
        actualResult << std::endl;
        actualResult << "----------------------------------------" << std::endl;
    }

    inline void isRenHC(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, RenHCRecognitionAbstractPtrType renHCRecognitionAbstractPtr,
                        const VariableSetType& currentComponentVariableSet, IgnorePureLiteralTypeEnum ignorePureLiteralType, std::stringstream& actualResult) {
        // Print
        Hydra::Other::printTitle(actualResult, "Initial", 30, '-');
        printCurrentFormula(formulaRepresentationAbstractPtr, actualResult);
        printRenHCRecognition(renHCRecognitionAbstractPtr, actualResult);

        // Compute connected components
        ClauseIdSetType pureClauseSet;
        ConnectedComponentType connectedComponents;
        if (ignorePureLiteralType == IgnorePureLiteralTypeEnum::NONE)
            connectedComponents = formulaRepresentationAbstractPtr->computeConnectedComponents(currentComponentVariableSet);
        else
            connectedComponents = formulaRepresentationAbstractPtr->computeConnectedComponents(currentComponentVariableSet, pureClauseSet, ignorePureLiteralType);
        printConnectedComponents(connectedComponents, (ignorePureLiteralType != IgnorePureLiteralTypeEnum::NONE), actualResult);
        if (ignorePureLiteralType != IgnorePureLiteralTypeEnum::NONE) {
            printPureClauses(pureClauseSet, actualResult);
            actualResult << std::endl;
        }

        if (ignorePureLiteralType != IgnorePureLiteralTypeEnum::NONE) {
            // Remove pure clauses
            renHCRecognitionAbstractPtr->setInactiveClauseSet(pureClauseSet);
            formulaRepresentationAbstractPtr->removeClausesContainingOnlyPureLiteralsOfIgnoredType(pureClauseSet, ignorePureLiteralType);

            // Print
            Hydra::Other::printTitle(actualResult, "Remove pure clauses", 30, '-');
            printCurrentFormula(formulaRepresentationAbstractPtr, actualResult);
            printRenHCRecognition(renHCRecognitionAbstractPtr, actualResult);
        }

        // Connected components
        for (const ConnectedComponentStruct& newConnectedComponent : connectedComponents) {
            // Set new component
            printSetNewConnectedComponent(newConnectedComponent, actualResult);
            PureVariableRemovedClausesVectorType pureVariableRemovedClausesVector = formulaRepresentationAbstractPtr->setNewComponent(newConnectedComponent,
                                                                                                                                      ignorePureLiteralType);
            printCurrentFormula(formulaRepresentationAbstractPtr, actualResult);

            // Is renH-C
            VariableSetOptionalType switchedVariableSet = renHCRecognitionAbstractPtr->isRenHC(newConnectedComponent);
            printIsRenHC(switchedVariableSet, actualResult);
            actualResult << std::endl;

            // Pop previous component
            printPopPreviousConnectedComponent(newConnectedComponent, actualResult);
            formulaRepresentationAbstractPtr->popPreviousComponent(newConnectedComponent, pureVariableRemovedClausesVector);
            printCurrentFormula(formulaRepresentationAbstractPtr, actualResult);

            actualResult << "--------------------------------------------------------------------------------" << std::endl;
            actualResult << std::endl;
        }

        if (ignorePureLiteralType != IgnorePureLiteralTypeEnum::NONE) {
            // Add pure clauses
            formulaRepresentationAbstractPtr->addClausesContainingOnlyPureLiteralsOfIgnoredType(pureClauseSet, ignorePureLiteralType);
            renHCRecognitionAbstractPtr->setActiveClauseSet(pureClauseSet, currentComponentVariableSet);

            // Print
            Hydra::Other::printTitle(actualResult, "Add pure clauses", 30, '-');
            printCurrentFormula(formulaRepresentationAbstractPtr, actualResult);
            printRenHCRecognition(renHCRecognitionAbstractPtr, actualResult);
        }
    }

    inline void verifyRenHC(RenHCRecognitionAbstractConstPtrType renHCRecognitionAbstractPtr, const VariableSetType& switchedVariableSet,
                            std::stringstream& actualResult) {
        actualResult << "Switched variables:";
        for (VarT var : Hydra::Other::sortUnorderedSet(switchedVariableSet))
            actualResult << " " << std::to_string(var);
        actualResult << std::endl;

        bool result = renHCRecognitionAbstractPtr->verifyRenHCDebug(switchedVariableSet);

        actualResult << "renH-C: " << std::to_string(result) << std::endl
                     << std::endl;
    }

    inline ConnectedComponentType computeConnectedComponents(FormulaRepresentationAbstractConstPtrType formulaRepresentationAbstractPtr,
                                                             const VariableSetType& currentComponentVariableSet, std::stringstream& actualResult) {
        ConnectedComponentType connectedComponents = formulaRepresentationAbstractPtr->computeConnectedComponents(currentComponentVariableSet);
        printConnectedComponents(connectedComponents, false, actualResult);

        return connectedComponents;
    }

    inline void setNewComponent(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                const ConnectedComponentStruct& newConnectedComponentStruct, std::stringstream& actualResult, bool print = true) {
        if (print)
            printSetNewConnectedComponent(newConnectedComponentStruct, actualResult);

        auto tmp = formulaRepresentationAbstractPtr->setNewComponent(newConnectedComponentStruct,
                                                                     IgnorePureLiteralTypeEnum::NONE);

        assert(tmp.empty());   // no pure clauses

        if (print)
            printCurrentFormula(formulaRepresentationAbstractPtr, actualResult);
    }

    inline void popPreviousComponent(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                     const ConnectedComponentStruct& currentConnectedComponentStruct, std::stringstream& actualResult, bool print = true) {
        if (print)
            printPopPreviousConnectedComponent(currentConnectedComponentStruct, actualResult);

        formulaRepresentationAbstractPtr->popPreviousComponent(currentConnectedComponentStruct, {});

        if (print)
            printCurrentFormula(formulaRepresentationAbstractPtr, actualResult);
    }

    inline void assignLiteral(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                              RenHCRecognitionAbstractPtrType renHCRecognitionAbstractPtr, const LiteralType& lit,
                              VariableSetType& currentComponentVariableSet, std::stringstream& actualResult) {
        assert(!formulaRepresentationAbstractPtr->isVariableAssigned(lit.getVariable()));   // not assigned
        assert(Hydra::Other::containInSet(currentComponentVariableSet, lit.getVariable()));

        currentComponentVariableSet.erase(lit.getVariable());

        actualResult << "--------------------" << std::endl;
        actualResult << "Assigned literal: " << lit << std::endl;
        actualResult << "--------------------" << std::endl;

        // Formula
        VariableVectorType freeVariableVector;
        formulaRepresentationAbstractPtr->addLiteralToPartialAssignment(lit, freeVariableVector);

        // Remove the free variables
        for (VarT var : freeVariableVector) {
            assert(Hydra::Other::containInSet(currentComponentVariableSet, var));

            currentComponentVariableSet.erase(var);
        }

        printCurrentFormula(formulaRepresentationAbstractPtr, actualResult);

        // RenH-C recognition
        renHCRecognitionAbstractPtr->setAssignedLiteral(lit, currentComponentVariableSet);

        printRenHCRecognition(renHCRecognitionAbstractPtr, actualResult);
    }

    inline void assignLiteralVector(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                    RenHCRecognitionAbstractPtrType renHCRecognitionAbstractPtr, const LiteralVectorType& literalVector,
                                    VariableSetType& currentComponentVariableSet, std::stringstream& actualResult) {
        for (const LiteralType& lit : literalVector) {
            assert(!formulaRepresentationAbstractPtr->isVariableAssigned(lit.getVariable()));   // not assigned
            assert(Hydra::Other::containInSet(currentComponentVariableSet, lit.getVariable()));

            currentComponentVariableSet.erase(lit.getVariable());
        }

        actualResult << "----------------------------------------" << std::endl;
        actualResult << "Assigned literals:";
        for (const LiteralType& lit : literalVector)
            actualResult << " " << lit;
        actualResult << std::endl;
        actualResult << "----------------------------------------" << std::endl;

        // Formula
        VariableVectorType freeVariableVector;
        formulaRepresentationAbstractPtr->addLiteralVectorToPartialAssignment(literalVector, freeVariableVector);

        // Remove the free variables
        for (VarT var : freeVariableVector) {
            assert(Hydra::Other::containInSet(currentComponentVariableSet, var));

            currentComponentVariableSet.erase(var);
        }

        printCurrentFormula(formulaRepresentationAbstractPtr, actualResult);

        // RenH-C recognition
        renHCRecognitionAbstractPtr->setAssignedLiteralVector(literalVector, currentComponentVariableSet);

        printRenHCRecognition(renHCRecognitionAbstractPtr, actualResult);
    }

    inline void unassignLiteral(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                RenHCRecognitionAbstractPtrType renHCRecognitionAbstractPtr, const LiteralType& lit,
                                VariableSetType& currentComponentVariableSet, std::stringstream& actualResult) {
        assert(formulaRepresentationAbstractPtr->isVariableAssigned(lit.getVariable()));   // assigned
        assert(!Hydra::Other::containInSet(currentComponentVariableSet, lit.getVariable()));

        currentComponentVariableSet.emplace(lit.getVariable());

        actualResult << "----------------------" << std::endl;
        actualResult << "Unassigned literal: " << lit << std::endl;
        actualResult << "----------------------" << std::endl;

        VariableVectorType unfreeVariableVector;
        formulaRepresentationAbstractPtr->removeLiteralFromPartialAssignment(lit, unfreeVariableVector);

        // Add the unfree variables
        for (VarT var : unfreeVariableVector) {
            assert(!Hydra::Other::containInSet(currentComponentVariableSet, var));

            currentComponentVariableSet.emplace(var);
        }

        printCurrentFormula(formulaRepresentationAbstractPtr, actualResult);

        // RenH-C recognition
        renHCRecognitionAbstractPtr->setUnassignedLiteral(lit);

        printRenHCRecognition(renHCRecognitionAbstractPtr, actualResult);
    }

    inline void unassignLiteralVector(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                      RenHCRecognitionAbstractPtrType renHCRecognitionAbstractPtr, const LiteralVectorType& literalVector,
                                      VariableSetType& currentComponentVariableSet, std::stringstream& actualResult) {
        for (const LiteralType& lit : literalVector) {
            assert(formulaRepresentationAbstractPtr->isVariableAssigned(lit.getVariable()));   // assigned
            assert(!Hydra::Other::containInSet(currentComponentVariableSet, lit.getVariable()));

            currentComponentVariableSet.emplace(lit.getVariable());
        }

        actualResult << "--------------------------------------------" << std::endl;
        actualResult << "Unassigned literals:";
        for (const LiteralType& lit : literalVector)
            actualResult << " " << lit;
        actualResult << std::endl;
        actualResult << "--------------------------------------------" << std::endl;

        VariableVectorType unfreeVariableVector;
        formulaRepresentationAbstractPtr->removeLiteralVectorFromPartialAssignment(literalVector, unfreeVariableVector);

        // Add the unfree variables
        for (VarT var : unfreeVariableVector) {
            assert(!Hydra::Other::containInSet(currentComponentVariableSet, var));

            currentComponentVariableSet.emplace(var);
        }

        printCurrentFormula(formulaRepresentationAbstractPtr, actualResult);

        // RenH-C recognition
        renHCRecognitionAbstractPtr->setUnassignedLiteralVector(literalVector);

        printRenHCRecognition(renHCRecognitionAbstractPtr, actualResult);
    }

    inline void partialAssignmentIsRenHC(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                         RenHCRecognitionAbstractPtrType renHCRecognitionAbstractPtr,
                                         const LiteralVectorType& partialAssignment, VariableSetType& currentComponentVariableSet,
                                         IgnorePureLiteralTypeEnum ignorePureLiteralType, std::stringstream& actualResult) {
        // Is renH-C
        isRenHC(formulaRepresentationAbstractPtr, renHCRecognitionAbstractPtr, currentComponentVariableSet, ignorePureLiteralType, actualResult);

        for (const LiteralType& lit : partialAssignment) {
            // Assign the literal
            assignLiteral(formulaRepresentationAbstractPtr, renHCRecognitionAbstractPtr, lit, currentComponentVariableSet, actualResult);

            // Is renH-C
            isRenHC(formulaRepresentationAbstractPtr, renHCRecognitionAbstractPtr, currentComponentVariableSet, ignorePureLiteralType, actualResult);
        }

        // Unassign all the literals
        unassignLiteralVector(formulaRepresentationAbstractPtr, renHCRecognitionAbstractPtr, partialAssignment, currentComponentVariableSet, actualResult);
    }
}   // namespace HydraTest::RenHCRecognition
