#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/formula/representation/contagious/ContagiousFormulaRepresentationTestResult.hpp"

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/computeConnectedComponents/ConnectedComponentStructure.hpp"

#include "Hydra/cache/cachingScheme/enums/OmitClauseTypeEnum.hpp"
#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"

namespace HydraTest::Formula::Representation::Contagious {

    using FormulaSizeType = Hydra::Formula::Representation::FormulaSizeType;

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;
    using ClauseIdT = char8_t;

    using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
    using VectorSetType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VectorSetType;
    using ClauseSizeType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeType;
    using ClauseIdSetType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdSetType;
    using VariableSetType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
    using ClauseStringType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseStringType;
    using LiteralVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
    using VariableVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
    using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
    using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
    using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
    using ClauseSizeCounterType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeCounterType;
    using ConnectedComponentType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ConnectedComponentType;
    using ClauseOffsetVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseOffsetVectorType;
    using ConnectedComponentStruct = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ConnectedComponentStruct;
    using VariableSortedVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableSortedVectorType;
    using ClauseIdReusableVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdReusableVectorType;
    using VariableReusableVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableReusableVectorType;
    using PureVariableRemovedClausesVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::PureVariableRemovedClausesVectorType;

    using ConnectedComponentStructure = Hydra::Container::ComputeConnectedComponents::ConnectedComponentStruct<VarT, LiteralT>;

    using IgnorePureLiteralTypeEnum = Hydra::IgnorePureLiteralTypeEnum;
    using OmitClauseTypeEnum = Hydra::Cache::CachingScheme::OmitClauseTypeEnum;
    //endregion

    //region Functions
    void printContagiousFormulaRepresentation(const ContagiousFormulaRepresentationType& contagiousFormulaRepresentation, std::stringstream& actualResult,
                                              bool printSeparator = true) {
        if (printSeparator) {
            actualResult << "--------------------" << std::endl;
            actualResult << "--------------------" << std::endl;
        }

        contagiousFormulaRepresentation.printFormulaRepresentationDebug(actualResult);
        actualResult << std::endl;
    }

    void printFormula(const FormulaType& formula, std::stringstream& actualResult) {
        actualResult << "Formula: ";
        for (const LiteralType& lit : formula)
            actualResult << lit << " ";
        actualResult << std::endl;
    }

    void printCurrentFormula(const ContagiousFormulaRepresentationType& contagiousFormulaRepresentation, std::stringstream& actualResult) {
        actualResult << "Formula: ";
        contagiousFormulaRepresentation.printCurrentFormulaDebug(actualResult);
        actualResult << std::endl
                     << std::endl;
    }

    void printClauseIdSortedReusableVector(const ClauseIdReusableVectorType& clauseIdSortedReusableVector, std::stringstream& actualResult) {
        actualResult << "Sorted clause IDs:";
        for (ClauseIdT clauseId : clauseIdSortedReusableVector)
            actualResult << " " << std::to_string(clauseId);
        actualResult << std::endl
                     << std::endl;
    }

    void printLiteralNumberOfOccurrences(const ClauseIdVectorType& clauseIdVector, std::stringstream& actualResult) {
        actualResult << "Literal - number of occurrences: ";
        for (LiteralT literalT = 2; literalT < clauseIdVector.size(); ++literalT) {
            LiteralType lit = Hydra::Formula::createLiteralFromLiteralT<VarT, LiteralT>(literalT);
            actualResult << lit << ": " << std::to_string(clauseIdVector[literalT]) << ", ";
        }
        actualResult << std::endl;
    }

    void printFormulaAndLiteralNumberOfOccurrences(const FormulaType& formula, const ClauseIdVectorType& clauseIdVector, std::stringstream& actualResult) {
        printFormula(formula, actualResult);
        printLiteralNumberOfOccurrences(clauseIdVector, actualResult);
    }

    void printClauseProperties(const ContagiousFormulaRepresentationType& contagiousFormulaRepresentation, std::stringstream& actualResult,
                               bool printFormula = true) {
        if (printFormula)
            printCurrentFormula(contagiousFormulaRepresentation, actualResult);

        for (ClauseIdT clauseId = 0; clauseId < contagiousFormulaRepresentation.getNumberOfOriginalClauses(); ++clauseId) {
            actualResult << "Clause ID: " << std::to_string(clauseId) << std::endl;

            actualResult << "\tclause status: " << Hydra::Formula::clauseStatusEnumToString(contagiousFormulaRepresentation.getCurrentClauseStatus(clauseId)) << std::endl;
            actualResult << "\tis clause untouched: " << std::to_string(contagiousFormulaRepresentation.isClauseUntouched(clauseId)) << std::endl;
            actualResult << "\tis clause untouched and binary: " << std::to_string(contagiousFormulaRepresentation.isClauseUntouchedAndBinary(clauseId)) << std::endl;

            // The clause is not satisfied
            if (!contagiousFormulaRepresentation.isClauseSatisfied(clauseId)) {
                actualResult << "\tclause size: " << std::to_string(contagiousFormulaRepresentation.getCurrentClauseSize(clauseId)) << std::endl;

                actualResult << "\tcurrent clause: ";
                contagiousFormulaRepresentation.printCurrentClauseDebug(actualResult, clauseId);
                actualResult << std::endl;

                actualResult << "\tvariables in clause: ";
                VariableSortedVectorType variableSortedVector = Hydra::Other::sortUnorderedSet(contagiousFormulaRepresentation.getUnassignedVariablesInClause(clauseId));
                for (VarT var : variableSortedVector)
                    actualResult << std::to_string(var) << " ";
                actualResult << std::endl;
            }
        }

        actualResult << std::endl;
    }

    void printVariableProperties(const ContagiousFormulaRepresentationType& contagiousFormulaRepresentation, const VariableSetType& currentComponentVariableSet,
                                 std::stringstream& actualResult, bool printFormula = true) {
        if (printFormula)
            printCurrentFormula(contagiousFormulaRepresentation, actualResult);

        ClauseIdReusableVectorType clauseIdReusableVector(contagiousFormulaRepresentation.getNumberOfOriginalClauses());

        for (VarT var = 1; var <= contagiousFormulaRepresentation.getNumberOfVariablesInOriginalFormula(); ++var) {
            actualResult << "Variable: " << std::to_string(var) << std::endl;

            actualResult << "\tis assigned: " << std::to_string(contagiousFormulaRepresentation.isVariableAssigned(var)) << std::endl;

            // The variable is not assigned
            if (!contagiousFormulaRepresentation.isVariableAssigned(var)) {
                actualResult << "\tis variable free: " << std::to_string(contagiousFormulaRepresentation.isVariableFree(var)) << std::endl;

                actualResult << "\tclauses: ";
                contagiousFormulaRepresentation.getCurrentClauses(currentComponentVariableSet, var, clauseIdReusableVector, VectorSetType());
                clauseIdReusableVector.sort();
                for (ClauseIdT clauseId : clauseIdReusableVector)
                    actualResult << std::to_string(clauseId) << " ";
                actualResult << std::endl;

                actualResult << "\tclause size counter: ";
                ClauseSizeCounterType clauseSizeCounter = contagiousFormulaRepresentation.getCurrentClauseSizeCounter(Hydra::Formula::getPositiveLiteralT<VarT, LiteralT>(var));

                for (auto [clauseSize, numberOfClauses] : contagiousFormulaRepresentation.getCurrentClauseSizeCounter(Hydra::Formula::getNegativeLiteralT<VarT, LiteralT>(var))) {
                    if (auto itTmp = clauseSizeCounter.find(clauseSize); itTmp != clauseSizeCounter.end())
                        clauseSizeCounter[clauseSize] += numberOfClauses;
                    else
                        clauseSizeCounter[clauseSize] = numberOfClauses;
                }

                std::vector<ClauseSizeType> keySortedVector = Hydra::Other::extractKeysFromMap(clauseSizeCounter, true);
                for (ClauseSizeType clauseSize : keySortedVector)
                    actualResult << std::to_string(clauseSize) << " (" << std::to_string(clauseSizeCounter[clauseSize]) << ") ";
                actualResult << std::endl;

                actualResult << "\tnumber of binary clauses: ";
                ClauseIdT numberOfBinaryClauses = contagiousFormulaRepresentation.getNumberOfCurrentBinaryClauses(Hydra::Formula::getPositiveLiteralT<VarT, LiteralT>(var)) +
                                                  contagiousFormulaRepresentation.getNumberOfCurrentBinaryClauses(Hydra::Formula::getNegativeLiteralT<VarT, LiteralT>(var));
                actualResult << std::to_string(numberOfBinaryClauses) << std::endl;
            }
        }

        actualResult << std::endl;
    }

    void printLiteralProperties(const ContagiousFormulaRepresentationType& contagiousFormulaRepresentation, std::stringstream& actualResult,
                                bool printFormula = true) {
        if (printFormula)
            printCurrentFormula(contagiousFormulaRepresentation, actualResult);

        for (VarT var = 1; var <= contagiousFormulaRepresentation.getNumberOfVariablesInOriginalFormula(); ++var) {
            actualResult << "Variable: " << std::to_string(var) << std::endl;

            // The variable is not assigned
            if (!contagiousFormulaRepresentation.isVariableAssigned(var)) {
                for (bool sign : { true, false }) {
                    LiteralType lit(var, sign);
                    actualResult << "\tLiteral: " << lit << std::endl;

                    actualResult << "\t\tnumber of current clauses: " << std::to_string(contagiousFormulaRepresentation.getNumberOfCurrentClauses(lit.getLiteralT())) << std::endl;

                    actualResult << "\t\tclause size counter: ";
                    ClauseSizeCounterType clauseSizeCounter = contagiousFormulaRepresentation.getCurrentClauseSizeCounter(lit.getLiteralT());
                    std::vector<ClauseSizeType> keySortedVector = Hydra::Other::extractKeysFromMap(clauseSizeCounter, true);
                    for (ClauseSizeType clauseSize : keySortedVector)
                        actualResult << std::to_string(clauseSize) << " (" << std::to_string(clauseSizeCounter[clauseSize]) << ") ";
                    actualResult << std::endl;

                    actualResult << "\tnumber of binary clauses: ";
                    ClauseIdT numberOfBinaryClauses = contagiousFormulaRepresentation.getNumberOfCurrentBinaryClauses(lit.getLiteralT());
                    actualResult << std::to_string(numberOfBinaryClauses) << std::endl;

                    actualResult << "\tin unit clause: ";
                    bool inUnitClause = contagiousFormulaRepresentation.isLiteralInUnitClause(lit);
                    actualResult << std::to_string(inUnitClause) << std::endl;
                }
            }
        }

        actualResult << std::endl;
    }

    void printConnectedComponents(const ConnectedComponentType& connectedComponents, std::stringstream& actualResult, bool printPureVariables = false) {
        actualResult << "Connected components: " << std::endl;

        for (const ConnectedComponentStruct& connectedComponentStruct : connectedComponents) {
            for (VarT var : Hydra::Other::sortUnorderedSet(connectedComponentStruct.variableSet))
                actualResult << std::to_string(var) << " ";

            if (printPureVariables) {
                // Pure literals
                actualResult << "|";
                for (const LiteralType& lit : connectedComponentStruct.pureLiteralVector)
                    actualResult << " " << lit;
            }

            actualResult << std::endl;
        }

        actualResult << std::endl;
    }

    void printClauseString(const ContagiousFormulaRepresentationType& contagiousFormulaRepresentation, ClauseIdT clauseId, std::stringstream& actualResult,
                           bool printCurrentClause = true) {
        if (printCurrentClause) {
            actualResult << "Clause: ";
            contagiousFormulaRepresentation.printCurrentClauseDebug(actualResult, clauseId);
            actualResult << std::endl;
        }

        // Clause string
        actualResult << "Clause string:";
        ClauseStringType clauseString = contagiousFormulaRepresentation.getClauseString(clauseId, false);
        for (LiteralT l : clauseString)
            actualResult << " " << std::to_string(l);
        actualResult << std::endl;

        // Clause string (variable)
        actualResult << "Clause string (variable):";
        clauseString = contagiousFormulaRepresentation.getClauseString(clauseId, true);
        for (LiteralT v : clauseString)
            actualResult << " " << std::to_string(v);
        actualResult << std::endl
                     << std::endl;
    }

    void printClauseIdReusableVector(const ClauseIdReusableVectorType& clauseIdReusableVector, std::stringstream& actualResult) {
        actualResult << "Clause IDs:";
        for (ClauseIdT clauseId : clauseIdReusableVector)
            actualResult << " " << std::to_string(clauseId);
        actualResult << std::endl;
    }

    void printClauses(const ContagiousFormulaRepresentationType& contagiousFormulaRepresentation, std::stringstream& actualResult) {
        for (ClauseIdT clauseId = 0; clauseId < contagiousFormulaRepresentation.getNumberOfOriginalClauses(); ++clauseId) {
            // The clause is satisfied
            if (contagiousFormulaRepresentation.isClauseSatisfied(clauseId))
                continue;

            actualResult << std::to_string(clauseId) << ": ";
            contagiousFormulaRepresentation.printCurrentClauseDebug(actualResult, clauseId);
            actualResult << std::endl;
        }
        actualResult << std::endl;
    }

    void printPureClauses(const ClauseIdSetType& pureClauseSet, std::stringstream& actualResult) {
        actualResult << "Pure clauses:";
        for (ClauseIdT clauseId : Hydra::Other::sortUnorderedSet(pureClauseSet))
            actualResult << " " << std::to_string(clauseId);
        actualResult << std::endl;
    }

    void processPureClauses(ContagiousFormulaRepresentationType& contagiousFormulaRepresentation, const ClauseIdSetType& pureClauseSet,
                            IgnorePureLiteralTypeEnum ignorePureLiteralType, std::stringstream& actualResult) {
        printContagiousFormulaRepresentation(contagiousFormulaRepresentation, actualResult, false);

        for (ClauseIdT clauseId : Hydra::Other::sortUnorderedSet(pureClauseSet)) {
            actualResult << "Pure clause: " << std::to_string(clauseId) << std::endl;

            // Remove the clause
            Hydra::Other::printTitle(actualResult, "remove", 30, '-');
            contagiousFormulaRepresentation.removeClausesContainingOnlyPureLiteralsOfIgnoredType({ clauseId }, ignorePureLiteralType);
            printContagiousFormulaRepresentation(contagiousFormulaRepresentation, actualResult, false);

            // Add the clause
            Hydra::Other::printTitle(actualResult, "add", 30, '-');
            contagiousFormulaRepresentation.addClausesContainingOnlyPureLiteralsOfIgnoredType({ clauseId }, ignorePureLiteralType);
            printContagiousFormulaRepresentation(contagiousFormulaRepresentation, actualResult, false);
        }

        actualResult << "Pure clauses:";
        for (ClauseIdT clauseId : Hydra::Other::sortUnorderedSet(pureClauseSet))
            actualResult << " " << std::to_string(clauseId);
        actualResult << std::endl;

        Hydra::Other::printTitle(actualResult, "remove", 30, '-');
        contagiousFormulaRepresentation.removeClausesContainingOnlyPureLiteralsOfIgnoredType(pureClauseSet, ignorePureLiteralType);
        printContagiousFormulaRepresentation(contagiousFormulaRepresentation, actualResult, false);

        // Add the clause
        Hydra::Other::printTitle(actualResult, "add", 30, '-');
        contagiousFormulaRepresentation.addClausesContainingOnlyPureLiteralsOfIgnoredType(pureClauseSet, ignorePureLiteralType);
        printContagiousFormulaRepresentation(contagiousFormulaRepresentation, actualResult, false);
    }

    void processSaveCurrentComponentFormulaToVector(const ContagiousFormulaRepresentationType& contagiousFormulaRepresentation,
                                                    const VariableSetType& currentComponentVariableSet, std::stringstream& actualResult) {
        LiteralVectorType formula;
        ClauseOffsetVectorType clauseOffsetVector;
        contagiousFormulaRepresentation.saveCurrentComponentFormulaToVector(currentComponentVariableSet, formula, clauseOffsetVector, true);

        // Formula
        actualResult << "Formula:";
        for (const LiteralType& lit : formula)
            actualResult << " " << lit;
        actualResult << std::endl;

        // Clause offsets
        actualResult << "Clause offsets:";
        for (FormulaSizeType clauseOffset : clauseOffsetVector)
            actualResult << " " << std::to_string(clauseOffset);
        actualResult << std::endl;
    }

    void processSaveFormulaDefinedByClausesToVector(const ContagiousFormulaRepresentationType& contagiousFormulaRepresentation,
                                                    const ClauseIdReusableVectorType& clauseIdReusableVector, std::stringstream& actualResult) {
        // Print the clauses
        actualResult << "Clauses:";
        for (ClauseIdT clauseId : clauseIdReusableVector)
            actualResult << " " << std::to_string(clauseId);
        actualResult << std::endl;

        LiteralVectorType formula;
        ClauseOffsetVectorType clauseOffsetVector;
        contagiousFormulaRepresentation.saveFormulaDefinedByClausesToVector(clauseIdReusableVector, formula, clauseOffsetVector, true);

        // Formula
        actualResult << "Formula:";
        for (const LiteralType& lit : formula)
            actualResult << " " << lit;
        actualResult << std::endl;

        // Clause offsets
        actualResult << "Clause offsets:";
        for (FormulaSizeType clauseOffset : clauseOffsetVector)
            actualResult << " " << std::to_string(clauseOffset);
        actualResult << std::endl;
    }

    void processSaveCurrentComponentFormulaToVectorConnectedComponents(ContagiousFormulaRepresentationType& contagiousFormulaRepresentation,
                                                                       const VariableSetType& currentComponentVariableSet,
                                                                       IgnorePureLiteralTypeEnum ignorePureLiteralType, std::stringstream& actualResult) {
        processSaveCurrentComponentFormulaToVector(contagiousFormulaRepresentation, currentComponentVariableSet, actualResult);
        actualResult << std::endl;

        // Compute connected components
        ConnectedComponentType connectedComponents;
        if (ignorePureLiteralType == IgnorePureLiteralTypeEnum::NONE)
            connectedComponents = contagiousFormulaRepresentation.computeConnectedComponents(currentComponentVariableSet);
        else {
            ClauseIdSetType pureClauseSet;
            connectedComponents = contagiousFormulaRepresentation.computeConnectedComponents(currentComponentVariableSet, pureClauseSet, ignorePureLiteralType);

            contagiousFormulaRepresentation.removeClausesContainingOnlyPureLiteralsOfIgnoredType(pureClauseSet, ignorePureLiteralType);

            printPureClauses(pureClauseSet, actualResult);
            actualResult << std::endl;
        }

        printConnectedComponents(connectedComponents, actualResult, (ignorePureLiteralType != IgnorePureLiteralTypeEnum::NONE));

        for (const ConnectedComponentStruct& connectedComponentStruct : connectedComponents) {
            actualResult << "Set new component: ";
            for (VarT var : Hydra::Other::sortUnorderedSet(connectedComponentStruct.variableSet))
                actualResult << std::to_string(var) << " ";
            actualResult << std::endl;

            PureVariableRemovedClausesVectorType pureVariableRemovedClausesVector = contagiousFormulaRepresentation.setNewComponent(connectedComponentStruct, ignorePureLiteralType);

            processSaveCurrentComponentFormulaToVector(contagiousFormulaRepresentation, connectedComponentStruct.variableSet, actualResult);

            contagiousFormulaRepresentation.popPreviousComponent(connectedComponentStruct, pureVariableRemovedClausesVector);
            actualResult << std::endl;
        }
    }
    //endregion

    //region ContagiousFormulaRepresentation
    ContagiousFormulaRepresentationType createContagiousFormulaRepresentationWithOneClause(VariableSetType& variableSet) {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litPos1, litNeg2, litPos3, zeroLit   // 0
        };

        VarT numberOfVariables = 3;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContagiousFormulaRepresentationType contagiousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3 };

        return contagiousFormulaRepresentation;
    }

    ContagiousFormulaRepresentationType createContagiousFormulaRepresentation(VariableSetType& variableSet) {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litPos7(7, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litNeg3, litNeg2, litPos1, zeroLit,   // 0
            litPos1, litNeg2, zeroLit,            // 1
            litNeg1, zeroLit,                     // 2
            litPos2, litNeg1, zeroLit,            // 3
            litPos4, litNeg1, zeroLit,            // 4
            litNeg5, litNeg1, zeroLit,            // 5
            litPos6, litNeg7, zeroLit,            // 6
            litPos8, litPos7, zeroLit             // 7
        };

        VarT numberOfVariables = 8;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContagiousFormulaRepresentationType contagiousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8 };

        return contagiousFormulaRepresentation;
    }

    ContagiousFormulaRepresentationType createContagiousFormulaRepresentationForConnectedComponents(VariableSetType& variableSet) {
        //region Literals
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg5(5, false);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType litNeg9(9, false);
        LiteralType litPos10(10, true);
        LiteralType litNeg10(10, false);
        LiteralType litPos11(11, true);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litPos2, litPos3, zeroLit,             // 0
            litNeg1, litNeg3, litPos4, zeroLit,    // 1
            litPos4, litNeg5, zeroLit,             // 2
            litNeg6, zeroLit,                      // 3
            litNeg1, litPos7, litPos8, zeroLit,    // 4
            litNeg8, litNeg9, litNeg10, zeroLit,   // 5
            litPos10, litPos11, zeroLit            // 6
        };

        VarT numberOfVariables = 11;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContagiousFormulaRepresentationType contagiousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

        return contagiousFormulaRepresentation;
    }

    ContagiousFormulaRepresentationType createContagiousFormulaRepresentationForPureLiterals(VariableSetType& variableSet) {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litPos2(2, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType litPos9(9, true);
        LiteralType litNeg9(9, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litPos1, litPos2, litPos8, zeroLit,   // 0
            litPos1, litNeg3, litPos9, zeroLit,   // 1
            litPos2, litPos4, litNeg8, zeroLit,   // 2
            litNeg3, litPos4, litNeg9, zeroLit,   // 3
            litNeg3, litNeg5, zeroLit,            // 4
            litPos6, zeroLit,                     // 5
            litNeg7, zeroLit                      // 6
        };

        VarT numberOfVariables = 9;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContagiousFormulaRepresentationType contagiousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        return contagiousFormulaRepresentation;
    }

    ContagiousFormulaRepresentationType createContagiousFormulaRepresentationForDuplicateClauses(VariableSetType& variableSet) {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litPos1, zeroLit,                     // 0
            litNeg1, zeroLit,                     // 1
            litPos2, zeroLit,                     // 2
            litPos2, zeroLit,                     // 3
            litNeg2, zeroLit,                     // 4
            litNeg2, zeroLit,                     // 5
            litPos1, litPos2, zeroLit,            // 6
            litNeg1, litPos2, litPos3, zeroLit,   // 7
            litNeg3, litPos4, zeroLit,            // 8
            litPos1, litNeg2, litPos3, zeroLit,   // 9
            litNeg1, litNeg2, zeroLit,            // 10
            litPos1, litPos2, litNeg3, zeroLit,   // 11
            litPos3, litNeg4, zeroLit,            // 12
            litPos1, litNeg2, litPos3, zeroLit,   // 13
            litPos1, litPos2, zeroLit,            // 14

            litPos1, litPos5, zeroLit,            // 15
            litNeg1, litPos5, zeroLit,            // 16
            litPos1, litPos2, litPos5, zeroLit,   // 17
            litNeg1, litNeg2, litPos5, zeroLit,   // 18
            litNeg3, litPos4, litPos5, zeroLit,   // 19
            litPos3, litNeg4, litPos5, zeroLit    // 20
        };

        VarT numberOfVariables = 5;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContagiousFormulaRepresentationType contagiousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3, 4, 5 };

        return contagiousFormulaRepresentation;
    }

    ContagiousFormulaRepresentationType createContagiousFormulaRepresentationForPureClauses(VariableSetType& variableSet) {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litPos6(6, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType litNeg9(9, false);
        LiteralType litNeg10(10, false);
        LiteralType litPos11(11, true);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litNeg7, zeroLit,                    // 0
            litPos11, zeroLit,                   // 1
            litPos1, litPos2, zeroLit,           // 2
            litPos3, litNeg4, zeroLit,           // 3
            litPos3, litPos8, zeroLit,           // 4
            litPos3, litNeg9, zeroLit,           // 5
            litNeg4, litPos5, zeroLit,           // 6
            litPos5, litPos6, zeroLit,           // 7
            litNeg8, litNeg9, zeroLit,           // 8
            litNeg9, litNeg10, zeroLit,          // 9
            litNeg1, litNeg2, litPos3, zeroLit   // 10
        };

        VarT numberOfVariables = 11;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContagiousFormulaRepresentationType contagiousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

        return contagiousFormulaRepresentation;
    }

    ContagiousFormulaRepresentationType createContagiousFormulaRepresentationForConnectedComponentPositivePureVariables(VariableSetType& variableSet) {
        //region Literals
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litPos8(8, true);
        LiteralType litNeg9(9, false);
        LiteralType litPos10(10, true);
        LiteralType litNeg10(10, false);
        LiteralType litPos11(11, true);
        LiteralType litNeg12(12, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litPos11, zeroLit,            // 0
            litNeg12, zeroLit,            // 1
            litNeg1, litNeg2, zeroLit,    // 2
            litNeg1, litNeg10, zeroLit,   // 3
            litNeg1, litPos10, zeroLit,   // 4
            litPos2, litPos3, zeroLit,    // 5
            litPos3, litNeg4, zeroLit,    // 6
            litPos3, litNeg6, zeroLit,    // 7
            litPos3, litPos7, zeroLit,    // 8
            litPos4, litPos5, zeroLit,    // 9
            litNeg5, litPos8, zeroLit,    // 10
            litNeg5, litNeg9, zeroLit     // 11
        };

        VarT numberOfVariables = 12;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContagiousFormulaRepresentationType contagiousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

        return contagiousFormulaRepresentation;
    }

    ContagiousFormulaRepresentationType createContagiousFormulaRepresentationForConnectedComponentNegativePureVariables(VariableSetType& variableSet) {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg7(7, false);
        LiteralType litNeg8(8, false);
        LiteralType litPos9(9, true);
        LiteralType litPos10(10, true);
        LiteralType litNeg10(10, false);
        LiteralType litNeg11(11, false);
        LiteralType litPos12(12, true);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litNeg11, zeroLit,            // 0
            litPos12, zeroLit,            // 1
            litPos1, litPos2, zeroLit,    // 2
            litPos1, litNeg10, zeroLit,   // 3
            litPos1, litPos10, zeroLit,   // 4
            litNeg2, litNeg3, zeroLit,    // 5
            litNeg3, litPos4, zeroLit,    // 6
            litNeg3, litPos6, zeroLit,    // 7
            litNeg3, litNeg7, zeroLit,    // 8
            litNeg4, litNeg5, zeroLit,    // 9
            litPos5, litNeg8, zeroLit,    // 10
            litPos5, litPos9, zeroLit     // 11
        };

        VarT numberOfVariables = 12;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContagiousFormulaRepresentationType contagiousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

        return contagiousFormulaRepresentation;
    }

    ContagiousFormulaRepresentationType createContagiousFormulaRepresentationForSortVariablesBasedOnClauseReductionHeuristic(VariableSetType& variableSet) {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litNeg1, litNeg2, zeroLit,            // 0
            litPos1, litNeg2, zeroLit,            // 1
            litNeg3, litPos4, zeroLit,            // 2
            litPos3, litPos4, zeroLit,            // 3
            litPos1, litNeg3, litPos4, zeroLit,   // 4
            litNeg2, litPos3, litPos4, zeroLit    // 5
        };

        VarT numberOfVariables = 4;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContagiousFormulaRepresentationType contagiousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3, 4 };

        return contagiousFormulaRepresentation;
    }
    //endregion

    /**
     * Constructor
     */
    TEST_CASE("[Formula::Representation::Contagious] constructor", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);
            LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

            // Copy constructor
            actualResult << "Copy constructor" << std::endl;
            FormulaType formula1 { litPos1, zeroLit };
            ClauseIdVectorType literalNumberOfOccurrences1 { 0, 0, 1, 0, 0, 0 };
            printFormulaAndLiteralNumberOfOccurrences(formula1, literalNumberOfOccurrences1, actualResult);
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation1(formula1, 2, 1, literalNumberOfOccurrences1);
            printContagiousFormulaRepresentation(contagiousFormulaRepresentation1, actualResult);
            actualResult << std::endl;

            // Move constructor
            actualResult << "Move constructor" << std::endl;
            FormulaType formula2 { litNeg1, litNeg2, zeroLit, litPos1, litPos2, litPos3, zeroLit, litNeg2, litPos3, zeroLit };
            ClauseIdVectorType literalNumberOfOccurrences2 { 0, 0, 1, 1, 1, 2, 2, 0 };
            printFormulaAndLiteralNumberOfOccurrences(formula2, literalNumberOfOccurrences2, actualResult);
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation2(std::move(formula2), 3, 3, literalNumberOfOccurrences2);
            printContagiousFormulaRepresentation(contagiousFormulaRepresentation2, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move
     */
    TEST_CASE("[Formula::Representation::Contagious] move", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationMoveResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);
            LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

            ContagiousFormulaRepresentationType contagiousFormulaRepresentation1({ litNeg1, litNeg2, zeroLit, litPos1, litPos2, litPos3, zeroLit, litNeg2, litPos3, zeroLit },
                                                                                 3, 3,
                                                                                 { 0, 0, 1, 1, 1, 2, 2, 0 });
            printContagiousFormulaRepresentation(contagiousFormulaRepresentation1, actualResult);

            actualResult << "Move method" << std::endl;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation2 = std::move(contagiousFormulaRepresentation1);
            printContagiousFormulaRepresentation(contagiousFormulaRepresentation2, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Formula sorting - omit none
     */
    TEST_CASE("[Formula::Representation::Contagious] formula sorting - omit none", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationFormulaSortingOmitNoneResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentation(variableSet);

            printCurrentFormula(contagiousFormulaRepresentation, actualResult);
            ClauseIdReusableVectorType clauseIdReusableVector(contagiousFormulaRepresentation.getNumberOfOriginalClauses());
            contagiousFormulaRepresentation.getSortedCurrentComponentClauses({}, clauseIdReusableVector, false, false, OmitClauseTypeEnum::NONE);
            printClauseIdSortedReusableVector(clauseIdReusableVector, actualResult);

            // Assign 2
            VariableVectorType freeVariableVector;
            contagiousFormulaRepresentation.addLiteralToPartialAssignment(LiteralType(2, true), freeVariableVector);

            printCurrentFormula(contagiousFormulaRepresentation, actualResult);
            contagiousFormulaRepresentation.getSortedCurrentComponentClauses({}, clauseIdReusableVector, false, false, OmitClauseTypeEnum::NONE);
            printClauseIdSortedReusableVector(clauseIdReusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Formula sorting - omit untouched clauses
     */
    TEST_CASE("[Formula::Representation::Contagious] formula sorting - omit untouched clauses", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationFormulaSortingOmitUnctouchedClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentation(variableSet);

            printCurrentFormula(contagiousFormulaRepresentation, actualResult);
            ClauseIdReusableVectorType clauseIdReusableVector(contagiousFormulaRepresentation.getNumberOfOriginalClauses());
            contagiousFormulaRepresentation.getSortedCurrentComponentClauses({}, clauseIdReusableVector, false, false, OmitClauseTypeEnum::UNTOUCHED);
            printClauseIdSortedReusableVector(clauseIdReusableVector, actualResult);

            // Assign 2
            VariableVectorType freeVariableVector;
            contagiousFormulaRepresentation.addLiteralToPartialAssignment(LiteralType(2, true), freeVariableVector);

            printCurrentFormula(contagiousFormulaRepresentation, actualResult);
            contagiousFormulaRepresentation.getSortedCurrentComponentClauses({}, clauseIdReusableVector, false, false, OmitClauseTypeEnum::UNTOUCHED);
            printClauseIdSortedReusableVector(clauseIdReusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Formula sorting - omit original binary clauses
     */
    TEST_CASE("[Formula::Representation::Contagious] formula sorting - omit original binary clauses", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationFormulaSortingOmitOriginalBinaryClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentation(variableSet);

            printCurrentFormula(contagiousFormulaRepresentation, actualResult);
            ClauseIdReusableVectorType clauseIdReusableVector(contagiousFormulaRepresentation.getNumberOfOriginalClauses());
            contagiousFormulaRepresentation.getSortedCurrentComponentClauses({}, clauseIdReusableVector, false, false, OmitClauseTypeEnum::ORIGINAL_BINARY);
            printClauseIdSortedReusableVector(clauseIdReusableVector, actualResult);

            // Assign 2
            VariableVectorType freeVariableVector;
            contagiousFormulaRepresentation.addLiteralToPartialAssignment(LiteralType(2, true), freeVariableVector);

            printCurrentFormula(contagiousFormulaRepresentation, actualResult);
            contagiousFormulaRepresentation.getSortedCurrentComponentClauses({}, clauseIdReusableVector, false, false, OmitClauseTypeEnum::ORIGINAL_BINARY);
            printClauseIdSortedReusableVector(clauseIdReusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clause string
     */
    TEST_CASE("[Formula::Representation::Contagious] clause string", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationClauseStringResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForDuplicateClauses(variableSet);

            for (ClauseIdT clauseId = 0; clauseId < contagiousFormulaRepresentation.getNumberOfOriginalClauses(); ++clauseId)
                printClauseString(contagiousFormulaRepresentation, clauseId, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clause string (assignment)
     */
    TEST_CASE("[Formula::Representation::Contagious] clause string (assignment)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationClauseStringAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForDuplicateClauses(variableSet);

            VariableVectorType tmp;
            contagiousFormulaRepresentation.addLiteralToPartialAssignment(LiteralType(5, false), tmp);

            for (ClauseIdT clauseId = 0; clauseId < contagiousFormulaRepresentation.getNumberOfOriginalClauses(); ++clauseId) {
                // The clause is satisfied
                if (contagiousFormulaRepresentation.isClauseSatisfied(clauseId))
                    continue;

                printClauseString(contagiousFormulaRepresentation, clauseId, actualResult);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clause comparator
     */
    TEST_CASE("[Formula::Representation::Contagious] clause comparator", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationClauseComparatorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentation(variableSet);
            printCurrentFormula(contagiousFormulaRepresentation, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(contagiousFormulaRepresentation.getNumberOfOriginalClauses());
            contagiousFormulaRepresentation.getCurrentComponentClauses(variableSet, clauseIdReusableVector);
            std::stable_sort(clauseIdReusableVector.begin(), clauseIdReusableVector.end(),
                             ContagiousFormulaRepresentationType::ClauseComparatorFunctor(&contagiousFormulaRepresentation));
            printClauseIdSortedReusableVector(clauseIdReusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clause comparator (assignment)
     */
    TEST_CASE("[Formula::Representation::Contagious] clause comparator (assignment)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationClauseComparatorAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentation(variableSet);

            VariableVectorType tmp;
            variableSet.erase((VarT)2);
            variableSet.erase((VarT)6);
            contagiousFormulaRepresentation.addLiteralVectorToPartialAssignment({ LiteralType(2, true), LiteralType(6, false) }, tmp);

            printCurrentFormula(contagiousFormulaRepresentation, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(contagiousFormulaRepresentation.getNumberOfOriginalClauses());
            contagiousFormulaRepresentation.getCurrentComponentClauses(variableSet, clauseIdReusableVector);
            std::stable_sort(clauseIdReusableVector.begin(), clauseIdReusableVector.end(),
                             ContagiousFormulaRepresentationType::ClauseComparatorFunctor(&contagiousFormulaRepresentation));
            printClauseIdSortedReusableVector(clauseIdReusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clause variable comparator
     */
    TEST_CASE("[Formula::Representation::Contagious] clause variable comparator", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationClauseVariableComparatorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentation(variableSet);
            printCurrentFormula(contagiousFormulaRepresentation, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(contagiousFormulaRepresentation.getNumberOfOriginalClauses());
            contagiousFormulaRepresentation.getCurrentComponentClauses(variableSet, clauseIdReusableVector);
            std::stable_sort(clauseIdReusableVector.begin(), clauseIdReusableVector.end(),
                             ContagiousFormulaRepresentationType::ClauseVariableComparatorFunctor(&contagiousFormulaRepresentation));
            printClauseIdSortedReusableVector(clauseIdReusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clause variable comparator (assignment)
     */
    TEST_CASE("[Formula::Representation::Contagious] clause variable comparator (assignment)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationClauseVariableComparatorAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentation(variableSet);

            VariableVectorType tmp;
            variableSet.erase((VarT)2);
            variableSet.erase((VarT)6);
            contagiousFormulaRepresentation.addLiteralVectorToPartialAssignment({ LiteralType(2, true), LiteralType(6, false) }, tmp);

            printCurrentFormula(contagiousFormulaRepresentation, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(contagiousFormulaRepresentation.getNumberOfOriginalClauses());
            contagiousFormulaRepresentation.getCurrentComponentClauses(variableSet, clauseIdReusableVector);
            std::stable_sort(clauseIdReusableVector.begin(), clauseIdReusableVector.end(),
                             ContagiousFormulaRepresentationType::ClauseVariableComparatorFunctor(&contagiousFormulaRepresentation));
            printClauseIdSortedReusableVector(clauseIdReusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clause sorting
     */
    TEST_CASE("[Formula::Representation::Contagious] clause sorting", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationClauseSortingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);
            LiteralType litNeg3(3, false);
            LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

            FormulaType formula { litPos1, zeroLit,
                                  litNeg2, zeroLit,
                                  litPos2, litPos1, zeroLit,
                                  litNeg3, litPos2, zeroLit,
                                  litPos2, litNeg3, zeroLit,
                                  litPos1, litPos2, zeroLit,
                                  litPos1, litNeg3, zeroLit,
                                  litNeg2, litPos3, zeroLit,
                                  litPos3, litNeg2, litPos1, zeroLit,
                                  litNeg3, litNeg2, litNeg1, zeroLit,
                                  litPos3, litPos1, litPos2, zeroLit,
                                  litPos1, litPos3, litPos2, zeroLit,
                                  litPos3, litPos2, litPos1, zeroLit,
                                  litNeg1, litPos2, litNeg3, zeroLit };
            ClauseIdVectorType literalNumberOfOccurrences { 0, 0, 8, 2, 8, 4, 5, 5 };

            actualResult << "Before sorting" << std::endl;
            printFormula(formula, actualResult);
            actualResult << std::endl;

            ContagiousFormulaRepresentationType contagiousFormulaRepresentation(formula, 3, 14, literalNumberOfOccurrences);

            actualResult << "After sorting" << std::endl;
            printContagiousFormulaRepresentation(contagiousFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clause iterator
     */
    TEST_CASE("[Formula::Representation::Contagious] clause iterator", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationClauseIteratorResult);
        std::stringstream& actualResult = test.getStringStream();

        auto printClausesLambda = [&actualResult](const ContagiousFormulaRepresentationType& contagiousFormulaRepresentation) {
            for (ClauseIdT clauseId = 0; clauseId < contagiousFormulaRepresentation.getNumberOfOriginalClauses(); ++clauseId) {
                actualResult << "Clause " << std::to_string(clauseId) << ": ";

                try {
                    for (auto clauseIt = contagiousFormulaRepresentation.beginSortedClause(clauseId); clauseIt != contagiousFormulaRepresentation.endSortedClause(); ++clauseIt)
                        actualResult << (*clauseIt) << " ";
                }
                catch (const std::exception& e) {
                    actualResult << e.what();
                }

                actualResult << std::endl;
            }
            actualResult << std::endl;
        };

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentation(variableSet);
            printClausesLambda(contagiousFormulaRepresentation);

            VariableVectorType tmp;
            LiteralType litNeg1(1, false);
            LiteralType litNeg7(7, true);

            // Add assignment: -x1
            actualResult << "Add assignment: -x1" << std::endl;
            contagiousFormulaRepresentation.addLiteralToPartialAssignment(litNeg1, tmp);
            printClausesLambda(contagiousFormulaRepresentation);

            // Add assignment: x7
            actualResult << "Add assignment: x7" << std::endl;
            contagiousFormulaRepresentation.addLiteralToPartialAssignment(litNeg7, tmp);
            printClausesLambda(contagiousFormulaRepresentation);

            // Remove assignment: x7
            actualResult << "Remove assignment: x7" << std::endl;
            contagiousFormulaRepresentation.removeLiteralFromPartialAssignment(litNeg7, tmp);
            printClausesLambda(contagiousFormulaRepresentation);

            // Remove assignment: -x1
            actualResult << "Remove assignment: -x1" << std::endl;
            contagiousFormulaRepresentation.removeLiteralFromPartialAssignment(litNeg1, tmp);
            printClausesLambda(contagiousFormulaRepresentation);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Assignment
     */
    TEST_CASE("[Formula::Representation::Contagious] assignment", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        auto printFreeVariablesLambda = [&actualResult](const VariableVectorType& freeVariableVector, bool unfree) {
            if (!unfree)
                actualResult << "Free variables: ";
            else
                actualResult << "Unfree variables: ";

            for (VarT freeVariable : freeVariableVector)
                actualResult << std::to_string(freeVariable) << " ";
            actualResult << std::endl;
        };

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentation(variableSet);

            //region Literals
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);
            LiteralType litNeg3(3, false);
            LiteralType litPos4(4, true);
            LiteralType litNeg4(4, false);
            LiteralType litPos6(6, true);
            LiteralType litPos7(7, true);
            //endregion

            std::vector<LiteralVectorType> assignmentVector { { litNeg1, litPos1 },            // -
                                                              { litPos2, litNeg3, litNeg2 },   // -, watcher
                                                              { litPos4 },
                                                              { litNeg4 },
                                                              { litNeg1, litPos7 },
                                                              { litNeg1, litNeg2, litPos7, litPos6 } };

            for (const LiteralVectorType& assignment : assignmentVector) {
                LiteralVectorType assignmentTmp;
                assignmentTmp.reserve(assignment.size());

                // Add assignment
                try {
                    for (const LiteralType& lit : assignment) {
                        actualResult << "Add: " << lit << std::endl;

                        VariableVectorType freeVariableVector;
                        contagiousFormulaRepresentation.addLiteralToPartialAssignment(lit, freeVariableVector);
                        printFreeVariablesLambda(freeVariableVector, false);
                        printContagiousFormulaRepresentation(contagiousFormulaRepresentation, actualResult);
                        actualResult << "--------------------" << std::endl
                                     << std::endl;

                        assignmentTmp.push_back(lit);
                    }
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl
                                 << std::endl;
                }

                // Remove assignment
                try {
                    for (auto it = assignmentTmp.rbegin(); it != assignmentTmp.rend(); ++it) {
                        const LiteralType& lit = *it;
                        actualResult << "Remove: " << lit << std::endl;

                        VariableVectorType freeVariableVector;
                        contagiousFormulaRepresentation.removeLiteralFromPartialAssignment(lit, freeVariableVector);
                        printFreeVariablesLambda(freeVariableVector, true);
                        printContagiousFormulaRepresentation(contagiousFormulaRepresentation, actualResult);
                        actualResult << "--------------------" << std::endl
                                     << std::endl;
                    }
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                actualResult << "----------------------------------------" << std::endl
                             << std::endl
                             << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clause properties
     */
    TEST_CASE("[Formula::Representation::Contagious] clause properties", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationClausePropertiesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentation(variableSet);
            printClauseProperties(contagiousFormulaRepresentation, actualResult);

            //region Literals
            LiteralType litNeg1(1, false);
            LiteralType litNeg2(2, false);
            LiteralType litNeg3(3, false);
            LiteralType litNeg5(5, false);
            LiteralType litPos6(6, true);
            LiteralType litPos7(7, true);
            LiteralType litNeg7(7, false);
            LiteralType litPos8(8, true);
            //endregion

            std::vector<LiteralVectorType> assignmentVector { { litNeg1 },
                                                              { litNeg7, litPos8, litPos6 },
                                                              { litNeg3, litNeg2, litPos7, litPos6, litNeg1, litNeg5 } };

            for (const LiteralVectorType& assignment : assignmentVector) {
                // Add assignment
                for (const LiteralType& lit : assignment) {
                    actualResult << "--------------------" << std::endl;
                    actualResult << "Add: " << lit << std::endl;
                    actualResult << "--------------------" << std::endl
                                 << std::endl;

                    VariableVectorType freeVariableVector;
                    contagiousFormulaRepresentation.addLiteralToPartialAssignment(lit, freeVariableVector);

                    printClauseProperties(contagiousFormulaRepresentation, actualResult);
                }

                // Remove assignment
                for (auto it = assignment.rbegin(); it != assignment.rend(); ++it) {
                    const LiteralType& lit = *it;
                    actualResult << "--------------------" << std::endl;
                    actualResult << "Remove: " << lit << std::endl;
                    actualResult << "--------------------" << std::endl
                                 << std::endl;

                    VariableVectorType freeVariableVector;
                    contagiousFormulaRepresentation.removeLiteralFromPartialAssignment(lit, freeVariableVector);

                    printClauseProperties(contagiousFormulaRepresentation, actualResult);
                }

                actualResult << "----------------------------------------" << std::endl
                             << std::endl
                             << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Variable properties
     */
    TEST_CASE("[Formula::Representation::Contagious] variable properties", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationVariablePropertiesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentation(variableSet);
            printVariableProperties(contagiousFormulaRepresentation, variableSet, actualResult);

            //region Literals
            LiteralType litNeg1(1, false);
            LiteralType litNeg2(2, false);
            LiteralType litNeg3(3, false);
            LiteralType litNeg5(5, false);
            LiteralType litPos6(6, true);
            LiteralType litPos7(7, true);
            LiteralType litNeg7(7, false);
            LiteralType litPos8(8, true);
            //endregion

            std::vector<LiteralVectorType> assignmentVector { { litNeg1 },
                                                              { litNeg7, litPos8, litPos6 },
                                                              { litNeg3, litNeg2, litPos7, litPos6, litNeg1, litNeg5 } };

            for (const LiteralVectorType& assignment : assignmentVector) {
                // Add assignment
                for (const LiteralType& lit : assignment) {
                    actualResult << "--------------------" << std::endl;
                    actualResult << "Add: " << lit << std::endl;
                    actualResult << "--------------------" << std::endl
                                 << std::endl;

                    VariableVectorType freeVariableVector;
                    contagiousFormulaRepresentation.addLiteralToPartialAssignment(lit, freeVariableVector);

                    printVariableProperties(contagiousFormulaRepresentation, variableSet, actualResult);
                }

                // Remove assignment
                for (auto it = assignment.rbegin(); it != assignment.rend(); ++it) {
                    const LiteralType& lit = *it;
                    actualResult << "--------------------" << std::endl;
                    actualResult << "Remove: " << lit << std::endl;
                    actualResult << "--------------------" << std::endl
                                 << std::endl;

                    VariableVectorType freeVariableVector;
                    contagiousFormulaRepresentation.removeLiteralFromPartialAssignment(lit, freeVariableVector);

                    printVariableProperties(contagiousFormulaRepresentation, variableSet, actualResult);
                }

                actualResult << "----------------------------------------" << std::endl
                             << std::endl
                             << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Literal properties
     */
    TEST_CASE("[Formula::Representation::Contagious] literal properties", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationLiteralPropertiesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentation(variableSet);
            printLiteralProperties(contagiousFormulaRepresentation, actualResult);

            //region Literals
            LiteralType litNeg1(1, false);
            LiteralType litNeg2(2, false);
            LiteralType litNeg3(3, false);
            LiteralType litNeg5(5, false);
            LiteralType litPos6(6, true);
            LiteralType litPos7(7, true);
            LiteralType litNeg7(7, false);
            LiteralType litPos8(8, true);
            //endregion

            std::vector<LiteralVectorType> assignmentVector { { litNeg1 },
                                                              { litNeg7, litPos8, litPos6 },
                                                              { litNeg3, litNeg2, litPos7, litPos6, litNeg1, litNeg5 } };

            for (const LiteralVectorType& assignment : assignmentVector) {
                // Add assignment
                for (const LiteralType& lit : assignment) {
                    actualResult << "--------------------" << std::endl;
                    actualResult << "Add: " << lit << std::endl;
                    actualResult << "--------------------" << std::endl
                                 << std::endl;

                    VariableVectorType freeVariableVector;
                    contagiousFormulaRepresentation.addLiteralToPartialAssignment(lit, freeVariableVector);

                    printLiteralProperties(contagiousFormulaRepresentation, actualResult);
                }

                // Remove assignment
                for (auto it = assignment.rbegin(); it != assignment.rend(); ++it) {
                    const LiteralType& lit = *it;
                    actualResult << "--------------------" << std::endl;
                    actualResult << "Remove: " << lit << std::endl;
                    actualResult << "--------------------" << std::endl
                                 << std::endl;

                    VariableVectorType freeVariableVector;
                    contagiousFormulaRepresentation.removeLiteralFromPartialAssignment(lit, freeVariableVector);

                    printLiteralProperties(contagiousFormulaRepresentation, actualResult);
                }

                actualResult << "----------------------------------------" << std::endl
                             << std::endl
                             << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Connected components
     */
    TEST_CASE("[Formula::Representation::Contagious] connected components", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationConnectedComponentsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForConnectedComponents(currentComponentVariableSet);
            printCurrentFormula(contagiousFormulaRepresentation, actualResult);

            LiteralType litPos1(1, true);
            LiteralType litNeg4(4, false);
            LiteralType litNeg9(9, false);

            ConnectedComponentType connectedComponents = contagiousFormulaRepresentation.computeConnectedComponents(currentComponentVariableSet);
            printConnectedComponents(connectedComponents, actualResult);

            actualResult << "Add: " << litPos1 << std::endl;
            currentComponentVariableSet.erase(1);
            VariableVectorType freeVariableVector;
            contagiousFormulaRepresentation.addLiteralToPartialAssignment(litPos1, freeVariableVector);

            connectedComponents = contagiousFormulaRepresentation.computeConnectedComponents(currentComponentVariableSet);
            printConnectedComponents(connectedComponents, actualResult);

            for (ConnectedComponentStruct& connectedComponentStruct : connectedComponents) {
                actualResult << "Set new component: ";
                for (VarT var : Hydra::Other::sortUnorderedSet(connectedComponentStruct.variableSet))
                    actualResult << std::to_string(var) << " ";
                actualResult << std::endl;

                contagiousFormulaRepresentation.setNewComponent(connectedComponentStruct, IgnorePureLiteralTypeEnum::NONE);
                printCurrentFormula(contagiousFormulaRepresentation, actualResult);

                // Component: 2 3 4 5
                if (Hydra::Other::containInSet<VarT>(connectedComponentStruct.variableSet, 4)) {
                    actualResult << "Add: " << litNeg4 << std::endl;
                    connectedComponentStruct.variableSet.erase(4);
                    contagiousFormulaRepresentation.addLiteralToPartialAssignment(litNeg4, freeVariableVector);

                    ConnectedComponentType connectedComponentsTmp = contagiousFormulaRepresentation.computeConnectedComponents(connectedComponentStruct.variableSet);
                    printConnectedComponents(connectedComponentsTmp, actualResult);

                    actualResult << "Remove: " << litNeg4 << std::endl;
                    connectedComponentStruct.variableSet.insert(4);
                    contagiousFormulaRepresentation.removeLiteralFromPartialAssignment(litNeg4, freeVariableVector);
                }

                // Component: 7 8 9 10 11
                if (Hydra::Other::containInSet<VarT>(connectedComponentStruct.variableSet, 9)) {
                    actualResult << "Add: " << litNeg9 << std::endl;
                    connectedComponentStruct.variableSet.erase(9);
                    contagiousFormulaRepresentation.addLiteralToPartialAssignment(litNeg9, freeVariableVector);

                    ConnectedComponentType connectedComponentsTmp = contagiousFormulaRepresentation.computeConnectedComponents(connectedComponentStruct.variableSet);
                    printConnectedComponents(connectedComponentsTmp, actualResult);

                    actualResult << "Remove: " << litNeg9 << std::endl;
                    connectedComponentStruct.variableSet.insert(9);
                    contagiousFormulaRepresentation.removeLiteralFromPartialAssignment(litNeg9, freeVariableVector);
                }

                actualResult << "Pop previous component" << std::endl;
                contagiousFormulaRepresentation.popPreviousComponent(connectedComponentStruct, {});
                actualResult << "--------------------" << std::endl
                             << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Variable properties (get current clauses)
     */
    TEST_CASE("[Formula::Representation::Contagious] variable properties (get current clauses)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationVariablePropertiesGetCurrentClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentation(variableSet);

            ClauseIdReusableVectorType clauseIdReusableVector(contagiousFormulaRepresentation.getNumberOfOriginalClauses());

            std::vector<VariableVectorType> variableVectorVector { { 1 }, { 1, 7 }, { 2, 4 }, { 3, 2 }, { 6, 7 } };

            for (const VariableVectorType& variableVector : variableVectorVector) {
                actualResult << "Variables: ";
                for (VarT var : variableVector)
                    actualResult << std::to_string(var) << " ";
                actualResult << std::endl;

                contagiousFormulaRepresentation.getCurrentClauses(variableSet, variableVector, clauseIdReusableVector, VectorSetType());
                clauseIdReusableVector.sort();

                actualResult << "Clauses: ";
                for (ClauseIdT clauseId : clauseIdReusableVector)
                    actualResult << std::to_string(clauseId) << " ";
                actualResult << std::endl
                             << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Pure literals
     */
    TEST_CASE("[Formula::Representation::Contagious] pure literals", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationPureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForPureLiterals(variableSet);
            printCurrentFormula(contagiousFormulaRepresentation, actualResult);

            for (VarT var : Hydra::Other::sortUnorderedSet(variableSet)) {
                actualResult << std::to_string(var) << std::endl;

                actualResult << "is pure literal: " << std::to_string(contagiousFormulaRepresentation.isPureLiteralInCurrentFormula(var)) << std::endl;
                actualResult << "is positive pure literal: " << std::to_string(contagiousFormulaRepresentation.isPositivePureLiteralInCurrentFormula(var)) << std::endl;
                actualResult << "is negative pure literal: " << std::to_string(contagiousFormulaRepresentation.isNegativePureLiteralInCurrentFormula(var)) << std::endl;
                actualResult << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Not duplicate clauses
     */
    TEST_CASE("[Formula::Representation::Contagious] not duplicate clauses", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationNotDuplicateClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForDuplicateClauses(variableSet);
            printClauses(contagiousFormulaRepresentation, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(contagiousFormulaRepresentation.getNumberOfOriginalClauses());
            contagiousFormulaRepresentation.getCurrentComponentNotDuplicateClauses(variableSet, clauseIdReusableVector, false, true);
            printClauseIdReusableVector(clauseIdReusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Not duplicate clauses (assignment)
     */
    TEST_CASE("[Formula::Representation::Contagious] not duplicate clauses (assignment)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationNotDuplicateClausesAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForDuplicateClauses(variableSet);

            VariableVectorType tmp;
            contagiousFormulaRepresentation.addLiteralToPartialAssignment(LiteralType(5, false), tmp);

            printClauses(contagiousFormulaRepresentation, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(contagiousFormulaRepresentation.getNumberOfOriginalClauses());
            contagiousFormulaRepresentation.getCurrentComponentNotDuplicateClauses(variableSet, clauseIdReusableVector, false, true);
            printClauseIdReusableVector(clauseIdReusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Not duplicate clauses - variables
     */
    TEST_CASE("[Formula::Representation::Contagious] not duplicate clauses - variables", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationNotDuplicateClausesVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForDuplicateClauses(variableSet);
            printClauses(contagiousFormulaRepresentation, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(contagiousFormulaRepresentation.getNumberOfOriginalClauses());
            contagiousFormulaRepresentation.getCurrentComponentNotDuplicateClauses(variableSet, clauseIdReusableVector, true, true);
            printClauseIdReusableVector(clauseIdReusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Not duplicate clauses - variables (assignment)
     */
    TEST_CASE("[Formula::Representation::Contagious] not duplicate clauses - variables (assignment)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationNotDuplicateClausesVariablesAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForDuplicateClauses(variableSet);

            VariableVectorType tmp;
            contagiousFormulaRepresentation.addLiteralToPartialAssignment(LiteralType(5, false), tmp);

            printClauses(contagiousFormulaRepresentation, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(contagiousFormulaRepresentation.getNumberOfOriginalClauses());
            contagiousFormulaRepresentation.getCurrentComponentNotDuplicateClauses(variableSet, clauseIdReusableVector, true, true);
            printClauseIdReusableVector(clauseIdReusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    #if defined(BELLA_COMPILER)
    /**
     * Pure clauses (ignore positive pure literals)
     */
    TEST_CASE("[Formula::Representation::Contagious] pure clauses (ignore positive pure literals)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationPureClausesIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForPureClauses(variableSet);
            processPureClauses(contagiousFormulaRepresentation, { 1, 7 },
                               IgnorePureLiteralTypeEnum::ONLY_POSITIVE, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Pure clauses (ignore negative pure literals)
     */
    TEST_CASE("[Formula::Representation::Contagious] pure clauses (ignore negative pure literals)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationPureClausesIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForPureClauses(variableSet);
            processPureClauses(contagiousFormulaRepresentation, { 0, 9 },
                               IgnorePureLiteralTypeEnum::ONLY_NEGATIVE, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Pure clauses (ignore pure literals)
     */
    TEST_CASE("[Formula::Representation::Contagious] pure clauses (ignore pure literals)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationPureClausesIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForPureClauses(variableSet);
            processPureClauses(contagiousFormulaRepresentation, { 0, 1, 3, 5, 6, 7, 9 },
                               IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Connected components (ignore positive pure literals)
     */
    TEST_CASE("[Formula::Representation::Contagious] connected components (ignore positive pure literals)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationConnectedComponentsIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForConnectedComponentPositivePureVariables(variableSet);
            printContagiousFormulaRepresentation(contagiousFormulaRepresentation, actualResult);

            ClauseIdSetType pureClauseSet;
            ConnectedComponentType connectedComponents = contagiousFormulaRepresentation.computeConnectedComponents(variableSet, pureClauseSet,
                                                                                                                    IgnorePureLiteralTypeEnum::ONLY_POSITIVE);

            printPureClauses(pureClauseSet, actualResult);
            printConnectedComponents(connectedComponents, actualResult, true);
            printContagiousFormulaRepresentation(contagiousFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Connected components (ignore negative pure literals)
     */
    TEST_CASE("[Formula::Representation::Contagious] connected components (ignore negative pure literals)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationConnectedComponentsIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForConnectedComponentNegativePureVariables(variableSet);
            printContagiousFormulaRepresentation(contagiousFormulaRepresentation, actualResult);

            ClauseIdSetType pureClauseSet;
            ConnectedComponentType connectedComponents = contagiousFormulaRepresentation.computeConnectedComponents(variableSet, pureClauseSet,
                                                                                                                    IgnorePureLiteralTypeEnum::ONLY_NEGATIVE);

            printPureClauses(pureClauseSet, actualResult);
            printConnectedComponents(connectedComponents, actualResult, true);
            printContagiousFormulaRepresentation(contagiousFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Connected components (ignore pure literals)
     */
    TEST_CASE("[Formula::Representation::Contagious] connected components (ignore pure literals)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationConnectedComponentsIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForConnectedComponentPositivePureVariables(variableSet);
            printContagiousFormulaRepresentation(contagiousFormulaRepresentation, actualResult);

            ClauseIdSetType pureClauseSet;
            ConnectedComponentType connectedComponents = contagiousFormulaRepresentation.computeConnectedComponents(variableSet, pureClauseSet,
                                                                                                                    IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE);

            printPureClauses(pureClauseSet, actualResult);
            printConnectedComponents(connectedComponents, actualResult, true);
            printContagiousFormulaRepresentation(contagiousFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif

    /**
     * Sort variables based on clause reduction heuristic (ascending)
     */
    TEST_CASE("[Formula::Representation::Contagious] sort variables based on clause reduction heuristic (ascending)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSortVariablesBasedOnClauseReductionHeuristicAscendingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForSortVariablesBasedOnClauseReductionHeuristic(variableSet);
            printCurrentFormula(contagiousFormulaRepresentation, actualResult);

            VariableReusableVectorType variableOrder(contagiousFormulaRepresentation.getNumberOfVariablesInOriginalFormula());
            variableOrder.copySet(variableSet);

            contagiousFormulaRepresentation.sortVariablesBasedOnClauseReductionHeuristic(variableSet, variableOrder, true);

            actualResult << "Sorted variables:";
            for (VarT var : variableOrder)
                actualResult << " " << std::to_string(var);
            actualResult << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sort variables based on clause reduction heuristic (descending)
     */
    TEST_CASE("[Formula::Representation::Contagious] sort variables based on clause reduction heuristic (descending)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSortVariablesBasedOnClauseReductionHeuristicDescendingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForSortVariablesBasedOnClauseReductionHeuristic(variableSet);
            printCurrentFormula(contagiousFormulaRepresentation, actualResult);

            VariableReusableVectorType variableOrder(contagiousFormulaRepresentation.getNumberOfVariablesInOriginalFormula());
            variableOrder.copySet(variableSet);

            contagiousFormulaRepresentation.sortVariablesBasedOnClauseReductionHeuristic(variableSet, variableOrder, false);

            actualResult << "Sorted variables:";
            for (VarT var : variableOrder)
                actualResult << " " << std::to_string(var);
            actualResult << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Save current component formula
     */
    TEST_CASE("[Formula::Representation::Contagious] save current component formula", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSaveCurrentComponentFormulaResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForSortVariablesBasedOnClauseReductionHeuristic(currentComponentVariableSet);

            processSaveCurrentComponentFormulaToVector(contagiousFormulaRepresentation, currentComponentVariableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Save current component formula (one clause)
     */
    TEST_CASE("[Formula::Representation::Contagious] save current component formula (one clause)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSaveCurrentComponentFormulaOneClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationWithOneClause(currentComponentVariableSet);

            processSaveCurrentComponentFormulaToVector(contagiousFormulaRepresentation, currentComponentVariableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    #if defined(BELLA_COMPILER)
    /**
     * Save current component formula (pure clauses)
     */
    TEST_CASE("[Formula::Representation::Contagious] save current component formula (pure clauses)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSaveCurrentComponentFormulaPureClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForPureClauses(currentComponentVariableSet);

            // Remove pure clauses
            ClauseIdSetType pureClauseSet = { 0, 1, 3, 5, 6, 7, 9 };
            contagiousFormulaRepresentation.removeClausesContainingOnlyPureLiteralsOfIgnoredType(pureClauseSet,
                                                                                                 IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE);

            processSaveCurrentComponentFormulaToVector(contagiousFormulaRepresentation, currentComponentVariableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif

    /**
     * Save current component formula (assignment)
     */
    TEST_CASE("[Formula::Representation::Contagious] save current component formula (assignment)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSaveCurrentComponentFormulaAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForConnectedComponents(currentComponentVariableSet);

            // Assign x_1, -x_6
            VariableVectorType tmp;
            currentComponentVariableSet.erase((VarT)1);
            currentComponentVariableSet.erase((VarT)6);
            contagiousFormulaRepresentation.addLiteralVectorToPartialAssignment({ LiteralType(1, true), LiteralType(6, false) }, tmp);

            processSaveCurrentComponentFormulaToVectorConnectedComponents(contagiousFormulaRepresentation, currentComponentVariableSet,
                                                                          IgnorePureLiteralTypeEnum::NONE, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    #if defined(BELLA_COMPILER)
    /**
     * Save current component formula (ignore positive pure literals)
     */
    TEST_CASE("[Formula::Representation::Contagious] save current component formula (ignore positive pure literals)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSaveCurrentComponentFormulaIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForConnectedComponentPositivePureVariables(currentComponentVariableSet);

            processSaveCurrentComponentFormulaToVectorConnectedComponents(contagiousFormulaRepresentation, currentComponentVariableSet,
                                                                          IgnorePureLiteralTypeEnum::ONLY_POSITIVE, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Save current component formula (ignore negative pure literals)
     */
    TEST_CASE("[Formula::Representation::Contagious] save current component formula (ignore negative pure literals)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSaveCurrentComponentFormulaIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForConnectedComponentNegativePureVariables(currentComponentVariableSet);

            processSaveCurrentComponentFormulaToVectorConnectedComponents(contagiousFormulaRepresentation, currentComponentVariableSet,
                                                                          IgnorePureLiteralTypeEnum::ONLY_NEGATIVE, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Save current component formula (ignore pure literals)
     */
    TEST_CASE("[Formula::Representation::Contagious] save current component formula (ignore pure literals)", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSaveCurrentComponentFormulaIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForConnectedComponentPositivePureVariables(currentComponentVariableSet);

            processSaveCurrentComponentFormulaToVectorConnectedComponents(contagiousFormulaRepresentation, currentComponentVariableSet,
                                                                          IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif

    /**
     * Save formula defined by clauses
     */
    TEST_CASE("[Formula::Representation::Contagious] save formula defined by clauses", "[Formula::Representation::Contagious]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSaveFormulaDefinedByClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContagiousFormulaRepresentationType contagiousFormulaRepresentation = createContagiousFormulaRepresentationForSortVariablesBasedOnClauseReductionHeuristic(currentComponentVariableSet);

            std::vector<ClauseIdReusableVectorType> clausesReusableVector;
            std::vector<ClauseIdVectorType> clausesVector = { { 0 }, { 1 }, { 2 }, { 3 }, { 4 }, { 5 }, { 0, 2, 4 }, { 1, 3, 5 }, { 0, 1, 2, 3, 4, 5 } };

            for (const ClauseIdVectorType& clauseIdVector : clausesVector) {
                clausesReusableVector.emplace_back(contagiousFormulaRepresentation.getNumberOfOriginalClauses());

                for (ClauseIdT clauseId : clauseIdVector)
                    clausesReusableVector.back().emplace_back(clauseId);
            }

            for (const ClauseIdReusableVectorType& clauseReusableVector : clausesReusableVector) {
                processSaveFormulaDefinedByClausesToVector(contagiousFormulaRepresentation, clauseReusableVector, actualResult);
                actualResult << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Formula::Representation::Contagious
