#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/circuit/CircuitTestResult.hpp"
#include "HydraTest/circuit/CreateCircuit.hpp"

#include "Hydra/circuit/Circuit.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/Other.hpp"

namespace HydraTest::Circuit {

    //region Types
    using IdNodeType = Hydra::Circuit::IdNodeType;
    using OriginalVarType = Hydra::Formula::OriginalVarType;

    using VarT = char8_t;
    using LiteralT = char8_t;

    using RootType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::RootType;
    using LiteralType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::LiteralType;
    using IdNodeVectorType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::IdNodeVectorType;
    using LiteralVectorType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::LiteralVectorType;
    using VariableVectorType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::VariableVectorType;
    using MappingFromVariableToOriginalVariableType = typename Hydra::Circuit::Node::NodeAbstract<VarT, LiteralT>::MappingFromVariableToOriginalVariableType;
    using MappingFromOriginalVariableToVariableType = typename Hydra::Circuit::Node::NodeAbstract<VarT, LiteralT>::MappingFromOriginalVariableToVariableType;

    using CircuitType = Hydra::Circuit::Circuit<VarT, LiteralT>;

    using DecomposabilityTypeEnum = Hydra::Circuit::Node::DecomposabilityTypeEnum;
    //endregion

    //region Functions
    void printCircuit(CircuitType& circuit, std::stringstream& actualResult) {
        circuit.printCircuitDebug(actualResult);
        actualResult << std::endl;
        actualResult << circuit;
        actualResult << std::endl;
    }

    void printMapping(const MappingFromVariableToOriginalVariableType& mapping, std::stringstream& actualResult) {
        actualResult << "Mapping: ";

        VariableVectorType keyVectorTmp = Hydra::Other::extractKeysFromMap(mapping, true);
        for (VarT var : keyVectorTmp)
            actualResult << std::to_string(var) << " -> " << mapping.at(var) << " ";
        actualResult << std::endl
                     << std::endl;
    }
    //endregion

    #if defined(BELLA_COMPILER)
    /**
     * Constant leaves (unique node cache)
     */
    TEST_CASE("[Circuit] constant leaves (unique node cache)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitConstantLeavesUniqueNodeCacheResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(0, false);

            IdNodeType id = circuit.createConstantLeaf(false);
            actualResult << "ID (false): " << id << std::endl;

            id = circuit.createConstantLeaf(true);
            actualResult << "ID (true): " << id << std::endl;

            id = circuit.createConstantLeaf(false);
            actualResult << "ID (false): " << id << std::endl;

            id = circuit.createConstantLeaf(true);
            actualResult << "ID (true): " << id << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Literal leaves (unique node cache)
     */
    TEST_CASE("[Circuit] literal leaves (unique node cache)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitLiteralLeavesUniqueNodeCacheResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(1, false);

            LiteralType litPos(1, true);
            LiteralType litNeg(1, false);

            IdNodeType id = circuit.createLiteralLeaf(litPos);
            actualResult << "ID (" << litPos << "): " << id << std::endl;

            id = circuit.createLiteralLeaf(litNeg);
            actualResult << "ID (" << litNeg << "): " << id << std::endl;

            id = circuit.createLiteralLeaf(litPos);
            actualResult << "ID (" << litPos << "): " << id << std::endl;

            id = circuit.createLiteralLeaf(litNeg);
            actualResult << "ID (" << litNeg << "): " << id << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * AND inner node (unique node cache)
     */
    TEST_CASE("[Circuit] AND inner node (unique node cache)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitAndInnerNodeUniqueNodeCacheResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(3, false);

            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);
            LiteralType litNeg3(3, false);

            std::vector<LiteralVectorType> childrenVector { { litPos1, litNeg2, litPos3 }, { litNeg1, litNeg2, litPos3 }, { litNeg1, litPos2, litNeg3 }, { litPos3, litNeg2, litPos1 }, { litNeg1, litNeg3, litPos2 } };

            for (LiteralVectorType& children : childrenVector) {
                for (const LiteralType& lit : children)
                    actualResult << lit << " ";
                actualResult << std::endl;

                IdNodeType id = circuit.createAndInnerNode(children);
                actualResult << "ID: " << id << std::endl;
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
     * OR inner node (unique node cache)
     */
    TEST_CASE("[Circuit] OR inner node (unique node cache)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitOrInnerNodeUniqueNodeCacheResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(3, false);

            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);
            LiteralType litNeg3(3, false);

            std::vector<LiteralVectorType> childrenVector { { litPos1, litNeg2, litPos3 }, { litNeg1, litNeg2, litPos3 }, { litNeg1, litPos2, litNeg3 }, { litPos3, litNeg2, litPos1 }, { litNeg1, litNeg3, litPos2 } };

            for (LiteralVectorType& children : childrenVector) {
                for (const LiteralType& lit : children)
                    actualResult << lit << " ";
                actualResult << std::endl;

                IdNodeType id = circuit.createOrInnerNode(children);
                actualResult << "ID: " << id << std::endl;
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
     * Trivial OR inner node (unique node cache)
     */
    TEST_CASE("[Circuit] trivial OR inner node (unique node cache)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitTrivialOrInnerNodeUniqueNodeCacheResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(3, true);

            for (VarT var : VariableVectorType { 1, 2, 3, 3, 2, 1 }) {
                actualResult << "Var (" << std::to_string(var) << "): ";

                IdNodeType id = circuit.createTrivialOrInnerNode(var);
                actualResult << id << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Initialize (constant and literal leaves)
     */
    TEST_CASE("[Circuit] initialize (constant and literal leaves)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitInitializeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(4, false);
            circuit.printCircuitDebug(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * ID exists
     */
    TEST_CASE("[Circuit] ID exists", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitIdExistsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(2, false);

            VariableVectorType variableVector { 0, 1, 2, 3, 4, 5, 6, 7 };

            for (IdNodeType id : variableVector) {
                actualResult << "ID exists (" << id << "): ";
                bool idExists = circuit.idExists(id);
                actualResult << idExists << std::endl;
            }
            actualResult << std::endl;

            IdNodeType idNewNode = circuit.createTrivialOrInnerNode(1);
            actualResult << "Added new node: " << idNewNode << std::endl
                         << std::endl;

            for (IdNodeType id : variableVector) {
                actualResult << "ID exists (" << id << "): ";
                bool idExists = circuit.idExists(id);
                actualResult << idExists << std::endl;
            }
            actualResult << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Root
     */
    TEST_CASE("[Circuit] root", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitRootResult);
        std::stringstream& actualResult = test.getStringStream();

        auto printRootLambda = [&actualResult](CircuitType& circuit) {
            RootType root = circuit.getRoot();
            actualResult << "Root: ";
            if (root.has_value())
                actualResult << *root;
            else
                actualResult << "not set";
            actualResult << std::endl;
        };

        try {
            try {
                CircuitType circuit(1, false);
                printRootLambda(circuit);

                IdNodeType id = circuit.createTrivialOrInnerNode(1);
                actualResult << "Added new node: " << id << std::endl;

                actualResult << "Set root" << std::endl;
                circuit.setRoot();
                printRootLambda(circuit);

                actualResult << "Set root again" << std::endl;
                circuit.setRoot();
                printRootLambda(circuit);
            }
            catch (const Hydra::Exception::CompilerException& e) {
                actualResult << e.what() << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One child
     */
    TEST_CASE("[Circuit] one child", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitOneChildResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(1, false);

            LiteralType lit(1, true);
            IdNodeType idLit = circuit.createLiteralLeaf(lit);
            actualResult << "Literal leaf: " << idLit << std::endl;
            actualResult << std::endl;

            LiteralVectorType literalVector { lit };

            actualResult << "Create OR inner node (literals only): ";
            IdNodeType id = circuit.createOrInnerNode(literalVector);
            actualResult << id << std::endl;
            actualResult << std::endl;

            actualResult << "Create AND inner node (literals only): ";
            id = circuit.createAndInnerNode(literalVector);
            actualResult << id << std::endl;
            actualResult << std::endl;

            actualResult << "Create AND inner node: ";
            id = circuit.createAndInnerNode({ idLit },
                                            DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);
            actualResult << id << std::endl;
            actualResult << std::endl;
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
    TEST_CASE("[Circuit] move", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitMoveResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit1(6, false);
            createPWDnnf(circuit1);
            actualResult << "circuit1" << std::endl;
            printCircuit(circuit1, actualResult);

            actualResult << "Move method" << std::endl;
            CircuitType circuit2 = std::move(circuit1);
            actualResult << "circuit2" << std::endl;
            printCircuit(circuit2, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * pwDNNF
     */
    TEST_CASE("[Circuit] pwDNNF", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitPWDnnfResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(6, false);
            createPWDnnf(circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * pwDNNF (mapping)
     */
    TEST_CASE("[Circuit] pwDNNF (mapping)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitPWDnnfMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            MappingFromVariableToOriginalVariableType mapping { { (VarT)1, (OriginalVarType)1 },
                                                                { (VarT)2, (OriginalVarType)6 },
                                                                { (VarT)3, (OriginalVarType)4 },
                                                                { (VarT)4, (OriginalVarType)3 },
                                                                { (VarT)5, (OriginalVarType)7 },
                                                                { (VarT)6, (OriginalVarType)8 } };
            MappingFromOriginalVariableToVariableType invertedMapping = Hydra::Other::invertMap(mapping);
            printMapping(mapping, actualResult);

            CircuitType circuit(6, false,
                                std::move(mapping), std::move(invertedMapping));
            createPWDnnf(circuit);

            circuit.printCircuit(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * pwDNNF (missing variables)
     */
    TEST_CASE("[Circuit] pwDNNF (missing variables)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitPWDnnfMissingVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(7, false);
            createPWDnnf(circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * pwDNNF (smoothness)
     */
    TEST_CASE("[Circuit] pwDNNF (smoothness)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitPWDnnfSmoothnessResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(6, true);
            createPWDnnf(circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * nwDNNF
     */
    TEST_CASE("[Circuit] nwDNNF", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNWDnnfResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(3, false);
            createNWDnnf(circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * nwDNNF (mapping)
     */
    TEST_CASE("[Circuit] nwDNNF (mapping)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNWDnnfMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            MappingFromVariableToOriginalVariableType mapping { { (VarT)1, (OriginalVarType)1 },
                                                                { (VarT)2, (OriginalVarType)5 },
                                                                { (VarT)3, (OriginalVarType)4 },
                                                                { (VarT)4, (OriginalVarType)3 } };
            MappingFromOriginalVariableToVariableType invertedMapping = Hydra::Other::invertMap(mapping);
            printMapping(mapping, actualResult);

            CircuitType circuit(4, false,
                                std::move(mapping), std::move(invertedMapping));
            createNWDnnf(circuit);

            circuit.printCircuit(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * nwDNNF (missing variables)
     */
    TEST_CASE("[Circuit] nwDNNF (missing variables)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNWDnnfMissingVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(4, false);
            createNWDnnf(circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * nwDNNF (smoothness)
     */
    TEST_CASE("[Circuit] nwDNNF (smoothness)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNWDnnfSmoothnessResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(3, true);
            createNWDnnf(circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * wDNNF 1
     */
    TEST_CASE("[Circuit] wDNNF 1", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitWDnnf1Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(2, false);
            createWDnnf1(circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * wDNNF 1 (missing variables)
     */
    TEST_CASE("[Circuit] wDNNF 1 (missing variables)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitWDnnf1MissingVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(3, false);
            createWDnnf1(circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * wDNNF 1 (smoothness)
     */
    TEST_CASE("[Circuit] wDNNF 1 (smoothness)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitWDnnf1SmoothnessResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(2, true);
            createWDnnf1(circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * wDNNF 2
     */
    TEST_CASE("[Circuit] wDNNF 2", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitWDnnf2Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(3, false);
            createWDnnf2(circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * wDNNF 2 (missing variables)
     */
    TEST_CASE("[Circuit] wDNNF 2 (missing variables)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitWDnnf2MissingVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(4, false);
            createWDnnf2(circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * wDNNF 2 (smoothness)
     */
    TEST_CASE("[Circuit] wDNNF 2 (smoothness)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitWDnnf2SmoothnessResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(3, true);
            createWDnnf2(circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * d-DNNF
     */
    TEST_CASE("[Circuit] d-DNNF", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitDDnnfResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(6, smooth);
            createDDnnf(smooth, circuit);
            printCircuit(circuit, actualResult);
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
    TEST_CASE("[Circuit] sd-DNNF (mapping)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitSDDnnfMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            MappingFromVariableToOriginalVariableType mapping { { (VarT)1, (OriginalVarType)1 },
                                                                { (VarT)2, (OriginalVarType)6 },
                                                                { (VarT)3, (OriginalVarType)4 },
                                                                { (VarT)4, (OriginalVarType)3 },
                                                                { (VarT)5, (OriginalVarType)9 },
                                                                { (VarT)6, (OriginalVarType)8 } };
            MappingFromOriginalVariableToVariableType invertedMapping = Hydra::Other::invertMap(mapping);
            printMapping(mapping, actualResult);

            bool smooth = true;
            CircuitType circuit(7, smooth,
                                std::move(mapping), std::move(invertedMapping));
            createDDnnf(smooth, circuit);

            circuit.printCircuit(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * d-DNNF (missing variables)
     */
    TEST_CASE("[Circuit] d-DNNF (missing variables)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitDDnnfMissingVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(7, smooth);
            createDDnnf(smooth, circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sd-DNNF
     */
    TEST_CASE("[Circuit] sd-DNNF", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitSDDnnfResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = true;
            CircuitType circuit(6, smooth);
            createDDnnf(smooth, circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {Krom-C}-d-BDMC
     */
    TEST_CASE("[Circuit] {Krom-C}-d-BDMC", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitKromCDBdmcResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(4, smooth);
            createKromCDBdmc(smooth, circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {Krom-C}-d-BDMC (missing variables)
     */
    TEST_CASE("[Circuit] {Krom-C}-d-BDMC (missing variables)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitKromCDBdmcMissingVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(5, smooth);
            createKromCDBdmc(smooth, circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {Krom-C}-sd-BDMC
     */
    TEST_CASE("[Circuit] {Krom-C}-sd-BDMC", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitKromCSDBdmcResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = true;
            CircuitType circuit(4, smooth);
            createKromCDBdmc(smooth, circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {renH-C}-d-BDMC
     */
    TEST_CASE("[Circuit] {renH-C}-d-BDMC", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitRenHCDBdmcResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(5, smooth);
            createRenHCDBdmc(smooth, circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {renH-C}-d-BDMC (missing variables)
     */
    TEST_CASE("[Circuit] {renH-C}-d-BDMC (missing variables)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitRenHCDBdmcMissingVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(6, smooth);
            createRenHCDBdmc(smooth, circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {renH-C}-sd-BDMC
     */
    TEST_CASE("[Circuit] {renH-C}-sd-BDMC", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitRenHCSDBdmcResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = true;
            CircuitType circuit(5, smooth);
            createRenHCDBdmc(smooth, circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * NNF
     */
    TEST_CASE("[Circuit] NNF", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNnfResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(3, smooth);
            createNnf(smooth, circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * s-NNF
     */
    TEST_CASE("[Circuit] s-NNF", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitSNnfResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = true;
            CircuitType circuit(3, smooth);
            createNnf(smooth, circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * NNF (missing variables)
     */
    TEST_CASE("[Circuit] NNF (missing variables)", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitNnfMissingVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(4, smooth);
            createNnf(smooth, circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * DNNF
     */
    TEST_CASE("[Circuit] DNNF", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitDnnfResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(2, false);
            createDnnf(circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * s-DNNF
     */
    TEST_CASE("[Circuit] s-DNNF", "[Circuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitSDnnfResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(1, true);
            createSDnnf(circuit);
            printCircuit(circuit, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif
}   // namespace HydraTest::Circuit
