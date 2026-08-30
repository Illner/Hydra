#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/external/unitTesting/Catch2/catch.hpp"
#include "HydraTest/formula/representation/contiguous/ContiguousFormulaRepresentationTestResult.hpp"

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contiguous/ContiguousFormulaRepresentation.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/computeConnectedComponents/ConnectedComponentStructure.hpp"

#include "Hydra/cache/cachingScheme/enums/OmitClauseTypeEnum.hpp"
#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"

namespace HydraTest::Formula::Representation::Contiguous {

    using FormulaSizeType = Hydra::Formula::Representation::FormulaSizeType;

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;
    using ClauseIdT = char8_t;

    using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
    using FormulaType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::FormulaType;
    using VectorSetType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VectorSetType;
    using ClauseSizeType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeType;
    using ClauseIdSetType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdSetType;
    using VariableSetType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
    using ClauseStringType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseStringType;
    using LiteralVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
    using VariableVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
    using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
    using ContiguousFormulaRepresentationType = Hydra::Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
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
    void printContiguousFormulaRepresentation(const ContiguousFormulaRepresentationType& contiguousFormulaRepresentation, std::stringstream& actualResult,
                                              bool printSeparator = true) {
        if (printSeparator) {
            actualResult << "--------------------" << std::endl;
            actualResult << "--------------------" << std::endl;
        }

        contiguousFormulaRepresentation.printFormulaRepresentationDebug(actualResult);
        actualResult << std::endl;
    }

    void printFormula(const FormulaType& formula, std::stringstream& actualResult) {
        actualResult << "Formula: ";
        for (const LiteralType& lit : formula)
            actualResult << lit << " ";
        actualResult << std::endl;
    }

    void printCurrentFormula(const ContiguousFormulaRepresentationType& contiguousFormulaRepresentation, std::stringstream& actualResult) {
        actualResult << "Formula: ";
        contiguousFormulaRepresentation.printCurrentFormulaDebug(actualResult);
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

    void printClauseProperties(const ContiguousFormulaRepresentationType& contiguousFormulaRepresentation, std::stringstream& actualResult,
                               bool printFormula = true) {
        if (printFormula)
            printCurrentFormula(contiguousFormulaRepresentation, actualResult);

        for (ClauseIdT clauseId = 0; clauseId < contiguousFormulaRepresentation.getNumberOfOriginalClauses(); ++clauseId) {
            actualResult << "Clause ID: " << std::to_string(clauseId) << std::endl;

            actualResult << "\tclause status: " << Hydra::Formula::clauseStatusEnumToString(contiguousFormulaRepresentation.getCurrentClauseStatus(clauseId)) << std::endl;
            actualResult << "\tis clause untouched: " << std::to_string(contiguousFormulaRepresentation.isClauseUntouched(clauseId)) << std::endl;
            actualResult << "\tis clause untouched and binary: " << std::to_string(contiguousFormulaRepresentation.isClauseUntouchedAndBinary(clauseId)) << std::endl;

            // The clause is not satisfied
            if (!contiguousFormulaRepresentation.isClauseSatisfied(clauseId)) {
                actualResult << "\tclause size: " << std::to_string(contiguousFormulaRepresentation.getCurrentClauseSize(clauseId)) << std::endl;

                actualResult << "\tcurrent clause: ";
                contiguousFormulaRepresentation.printCurrentClauseDebug(actualResult, clauseId);
                actualResult << std::endl;

                actualResult << "\tvariables in clause: ";
                VariableSortedVectorType variableSortedVector = Hydra::Other::sortUnorderedSet(contiguousFormulaRepresentation.getUnassignedVariablesInClause(clauseId));
                for (VarT var : variableSortedVector)
                    actualResult << std::to_string(var) << " ";
                actualResult << std::endl;
            }
        }

        actualResult << std::endl;
    }

    void printVariableProperties(const ContiguousFormulaRepresentationType& contiguousFormulaRepresentation, const VariableSetType& currentComponentVariableSet,
                                 std::stringstream& actualResult, bool printFormula = true) {
        if (printFormula)
            printCurrentFormula(contiguousFormulaRepresentation, actualResult);

        ClauseIdReusableVectorType clauseIdReusableVector(contiguousFormulaRepresentation.getNumberOfOriginalClauses());

        for (VarT var = 1; var <= contiguousFormulaRepresentation.getNumberOfVariablesInOriginalFormula(); ++var) {
            actualResult << "Variable: " << std::to_string(var) << std::endl;

            actualResult << "\tis assigned: " << std::to_string(contiguousFormulaRepresentation.isVariableAssigned(var)) << std::endl;

            // The variable is not assigned
            if (!contiguousFormulaRepresentation.isVariableAssigned(var)) {
                actualResult << "\tis variable free: " << std::to_string(contiguousFormulaRepresentation.isVariableFree(var)) << std::endl;

                actualResult << "\tclauses: ";
                contiguousFormulaRepresentation.getCurrentClauses(currentComponentVariableSet, var, clauseIdReusableVector, VectorSetType());
                clauseIdReusableVector.sort();
                for (ClauseIdT clauseId : clauseIdReusableVector)
                    actualResult << std::to_string(clauseId) << " ";
                actualResult << std::endl;

                actualResult << "\tclause size counter: ";
                ClauseSizeCounterType clauseSizeCounter = contiguousFormulaRepresentation.getCurrentClauseSizeCounter(Hydra::Formula::getPositiveLiteralT<VarT, LiteralT>(var));

                for (auto [clauseSize, numberOfClauses] : contiguousFormulaRepresentation.getCurrentClauseSizeCounter(Hydra::Formula::getNegativeLiteralT<VarT, LiteralT>(var))) {
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
                ClauseIdT numberOfBinaryClauses = contiguousFormulaRepresentation.getNumberOfCurrentBinaryClauses(Hydra::Formula::getPositiveLiteralT<VarT, LiteralT>(var)) +
                                                  contiguousFormulaRepresentation.getNumberOfCurrentBinaryClauses(Hydra::Formula::getNegativeLiteralT<VarT, LiteralT>(var));
                actualResult << std::to_string(numberOfBinaryClauses) << std::endl;
            }
        }

        actualResult << std::endl;
    }

    void printLiteralProperties(const ContiguousFormulaRepresentationType& contiguousFormulaRepresentation, std::stringstream& actualResult,
                                bool printFormula = true) {
        if (printFormula)
            printCurrentFormula(contiguousFormulaRepresentation, actualResult);

        for (VarT var = 1; var <= contiguousFormulaRepresentation.getNumberOfVariablesInOriginalFormula(); ++var) {
            actualResult << "Variable: " << std::to_string(var) << std::endl;

            // The variable is not assigned
            if (!contiguousFormulaRepresentation.isVariableAssigned(var)) {
                for (bool sign : { true, false }) {
                    LiteralType lit(var, sign);
                    actualResult << "\tLiteral: " << lit << std::endl;

                    actualResult << "\t\tnumber of current clauses: " << std::to_string(contiguousFormulaRepresentation.getNumberOfCurrentClauses(lit.getLiteralT())) << std::endl;

                    actualResult << "\t\tclause size counter: ";
                    ClauseSizeCounterType clauseSizeCounter = contiguousFormulaRepresentation.getCurrentClauseSizeCounter(lit.getLiteralT());
                    std::vector<ClauseSizeType> keySortedVector = Hydra::Other::extractKeysFromMap(clauseSizeCounter, true);
                    for (ClauseSizeType clauseSize : keySortedVector)
                        actualResult << std::to_string(clauseSize) << " (" << std::to_string(clauseSizeCounter[clauseSize]) << ") ";
                    actualResult << std::endl;

                    actualResult << "\tnumber of binary clauses: ";
                    ClauseIdT numberOfBinaryClauses = contiguousFormulaRepresentation.getNumberOfCurrentBinaryClauses(lit.getLiteralT());
                    actualResult << std::to_string(numberOfBinaryClauses) << std::endl;

                    actualResult << "\tin unit clause: ";
                    bool inUnitClause = contiguousFormulaRepresentation.isLiteralInUnitClause(lit);
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

    void printClauseString(const ContiguousFormulaRepresentationType& contiguousFormulaRepresentation, ClauseIdT clauseId, std::stringstream& actualResult,
                           bool printCurrentClause = true) {
        if (printCurrentClause) {
            actualResult << "Clause: ";
            contiguousFormulaRepresentation.printCurrentClauseDebug(actualResult, clauseId);
            actualResult << std::endl;
        }

        // Clause string
        actualResult << "Clause string:";
        ClauseStringType clauseString = contiguousFormulaRepresentation.getClauseString(clauseId, false);
        for (LiteralT l : clauseString)
            actualResult << " " << std::to_string(l);
        actualResult << std::endl;

        // Clause string (variable)
        actualResult << "Clause string (variable):";
        clauseString = contiguousFormulaRepresentation.getClauseString(clauseId, true);
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

    void printClauses(const ContiguousFormulaRepresentationType& contiguousFormulaRepresentation, std::stringstream& actualResult) {
        for (ClauseIdT clauseId = 0; clauseId < contiguousFormulaRepresentation.getNumberOfOriginalClauses(); ++clauseId) {
            // The clause is satisfied
            if (contiguousFormulaRepresentation.isClauseSatisfied(clauseId))
                continue;

            actualResult << std::to_string(clauseId) << ": ";
            contiguousFormulaRepresentation.printCurrentClauseDebug(actualResult, clauseId);
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

    void processPureClauses(ContiguousFormulaRepresentationType& contiguousFormulaRepresentation, const ClauseIdSetType& pureClauseSet,
                            IgnorePureLiteralTypeEnum ignorePureLiteralType, std::stringstream& actualResult) {
        printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult, false);

        for (ClauseIdT clauseId : Hydra::Other::sortUnorderedSet(pureClauseSet)) {
            actualResult << "Pure clause: " << std::to_string(clauseId) << std::endl;

            // Remove the clause
            Hydra::Other::printTitle(actualResult, "remove", 30, '-');
            contiguousFormulaRepresentation.removeClausesContainingOnlyPureLiteralsOfIgnoredType({ clauseId }, ignorePureLiteralType);
            printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult, false);

            // Add the clause
            Hydra::Other::printTitle(actualResult, "add", 30, '-');
            contiguousFormulaRepresentation.addClausesContainingOnlyPureLiteralsOfIgnoredType({ clauseId }, ignorePureLiteralType);
            printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult, false);
        }

        actualResult << "Pure clauses:";
        for (ClauseIdT clauseId : Hydra::Other::sortUnorderedSet(pureClauseSet))
            actualResult << " " << std::to_string(clauseId);
        actualResult << std::endl;

        Hydra::Other::printTitle(actualResult, "remove", 30, '-');
        contiguousFormulaRepresentation.removeClausesContainingOnlyPureLiteralsOfIgnoredType(pureClauseSet, ignorePureLiteralType);
        printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult, false);

        // Add the clause
        Hydra::Other::printTitle(actualResult, "add", 30, '-');
        contiguousFormulaRepresentation.addClausesContainingOnlyPureLiteralsOfIgnoredType(pureClauseSet, ignorePureLiteralType);
        printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult, false);
    }

    void processSaveCurrentComponentFormulaToVector(const ContiguousFormulaRepresentationType& contiguousFormulaRepresentation,
                                                    const VariableSetType& currentComponentVariableSet, std::stringstream& actualResult) {
        LiteralVectorType formula;
        ClauseOffsetVectorType clauseOffsetVector;
        contiguousFormulaRepresentation.saveCurrentComponentFormulaToVector(currentComponentVariableSet, formula, clauseOffsetVector, true);

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

    void processSaveFormulaDefinedByClausesToVector(const ContiguousFormulaRepresentationType& contiguousFormulaRepresentation,
                                                    const ClauseIdReusableVectorType& clauseIdReusableVector, std::stringstream& actualResult) {
        // Print the clauses
        actualResult << "Clauses:";
        for (ClauseIdT clauseId : clauseIdReusableVector)
            actualResult << " " << std::to_string(clauseId);
        actualResult << std::endl;

        LiteralVectorType formula;
        ClauseOffsetVectorType clauseOffsetVector;
        contiguousFormulaRepresentation.saveFormulaDefinedByClausesToVector(clauseIdReusableVector, formula, clauseOffsetVector, true);

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

    void processSaveCurrentComponentFormulaToVectorConnectedComponents(ContiguousFormulaRepresentationType& contiguousFormulaRepresentation,
                                                                       const VariableSetType& currentComponentVariableSet,
                                                                       IgnorePureLiteralTypeEnum ignorePureLiteralType, std::stringstream& actualResult) {
        processSaveCurrentComponentFormulaToVector(contiguousFormulaRepresentation, currentComponentVariableSet, actualResult);
        actualResult << std::endl;

        // Compute connected components
        ConnectedComponentType connectedComponents;
        if (ignorePureLiteralType == IgnorePureLiteralTypeEnum::NONE)
            connectedComponents = contiguousFormulaRepresentation.computeConnectedComponents(currentComponentVariableSet);
        else {
            ClauseIdSetType pureClauseSet;
            connectedComponents = contiguousFormulaRepresentation.computeConnectedComponents(currentComponentVariableSet, pureClauseSet, ignorePureLiteralType);

            contiguousFormulaRepresentation.removeClausesContainingOnlyPureLiteralsOfIgnoredType(pureClauseSet, ignorePureLiteralType);

            printPureClauses(pureClauseSet, actualResult);
            actualResult << std::endl;
        }

        printConnectedComponents(connectedComponents, actualResult, (ignorePureLiteralType != IgnorePureLiteralTypeEnum::NONE));

        for (const ConnectedComponentStruct& connectedComponentStruct : connectedComponents) {
            actualResult << "Set new component: ";
            for (VarT var : Hydra::Other::sortUnorderedSet(connectedComponentStruct.variableSet))
                actualResult << std::to_string(var) << " ";
            actualResult << std::endl;

            PureVariableRemovedClausesVectorType pureVariableRemovedClausesVector = contiguousFormulaRepresentation.setNewComponent(connectedComponentStruct, ignorePureLiteralType);

            processSaveCurrentComponentFormulaToVector(contiguousFormulaRepresentation, connectedComponentStruct.variableSet, actualResult);

            contiguousFormulaRepresentation.popPreviousComponent(connectedComponentStruct, pureVariableRemovedClausesVector);
            actualResult << std::endl;
        }
    }
    //endregion

    //region ContiguousFormulaRepresentation
    ContiguousFormulaRepresentationType createContiguousFormulaRepresentationWithOneClause(VariableSetType& variableSet) {
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
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contiguous::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contiguous::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContiguousFormulaRepresentationType contiguousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3 };

        return contiguousFormulaRepresentation;
    }

    ContiguousFormulaRepresentationType createContiguousFormulaRepresentation(VariableSetType& variableSet) {
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
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contiguous::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contiguous::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContiguousFormulaRepresentationType contiguousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8 };

        return contiguousFormulaRepresentation;
    }

    ContiguousFormulaRepresentationType createContiguousFormulaRepresentationForConnectedComponents(VariableSetType& variableSet) {
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
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contiguous::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contiguous::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContiguousFormulaRepresentationType contiguousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

        return contiguousFormulaRepresentation;
    }

    ContiguousFormulaRepresentationType createContiguousFormulaRepresentationForPureLiterals(VariableSetType& variableSet) {
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
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contiguous::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contiguous::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContiguousFormulaRepresentationType contiguousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        return contiguousFormulaRepresentation;
    }

    ContiguousFormulaRepresentationType createContiguousFormulaRepresentationForDuplicateClauses(VariableSetType& variableSet) {
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
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contiguous::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contiguous::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContiguousFormulaRepresentationType contiguousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3, 4, 5 };

        return contiguousFormulaRepresentation;
    }

    ContiguousFormulaRepresentationType createContiguousFormulaRepresentationForPureClauses(VariableSetType& variableSet) {
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
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contiguous::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contiguous::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContiguousFormulaRepresentationType contiguousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

        return contiguousFormulaRepresentation;
    }

    ContiguousFormulaRepresentationType createContiguousFormulaRepresentationForConnectedComponentPositivePureVariables(VariableSetType& variableSet) {
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
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contiguous::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contiguous::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContiguousFormulaRepresentationType contiguousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

        return contiguousFormulaRepresentation;
    }

    ContiguousFormulaRepresentationType createContiguousFormulaRepresentationForConnectedComponentNegativePureVariables(VariableSetType& variableSet) {
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
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contiguous::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contiguous::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContiguousFormulaRepresentationType contiguousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

        return contiguousFormulaRepresentation;
    }

    ContiguousFormulaRepresentationType createContiguousFormulaRepresentationForSortVariablesBasedOnClauseReductionHeuristic(VariableSetType& variableSet) {
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
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contiguous::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contiguous::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContiguousFormulaRepresentationType contiguousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences);

        variableSet = { 1, 2, 3, 4 };

        return contiguousFormulaRepresentation;
    }
    //endregion

    /**
     * Constructor
     */
    TEST_CASE("[Formula::Representation::Contiguous] constructor", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationConstructorResult);
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
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation1(formula1, 2, 1, literalNumberOfOccurrences1);
            printContiguousFormulaRepresentation(contiguousFormulaRepresentation1, actualResult);
            actualResult << std::endl;

            // Move constructor
            actualResult << "Move constructor" << std::endl;
            FormulaType formula2 { litNeg1, litNeg2, zeroLit, litPos1, litPos2, litPos3, zeroLit, litNeg2, litPos3, zeroLit };
            ClauseIdVectorType literalNumberOfOccurrences2 { 0, 0, 1, 1, 1, 2, 2, 0 };
            printFormulaAndLiteralNumberOfOccurrences(formula2, literalNumberOfOccurrences2, actualResult);
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation2(std::move(formula2), 3, 3, literalNumberOfOccurrences2);
            printContiguousFormulaRepresentation(contiguousFormulaRepresentation2, actualResult);
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
    TEST_CASE("[Formula::Representation::Contiguous] move", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationMoveResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);
            LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

            ContiguousFormulaRepresentationType contiguousFormulaRepresentation1({ litNeg1, litNeg2, zeroLit, litPos1, litPos2, litPos3, zeroLit, litNeg2, litPos3, zeroLit },
                                                                                 3, 3,
                                                                                 { 0, 0, 1, 1, 1, 2, 2, 0 });
            printContiguousFormulaRepresentation(contiguousFormulaRepresentation1, actualResult);

            actualResult << "Move method" << std::endl;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation2 = std::move(contiguousFormulaRepresentation1);
            printContiguousFormulaRepresentation(contiguousFormulaRepresentation2, actualResult);
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
    TEST_CASE("[Formula::Representation::Contiguous] formula sorting - omit none", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationFormulaSortingOmitNoneResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentation(variableSet);

            printCurrentFormula(contiguousFormulaRepresentation, actualResult);
            ClauseIdReusableVectorType clauseIdReusableVector(contiguousFormulaRepresentation.getNumberOfOriginalClauses());
            contiguousFormulaRepresentation.getSortedCurrentComponentClauses({}, clauseIdReusableVector, false, false, OmitClauseTypeEnum::NONE);
            printClauseIdSortedReusableVector(clauseIdReusableVector, actualResult);

            // Assign 2
            VariableVectorType freeVariableVector;
            contiguousFormulaRepresentation.addLiteralToPartialAssignment(LiteralType(2, true), freeVariableVector);

            printCurrentFormula(contiguousFormulaRepresentation, actualResult);
            contiguousFormulaRepresentation.getSortedCurrentComponentClauses({}, clauseIdReusableVector, false, false, OmitClauseTypeEnum::NONE);
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
    TEST_CASE("[Formula::Representation::Contiguous] formula sorting - omit untouched clauses", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationFormulaSortingOmitUnctouchedClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentation(variableSet);

            printCurrentFormula(contiguousFormulaRepresentation, actualResult);
            ClauseIdReusableVectorType clauseIdReusableVector(contiguousFormulaRepresentation.getNumberOfOriginalClauses());
            contiguousFormulaRepresentation.getSortedCurrentComponentClauses({}, clauseIdReusableVector, false, false, OmitClauseTypeEnum::UNTOUCHED);
            printClauseIdSortedReusableVector(clauseIdReusableVector, actualResult);

            // Assign 2
            VariableVectorType freeVariableVector;
            contiguousFormulaRepresentation.addLiteralToPartialAssignment(LiteralType(2, true), freeVariableVector);

            printCurrentFormula(contiguousFormulaRepresentation, actualResult);
            contiguousFormulaRepresentation.getSortedCurrentComponentClauses({}, clauseIdReusableVector, false, false, OmitClauseTypeEnum::UNTOUCHED);
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
    TEST_CASE("[Formula::Representation::Contiguous] formula sorting - omit original binary clauses", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationFormulaSortingOmitOriginalBinaryClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentation(variableSet);

            printCurrentFormula(contiguousFormulaRepresentation, actualResult);
            ClauseIdReusableVectorType clauseIdReusableVector(contiguousFormulaRepresentation.getNumberOfOriginalClauses());
            contiguousFormulaRepresentation.getSortedCurrentComponentClauses({}, clauseIdReusableVector, false, false, OmitClauseTypeEnum::ORIGINAL_BINARY);
            printClauseIdSortedReusableVector(clauseIdReusableVector, actualResult);

            // Assign 2
            VariableVectorType freeVariableVector;
            contiguousFormulaRepresentation.addLiteralToPartialAssignment(LiteralType(2, true), freeVariableVector);

            printCurrentFormula(contiguousFormulaRepresentation, actualResult);
            contiguousFormulaRepresentation.getSortedCurrentComponentClauses({}, clauseIdReusableVector, false, false, OmitClauseTypeEnum::ORIGINAL_BINARY);
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
    TEST_CASE("[Formula::Representation::Contiguous] clause string", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationClauseStringResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForDuplicateClauses(variableSet);

            for (ClauseIdT clauseId = 0; clauseId < contiguousFormulaRepresentation.getNumberOfOriginalClauses(); ++clauseId)
                printClauseString(contiguousFormulaRepresentation, clauseId, actualResult);
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
    TEST_CASE("[Formula::Representation::Contiguous] clause string (assignment)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationClauseStringAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForDuplicateClauses(variableSet);

            VariableVectorType tmp;
            contiguousFormulaRepresentation.addLiteralToPartialAssignment(LiteralType(5, false), tmp);

            for (ClauseIdT clauseId = 0; clauseId < contiguousFormulaRepresentation.getNumberOfOriginalClauses(); ++clauseId) {
                // The clause is satisfied
                if (contiguousFormulaRepresentation.isClauseSatisfied(clauseId))
                    continue;

                printClauseString(contiguousFormulaRepresentation, clauseId, actualResult);
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
    TEST_CASE("[Formula::Representation::Contiguous] clause comparator", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationClauseComparatorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentation(variableSet);
            printCurrentFormula(contiguousFormulaRepresentation, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(contiguousFormulaRepresentation.getNumberOfOriginalClauses());
            contiguousFormulaRepresentation.getCurrentComponentClauses(variableSet, clauseIdReusableVector);
            std::stable_sort(clauseIdReusableVector.begin(), clauseIdReusableVector.end(),
                             ContiguousFormulaRepresentationType::ClauseComparatorFunctor(&contiguousFormulaRepresentation));
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
    TEST_CASE("[Formula::Representation::Contiguous] clause comparator (assignment)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationClauseComparatorAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentation(variableSet);

            VariableVectorType tmp;
            variableSet.erase((VarT)2);
            variableSet.erase((VarT)6);
            contiguousFormulaRepresentation.addLiteralVectorToPartialAssignment({ LiteralType(2, true), LiteralType(6, false) }, tmp);

            printCurrentFormula(contiguousFormulaRepresentation, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(contiguousFormulaRepresentation.getNumberOfOriginalClauses());
            contiguousFormulaRepresentation.getCurrentComponentClauses(variableSet, clauseIdReusableVector);
            std::stable_sort(clauseIdReusableVector.begin(), clauseIdReusableVector.end(),
                             ContiguousFormulaRepresentationType::ClauseComparatorFunctor(&contiguousFormulaRepresentation));
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
    TEST_CASE("[Formula::Representation::Contiguous] clause variable comparator", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationClauseVariableComparatorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentation(variableSet);
            printCurrentFormula(contiguousFormulaRepresentation, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(contiguousFormulaRepresentation.getNumberOfOriginalClauses());
            contiguousFormulaRepresentation.getCurrentComponentClauses(variableSet, clauseIdReusableVector);
            std::stable_sort(clauseIdReusableVector.begin(), clauseIdReusableVector.end(),
                             ContiguousFormulaRepresentationType::ClauseVariableComparatorFunctor(&contiguousFormulaRepresentation));
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
    TEST_CASE("[Formula::Representation::Contiguous] clause variable comparator (assignment)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationClauseVariableComparatorAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentation(variableSet);

            VariableVectorType tmp;
            variableSet.erase((VarT)2);
            variableSet.erase((VarT)6);
            contiguousFormulaRepresentation.addLiteralVectorToPartialAssignment({ LiteralType(2, true), LiteralType(6, false) }, tmp);

            printCurrentFormula(contiguousFormulaRepresentation, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(contiguousFormulaRepresentation.getNumberOfOriginalClauses());
            contiguousFormulaRepresentation.getCurrentComponentClauses(variableSet, clauseIdReusableVector);
            std::stable_sort(clauseIdReusableVector.begin(), clauseIdReusableVector.end(),
                             ContiguousFormulaRepresentationType::ClauseVariableComparatorFunctor(&contiguousFormulaRepresentation));
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
    TEST_CASE("[Formula::Representation::Contiguous] clause sorting", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationClauseSortingResult);
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

            ContiguousFormulaRepresentationType contiguousFormulaRepresentation(formula, 3, 14, literalNumberOfOccurrences);

            actualResult << "After sorting" << std::endl;
            printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult);
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
    TEST_CASE("[Formula::Representation::Contiguous] clause iterator", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationClauseIteratorResult);
        std::stringstream& actualResult = test.getStringStream();

        auto printClausesLambda = [&actualResult](const ContiguousFormulaRepresentationType& contiguousFormulaRepresentation) {
            for (ClauseIdT clauseId = 0; clauseId < contiguousFormulaRepresentation.getNumberOfOriginalClauses(); ++clauseId) {
                actualResult << "Clause " << std::to_string(clauseId) << ": ";

                try {
                    for (auto clauseIt = contiguousFormulaRepresentation.beginSortedClause(clauseId); clauseIt != contiguousFormulaRepresentation.endSortedClause(); ++clauseIt)
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
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentation(variableSet);
            printClausesLambda(contiguousFormulaRepresentation);

            VariableVectorType tmp;
            LiteralType litNeg1(1, false);
            LiteralType litNeg7(7, true);

            // Add assignment: -x1
            actualResult << "Add assignment: -x1" << std::endl;
            contiguousFormulaRepresentation.addLiteralToPartialAssignment(litNeg1, tmp);
            printClausesLambda(contiguousFormulaRepresentation);

            // Add assignment: x7
            actualResult << "Add assignment: x7" << std::endl;
            contiguousFormulaRepresentation.addLiteralToPartialAssignment(litNeg7, tmp);
            printClausesLambda(contiguousFormulaRepresentation);

            // Remove assignment: x7
            actualResult << "Remove assignment: x7" << std::endl;
            contiguousFormulaRepresentation.removeLiteralFromPartialAssignment(litNeg7, tmp);
            printClausesLambda(contiguousFormulaRepresentation);

            // Remove assignment: -x1
            actualResult << "Remove assignment: -x1" << std::endl;
            contiguousFormulaRepresentation.removeLiteralFromPartialAssignment(litNeg1, tmp);
            printClausesLambda(contiguousFormulaRepresentation);
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
    TEST_CASE("[Formula::Representation::Contiguous] assignment", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationAssignmentResult);
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
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentation(variableSet);

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
                        contiguousFormulaRepresentation.addLiteralToPartialAssignment(lit, freeVariableVector);
                        printFreeVariablesLambda(freeVariableVector, false);
                        printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult);
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
                        contiguousFormulaRepresentation.removeLiteralFromPartialAssignment(lit, freeVariableVector);
                        printFreeVariablesLambda(freeVariableVector, true);
                        printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult);
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
    TEST_CASE("[Formula::Representation::Contiguous] clause properties", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationClausePropertiesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentation(variableSet);
            printClauseProperties(contiguousFormulaRepresentation, actualResult);

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
                    contiguousFormulaRepresentation.addLiteralToPartialAssignment(lit, freeVariableVector);

                    printClauseProperties(contiguousFormulaRepresentation, actualResult);
                }

                // Remove assignment
                for (auto it = assignment.rbegin(); it != assignment.rend(); ++it) {
                    const LiteralType& lit = *it;
                    actualResult << "--------------------" << std::endl;
                    actualResult << "Remove: " << lit << std::endl;
                    actualResult << "--------------------" << std::endl
                                 << std::endl;

                    VariableVectorType freeVariableVector;
                    contiguousFormulaRepresentation.removeLiteralFromPartialAssignment(lit, freeVariableVector);

                    printClauseProperties(contiguousFormulaRepresentation, actualResult);
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
    TEST_CASE("[Formula::Representation::Contiguous] variable properties", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationVariablePropertiesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentation(variableSet);
            printVariableProperties(contiguousFormulaRepresentation, variableSet, actualResult);

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
                    contiguousFormulaRepresentation.addLiteralToPartialAssignment(lit, freeVariableVector);

                    printVariableProperties(contiguousFormulaRepresentation, variableSet, actualResult);
                }

                // Remove assignment
                for (auto it = assignment.rbegin(); it != assignment.rend(); ++it) {
                    const LiteralType& lit = *it;
                    actualResult << "--------------------" << std::endl;
                    actualResult << "Remove: " << lit << std::endl;
                    actualResult << "--------------------" << std::endl
                                 << std::endl;

                    VariableVectorType freeVariableVector;
                    contiguousFormulaRepresentation.removeLiteralFromPartialAssignment(lit, freeVariableVector);

                    printVariableProperties(contiguousFormulaRepresentation, variableSet, actualResult);
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
    TEST_CASE("[Formula::Representation::Contiguous] literal properties", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationLiteralPropertiesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentation(variableSet);
            printLiteralProperties(contiguousFormulaRepresentation, actualResult);

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
                    contiguousFormulaRepresentation.addLiteralToPartialAssignment(lit, freeVariableVector);

                    printLiteralProperties(contiguousFormulaRepresentation, actualResult);
                }

                // Remove assignment
                for (auto it = assignment.rbegin(); it != assignment.rend(); ++it) {
                    const LiteralType& lit = *it;
                    actualResult << "--------------------" << std::endl;
                    actualResult << "Remove: " << lit << std::endl;
                    actualResult << "--------------------" << std::endl
                                 << std::endl;

                    VariableVectorType freeVariableVector;
                    contiguousFormulaRepresentation.removeLiteralFromPartialAssignment(lit, freeVariableVector);

                    printLiteralProperties(contiguousFormulaRepresentation, actualResult);
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
    TEST_CASE("[Formula::Representation::Contiguous] connected components", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationConnectedComponentsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForConnectedComponents(currentComponentVariableSet);
            printCurrentFormula(contiguousFormulaRepresentation, actualResult);

            LiteralType litPos1(1, true);
            LiteralType litNeg4(4, false);
            LiteralType litNeg9(9, false);

            ConnectedComponentType connectedComponents = contiguousFormulaRepresentation.computeConnectedComponents(currentComponentVariableSet);
            printConnectedComponents(connectedComponents, actualResult);

            actualResult << "Add: " << litPos1 << std::endl;
            currentComponentVariableSet.erase(1);
            VariableVectorType freeVariableVector;
            contiguousFormulaRepresentation.addLiteralToPartialAssignment(litPos1, freeVariableVector);

            connectedComponents = contiguousFormulaRepresentation.computeConnectedComponents(currentComponentVariableSet);
            printConnectedComponents(connectedComponents, actualResult);

            for (ConnectedComponentStruct& connectedComponentStruct : connectedComponents) {
                actualResult << "Set new component: ";
                for (VarT var : Hydra::Other::sortUnorderedSet(connectedComponentStruct.variableSet))
                    actualResult << std::to_string(var) << " ";
                actualResult << std::endl;

                contiguousFormulaRepresentation.setNewComponent(connectedComponentStruct, IgnorePureLiteralTypeEnum::NONE);
                printCurrentFormula(contiguousFormulaRepresentation, actualResult);

                // Component: 2 3 4 5
                if (Hydra::Other::containInSet<VarT>(connectedComponentStruct.variableSet, 4)) {
                    actualResult << "Add: " << litNeg4 << std::endl;
                    connectedComponentStruct.variableSet.erase(4);
                    contiguousFormulaRepresentation.addLiteralToPartialAssignment(litNeg4, freeVariableVector);

                    ConnectedComponentType connectedComponentsTmp = contiguousFormulaRepresentation.computeConnectedComponents(connectedComponentStruct.variableSet);
                    printConnectedComponents(connectedComponentsTmp, actualResult);

                    actualResult << "Remove: " << litNeg4 << std::endl;
                    connectedComponentStruct.variableSet.insert(4);
                    contiguousFormulaRepresentation.removeLiteralFromPartialAssignment(litNeg4, freeVariableVector);
                }

                // Component: 7 8 9 10 11
                if (Hydra::Other::containInSet<VarT>(connectedComponentStruct.variableSet, 9)) {
                    actualResult << "Add: " << litNeg9 << std::endl;
                    connectedComponentStruct.variableSet.erase(9);
                    contiguousFormulaRepresentation.addLiteralToPartialAssignment(litNeg9, freeVariableVector);

                    ConnectedComponentType connectedComponentsTmp = contiguousFormulaRepresentation.computeConnectedComponents(connectedComponentStruct.variableSet);
                    printConnectedComponents(connectedComponentsTmp, actualResult);

                    actualResult << "Remove: " << litNeg9 << std::endl;
                    connectedComponentStruct.variableSet.insert(9);
                    contiguousFormulaRepresentation.removeLiteralFromPartialAssignment(litNeg9, freeVariableVector);
                }

                actualResult << "Pop previous component" << std::endl;
                contiguousFormulaRepresentation.popPreviousComponent(connectedComponentStruct, {});
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
    TEST_CASE("[Formula::Representation::Contiguous] variable properties (get current clauses)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationVariablePropertiesGetCurrentClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentation(variableSet);

            ClauseIdReusableVectorType clauseIdReusableVector(contiguousFormulaRepresentation.getNumberOfOriginalClauses());

            std::vector<VariableVectorType> variableVectorVector { { 1 }, { 1, 7 }, { 2, 4 }, { 3, 2 }, { 6, 7 } };

            for (const VariableVectorType& variableVector : variableVectorVector) {
                actualResult << "Variables: ";
                for (VarT var : variableVector)
                    actualResult << std::to_string(var) << " ";
                actualResult << std::endl;

                contiguousFormulaRepresentation.getCurrentClauses(variableSet, variableVector, clauseIdReusableVector, VectorSetType());
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
    TEST_CASE("[Formula::Representation::Contiguous] pure literals", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationPureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForPureLiterals(variableSet);
            printCurrentFormula(contiguousFormulaRepresentation, actualResult);

            for (VarT var : Hydra::Other::sortUnorderedSet(variableSet)) {
                actualResult << std::to_string(var) << std::endl;

                actualResult << "is pure literal: " << std::to_string(contiguousFormulaRepresentation.isPureLiteralInCurrentFormula(var)) << std::endl;
                actualResult << "is positive pure literal: " << std::to_string(contiguousFormulaRepresentation.isPositivePureLiteralInCurrentFormula(var)) << std::endl;
                actualResult << "is negative pure literal: " << std::to_string(contiguousFormulaRepresentation.isNegativePureLiteralInCurrentFormula(var)) << std::endl;
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
    TEST_CASE("[Formula::Representation::Contiguous] not duplicate clauses", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationNotDuplicateClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForDuplicateClauses(variableSet);
            printClauses(contiguousFormulaRepresentation, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(contiguousFormulaRepresentation.getNumberOfOriginalClauses());
            contiguousFormulaRepresentation.getCurrentComponentNotDuplicateClauses(variableSet, clauseIdReusableVector, false, true);
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
    TEST_CASE("[Formula::Representation::Contiguous] not duplicate clauses (assignment)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationNotDuplicateClausesAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForDuplicateClauses(variableSet);

            VariableVectorType tmp;
            contiguousFormulaRepresentation.addLiteralToPartialAssignment(LiteralType(5, false), tmp);

            printClauses(contiguousFormulaRepresentation, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(contiguousFormulaRepresentation.getNumberOfOriginalClauses());
            contiguousFormulaRepresentation.getCurrentComponentNotDuplicateClauses(variableSet, clauseIdReusableVector, false, true);
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
    TEST_CASE("[Formula::Representation::Contiguous] not duplicate clauses - variables", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationNotDuplicateClausesVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForDuplicateClauses(variableSet);
            printClauses(contiguousFormulaRepresentation, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(contiguousFormulaRepresentation.getNumberOfOriginalClauses());
            contiguousFormulaRepresentation.getCurrentComponentNotDuplicateClauses(variableSet, clauseIdReusableVector, true, true);
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
    TEST_CASE("[Formula::Representation::Contiguous] not duplicate clauses - variables (assignment)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationNotDuplicateClausesVariablesAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForDuplicateClauses(variableSet);

            VariableVectorType tmp;
            contiguousFormulaRepresentation.addLiteralToPartialAssignment(LiteralType(5, false), tmp);

            printClauses(contiguousFormulaRepresentation, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(contiguousFormulaRepresentation.getNumberOfOriginalClauses());
            contiguousFormulaRepresentation.getCurrentComponentNotDuplicateClauses(variableSet, clauseIdReusableVector, true, true);
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
    TEST_CASE("[Formula::Representation::Contiguous] pure clauses (ignore positive pure literals)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationPureClausesIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForPureClauses(variableSet);
            processPureClauses(contiguousFormulaRepresentation, { 1, 7 },
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
    TEST_CASE("[Formula::Representation::Contiguous] pure clauses (ignore negative pure literals)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationPureClausesIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForPureClauses(variableSet);
            processPureClauses(contiguousFormulaRepresentation, { 0, 9 },
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
    TEST_CASE("[Formula::Representation::Contiguous] pure clauses (ignore pure literals)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationPureClausesIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForPureClauses(variableSet);
            processPureClauses(contiguousFormulaRepresentation, { 0, 1, 3, 5, 6, 7, 9 },
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
    TEST_CASE("[Formula::Representation::Contiguous] connected components (ignore positive pure literals)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationConnectedComponentsIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForConnectedComponentPositivePureVariables(variableSet);
            printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult);

            ClauseIdSetType pureClauseSet;
            ConnectedComponentType connectedComponents = contiguousFormulaRepresentation.computeConnectedComponents(variableSet, pureClauseSet,
                                                                                                                    IgnorePureLiteralTypeEnum::ONLY_POSITIVE);

            printPureClauses(pureClauseSet, actualResult);
            printConnectedComponents(connectedComponents, actualResult, true);
            printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult);
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
    TEST_CASE("[Formula::Representation::Contiguous] connected components (ignore negative pure literals)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationConnectedComponentsIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForConnectedComponentNegativePureVariables(variableSet);
            printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult);

            ClauseIdSetType pureClauseSet;
            ConnectedComponentType connectedComponents = contiguousFormulaRepresentation.computeConnectedComponents(variableSet, pureClauseSet,
                                                                                                                    IgnorePureLiteralTypeEnum::ONLY_NEGATIVE);

            printPureClauses(pureClauseSet, actualResult);
            printConnectedComponents(connectedComponents, actualResult, true);
            printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult);
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
    TEST_CASE("[Formula::Representation::Contiguous] connected components (ignore pure literals)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationConnectedComponentsIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForConnectedComponentPositivePureVariables(variableSet);
            printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult);

            ClauseIdSetType pureClauseSet;
            ConnectedComponentType connectedComponents = contiguousFormulaRepresentation.computeConnectedComponents(variableSet, pureClauseSet,
                                                                                                                    IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE);

            printPureClauses(pureClauseSet, actualResult);
            printConnectedComponents(connectedComponents, actualResult, true);
            printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult);
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
    TEST_CASE("[Formula::Representation::Contiguous] sort variables based on clause reduction heuristic (ascending)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationSortVariablesBasedOnClauseReductionHeuristicAscendingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForSortVariablesBasedOnClauseReductionHeuristic(variableSet);
            printCurrentFormula(contiguousFormulaRepresentation, actualResult);

            VariableReusableVectorType variableOrder(contiguousFormulaRepresentation.getNumberOfVariablesInOriginalFormula());
            variableOrder.copySet(variableSet);

            contiguousFormulaRepresentation.sortVariablesBasedOnClauseReductionHeuristic(variableSet, variableOrder, true);

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
    TEST_CASE("[Formula::Representation::Contiguous] sort variables based on clause reduction heuristic (descending)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationSortVariablesBasedOnClauseReductionHeuristicDescendingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForSortVariablesBasedOnClauseReductionHeuristic(variableSet);
            printCurrentFormula(contiguousFormulaRepresentation, actualResult);

            VariableReusableVectorType variableOrder(contiguousFormulaRepresentation.getNumberOfVariablesInOriginalFormula());
            variableOrder.copySet(variableSet);

            contiguousFormulaRepresentation.sortVariablesBasedOnClauseReductionHeuristic(variableSet, variableOrder, false);

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
    TEST_CASE("[Formula::Representation::Contiguous] save current component formula", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationSaveCurrentComponentFormulaResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForSortVariablesBasedOnClauseReductionHeuristic(currentComponentVariableSet);

            processSaveCurrentComponentFormulaToVector(contiguousFormulaRepresentation, currentComponentVariableSet, actualResult);
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
    TEST_CASE("[Formula::Representation::Contiguous] save current component formula (one clause)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationSaveCurrentComponentFormulaOneClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationWithOneClause(currentComponentVariableSet);

            processSaveCurrentComponentFormulaToVector(contiguousFormulaRepresentation, currentComponentVariableSet, actualResult);
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
    TEST_CASE("[Formula::Representation::Contiguous] save current component formula (pure clauses)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationSaveCurrentComponentFormulaPureClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForPureClauses(currentComponentVariableSet);

            // Remove pure clauses
            ClauseIdSetType pureClauseSet = { 0, 1, 3, 5, 6, 7, 9 };
            contiguousFormulaRepresentation.removeClausesContainingOnlyPureLiteralsOfIgnoredType(pureClauseSet,
                                                                                                 IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE);

            processSaveCurrentComponentFormulaToVector(contiguousFormulaRepresentation, currentComponentVariableSet, actualResult);
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
    TEST_CASE("[Formula::Representation::Contiguous] save current component formula (assignment)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationSaveCurrentComponentFormulaAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForConnectedComponents(currentComponentVariableSet);

            // Assign x_1, -x_6
            VariableVectorType tmp;
            currentComponentVariableSet.erase((VarT)1);
            currentComponentVariableSet.erase((VarT)6);
            contiguousFormulaRepresentation.addLiteralVectorToPartialAssignment({ LiteralType(1, true), LiteralType(6, false) }, tmp);

            processSaveCurrentComponentFormulaToVectorConnectedComponents(contiguousFormulaRepresentation, currentComponentVariableSet,
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
    TEST_CASE("[Formula::Representation::Contiguous] save current component formula (ignore positive pure literals)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationSaveCurrentComponentFormulaIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForConnectedComponentPositivePureVariables(currentComponentVariableSet);

            processSaveCurrentComponentFormulaToVectorConnectedComponents(contiguousFormulaRepresentation, currentComponentVariableSet,
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
    TEST_CASE("[Formula::Representation::Contiguous] save current component formula (ignore negative pure literals)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationSaveCurrentComponentFormulaIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForConnectedComponentNegativePureVariables(currentComponentVariableSet);

            processSaveCurrentComponentFormulaToVectorConnectedComponents(contiguousFormulaRepresentation, currentComponentVariableSet,
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
    TEST_CASE("[Formula::Representation::Contiguous] save current component formula (ignore pure literals)", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationSaveCurrentComponentFormulaIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForConnectedComponentPositivePureVariables(currentComponentVariableSet);

            processSaveCurrentComponentFormulaToVectorConnectedComponents(contiguousFormulaRepresentation, currentComponentVariableSet,
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
    TEST_CASE("[Formula::Representation::Contiguous] save formula defined by clauses", "[Formula::Representation::Contiguous]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationSaveFormulaDefinedByClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            ContiguousFormulaRepresentationType contiguousFormulaRepresentation = createContiguousFormulaRepresentationForSortVariablesBasedOnClauseReductionHeuristic(currentComponentVariableSet);

            std::vector<ClauseIdReusableVectorType> clausesReusableVector;
            std::vector<ClauseIdVectorType> clausesVector = { { 0 }, { 1 }, { 2 }, { 3 }, { 4 }, { 5 }, { 0, 2, 4 }, { 1, 3, 5 }, { 0, 1, 2, 3, 4, 5 } };

            for (const ClauseIdVectorType& clauseIdVector : clausesVector) {
                clausesReusableVector.emplace_back(contiguousFormulaRepresentation.getNumberOfOriginalClauses());

                for (ClauseIdT clauseId : clauseIdVector)
                    clausesReusableVector.back().emplace_back(clauseId);
            }

            for (const ClauseIdReusableVectorType& clauseReusableVector : clausesReusableVector) {
                processSaveFormulaDefinedByClausesToVector(contiguousFormulaRepresentation, clauseReusableVector, actualResult);
                actualResult << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Formula::Representation::Contiguous
