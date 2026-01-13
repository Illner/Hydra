#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/circuit/node/NodeTestResult.hpp"

#include "Hydra/circuit/Circuit.hpp"
#include "Hydra/circuit/node/NodeAbstract.hpp"
#include "Hydra/circuit/node/innerNode/AndInnerNode.hpp"
#include "Hydra/circuit/node/innerNode/BinaryOrInnerNode.hpp"
#include "Hydra/circuit/node/innerNode/OrInnerNode.hpp"
#include "Hydra/circuit/node/leafNode/ConstantLeaf.hpp"
#include "Hydra/circuit/node/leafNode/LiteralLeaf.hpp"
#include "Hydra/circuit/node/leafNode/formulaLeaf/KromCLeaf.hpp"
#include "Hydra/circuit/node/leafNode/formulaLeaf/RenHCLeaf.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/Other.hpp"

namespace HydraTest::Circuit::Node {

    //region Types
    using OriginalVarType = Hydra::Formula::OriginalVarType;

    using VarT = char8_t;
    using LiteralT = char8_t;

    using LiteralType = typename Hydra::Circuit::Node::NodeAbstract<VarT, LiteralT>::LiteralType;
    using ClauseType = typename Hydra::Circuit::Node::FormulaLeafAbstract<VarT, LiteralT>::ClauseType;
    using FormulaType = typename Hydra::Circuit::Node::FormulaLeafAbstract<VarT, LiteralT>::FormulaType;
    using VariableSetType = typename Hydra::Circuit::Node::NodeAbstract<VarT, LiteralT>::VariableSetType;
    using LiteralVectorType = typename Hydra::Circuit::Node::NodeAbstract<VarT, LiteralT>::LiteralVectorType;
    using ClauseVectorType = typename Hydra::Circuit::Node::FormulaLeafAbstract<VarT, LiteralT>::FormulaType;
    using VariableVectorType = typename Hydra::Circuit::Node::NodeAbstract<VarT, LiteralT>::VariableSortedVectorType;
    using PartialAssignmentType = typename Hydra::Circuit::Node::NodeAbstract<VarT, LiteralT>::PartialAssignmentType;
    using MappingFromVariableToLiteralType = typename Hydra::Circuit::Node::NodeAbstract<VarT, LiteralT>::MappingFromVariableToLiteralType;
    using MappingFromVariableToVariableType = typename Hydra::Circuit::Node::NodeAbstract<VarT, LiteralT>::MappingFromVariableToVariableType;
    using MappingFromVariableToOriginalVariableType = typename Hydra::Circuit::Node::NodeAbstract<VarT, LiteralT>::MappingFromVariableToOriginalVariableType;

    using ClauseStatusEnum = Hydra::Formula::ClauseStatusEnum;
    using FormulaStatusEnum = Hydra::Formula::FormulaStatusEnum;
    using DecomposabilityTypeEnum = Hydra::Circuit::Node::DecomposabilityTypeEnum;
    using ClauseStatusWatchedLiteralEnum = Hydra::Formula::ClauseStatusWatchedLiteralEnum;

    using RenHCLeafType = Hydra::Circuit::Node::RenHCLeaf<VarT, LiteralT>;
    using KromCLeafType = Hydra::Circuit::Node::KromCLeaf<VarT, LiteralT>;
    using LiteralLeafType = Hydra::Circuit::Node::LiteralLeaf<VarT, LiteralT>;
    using OrInnerNodeType = Hydra::Circuit::Node::OrInnerNode<VarT, LiteralT>;
    using NodeAbstractType = Hydra::Circuit::Node::NodeAbstract<VarT, LiteralT>;
    using ConstantLeafType = Hydra::Circuit::Node::ConstantLeaf<VarT, LiteralT>;
    using LeafAbstractType = Hydra::Circuit::Node::LeafAbstract<VarT, LiteralT>;
    using AndInnerNodeType = Hydra::Circuit::Node::AndInnerNode<VarT, LiteralT>;
    using FormulaLeafType = Hydra::Circuit::Node::FormulaLeafAbstract<VarT, LiteralT>;
    using BinaryOrInnerNodeType = Hydra::Circuit::Node::BinaryOrInnerNode<VarT, LiteralT>;
    //endregion

    //region Functions
    void printNode(NodeAbstractType& node, std::stringstream& actualResult) {
        node.printNodeDebug(actualResult);
        actualResult << node;
    }

    void printClause(ClauseType& clause, std::stringstream& actualResult) {
        actualResult << "Clause size: " << std::to_string(clause.getClauseSize()) << std::endl;
        actualResult << clause;
        clause.printClauseDebug(actualResult);
        actualResult << std::endl;
    }

    void printMapping(const MappingFromVariableToOriginalVariableType& mapping, std::stringstream& actualResult) {
        VariableVectorType keyVectorTmp = Hydra::Other::extractKeysFromMap(mapping, true);
        for (VarT var : keyVectorTmp)
            actualResult << std::to_string(var) << " -> " << mapping.at(var) << " ";
        actualResult << std::endl;
    }
    //endregion

    #if defined(BELLA_COMPILER)
    /**
     * Literal leaves and constant leaves
     */
    TEST_CASE("[Circuit::Node] leaves", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeLeavesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            // Literal leaves
            LiteralType litPos1(1, true);
            LiteralLeafType literalLeafPos1(1, litPos1);
            printNode(literalLeafPos1, actualResult);

            LiteralType litNeg1(1, false);
            LiteralLeafType literalLeafNeg1(1, litNeg1);
            printNode(literalLeafNeg1, actualResult);

            LiteralType litPos2(2, true);
            LiteralLeafType literalLeafPos2(1, litPos2);
            printNode(literalLeafPos2, actualResult);

            LiteralType litNeg2(2, false);
            LiteralLeafType literalLeafNeg2(1, litNeg2);
            printNode(literalLeafNeg2, actualResult);

            // Constant leaves
            ConstantLeafType constantLeafTrue(1, true);
            printNode(constantLeafTrue, actualResult);

            ConstantLeafType constantLeafFalse(1, false);
            printNode(constantLeafFalse, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Literal leaves (mapping)
     */
    TEST_CASE("[Circuit::Node] literal leaves (mapping)", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeLiteralLeavesMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos(1, true);
            LiteralType litNeg(1, false);

            std::vector<MappingFromVariableToOriginalVariableType> mappingVector { {}, { { (VarT)1, (OriginalVarType)1 } }, { { (VarT)1, (OriginalVarType)2 } }, { { (VarT)2, (OriginalVarType)3 } } };

            for (const MappingFromVariableToOriginalVariableType& mapping : mappingVector) {
                actualResult << "Mapping: ";
                printMapping(mapping, actualResult);

                actualResult << litPos << ": ";
                litPos.printLiteral(actualResult, mapping);
                actualResult << std::endl;

                actualResult << litNeg << ": ";
                litNeg.printLiteral(actualResult, mapping);
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
     * Clauses (constructor)
     */
    TEST_CASE("[Circuit::Node] clauses (constructor)", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeClausesConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            actualResult << "Empty clause: " << std::endl;
            ClauseType clause1;
            printClause(clause1, actualResult);

            LiteralType lit1(1, true);
            LiteralType lit2(2, false);

            actualResult << "Add a literal to the clause: " << std::endl;
            clause1 += lit2;
            printClause(clause1, actualResult);

            actualResult << "Copy constructor: " << std::endl;
            ClauseType clause2(clause1);
            clause1 += std::move(lit1);
            actualResult << "Clause 1: " << std::endl;
            printClause(clause1, actualResult);
            actualResult << "Clause 2: " << std::endl;
            printClause(clause2, actualResult);

            actualResult << "Move constructor: " << std::endl;
            ClauseType clause3(std::move(clause1));
            printClause(clause3, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clauses (copy and move)
     */
    TEST_CASE("[Circuit::Node] clauses (copy and move)", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeClausesCopyAndMoveResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType lit1(1, true);
            LiteralType lit2(2, false);
            LiteralType lit3(3, true);
            LiteralType lit4(4, false);

            ClauseType clause1({ lit1, lit2, lit3 });
            actualResult << "clause1: " << clause1 << std::endl;

            actualResult << "Copy method" << std::endl;
            ClauseType clause2 = clause1;
            clause2 += lit4;
            actualResult << "clause1: " << clause1 << std::endl;
            actualResult << "clause2: " << clause2 << std::endl;

            actualResult << "Move method" << std::endl;
            ClauseType clause3 = std::move(clause1);
            actualResult << "clause3: " << clause3 << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clauses (operator - modification)
     */
    TEST_CASE("[Circuit::Node] clauses (operator - modification)", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeClausesOperatorModificationResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg3(3, false);

            ClauseType clause1;
            clause1.addLiteral(litPos1);

            actualResult << "Multi-occurrent literal = false: " << std::endl;
            clause1.addLiteral(litPos1, false);
            printClause(clause1, actualResult);

            actualResult << "Multi-occurrent literal = true: " << std::endl;
            clause1.addLiteral(litPos1, true);
            printClause(clause1, actualResult);

            actualResult << "+= (copy): " << std::endl;
            clause1 += litPos2;
            printClause(clause1, actualResult);

            actualResult << "+= (move): " << std::endl;
            clause1 += std::move(litNeg3);
            printClause(clause1, actualResult);

            ClauseType clause2;
            clause2 += litNeg1;
            actualResult << "Clause = Clause + Literal (exists): " << std::endl;
            ClauseType clause3 = clause2 + litNeg1;
            printClause(clause3, actualResult);

            actualResult << "Clause = Clause + Literal (does not exist): " << std::endl;
            ClauseType clause4 = clause2 + litPos2;
            printClause(clause4, actualResult);

            ClauseType clause5;
            clause5 += litPos1;
            clause5 += litPos2;
            ClauseType clause6;
            clause6 += litPos1;
            clause6 += litNeg1;

            actualResult << "Clause = Clause + Clause: " << std::endl;
            ClauseType clause7 = clause5 + clause6;
            printClause(clause7, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clauses (operator)
     */
    TEST_CASE("[Circuit::Node] clauses (operator)", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeClausesOperatorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg3(3, false);

            ClauseType clause0;
            ClauseType clause1({ litPos1 });
            ClauseType clause2({ litNeg1 });
            ClauseType clause3({ litPos1, litPos2 });
            ClauseType clause4({ litPos1, litNeg3 });
            ClauseType clause5({ litPos1, litNeg3 });

            ClauseVectorType clauseVector({ std::move(clause0), clause1, std::move(clause2),
                                            clause3, std::move(clause4), clause5 });

            // Print clause
            for (std::size_t i = 0; i < clauseVector.size(); ++i) {
                clauseVector[i].sortClauseDebug();
                actualResult << "Clause" << i << ": " << clauseVector[i];
            }

            // Operators
            for (std::size_t i = 0; i < clauseVector.size() - 1; ++i) {
                for (std::size_t j = i + 1; j < clauseVector.size(); ++j) {
                    actualResult << "Clause" << i << " == "
                                 << "clause" << j << ": " << (clauseVector[i] == clauseVector[j]) << std::endl;
                    actualResult << "Clause" << i << " != "
                                 << "clause" << j << ": " << (clauseVector[i] != clauseVector[j]) << std::endl;
                    actualResult << "Clause" << i << " < "
                                 << "clause" << j << ": " << (clauseVector[i] < clauseVector[j]) << std::endl;
                    actualResult << "Clause" << i << " > "
                                 << "clause" << j << ": " << (clauseVector[i] > clauseVector[j]) << std::endl;
                }
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clauses (property)
     */
    TEST_CASE("[Circuit::Node] clauses (property)", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeClausesPropertyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg2(2, false);
            LiteralType litNeg3(3, false);
            LiteralType litPos4(4, true);

            ClauseType clause0;
            ClauseType clause1({ litPos1 });
            ClauseType clause2({ litPos1, litNeg2 });
            ClauseType clause3({ litPos1, litNeg2, litNeg3 });
            ClauseType clause4({ litPos1, litNeg2, litNeg3, litPos4 });

            ClauseVectorType clauseVector({ clause0, std::move(clause1), clause2,
                                            std::move(clause3), clause4 });

            // Print clause
            for (std::size_t i = 0; i < clauseVector.size(); ++i) {
                actualResult << "Clause" << i << ": " << clauseVector[i];
            }

            // Krom
            for (std::size_t i = 0; i < clauseVector.size(); ++i) {
                actualResult << "Clause" << i << " is Krom: " << clauseVector[i].clauseHasAtMostTwoLiterals() << std::endl;
            }

            // Horn
            for (std::size_t i = 0; i < clauseVector.size(); ++i) {
                actualResult << "Clause" << i << " is Horn: " << clauseVector[i].clauseIsHorn() << std::endl;
            }

            // RenH
            std::vector<VariableSetType> switchedVariablesVector({ {}, { 1 }, { 2 }, { 1, 4 }, { 1, 3 } });

            std::size_t clauseRenHCIndex = 4;
            for (const VariableSetType& switchedVariables : switchedVariablesVector) {
                actualResult << "Clause" << clauseRenHCIndex << " is renH (switched variables:";

                VariableVectorType variableVectorTemp = Hydra::Other::sortUnorderedSet(switchedVariables);
                for (VarT var : variableVectorTemp)
                    actualResult << " " << std::to_string(var);

                actualResult << "): " << clauseVector[clauseRenHCIndex].clauseIsRenamableHorn(switchedVariables) << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clauses (watched literals)
     */
    TEST_CASE("[Circuit::Node] clauses (watched literals)", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeClausesWatchedLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);
            LiteralType litNeg3(3, false);
            LiteralType litPos4(4, true);

            ClauseType clause0;
            ClauseType clause1({ litPos1 });
            ClauseType clause2({ litPos1, litNeg2 });
            ClauseType clause3({ litPos1, litNeg2, litNeg3 });
            ClauseType clause4({ litPos1, litNeg2, litNeg3, litPos4 });

            ClauseVectorType clauseVector({ std::move(clause0), clause1, std::move(clause2),
                                            clause3, std::move(clause4) });

            std::vector<PartialAssignmentType> partialAssignmentVector;
            std::vector<LiteralVectorType> tmp { {}, { litNeg1 }, { litPos1 }, { litNeg3 }, { litPos3 }, { litNeg1, litNeg2 }, { litNeg1, litPos2 } };
            for (const LiteralVectorType& literalVector : tmp) {
                PartialAssignmentType partialAssignmentTmp(literalVector, 3);
                partialAssignmentVector.push_back(partialAssignmentTmp);
            }

            for (ClauseType& clause : clauseVector) {
                for (const PartialAssignmentType& partialAssignment : partialAssignmentVector) {
                    actualResult << "Clause: " << clause;
                    actualResult << "Partial assignment: " << partialAssignment << std::endl;

                    actualResult << "Initialized watched literals: ";
                    clause.printWatchedLiterals(actualResult);
                    actualResult << std::endl;

                    ClauseStatusWatchedLiteralEnum clauseStatusWatchedLiteral = clause.updateWatchedLiterals(partialAssignment);
                    actualResult << "Clause status: " << Hydra::Formula::clauseStatusWatchedLiteralEnumToString(clauseStatusWatchedLiteral) << std::endl;

                    actualResult << "Watched literals after: ";
                    clause.printWatchedLiterals(actualResult);
                    actualResult << std::endl;

                    actualResult << std::endl;
                }
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clauses (status)
     */
    TEST_CASE("[Circuit::Node] clauses (status)", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeClausesStatusResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);
            LiteralType litNeg3(3, false);

            ClauseType clause0;
            ClauseType clause1({ litPos1 });
            ClauseType clause2({ litPos1, litNeg2 });

            ClauseVectorType clauseVector({ std::move(clause0), clause1, std::move(clause2) });

            std::vector<PartialAssignmentType> partialAssignmentVector;
            std::vector<LiteralVectorType> tmp { {}, { litNeg1 }, { litPos1 }, { litNeg3 }, { litPos3 }, { litNeg1, litNeg2 }, { litNeg1, litPos2 } };
            for (const LiteralVectorType& literalVector : tmp) {
                PartialAssignmentType partialAssignmentTmp(literalVector, 3);
                partialAssignmentVector.push_back(partialAssignmentTmp);
            }

            for (const ClauseType& clause : clauseVector) {
                for (const PartialAssignmentType& partialAssignment : partialAssignmentVector) {
                    actualResult << "Clause: " << clause;
                    actualResult << "Partial assignment: " << partialAssignment << std::endl;

                    ClauseStatusEnum clauseStatus = clause.getClauseStatus(partialAssignment);
                    actualResult << "Status: " << Hydra::Formula::clauseStatusEnumToString(clauseStatus) << std::endl;
                    actualResult << std::endl;
                }
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clauses (mapping)
     */
    TEST_CASE("[Circuit::Node] clauses (mapping)", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeClausesMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);

            ClauseType clause0;
            ClauseType clause1({ litPos1 });
            ClauseType clause2({ litNeg1, litPos2 });

            ClauseVectorType clauseVector({ std::move(clause0), clause1, std::move(clause2) });

            std::vector<MappingFromVariableToOriginalVariableType> mappingVector { {}, { { (VarT)1, (OriginalVarType)1 }, { (VarT)2, (OriginalVarType)2 } }, { { (VarT)1, (OriginalVarType)2 }, { (VarT)2, (OriginalVarType)1 } }, { { (VarT)1, (OriginalVarType)3 }, { (VarT)2, (OriginalVarType)4 } } };

            for (const ClauseType& clause : clauseVector) {
                for (const MappingFromVariableToOriginalVariableType& mapping : mappingVector) {
                    actualResult << "Clause: " << clause;

                    actualResult << "Mapping: ";
                    printMapping(mapping, actualResult);

                    clause.printClause(actualResult, mapping);
                    actualResult << std::endl;
                }
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clauses (copy)
     */
    TEST_CASE("[Circuit::Node] clauses (copy)", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeClausesCopyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);
            LiteralType litNeg3(3, false);

            ClauseType clause0;
            ClauseType clause1({ litPos1 });
            ClauseType clause2({ litNeg1, litPos2 });
            ClauseType clause3({ litPos1, litPos2, litPos3 });
            ClauseType clause4({ litNeg1, litNeg2, litNeg3 });
            ClauseType clause5({ litPos1, litPos2, litNeg3 });
            ClauseType clause6({ litNeg1, litNeg2, litPos3 });

            ClauseVectorType clauseVector({ std::move(clause0), std::move(clause1), std::move(clause2),
                                            std::move(clause3), std::move(clause4), std::move(clause5), std::move(clause6) });

            std::vector<MappingFromVariableToLiteralType> mappingVector { { { (VarT)1, litPos1 }, { (VarT)2, litPos2 }, { (VarT)3, litPos3 } },
                                                                          { { (VarT)1, litNeg1 }, { (VarT)2, litNeg2 }, { (VarT)3, litNeg3 } },
                                                                          { { (VarT)1, litPos1 }, { (VarT)2, litNeg2 }, { (VarT)3, litPos3 } },

                                                                          { { (VarT)1, litPos3 }, { (VarT)2, litPos2 }, { (VarT)3, litPos1 } },
                                                                          { { (VarT)1, litNeg3 }, { (VarT)2, litNeg2 }, { (VarT)3, litNeg1 } },
                                                                          { { (VarT)1, litNeg3 }, { (VarT)2, litPos2 }, { (VarT)3, litNeg1 } } };

            for (const MappingFromVariableToLiteralType& mapping : mappingVector) {
                actualResult << "Mapping: " << std::endl;
                VariableVectorType keyVectorTmp = Hydra::Other::extractKeysFromMap(mapping, true);
                for (VarT var : keyVectorTmp)
                    actualResult << "\t" << std::to_string(var) << " -> " << mapping.at(var) << std::endl;
                actualResult << std::endl;

                for (const ClauseType& clause : clauseVector) {
                    actualResult << "Clause: " << clause;

                    ClauseType mappedClause = clause.copyClause(mapping);
                    actualResult << "Mapped clause: " << mappedClause << std::endl;
                }
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Formula (constructor)
     */
    TEST_CASE("[Circuit::Node] formula (constructor)", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeFormulaConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        auto printFormulaLambda = [&actualResult](FormulaLeafType& formulaLeaf) {
            formulaLeaf.printFormulaDebug(actualResult);
            actualResult << std::endl;
            formulaLeaf.printFormulaInDimacsCnfFormat(actualResult, {}, formulaLeaf.getNumberOfVariables());

            std::pair<MappingFromVariableToVariableType, MappingFromVariableToVariableType> mapping = formulaLeaf.getVariableMapping();
            MappingFromVariableToVariableType& mappingFromIndexToVar = std::get<1>(mapping);

            actualResult << "Mapping (index -> Var): ";
            for (VarT i = 1; i <= mappingFromIndexToVar.size(); ++i)
                actualResult << std::to_string(i) << " -> " << std::to_string(mappingFromIndexToVar[i]) << ", ";
            actualResult << std::endl;
        };

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg3(3, false);

            ClauseType clause0({ litPos1 });
            ClauseType clause1({ litNeg1, litPos2 });
            ClauseType clause2({ litPos1, litNeg3 });
            ClauseType clause3({ litPos1, litPos2 });

            std::vector<FormulaType> formulaVector { { clause0 }, { clause0, clause1 } };

            actualResult << "Copy constructor: " << std::endl;
            for (const FormulaType& formula : formulaVector) {
                KromCLeafType formulaLeaf(1, formula);
                printFormulaLambda(formulaLeaf);
            }

            actualResult << "Move constructor: " << std::endl;
            KromCLeafType formulaLeaf(1, { clause0, clause1, clause2, clause3 });
            printFormulaLambda(formulaLeaf);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Formula (status)
     */
    TEST_CASE("[Circuit::Node] formula (status)", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeFormulaStatusResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);
            LiteralType litNeg3(3, false);

            ClauseType clause0({ litPos1 });
            ClauseType clause1({ litNeg1, litPos2 });
            ClauseType clause2({ litNeg1, litNeg2, litNeg3 });

            RenHCLeafType formulaLeaf(0, { std::move(clause0), clause1, std::move(clause2) }, {});
            formulaLeaf.printFormulaInDimacsCnfFormat(actualResult, {}, formulaLeaf.getNumberOfVariables());
            actualResult << std::endl;

            std::vector<PartialAssignmentType> partialAssignmentVector;
            std::vector<LiteralVectorType> tmp { {}, { litPos1 }, { litNeg1 }, { litPos1, litPos2 }, { litPos1, litPos2, litNeg3 }, { litPos1, litPos2, litPos3 } };
            for (const LiteralVectorType& literalVector : tmp) {
                PartialAssignmentType partialAssignmentTmp(literalVector, 3);
                partialAssignmentVector.push_back(partialAssignmentTmp);
            }

            for (const PartialAssignmentType& partialAssignment : partialAssignmentVector) {
                actualResult << "Partial assignment: " << partialAssignment << std::endl;

                FormulaStatusEnum formulaStatus = formulaLeaf.getFormulaStatus(partialAssignment);
                actualResult << "Status: " << Hydra::Formula::formulaStatusEnumToString(formulaStatus) << std::endl;
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
     * Formula (unit propagation)
     */
    TEST_CASE("[Circuit::Node] formula (unit propagation)", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeFormulaUnitPropagationResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);
            LiteralType litNeg3(3, false);

            ClauseType clause0({ litPos1 });
            ClauseType clause1({ litNeg1, litPos2 });
            ClauseType clause2({ litNeg1, litNeg2, litNeg3 });
            ClauseType clause3({ litNeg1, litPos2 });
            ClauseType clause4({ litNeg2, litPos3 });

            std::vector<FormulaType> formulaVector { { clause0 }, { clause0, clause1, clause2 }, { clause3, clause4 } };

            std::vector<PartialAssignmentType> partialAssignmentVector;
            std::vector<LiteralVectorType> tmp { {}, { litPos1 }, { litNeg1 }, { litPos2 }, { litNeg2 }, { litPos1, litNeg3 }, { litNeg3 } };
            for (const LiteralVectorType& literalVector : tmp) {
                PartialAssignmentType partialAssignmentTmp(literalVector, 3);
                partialAssignmentVector.push_back(partialAssignmentTmp);
            }

            for (const FormulaType& formula : formulaVector) {
                RenHCLeafType formulaLeaf(0, formula, {});
                formulaLeaf.printFormulaInDimacsCnfFormat(actualResult, {}, formulaLeaf.getNumberOfVariables());
                actualResult << std::endl;

                for (const PartialAssignmentType& partialAssignment : partialAssignmentVector) {
                    PartialAssignmentType partialAssignmentVectorCopy = partialAssignment;

                    actualResult << "Partial assignment (before unit propagation): " << partialAssignmentVectorCopy << std::endl;

                    bool isConsistent = formulaLeaf.unitPropagation(partialAssignmentVectorCopy);
                    actualResult << "Is consistent after unit propagation: " << isConsistent << std::endl;

                    actualResult << "Partial assignment (after unit propagation): " << partialAssignmentVectorCopy << std::endl;
                    actualResult << std::endl;
                }

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
     * Krom-C leaf
     */
    TEST_CASE("[Circuit::Node] Krom-C leaf", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeKromCLeafResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg3(3, false);

            ClauseType clause0({ litPos1 });
            ClauseType clause1({ litNeg1, litPos2 });
            ClauseType clause2({ litPos1, litNeg3 });
            ClauseType clause3({ litNeg1, litPos2, litNeg3 });

            std::vector<FormulaType> formulaVector { { clause0 }, { clause0, clause1 }, { clause0, clause1, clause2 }, { clause0, clause1, clause2, clause3 } };

            for (const FormulaType& formula : formulaVector) {
                try {
                    KromCLeafType kromCLeaf(1, formula);
                    printNode(kromCLeaf, actualResult);
                }
                catch (const Hydra::Exception::CompilerException& e) {
                    actualResult << e.what() << std::endl;
                }

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
     * Krom-C leaf (mapping)
     */
    TEST_CASE("[Circuit::Node] Krom-C leaf (mapping)", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeKromCLeafMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg3(3, false);

            ClauseType clause0({ litPos1 });
            ClauseType clause1({ litNeg1, litPos2 });
            ClauseType clause2({ litPos1, litNeg3 });

            std::vector<FormulaType> formulaVector { { clause0 }, { clause0, clause1 }, { clause0, clause1, clause2 } };

            std::vector<MappingFromVariableToOriginalVariableType> mappingVector { {},
                                                                                   { { (VarT)1, (OriginalVarType)1 }, { (VarT)2, (OriginalVarType)2 }, { (VarT)3, (OriginalVarType)3 } },
                                                                                   { { (VarT)1, (OriginalVarType)2 }, { (VarT)2, (OriginalVarType)1 }, { (VarT)3, (OriginalVarType)3 } },
                                                                                   { { (VarT)1, (OriginalVarType)3 }, { (VarT)2, (OriginalVarType)4 }, { (VarT)3, (OriginalVarType)1 } } };

            for (const FormulaType& formula : formulaVector) {
                for (const MappingFromVariableToOriginalVariableType& mapping : mappingVector) {
                    KromCLeafType kromCLeaf(0, formula);

                    actualResult << "Formula: " << std::endl;
                    actualResult << kromCLeaf;

                    actualResult << "Mapping: ";
                    printMapping(mapping, actualResult);

                    kromCLeaf.printNode(actualResult, mapping);
                    actualResult << std::endl;
                }
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * RenH-C leaf
     */
    TEST_CASE("[Circuit::Node] RenH-C leaf", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeRenHCLeafResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg3(3, false);

            ClauseType clause0({ litPos1 });
            ClauseType clause1({ litNeg1, litPos2 });
            ClauseType clause2({ litPos1, litPos2, litNeg3 });

            std::vector<FormulaType> formulaVector { { clause0 }, { clause0, clause1 }, { clause0, clause1, clause2 } };
            std::vector<VariableSetType> switchedVariablesVector { {}, { 1 }, { 1, 2 } };

            for (const FormulaType& formula : formulaVector) {
                for (const VariableSetType& switchedVariables : switchedVariablesVector) {
                    try {
                        RenHCLeafType renHCLeaf(1, formula, switchedVariables);
                        printNode(renHCLeaf, actualResult);
                    }
                    catch (const Hydra::Exception::CompilerException& e) {
                        actualResult << e.what() << std::endl;
                    }

                    actualResult << std::endl;
                }

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
     * RenH-C leaf (mapping)
     */
    TEST_CASE("[Circuit::Node] RenH-C leaf (mapping)", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeRenHCLeafMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg3(3, false);

            ClauseType clause0({ litPos1 });
            ClauseType clause1({ litNeg1, litPos2 });
            ClauseType clause2({ litPos1, litPos2, litNeg3 });

            std::vector<FormulaType> formulaVector { { clause0 }, { clause0, clause1 }, { clause0, clause1, clause2 } };
            std::vector<VariableSetType> switchedVariablesVector { {}, { 1 }, { 1, 2 } };

            std::vector<MappingFromVariableToOriginalVariableType> mappingVector { {},
                                                                                   { { (VarT)1, (OriginalVarType)1 }, { (VarT)2, (OriginalVarType)2 }, { (VarT)3, (OriginalVarType)3 } },
                                                                                   { { (VarT)1, (OriginalVarType)2 }, { (VarT)2, (OriginalVarType)1 }, { (VarT)3, (OriginalVarType)3 } },
                                                                                   { { (VarT)1, (OriginalVarType)3 }, { (VarT)2, (OriginalVarType)4 }, { (VarT)3, (OriginalVarType)1 } } };

            for (const FormulaType& formula : formulaVector) {
                for (const VariableSetType& switchedVariables : switchedVariablesVector) {
                    for (const MappingFromVariableToOriginalVariableType& mapping : mappingVector) {
                        try {
                            RenHCLeafType renHCLeaf(0, formula, switchedVariables);

                            actualResult << "Formula: " << std::endl;
                            actualResult << renHCLeaf;

                            actualResult << "Switched variables: ";
                            VariableVectorType variableVectorTmp = Hydra::Other::sortUnorderedSet(switchedVariables);
                            for (VarT var : variableVectorTmp)
                                actualResult << std::to_string(var) << " ";
                            actualResult << std::endl;

                            actualResult << "Mapping: ";
                            printMapping(mapping, actualResult);

                            renHCLeaf.printNode(actualResult, mapping);
                            actualResult << std::endl;
                        }
                        catch (const Hydra::Exception::CompilerException& e) {
                            actualResult << e.what() << std::endl;
                        }
                    }
                }
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Binary OR inner node
     */
    TEST_CASE("[Circuit::Node] binary OR inner node", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeBinaryOrInnerNodeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg3(3, false);

            ClauseType clause0({ litPos1 });
            ClauseType clause1({ litNeg1, litPos2 });
            ClauseType clause2({ litPos1, litPos2 });
            ClauseType clause3({ litNeg1, litNeg3 });

            ConstantLeafType constantLeafTrue(1, true);
            ConstantLeafType constantLeafFalse(2, false);
            LiteralLeafType literalLeafPos1(3, litPos1);
            LiteralLeafType literalLeafNeg1(4, litNeg1);
            LiteralLeafType literalLeafNeg3(5, litNeg3);
            KromCLeafType kromCLeaf(6, { clause0, clause1 });
            RenHCLeafType renHCLeaf(7, { clause2, clause3 }, { 1 });

            std::vector<VarT> decisionVariableVector { 0, 1 };
            std::vector<std::pair<NodeAbstractType*, NodeAbstractType*>> childrenVector { { &constantLeafTrue, &constantLeafFalse },
                                                                                          { &literalLeafPos1, &literalLeafNeg1 },
                                                                                          { &literalLeafPos1, &literalLeafNeg3 },
                                                                                          { &kromCLeaf, &renHCLeaf } };

            for (const std::pair<NodeAbstractType*, NodeAbstractType*>& childrenPair : childrenVector) {
                for (VarT decisionVariable : decisionVariableVector) {
                    try {
                        BinaryOrInnerNodeType binaryOrInnerNode(8, std::get<0>(childrenPair), std::get<1>(childrenPair), decisionVariable);
                        printNode(binaryOrInnerNode, actualResult);
                    }
                    catch (const Hydra::Exception::CompilerException& e) {
                        actualResult << e.what() << std::endl;
                    }

                    actualResult << std::endl;
                }

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
     * OR inner node
     */
    TEST_CASE("[Circuit::Node] OR inner node", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeOrInnerNodeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);

            ClauseType clause0({ litPos1 });
            ClauseType clause1({ litNeg1, litPos2 });
            ClauseType clause2({ litPos1, litPos2 });
            ClauseType clause3({ litNeg1, litPos2 });

            ConstantLeafType constantLeafTrue(1, true);
            ConstantLeafType constantLeafFalse(2, false);
            LiteralLeafType literalLeafPos1(3, litPos1);
            LiteralLeafType literalLeafNeg1(4, litNeg1);
            LiteralLeafType literalLeafPos2(5, litPos2);
            KromCLeafType kromCLeaf(6, { clause0, clause1 });          // 1 a (-1 v 2)
            RenHCLeafType renHCLeaf(7, { clause2, clause3 }, { 2 });   // (1 v 2) a (-1 v 2)

            std::vector<std::vector<NodeAbstractType*>> childrenVector { { &constantLeafTrue, &constantLeafFalse },
                                                                         { &literalLeafPos1, &literalLeafNeg1 },
                                                                         { &literalLeafPos1, &literalLeafPos2 },
                                                                         { &kromCLeaf, &renHCLeaf },
                                                                         { &kromCLeaf, &renHCLeaf, &literalLeafPos1 } };

            for (const std::vector<NodeAbstractType*>& children : childrenVector) {
                try {
                    OrInnerNodeType orInnerNode(8, children);
                    printNode(orInnerNode, actualResult);
                }
                catch (const Hydra::Exception::CompilerException& e) {
                    actualResult << e.what() << std::endl;
                }

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
     * AND inner node
     */
    TEST_CASE("[Circuit::Node] AND inner node", "[Circuit::Node]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNodeAndInnerNodeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg3(3, false);

            ClauseType clause0({ litPos1 });
            ClauseType clause1({ litNeg1, litPos2 });
            ClauseType clause2({ litPos1, litPos2 });
            ClauseType clause3({ litNeg1, litNeg3 });
            ClauseType clause4({ litNeg1 });
            ClauseType clause5({ litNeg1, litPos2 });

            ConstantLeafType constantLeafTrue(1, true);
            ConstantLeafType constantLeafFalse(2, false);
            LiteralLeafType literalLeafPos1(3, litPos1);
            LiteralLeafType literalLeafNeg1(4, litNeg1);
            LiteralLeafType literalLeafPos2(5, litPos2);
            LiteralLeafType literalLeafNeg3(6, litNeg3);
            KromCLeafType kromCLeaf1(7, { clause0, clause1 });           // 1 a (-1 v 2)
            KromCLeafType kromCLeaf2(8, { clause4, clause1 });           // -1 a (-1 v 2)
            RenHCLeafType renHCLeaf1(9, { clause2, clause3 }, { 1 });    // (1 v 2) a (-1 v -3)
            RenHCLeafType renHCLeaf2(10, { clause5, clause3 }, { 2 });   // (-1 v 2) a (-1 v -3)

            std::vector<DecomposabilityTypeEnum> decomposabilityTypeVector { DecomposabilityTypeEnum::NONE,
                                                                             DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY,
                                                                             DecomposabilityTypeEnum::BELLA_DECOMPOSABILITY,
                                                                             DecomposabilityTypeEnum::posBELLA_DECOMPOSABILITY,
                                                                             DecomposabilityTypeEnum::negBELLA_DECOMPOSABILITY };
            std::vector<std::vector<NodeAbstractType*>> childrenVector { { &constantLeafFalse },
                                                                         { &constantLeafTrue, &constantLeafFalse },
                                                                         { &literalLeafPos1, &literalLeafNeg1 },
                                                                         { &literalLeafPos1, &literalLeafNeg1, &literalLeafNeg3 },
                                                                         { &literalLeafPos1, &literalLeafPos1 },
                                                                         { &literalLeafNeg3, &literalLeafNeg3 },
                                                                         { &literalLeafPos1, &literalLeafPos1, &literalLeafNeg3 },
                                                                         { &literalLeafPos1, &literalLeafNeg3 },
                                                                         { &literalLeafPos1, &literalLeafNeg3, &literalLeafPos2 },
                                                                         { &kromCLeaf1, &renHCLeaf1 },
                                                                         { &kromCLeaf2, &renHCLeaf2 } };

            for (const std::vector<NodeAbstractType*>& children : childrenVector) {
                for (DecomposabilityTypeEnum decomposabilityType : decomposabilityTypeVector) {
                    try {
                        AndInnerNodeType andInnerNode(11, children, decomposabilityType);
                        printNode(andInnerNode, actualResult);
                    }
                    catch (const Hydra::Exception::CompilerException& e) {
                        actualResult << e.what() << std::endl;
                    }

                    actualResult << std::endl;
                }

                actualResult << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif
}   // namespace HydraTest::Circuit::Node
