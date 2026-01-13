#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/circuit/query/CircuitQueryTestCircuit.hpp"
#include "HydraTest/circuit/query/CircuitQueryTestResult.hpp"

#include "Hydra/circuit/Circuit.hpp"
#include "Hydra/circuit/parser/CircuitParser.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/Other.hpp"

namespace HydraTest::Circuit::Query {

    //region Types
    using IdNodeType = Hydra::Circuit::IdNodeType;
    using LargeNumberType = Hydra::Circuit::LargeNumberType;
    using OriginalVarType = Hydra::Circuit::OriginalVarType;
    using OriginalLiteralType = Hydra::Circuit::OriginalLiteralType;

    using VarT = char16_t;
    using LiteralT = char32_t;

    using ClauseType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::ClauseType;
    using FormulaType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::FormulaType;
    using LiteralType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::LiteralType;
    using VariableSetType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::VariableSetType;
    using NumberOfModelsType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::NumberOfModelsType;
    using OriginalLiteralSetType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::OriginalLiteralSetType;
    using OriginalVariableSetType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::OriginalVariableSetType;
    using VariableSortedVectorType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::VariableSortedVectorType;
    using MappingFromVariableToOriginalVariableType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::MappingFromVariableToOriginalVariableType;
    using MappingFromOriginalVariableToVariableType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::MappingFromOriginalVariableToVariableType;

    using CircuitType = Hydra::Circuit::Circuit<VarT, LiteralT>;
    using OriginalLiteralSetVectorType = std::vector<OriginalLiteralSetType>;
    using OriginalVariableSetVectorType = std::vector<OriginalVariableSetType>;

    using DecomposabilityTypeEnum = Hydra::Circuit::Node::DecomposabilityTypeEnum;
    //endregion

    //region Functions
    void printCircuit(CircuitType& circuit, std::stringstream& actualResult) {
        circuit.printCircuitDebug(actualResult);
        actualResult << std::endl;
        actualResult << circuit;
        actualResult << std::endl;
    }

    void printArgument(const OriginalLiteralSetType& partialAssignment, const OriginalVariableSetType& forgottenVariables, std::stringstream& actualResult) {
        actualResult << "Partial assignment:";
        for (OriginalLiteralType lit : Hydra::Other::sortUnorderedSet(partialAssignment))
            actualResult << " " << std::to_string(lit);
        actualResult << std::endl;

        actualResult << "Forgotten variables:";
        for (OriginalVarType var : Hydra::Other::sortUnorderedSet(forgottenVariables))
            actualResult << " " << std::to_string(var);
        actualResult << std::endl;
    }

    void parseCircuitAndModelCount(const std::string& circuitString, std::stringstream& actualResult, bool polynomialDelay) {
        try {
            unsigned int line = 1;

            std::istringstream stringStream(circuitString);
            std::istreambuf_iterator<char> begin(stringStream);
            std::istreambuf_iterator<char> end;

            auto header = Hydra::Circuit::Parser::parseDimacsNnfHeader(begin, end, line);
            auto circuit = Hydra::Circuit::Parser::parseCircuit<VarT, LiteralT, std::istreambuf_iterator<char>>(begin, end, header, line);

            NumberOfModelsType numberOfModels;

            if (polynomialDelay)
                numberOfModels = circuit.modelCountingWithPolynomialDelay({}, {}, false);
            else
                numberOfModels = circuit.modelCounting({});

            actualResult << numberOfModels << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }
    }

    void printMapping(const MappingFromVariableToOriginalVariableType& mapping, std::stringstream& actualResult) {
        actualResult << "Mapping: ";

        VariableSortedVectorType keyVectorTmp = Hydra::Other::extractKeysFromMap(mapping, true);
        for (VarT var : keyVectorTmp)
            actualResult << std::to_string(var) << " -> " << mapping.at(var) << " ";
        actualResult << std::endl
                     << std::endl;
    }
    //endregion

    //region Circuits
    /**
     * NNF
     */
    CircuitType createNnf(MappingFromVariableToOriginalVariableType&& mappingFromVariableToOriginalVariable) {
        auto mappingFromOriginalVariableToVariable = Hydra::Other::invertMap(mappingFromVariableToOriginalVariable);

        CircuitType circuit(3, false,
                            std::move(mappingFromVariableToOriginalVariable),
                            std::move(mappingFromOriginalVariableToVariable));

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg3(3, false);

        IdNodeType id8 = circuit.createOrInnerNode({ litPos1, litNeg3 });
        IdNodeType id9 = circuit.createOrInnerNode({ litNeg1, litPos2 });

        circuit.createAndInnerNode({ id8, id9 },
                                   DecomposabilityTypeEnum::NONE);

        circuit.setRoot();
        return circuit;
    }

    /**
     * pwDNNF
     */
    CircuitType createPWDnnf(MappingFromVariableToOriginalVariableType&& mappingFromVariableToOriginalVariable) {
        auto mappingFromOriginalVariableToVariable = Hydra::Other::invertMap(mappingFromVariableToOriginalVariable);

        CircuitType circuit(3, false,
                            std::move(mappingFromVariableToOriginalVariable),
                            std::move(mappingFromOriginalVariableToVariable));

        LiteralType litPos1(1, true);
        LiteralType litPos2(2, true);
        LiteralType litNeg3(3, false);

        IdNodeType id8 = circuit.createOrInnerNode({ litPos1, litNeg3 });
        IdNodeType id9 = circuit.createOrInnerNode({ litPos1, litPos2 });

        circuit.createAndInnerNode({ id8, id9 },
                                   DecomposabilityTypeEnum::posBELLA_DECOMPOSABILITY);

        circuit.setRoot();
        return circuit;
    }

    /**
     * nwDNNF
     */
    CircuitType createNWDnnf(MappingFromVariableToOriginalVariableType&& mappingFromVariableToOriginalVariable) {
        auto mappingFromOriginalVariableToVariable = Hydra::Other::invertMap(mappingFromVariableToOriginalVariable);

        CircuitType circuit(3, false,
                            std::move(mappingFromVariableToOriginalVariable),
                            std::move(mappingFromOriginalVariableToVariable));

        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg3(3, false);

        IdNodeType id8 = circuit.createOrInnerNode({ litNeg1, litNeg3 });
        IdNodeType id9 = circuit.createOrInnerNode({ litNeg1, litPos2 });

        circuit.createAndInnerNode({ id8, id9 },
                                   DecomposabilityTypeEnum::negBELLA_DECOMPOSABILITY);

        circuit.setRoot();
        return circuit;
    }

    /**
     * wDNNF
     */
    CircuitType createWDnnf(MappingFromVariableToOriginalVariableType&& mappingFromVariableToOriginalVariable) {
        auto mappingFromOriginalVariableToVariable = Hydra::Other::invertMap(mappingFromVariableToOriginalVariable);

        CircuitType circuit(3, false,
                            std::move(mappingFromVariableToOriginalVariable),
                            std::move(mappingFromOriginalVariableToVariable));

        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg3(3, false);

        IdNodeType id8 = circuit.createOrInnerNode({ litNeg1, litPos2, litNeg3 });
        IdNodeType id9 = circuit.createOrInnerNode({ litNeg1, litPos2 });

        circuit.createAndInnerNode({ id8, id9 },
                                   DecomposabilityTypeEnum::BELLA_DECOMPOSABILITY);

        circuit.setRoot();
        return circuit;
    }

    /**
     * (s)d-DNNF
     */
    CircuitType createDDnnf(bool smooth, MappingFromVariableToOriginalVariableType&& mappingFromVariableToOriginalVariable) {
        auto mappingFromOriginalVariableToVariable = Hydra::Other::invertMap(mappingFromVariableToOriginalVariable);

        CircuitType circuit(3, smooth,
                            std::move(mappingFromVariableToOriginalVariable),
                            std::move(mappingFromOriginalVariableToVariable));

        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);

        IdNodeType id1 = circuit.createConstantLeaf(true);
        IdNodeType id3 = circuit.createLiteralLeaf(litNeg1);
        IdNodeType id4 = circuit.createLiteralLeaf(litPos2);
        IdNodeType id5 = circuit.createLiteralLeaf(litNeg2);

        IdNodeType id8 = circuit.createAndInnerNode({ id3, id5 },
                                                    DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);
        IdNodeType id9 = circuit.createAndInnerNode({ id1, id4 },
                                                    DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);

        if (smooth)
            circuit.createDecisionInnerNode(3, id8, id9, {}, { (VarT)1 });
        else
            circuit.createDecisionInnerNode(3, id8, id9);

        circuit.setRoot();
        return circuit;
    }

    /**
     * {Krom-C}-sd-BDMC
     */
    CircuitType createKromCSDBdmc(MappingFromVariableToOriginalVariableType&& mappingFromVariableToOriginalVariable) {
        auto mappingFromOriginalVariableToVariable = Hydra::Other::invertMap(mappingFromVariableToOriginalVariable);

        CircuitType circuit(4, true,
                            std::move(mappingFromVariableToOriginalVariable),
                            std::move(mappingFromOriginalVariableToVariable));

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);

        ClauseType clause1({ litPos2, litNeg3 });
        ClauseType clause2({ litNeg2, litPos3 });
        ClauseType clause3({ litPos1 });
        ClauseType clause4({ litNeg1, litPos2 });

        FormulaType formula1 { clause1, clause2 };
        FormulaType formula2 { clause3, clause4 };

        IdNodeType id10 = circuit.createKromCLeaf(std::move(formula1));
        IdNodeType id11 = circuit.createKromCLeaf(std::move(formula2));

        circuit.createDecisionInnerNode(4, id10, id11, { (VarT)1 }, { (VarT)3 });

        circuit.setRoot();
        return circuit;
    }

    /**
     * {renH-C}-sd-BDMC
     */
    CircuitType createRenHCSDBdmc(MappingFromVariableToOriginalVariableType&& mappingFromVariableToOriginalVariable) {
        auto mappingFromOriginalVariableToVariable = Hydra::Other::invertMap(mappingFromVariableToOriginalVariable);

        CircuitType circuit(5, true,
                            std::move(mappingFromVariableToOriginalVariable),
                            std::move(mappingFromOriginalVariableToVariable));

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);

        ClauseType clause1({ litPos2, litNeg3, litPos5 });
        ClauseType clause2({ litNeg2, litPos3 });
        ClauseType clause3({ litNeg5 });
        ClauseType clause4({ litPos1, litNeg5 });
        ClauseType clause5({ litNeg1, litPos2 });

        FormulaType formula1 { clause1, clause2, clause3 };
        FormulaType formula2 { clause4, clause5 };

        VariableSetType switchedVariables1 { 2, 3, 5 };
        VariableSetType switchedVariables2 { 2 };

        IdNodeType id12 = circuit.createRenHCLeaf(std::move(formula1), std::move(switchedVariables1));
        IdNodeType id13 = circuit.createRenHCLeaf(std::move(formula2), std::move(switchedVariables2));

        circuit.createDecisionInnerNode(4, id12, id13, { (VarT)1 }, { (VarT)3 });

        circuit.setRoot();
        return circuit;
    }
    //endregion

    #if defined(BELLA_COMPILER)
    /**
     * NNF (consistency check)
     */
    TEST_CASE("[Circuit::Query] NNF (consistency check)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryNnfConsistencyCheckResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createNnf({});
            printCircuit(circuit, actualResult);

            actualResult << "Consistency check: " << std::endl;
            circuit.consistencyCheck({}, {});
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * NNF (model counting)
     */
    TEST_CASE("[Circuit::Query] NNF (model counting)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryNnfModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createNnf({});
            printCircuit(circuit, actualResult);

            actualResult << "Model counting: " << std::endl;
            circuit.modelCounting({});
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * NNF (model enumeration)
     */
    TEST_CASE("[Circuit::Query] NNF (model enumeration)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryNnfModelEnumerationResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createNnf({});
            printCircuit(circuit, actualResult);

            actualResult << "Model enumeration: " << std::endl;
            NumberOfModelsType numberOfModels = circuit.modelCountingWithPolynomialDelay({}, {}, true, actualResult);
            actualResult << "Number of models: " << numberOfModels << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * pwDNNF (consistency check)
     */
    TEST_CASE("[Circuit::Query] pwDNNF (consistency check)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryPWDnnfConsistencyCheckResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createPWDnnf({});
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { 1 }, { -1 }, { -2, 3 }, { -1, -2 }, { -1, -2, 3 } };
            OriginalVariableSetVectorType forgottenVariableVector { {}, { 1 }, { 3 }, { 1, 4 } };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                for (const OriginalVariableSetType& forgottenVariables : forgottenVariableVector) {
                    printArgument(partialAssignment, forgottenVariables, actualResult);
                    actualResult << "Consistency check: ";

                    try {
                        bool tmp = circuit.consistencyCheck(partialAssignment, forgottenVariables);
                        actualResult << std::to_string(tmp) << std::endl;
                    }
                    catch (const std::exception& e) {
                        actualResult << e.what() << std::endl;
                    }

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
     * pwDNNF (model counting)
     */
    TEST_CASE("[Circuit::Query] pwDNNF (model counting)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryPWDnnfModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createPWDnnf({});
            printCircuit(circuit, actualResult);

            actualResult << "Model counting: " << std::endl;
            circuit.modelCounting({});
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * pwDNNF (model enumeration)
     */
    TEST_CASE("[Circuit::Query] pwDNNF (model enumeration)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryPWDnnfModelEnumerationResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createPWDnnf({});
            printCircuit(circuit, actualResult);

            actualResult << "Model enumeration: " << std::endl;
            NumberOfModelsType numberOfModels = circuit.modelCountingWithPolynomialDelay({}, {}, true, actualResult);
            actualResult << "Number of models: " << numberOfModels << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * nwDNNF (consistency check)
     */
    TEST_CASE("[Circuit::Query] nwDNNF (consistency check)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryNWDnnfConsistencyCheckResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createNWDnnf({});
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { -1 }, { 1 }, { -2, 3 }, { 1, -2 }, { 1, -2, 3 } };
            OriginalVariableSetVectorType forgottenVariableVector { {}, { 1 }, { 3 }, { 1, 4 } };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                for (const OriginalVariableSetType& forgottenVariables : forgottenVariableVector) {
                    printArgument(partialAssignment, forgottenVariables, actualResult);
                    actualResult << "Consistency check: ";

                    try {
                        bool tmp = circuit.consistencyCheck(partialAssignment, forgottenVariables);
                        actualResult << std::to_string(tmp) << std::endl;
                    }
                    catch (const std::exception& e) {
                        actualResult << e.what() << std::endl;
                    }

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
     * nwDNNF (model counting)
     */
    TEST_CASE("[Circuit::Query] nwDNNF (model counting)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryNWDnnfModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createNWDnnf({});
            printCircuit(circuit, actualResult);

            actualResult << "Model counting: " << std::endl;
            circuit.modelCounting({});
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * nwDNNF (model enumeration)
     */
    TEST_CASE("[Circuit::Query] nwDNNF (model enumeration)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryNWDnnfModelEnumerationResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createNWDnnf({});
            printCircuit(circuit, actualResult);

            actualResult << "Model enumeration: " << std::endl;
            NumberOfModelsType numberOfModels = circuit.modelCountingWithPolynomialDelay({}, {}, true, actualResult);
            actualResult << "Number of models: " << numberOfModels << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * wDNNF (consistency check)
     */
    TEST_CASE("[Circuit::Query] wDNNF (consistency check)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryWDnnfConsistencyCheckResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createWDnnf({});
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { 1 }, { -1 }, { 2 }, { -2 }, { 1, -2 }, { 1, 2 }, { -1, -2 }, { -1, 2 }, { -2, 3 }, { 1, -2, 3 }, { -1, -2, 3 } };
            OriginalVariableSetVectorType forgottenVariableVector { {}, { 1 }, { 2 }, { 3 }, { 1, 2 }, { 1, 4 } };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                for (const OriginalVariableSetType& forgottenVariables : forgottenVariableVector) {
                    printArgument(partialAssignment, forgottenVariables, actualResult);
                    actualResult << "Consistency check: ";

                    try {
                        bool tmp = circuit.consistencyCheck(partialAssignment, forgottenVariables);
                        actualResult << std::to_string(tmp) << std::endl;
                    }
                    catch (const std::exception& e) {
                        actualResult << e.what() << std::endl;
                    }

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
     * wDNNF (model counting)
     */
    TEST_CASE("[Circuit::Query] wDNNF (model counting)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryWDnnfModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createWDnnf({});
            printCircuit(circuit, actualResult);

            actualResult << "Model counting: " << std::endl;
            circuit.modelCounting({});
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * wDNNF (model enumeration)
     */
    TEST_CASE("[Circuit::Query] wDNNF (model enumeration)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryWDnnfModelEnumerationResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createWDnnf({});
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { 1 }, { -1 }, { 2 }, { -2 }, { 1, -2 }, { 1, 2 }, { -1, -2 }, { -1, 2 }, { -2, 3 }, { 1, -2, 3 }, { -1, -2, 3 } };
            OriginalVariableSetVectorType forgottenVariableVector { {}, { 1 }, { 2 }, { 3 }, { 1, 2 }, { 1, 4 } };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                for (const OriginalVariableSetType& forgottenVariables : forgottenVariableVector) {
                    printArgument(partialAssignment, forgottenVariables, actualResult);
                    actualResult << "Model enumeration: " << std::endl;

                    try {
                        NumberOfModelsType numberOfModels = circuit.modelCountingWithPolynomialDelay(partialAssignment, forgottenVariables,
                                                                                                     true, actualResult);
                        actualResult << "Number of models: " << numberOfModels << std::endl;
                    }
                    catch (const std::exception& e) {
                        actualResult << e.what() << std::endl;
                    }

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
     * d-DNNF (consistency check)
     */
    TEST_CASE("[Circuit::Query] d-DNNF (consistency check)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryDDnnfConsistencyCheckResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createDDnnf(false, {});
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { 1, -2 }, { -2, -3 }, { -2, 3 } };
            OriginalVariableSetVectorType forgottenVariableVector { {} };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                for (const OriginalVariableSetType& forgottenVariables : forgottenVariableVector) {
                    printArgument(partialAssignment, forgottenVariables, actualResult);
                    actualResult << "Consistency check: ";

                    try {
                        bool tmp = circuit.consistencyCheck(partialAssignment, forgottenVariables);
                        actualResult << std::to_string(tmp) << std::endl;
                    }
                    catch (const std::exception& e) {
                        actualResult << e.what() << std::endl;
                    }

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
     * d-DNNF (model counting)
     */
    TEST_CASE("[Circuit::Query] d-DNNF (model counting)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryDDnnfModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createDDnnf(false, {});
            printCircuit(circuit, actualResult);

            actualResult << "Model counting: " << std::endl;
            circuit.modelCounting({});
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * d-DNNF (model enumeration)
     */
    TEST_CASE("[Circuit::Query] d-DNNF (model enumeration)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryDDnnfModelEnumerationResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createDDnnf(false, {});
            printCircuit(circuit, actualResult);

            actualResult << "Model enumeration: " << std::endl;
            NumberOfModelsType numberOfModels = circuit.modelCountingWithPolynomialDelay({}, {}, true, actualResult);
            actualResult << "Number of models: " << numberOfModels << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sd-DNNF (consistency check)
     */
    TEST_CASE("[Circuit::Query] sd-DNNF (consistency check)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQuerySDDnnfConsistencyCheckResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createDDnnf(true, {});
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { 1, -2 }, { -2, -3 }, { -2, 3 } };
            OriginalVariableSetVectorType forgottenVariableVector { {} };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                for (const OriginalVariableSetType& forgottenVariables : forgottenVariableVector) {
                    printArgument(partialAssignment, forgottenVariables, actualResult);
                    actualResult << "Consistency check: ";

                    try {
                        bool tmp = circuit.consistencyCheck(partialAssignment, forgottenVariables);
                        actualResult << std::to_string(tmp) << std::endl;
                    }
                    catch (const std::exception& e) {
                        actualResult << e.what() << std::endl;
                    }

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
     * sd-DNNF (model counting)
     */
    TEST_CASE("[Circuit::Query] sd-DNNF (model counting)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQuerySDDnnfModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createDDnnf(true, {});
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { 1 }, { 2 }, { -3 }, { -2, -3 }, { 1, -3 } };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                printArgument(partialAssignment, {}, actualResult);
                actualResult << "Model counting: ";

                try {
                    NumberOfModelsType tmp = circuit.modelCounting(partialAssignment);
                    actualResult << tmp << std::endl;
                }
                catch (const std::exception& e) {
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
     * sd-DNNF (model enumeration)
     */
    TEST_CASE("[Circuit::Query] sd-DNNF (model enumeration)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQuerySDDnnfModelEnumerationResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createDDnnf(true, {});
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { 1 }, { 2 }, { -3 }, { -2, -3 }, { 1, -3 } };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                printArgument(partialAssignment, {}, actualResult);
                actualResult << "Model enumeration: " << std::endl;

                try {
                    NumberOfModelsType numberOfModels = circuit.modelCountingWithPolynomialDelay(partialAssignment, {}, true, actualResult);
                    actualResult << "Number of models: " << numberOfModels << std::endl;
                }
                catch (const std::exception& e) {
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
     * {Krom-C}-sd-BDMC (consistency check)
     */
    TEST_CASE("[Circuit::Query] {Krom-C}-sd-BDMC (consistency check)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryKromCSDBdmcConsistencyCheckResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createKromCSDBdmc({});
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { -1 }, { -1, -4 }, { -2, -4 }, { 2, 4 }, { 2, -3, 4 } };
            OriginalVariableSetVectorType forgottenVariableVector { {} };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                for (const OriginalVariableSetType& forgottenVariables : forgottenVariableVector) {
                    printArgument(partialAssignment, forgottenVariables, actualResult);
                    actualResult << "Consistency check: ";

                    try {
                        bool tmp = circuit.consistencyCheck(partialAssignment, forgottenVariables);
                        actualResult << std::to_string(tmp) << std::endl;
                    }
                    catch (const std::exception& e) {
                        actualResult << e.what() << std::endl;
                    }

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
     * {Krom-C}-sd-BDMC (model counting)
     */
    TEST_CASE("[Circuit::Query] {Krom-C}-sd-BDMC (model counting)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryKromCSDBdmcModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createKromCSDBdmc({});
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { -1 }, { -1, -4 }, { -2, -4 }, { 2, 4 }, { 1, 2 }, { 2, -3, 4 } };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                printArgument(partialAssignment, {}, actualResult);
                actualResult << "Model counting: ";

                try {
                    NumberOfModelsType tmp = circuit.modelCounting(partialAssignment);
                    actualResult << tmp << std::endl;
                }
                catch (const std::exception& e) {
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
     * {Krom-C}-sd-BDMC (model enumeration)
     */
    TEST_CASE("[Circuit::Query] {Krom-C}-sd-BDMC (model enumeration)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryKromCSDBdmcModelEnumerationResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createKromCSDBdmc({});
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { -1 }, { -1, -4 }, { -2, -4 }, { 2, 4 }, { 1, 2 }, { 2, -3, 4 } };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                printArgument(partialAssignment, {}, actualResult);
                actualResult << "Model enumeration: " << std::endl;

                try {
                    NumberOfModelsType numberOfModels = circuit.modelCountingWithPolynomialDelay(partialAssignment, {}, true, actualResult);
                    actualResult << "Number of models: " << numberOfModels << std::endl;
                }
                catch (const std::exception& e) {
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
     * {renH-C}-sd-BDMC (consistency check)
     */
    TEST_CASE("[Circuit::Query] {renH-C}-sd-BDMC (consistency check)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryRenHCSDBdmcConsistencyCheckResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createRenHCSDBdmc({});
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { -2, 4 }, { 4, 5 }, { -2, 3 }, { -2, -4, 5 }, { -2, 3, 4 } };
            OriginalVariableSetVectorType forgottenVariableVector { {} };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                for (const OriginalVariableSetType& forgottenVariables : forgottenVariableVector) {
                    printArgument(partialAssignment, forgottenVariables, actualResult);
                    actualResult << "Consistency check: ";

                    try {
                        bool tmp = circuit.consistencyCheck(partialAssignment, forgottenVariables);
                        actualResult << std::to_string(tmp) << std::endl;
                    }
                    catch (const std::exception& e) {
                        actualResult << e.what() << std::endl;
                    }

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
     * {renH-C}-sd-BDMC (model counting)
     */
    TEST_CASE("[Circuit::Query] {renH-C}-sd-BDMC (model counting)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryRenHCSDBdmcModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createRenHCSDBdmc({});
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { -2, 4 }, { -3, 5 }, { 2, 3 }, { 1, 2, 3 }, { 1, 2, 5 } };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                printArgument(partialAssignment, {}, actualResult);
                actualResult << "Model counting: ";

                try {
                    NumberOfModelsType tmp = circuit.modelCounting(partialAssignment);
                    actualResult << tmp << std::endl;
                }
                catch (const std::exception& e) {
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
     * {renH-C}-sd-BDMC (model enumeration)
     */
    TEST_CASE("[Circuit::Query] {renH-C}-sd-BDMC (model enumeration)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryRenHCSDBdmcModelEnumerationResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit = createRenHCSDBdmc({});
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { -2, 4 }, { -3, 5 }, { 2, 3 }, { 1, 2, 3 }, { 1, 2, 5 } };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                printArgument(partialAssignment, {}, actualResult);
                actualResult << "Model enumeration: " << std::endl;

                try {
                    NumberOfModelsType numberOfModels = circuit.modelCountingWithPolynomialDelay(partialAssignment, {}, true, actualResult);
                    actualResult << "Number of models: " << numberOfModels << std::endl;
                }
                catch (const std::exception& e) {
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
     * sd-DNNF (mapping)
     */
    TEST_CASE("[Circuit::Query] sd-DNNF (mapping)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQuerySDDnnfMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            MappingFromVariableToOriginalVariableType mapping { { (VarT)1, (OriginalVarType)3 },
                                                                { (VarT)3, (OriginalVarType)1 },
                                                                { (VarT)2, (OriginalVarType)8 } };
            printMapping(mapping, actualResult);

            CircuitType circuit = createDDnnf(true, std::move(mapping));
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { 3 }, { 8 }, { -1 }, { -8, -1 }, { 3, -1 } };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                printArgument(partialAssignment, {}, actualResult);
                actualResult << "Model counting: ";

                try {
                    NumberOfModelsType tmp = circuit.modelCounting(partialAssignment);
                    actualResult << tmp << std::endl;
                }
                catch (const std::exception& e) {
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
     * {Krom-C}-sd-BDMC (mapping)
     */
    TEST_CASE("[Circuit::Query] {Krom-C}-sd-BDMC (mapping)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryKromCSDBdmcMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            MappingFromVariableToOriginalVariableType mapping { { (VarT)1, (OriginalVarType)4 },
                                                                { (VarT)4, (OriginalVarType)1 },
                                                                { (VarT)3, (OriginalVarType)8 } };
            printMapping(mapping, actualResult);

            CircuitType circuit = createKromCSDBdmc(std::move(mapping));
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { -4 }, { -4, -1 }, { -2, -1 }, { 2, 1 }, { 4, 2 }, { 2, -8, 1 } };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                printArgument(partialAssignment, {}, actualResult);
                actualResult << "Model counting: ";

                try {
                    NumberOfModelsType tmp = circuit.modelCounting(partialAssignment);
                    actualResult << tmp << std::endl;
                }
                catch (const std::exception& e) {
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
     * {renH-C}-sd-BDMC (mapping)
     */
    TEST_CASE("[Circuit::Query] {renH-C}-sd-BDMC (mapping)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryRenHCSDBdmcMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            MappingFromVariableToOriginalVariableType mapping { { (VarT)2, (OriginalVarType)2 }, { (VarT)3, (OriginalVarType)4 }, { (VarT)4, (OriginalVarType)3 }, { (VarT)5, (OriginalVarType)8 } };
            printMapping(mapping, actualResult);

            CircuitType circuit = createRenHCSDBdmc(std::move(mapping));
            printCircuit(circuit, actualResult);

            OriginalLiteralSetVectorType partialAssignmentVector { {}, { -2, 3 }, { -4, 8 }, { 2, 4 }, { 1, 2, 4 }, { 1, 2, 8 } };

            for (const OriginalLiteralSetType& partialAssignment : partialAssignmentVector) {
                printArgument(partialAssignment, {}, actualResult);
                actualResult << "Model counting: ";

                try {
                    NumberOfModelsType tmp = circuit.modelCounting(partialAssignment);
                    actualResult << tmp << std::endl;
                }
                catch (const std::exception& e) {
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
     * Model counting (anomaly)
     */
    TEST_CASE("[Circuit::Query] model counting (anomaly)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryAnomalyModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            parseCircuitAndModelCount(circuitQueryAnomalyCircuit, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting with polynomial delay (anomaly)
     */
    TEST_CASE("[Circuit::Query] model counting with polynomial delay (anomaly)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryAnomalyModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            parseCircuitAndModelCount(circuitQueryAnomalyCircuit, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting (wff.3.75.315)
     */
    TEST_CASE("[Circuit::Query] model counting (wff.3.75.315)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryWff_3_75_315ModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            parseCircuitAndModelCount(circuitQueryWff_3_75_315Circuit, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting with polynomial delay (wff.3.75.315)
     */
    TEST_CASE("[Circuit::Query] model counting with polynomial delay (wff.3.75.315)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryWff_3_75_315ModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            parseCircuitAndModelCount(circuitQueryWff_3_75_315Circuit, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting (s400.bench)
     */
    TEST_CASE("[Circuit::Query] model counting (s400.bench)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryS400_benchModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            parseCircuitAndModelCount(circuitQueryS400_benchCircuit, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting (4step)
     */
    TEST_CASE("[Circuit::Query] model counting (4step)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQuery4stepModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            parseCircuitAndModelCount(circuitQuery4stepCircuit, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting (D1119_M20)
     */
    TEST_CASE("[Circuit::Query] model counting (D1119_M20)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryD1119_M20ModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            parseCircuitAndModelCount(circuitQueryD1119_M20Circuit, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting (cnt06.shuffled)
     */
    TEST_CASE("[Circuit::Query] model counting (cnt06.shuffled)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryCnt06_shuffledModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            parseCircuitAndModelCount(circuitQueryCnt06_shuffledCircuit, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting with polynomial delay (cnt06.shuffled)
     */
    TEST_CASE("[Circuit::Query] model counting with polynomial delay (cnt06.shuffled)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryCnt06_shuffledModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            parseCircuitAndModelCount(circuitQueryCnt06_shuffledCircuit, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting (ais6)
     */
    TEST_CASE("[Circuit::Query] model counting (ais6)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryAis6ModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            parseCircuitAndModelCount(circuitQueryAis6Circuit, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting with polynomial delay (ais6)
     */
    TEST_CASE("[Circuit::Query] model counting with polynomial delay (ais6)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryAis6ModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            parseCircuitAndModelCount(circuitQueryAis6Circuit, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting (5step)
     */
    TEST_CASE("[Circuit::Query] model counting (5step)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQuery5stepModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            parseCircuitAndModelCount(circuitQuery5stepCircuit, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting (mixdup)
     */
    TEST_CASE("[Circuit::Query] model counting (mixdup)", "[Circuit::Query]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitQueryMixdupModelCountingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            parseCircuitAndModelCount(circuitQueryMixdupCircuit, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif
}   // namespace HydraTest::Circuit::Query
