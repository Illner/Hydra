#pragma once

#include <cassert>
#include <memory>
#include <sstream>
#include <string>

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"

namespace HydraTest::Formula::Representation::Recognition {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;
    using ClauseIdT = char8_t;

    using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
    using VariableSetType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
    using ClauseIdSetType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdSetType;
    using VariableVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
    using ConnectedComponentType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ConnectedComponentType;
    using ConnectedComponentStruct = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ConnectedComponentStruct;
    using PureVariableRemovedClausesVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::PureVariableRemovedClausesVectorType;

    using FormulaRepresentationAbstractPtrType = Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;
    using FormulaRepresentationAbstractConstPtrType = const Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;
    using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

    using IgnorePureLiteralTypeEnum = Hydra::IgnorePureLiteralTypeEnum;
    //endregion

    inline void printFormula(FormulaRepresentationAbstractConstPtrType formulaRepresentationAbstractPtr, std::stringstream& actualResult) {
        formulaRepresentationAbstractPtr->printFormulaRepresentationDebug(actualResult);
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

    inline void printPureClauses(const ClauseIdSetType& clauseSet, std::stringstream& actualResult) {
        actualResult << "Pure clauses:";
        for (ClauseIdT clauseId : Hydra::Other::sortUnorderedSet(clauseSet))
            actualResult << " " << std::to_string(clauseId);
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

    inline void isKromC(FormulaRepresentationAbstractConstPtrType formulaRepresentationAbstractPtr, const VariableSetType& currentComponentVariableSet,
                        std::stringstream& actualResult) {
        actualResult << "Krom-C: ";

        bool isKromC = formulaRepresentationAbstractPtr->isCurrentComponentFormulaKromC(currentComponentVariableSet);

        actualResult << std::to_string(isKromC) << std::endl;
    }

    inline void isHornC(FormulaRepresentationAbstractConstPtrType formulaRepresentationAbstractPtr, const VariableSetType& currentComponentVariableSet,
                        std::stringstream& actualResult) {
        actualResult << "Horn-C: ";

        bool isHornC = formulaRepresentationAbstractPtr->isCurrentComponentFormulaHornC(currentComponentVariableSet);

        actualResult << std::to_string(isHornC) << std::endl;
    }

    inline void isAntiHornC(FormulaRepresentationAbstractConstPtrType formulaRepresentationAbstractPtr, const VariableSetType& currentComponentVariableSet,
                            std::stringstream& actualResult) {
        actualResult << "anti-Horn-C: ";

        bool isAntiHornC = formulaRepresentationAbstractPtr->isCurrentComponentFormulaAntiHornC(currentComponentVariableSet);

        actualResult << std::to_string(isAntiHornC) << std::endl;
    }

    inline void assignLiteral(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, VariableSetType& currentComponentVariableSet,
                              const LiteralType& lit, std::stringstream& actualResult) {
        assert(Hydra::Other::containInSet(currentComponentVariableSet, lit.getVariable()));   // in the current component

        actualResult << "--------------------------------------------------------------------------------" << std::endl;
        actualResult << "Assign literal: " << lit << std::endl;
        actualResult << "--------------------------------------------------------------------------------" << std::endl;
        VariableVectorType freeVariableVector;
        currentComponentVariableSet.erase(lit.getVariable());
        formulaRepresentationAbstractPtr->addLiteralToPartialAssignment(lit, freeVariableVector);

        assert(freeVariableVector.empty());
    }

    inline void unassignLiteral(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, VariableSetType& currentComponentVariableSet,
                                const LiteralType& lit, std::stringstream& actualResult) {
        assert(!Hydra::Other::containInSet(currentComponentVariableSet, lit.getVariable()));   // NOT in the current component

        actualResult << "--------------------------------------------------------------------------------" << std::endl;
        actualResult << "Unassign literal: " << lit << std::endl;
        actualResult << "--------------------------------------------------------------------------------" << std::endl;
        VariableVectorType unfreeVariableVector;
        currentComponentVariableSet.emplace(lit.getVariable());
        formulaRepresentationAbstractPtr->removeLiteralFromPartialAssignment(lit, unfreeVariableVector);

        assert(unfreeVariableVector.empty());
    }

    inline void processRecognition(FormulaRepresentationAbstractConstPtrType formulaRepresentationAbstractPtr, const VariableSetType& currentComponentVariableSet,
                                   std::stringstream& actualResult, bool ignoreKromCRecognition = false) {
        // Print formula
        printFormula(formulaRepresentationAbstractPtr, actualResult);
        actualResult << "------------------------------" << std::endl;

        // Krom-C
        if (!ignoreKromCRecognition)
            isKromC(formulaRepresentationAbstractPtr, currentComponentVariableSet, actualResult);

        // Horn-C
        isHornC(formulaRepresentationAbstractPtr, currentComponentVariableSet, actualResult);

        // anti-Horn-C
        isAntiHornC(formulaRepresentationAbstractPtr, currentComponentVariableSet, actualResult);

        actualResult << "------------------------------" << std::endl;
        actualResult << std::endl;
    }

    inline void processRecognitionAssignment(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, VariableSetType& currentComponentVariableSet,
                                             const LiteralType& lit, std::stringstream& actualResult, bool ignoreKromCRecognition = false) {
        // Recognition
        processRecognition(formulaRepresentationAbstractPtr, currentComponentVariableSet, actualResult, ignoreKromCRecognition);

        // Assign the literal
        assignLiteral(formulaRepresentationAbstractPtr, currentComponentVariableSet, lit, actualResult);

        // Recognition
        processRecognition(formulaRepresentationAbstractPtr, currentComponentVariableSet, actualResult, ignoreKromCRecognition);

        // Unassign the literal
        unassignLiteral(formulaRepresentationAbstractPtr, currentComponentVariableSet, lit, actualResult);

        // Recognition
        processRecognition(formulaRepresentationAbstractPtr, currentComponentVariableSet, actualResult, ignoreKromCRecognition);
    }

    inline void processRecognitionConnectedComponents(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                                      const VariableSetType& currentComponentVariableSet, IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                                      std::stringstream& actualResult) {
        // Print
        Hydra::Other::printTitle(actualResult, "Initial", 30, '-');
        printFormula(formulaRepresentationAbstractPtr, actualResult);

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

        if (!pureClauseSet.empty()) {
            // Remove pure clauses
            formulaRepresentationAbstractPtr->removeClausesContainingOnlyPureLiteralsOfIgnoredType(pureClauseSet, ignorePureLiteralType);

            // Print
            Hydra::Other::printTitle(actualResult, "Remove pure clauses", 30, '-');
            printFormula(formulaRepresentationAbstractPtr, actualResult);
        }

        // Connected components
        for (const ConnectedComponentStruct& newConnectedComponent : connectedComponents) {
            // Set new component
            printSetNewConnectedComponent(newConnectedComponent, actualResult);
            PureVariableRemovedClausesVectorType pureVariableRemovedClausesVector = formulaRepresentationAbstractPtr->setNewComponent(newConnectedComponent,
                                                                                                                                      ignorePureLiteralType);

            // Recognition
            processRecognition(formulaRepresentationAbstractPtr, currentComponentVariableSet, actualResult);

            // Pop previous component
            printPopPreviousConnectedComponent(newConnectedComponent, actualResult);
            formulaRepresentationAbstractPtr->popPreviousComponent(newConnectedComponent, pureVariableRemovedClausesVector);
            printFormula(formulaRepresentationAbstractPtr, actualResult);

            actualResult << "--------------------------------------------------------------------------------" << std::endl;
            actualResult << std::endl;
        }

        if (!pureClauseSet.empty()) {
            // Add pure clauses
            formulaRepresentationAbstractPtr->addClausesContainingOnlyPureLiteralsOfIgnoredType(pureClauseSet, ignorePureLiteralType);

            // Print
            Hydra::Other::printTitle(actualResult, "Add pure clauses", 30, '-');
            printFormula(formulaRepresentationAbstractPtr, actualResult);
        }
    }
}   // namespace HydraTest::Formula::Representation::Recognition
