#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/circuit/CreateCircuit.hpp"
#include "HydraTest/circuit/copySubcircuit/CircuitCopySubcircuitTestResult.hpp"

#include "Hydra/circuit/Circuit.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/Other.hpp"

#include "Hydra/circuit/enums/CircuitTypeEnum.hpp"
#include "Hydra/circuit/node/enums/DecomposabilityTypeEnum.hpp"

namespace HydraTest::Circuit::CopySubcircuit {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;
    using ClauseIdT = char8_t;   // useless, because of copy subcircuit

    using LiteralType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::LiteralType;
    using VariableSortedVectorType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::VariableSortedVectorType;
    using MappingFromVariableToLiteralType = typename Hydra::Formula::Literal<VarT, LiteralT>::MappingFromVariableToLiteralType;

    using CircuitType = Hydra::Circuit::Circuit<VarT, LiteralT>;
    using MappingFromVariableToLiteralVectorType = std::vector<MappingFromVariableToLiteralType>;

    using CircuitTypeEnum = Hydra::Circuit::CircuitTypeEnum;
    using DecomposabilityTypeEnum = Hydra::Circuit::Node::DecomposabilityTypeEnum;
    //endregion

    //region Functions
    void printCircuit(CircuitType& circuit, std::stringstream& actualResult) {
        circuit.printCircuitDebug(actualResult);
    }

    void printMapping(const MappingFromVariableToLiteralType& mapping, std::stringstream& actualResult) {
        VariableSortedVectorType variableSortedVector = Hydra::Other::extractKeysFromMap(mapping, true);

        actualResult << "---------------------" << std::endl;
        actualResult << "       Mapping       " << std::endl;
        actualResult << "---------------------" << std::endl;
        for (VarT var : variableSortedVector)
            actualResult << std::to_string(var) << " -> " << mapping.at(var) << std::endl;
        actualResult << std::endl;
    }

    void copySubcircuit(CircuitType& circuit, IdNodeType rootId, const MappingFromVariableToLiteralType& mapping,
                        CircuitTypeEnum circuitType, std::stringstream& actualResult, bool print = true) {
        if (print) {
            actualResult << "----------------------" << std::endl;
            actualResult << "Before copy subcircuit" << std::endl;
            actualResult << "----------------------" << std::endl;
            printCircuit(circuit, actualResult);

            printMapping(mapping, actualResult);
        }

        bool isVariableToLiteralMapping = !Hydra::Other::containInSet(Hydra::Circuit::caraCachingSchemeVariableToVariableMappingCircuitTypeSet, circuitType);

        // Copy subcircuit
        IdNodeType newNodeId = circuit.copySubcircuit<ClauseIdT>(rootId, mapping, isVariableToLiteralMapping);
        circuit.createAndInnerNode({ rootId, newNodeId },
                                   DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);
        circuit.setRoot();

        if (print) {
            actualResult << "---------------------" << std::endl;
            actualResult << "After copy subcircuit" << std::endl;
            actualResult << "---------------------" << std::endl;
            printCircuit(circuit, actualResult);
        }
    }
    //endregion

    #if defined(BELLA_COMPILER)
    /**
     * NNF (positive mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] NNF (positive mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitNnfPositiveMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(6, smooth);
            IdNodeType rootId = Circuit::createNnf(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(6, true) },
                                                       { (VarT)2, LiteralType(5, true) },
                                                       { (VarT)3, LiteralType(4, true) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::NNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * NNF (negative mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] NNF (negative mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitNnfNegativeMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(6, smooth);
            IdNodeType rootId = Circuit::createNnf(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(6, false) },
                                                       { (VarT)2, LiteralType(5, false) },
                                                       { (VarT)3, LiteralType(4, false) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::NNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * s-NNF (positive mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] s-NNF (positive mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitSNnfPositiveMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = true;
            CircuitType circuit(6, smooth);
            IdNodeType rootId = Circuit::createNnf(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(6, true) },
                                                       { (VarT)2, LiteralType(5, true) },
                                                       { (VarT)3, LiteralType(4, true) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::s_NNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * s-NNF (negative mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] s-NNF (negative mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitSNnfNegativeMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = true;
            CircuitType circuit(6, smooth);
            IdNodeType rootId = Circuit::createNnf(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(6, false) },
                                                       { (VarT)2, LiteralType(5, false) },
                                                       { (VarT)3, LiteralType(4, false) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::s_NNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * DNNF (positive mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] DNNF (positive mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitDnnfPositiveMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(4, false);
            IdNodeType rootId = Circuit::createDnnf(circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(4, true) },
                                                       { (VarT)2, LiteralType(3, true) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::DNNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * DNNF (negative mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] DNNF (negative mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitDnnfNegativeMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(4, false);
            IdNodeType rootId = Circuit::createDnnf(circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(4, false) },
                                                       { (VarT)2, LiteralType(3, false) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::DNNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * s-DNNF (positive mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] s-DNNF (positive mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitSDnnfPositiveMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(2, true);
            IdNodeType rootId = Circuit::createSDnnf(circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(2, true) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::s_DNNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * s-DNNF (negative mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] s-DNNF (negative mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitSDnnfNegativeMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(2, true);
            IdNodeType rootId = Circuit::createSDnnf(circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(2, false) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::s_DNNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * pwDNNF (positive mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] pwDNNF (positive mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitPWDnnfPositiveMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(12, false);
            IdNodeType rootId = Circuit::createPWDnnf(circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(12, true) },
                                                       { (VarT)2, LiteralType(11, true) },
                                                       { (VarT)3, LiteralType(10, true) },
                                                       { (VarT)4, LiteralType(9, true) },
                                                       { (VarT)5, LiteralType(8, true) },
                                                       { (VarT)6, LiteralType(7, true) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::pwDNNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    //    /**
    //     * pwDNNF (negative mapping)
    //     */
    //    TEST_CASE("[Circuit::CopySubcircuit] pwDNNF (negative mapping)", "[Circuit::CopySubcircuit]") {
    //        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
    //                          circuitCopySubcircuitPWDnnfNegativeMappingResult);
    //        std::stringstream& actualResult = test.getStringStream();
    //
    //        try {
    //            CircuitType circuit(12, false);
    //            IdNodeType rootId = Circuit::createPWDnnf(circuit, false);
    //
    //            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(12, false) },
    //                                                       { (VarT)2, LiteralType(11, false) },
    //                                                       { (VarT)3, LiteralType(10, false) },
    //                                                       { (VarT)4, LiteralType(9, false) },
    //                                                       { (VarT)5, LiteralType(8, false) },
    //                                                       { (VarT)6, LiteralType(7, false) } };
    //
    //            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::pwDNNF, actualResult);
    //        }
    //        catch (const std::exception& e) {
    //            actualResult << e.what() << std::endl;
    //        }
    //
    //        // test.saveActualResultToFile();
    //        REQUIRE(test.checkTest());
    //    }

    /**
     * nwDNNF (positive mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] nwDNNF (positive mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitNWDnnfPositiveMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(6, false);
            IdNodeType rootId = Circuit::createNWDnnf(circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(6, true) },
                                                       { (VarT)2, LiteralType(5, true) },
                                                       { (VarT)3, LiteralType(4, true) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::nwDNNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    //    /**
    //     * nwDNNF (negative mapping)
    //     */
    //    TEST_CASE("[Circuit::CopySubcircuit] nwDNNF (negative mapping)", "[Circuit::CopySubcircuit]") {
    //        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
    //                          circuitCopySubcircuitNWDnnfNegativeMappingResult);
    //        std::stringstream& actualResult = test.getStringStream();
    //
    //        try {
    //            CircuitType circuit(6, false);
    //            IdNodeType rootId = Circuit::createNWDnnf(circuit, false);
    //
    //            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(6, false) },
    //                                                       { (VarT)2, LiteralType(5, false) },
    //                                                       { (VarT)3, LiteralType(4, false) } };
    //
    //            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::nwDNNF, actualResult);
    //        }
    //        catch (const std::exception& e) {
    //            actualResult << e.what() << std::endl;
    //        }
    //
    //        // test.saveActualResultToFile();
    //        REQUIRE(test.checkTest());
    //    }

    /**
     * wDNNF 1 (positive mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] wDNNF 1 (positive mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitWDnnf1PositiveMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(4, false);
            IdNodeType rootId = Circuit::createWDnnf1(circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(4, true) },
                                                       { (VarT)2, LiteralType(3, true) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::wDNNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * wDNNF 1 (negative mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] wDNNF 1 (negative mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitWDnnf1NegativeMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(4, false);
            IdNodeType rootId = Circuit::createWDnnf1(circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(4, false) },
                                                       { (VarT)2, LiteralType(3, false) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::wDNNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * wDNNF 2 (positive mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] wDNNF 2 (positive mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitWDnnf2PositiveMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(6, false);
            IdNodeType rootId = Circuit::createWDnnf2(circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(6, true) },
                                                       { (VarT)2, LiteralType(5, true) },
                                                       { (VarT)3, LiteralType(4, true) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::wDNNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * wDNNF 2 (negative mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] wDNNF 2 (negative mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitWDnnf2NegativeMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CircuitType circuit(6, false);
            IdNodeType rootId = Circuit::createWDnnf2(circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(6, false) },
                                                       { (VarT)2, LiteralType(5, false) },
                                                       { (VarT)3, LiteralType(4, false) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::wDNNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * d-DNNF (positive mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] d-DNNF (positive mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitDDnnfPositiveMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(12, smooth);
            IdNodeType rootId = Circuit::createDDnnf(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(12, true) },
                                                       { (VarT)2, LiteralType(11, true) },
                                                       { (VarT)3, LiteralType(10, true) },
                                                       { (VarT)4, LiteralType(9, true) },
                                                       { (VarT)5, LiteralType(8, true) },
                                                       { (VarT)6, LiteralType(7, true) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::d_DNNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * d-DNNF (negative mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] d-DNNF (negative mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitDDnnfNegativeMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(12, smooth);
            IdNodeType rootId = Circuit::createDDnnf(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(12, false) },
                                                       { (VarT)2, LiteralType(11, false) },
                                                       { (VarT)3, LiteralType(10, false) },
                                                       { (VarT)4, LiteralType(9, false) },
                                                       { (VarT)5, LiteralType(8, false) },
                                                       { (VarT)6, LiteralType(7, false) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::d_DNNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sd-DNNF (positive mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] sd-DNNF (positive mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitSDDnnfPositiveMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = true;
            CircuitType circuit(12, smooth);
            IdNodeType rootId = Circuit::createDDnnf(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(12, true) },
                                                       { (VarT)2, LiteralType(11, true) },
                                                       { (VarT)3, LiteralType(10, true) },
                                                       { (VarT)4, LiteralType(9, true) },
                                                       { (VarT)5, LiteralType(8, true) },
                                                       { (VarT)6, LiteralType(7, true) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::sd_DNNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sd-DNNF (negative mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] sd-DNNF (negative mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitSDDnnfNegativeMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = true;
            CircuitType circuit(12, smooth);
            IdNodeType rootId = Circuit::createDDnnf(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(12, false) },
                                                       { (VarT)2, LiteralType(11, false) },
                                                       { (VarT)3, LiteralType(10, false) },
                                                       { (VarT)4, LiteralType(9, false) },
                                                       { (VarT)5, LiteralType(8, false) },
                                                       { (VarT)6, LiteralType(7, false) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::sd_DNNF, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {Krom-C}-d-BDMC (positive mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] {Krom-C}-d-BDMC (positive mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitKromCDBdmcPositiveMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(8, smooth);
            IdNodeType rootId = Circuit::createKromCDBdmc(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(8, true) },
                                                       { (VarT)2, LiteralType(7, true) },
                                                       { (VarT)3, LiteralType(6, true) },
                                                       { (VarT)4, LiteralType(5, true) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::Krom_C_d_BDMC, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {Krom-C}-d-BDMC (negative mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] {Krom-C}-d-BDMC (negative mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitKromCDBdmcNegativeMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(8, smooth);
            IdNodeType rootId = Circuit::createKromCDBdmc(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(8, false) },
                                                       { (VarT)2, LiteralType(7, false) },
                                                       { (VarT)3, LiteralType(6, false) },
                                                       { (VarT)4, LiteralType(5, false) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::Krom_C_d_BDMC, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {Krom-C}-sd-BDMC (positive mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] {Krom-C}-sd-BDMC (positive mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitKromCSDBdmcPositiveMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = true;
            CircuitType circuit(8, smooth);
            IdNodeType rootId = Circuit::createKromCDBdmc(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(8, true) },
                                                       { (VarT)2, LiteralType(7, true) },
                                                       { (VarT)3, LiteralType(6, true) },
                                                       { (VarT)4, LiteralType(5, true) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::Krom_C_sd_BDMC, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {Krom-C}-sd-BDMC (negative mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] {Krom-C}-sd-BDMC (negative mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitKromCSDBdmcNegativeMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = true;
            CircuitType circuit(8, smooth);
            IdNodeType rootId = Circuit::createKromCDBdmc(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(8, false) },
                                                       { (VarT)2, LiteralType(7, false) },
                                                       { (VarT)3, LiteralType(6, false) },
                                                       { (VarT)4, LiteralType(5, false) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::Krom_C_sd_BDMC, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {renH-C}-d-BDMC (positive mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] {renH-C}-d-BDMC (positive mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitRenHCDBdmcPositiveMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(10, smooth);
            IdNodeType rootId = Circuit::createRenHCDBdmc(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(10, true) },
                                                       { (VarT)2, LiteralType(9, true) },
                                                       { (VarT)3, LiteralType(8, true) },
                                                       { (VarT)4, LiteralType(7, true) },
                                                       { (VarT)5, LiteralType(6, true) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::renH_C_d_BDMC, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {renH-C}-d-BDMC (negative mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] {renH-C}-d-BDMC (negative mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitRenHCDBdmcNegativeMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(10, smooth);
            IdNodeType rootId = Circuit::createRenHCDBdmc(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(10, false) },
                                                       { (VarT)2, LiteralType(9, false) },
                                                       { (VarT)3, LiteralType(8, false) },
                                                       { (VarT)4, LiteralType(7, false) },
                                                       { (VarT)5, LiteralType(6, false) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::renH_C_d_BDMC, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {renH-C}-sd-BDMC (positive mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] {renH-C}-sd-BDMC (positive mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitRenHCSDBdmcPositiveMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = true;
            CircuitType circuit(10, smooth);
            IdNodeType rootId = Circuit::createRenHCDBdmc(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(10, true) },
                                                       { (VarT)2, LiteralType(9, true) },
                                                       { (VarT)3, LiteralType(8, true) },
                                                       { (VarT)4, LiteralType(7, true) },
                                                       { (VarT)5, LiteralType(6, true) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::renH_C_sd_BDMC, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {renH-C}-sd-BDMC (negative mapping)
     */
    TEST_CASE("[Circuit::CopySubcircuit] {renH-C}-sd-BDMC (negative mapping)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitRenHCSDBdmcNegativeMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = true;
            CircuitType circuit(10, smooth);
            IdNodeType rootId = Circuit::createRenHCDBdmc(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(10, false) },
                                                       { (VarT)2, LiteralType(9, false) },
                                                       { (VarT)3, LiteralType(8, false) },
                                                       { (VarT)4, LiteralType(7, false) },
                                                       { (VarT)5, LiteralType(6, false) } };

            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::renH_C_sd_BDMC, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid mapping (no bijective)
     */
    TEST_CASE("[Circuit::CopySubcircuit] invalid mapping (no bijective)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitInvalidMappingNoBijectiveResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(3, smooth);
            IdNodeType rootId = Circuit::createNnf(smooth, circuit, false);

            MappingFromVariableToLiteralVectorType mappingVector;
            mappingVector.push_back({ { (VarT)1, LiteralType(1, true) },
                                      { (VarT)2, LiteralType(2, true) },
                                      { (VarT)3, LiteralType(1, false) } });
            mappingVector.push_back({ { (VarT)1, LiteralType(2, true) },
                                      { (VarT)2, LiteralType(1, true) },
                                      { (VarT)3, LiteralType(2, true) } });
            mappingVector.push_back({ { (VarT)1, LiteralType(2, false) },
                                      { (VarT)2, LiteralType(1, false) },
                                      { (VarT)3, LiteralType(2, false) } });

            for (const MappingFromVariableToLiteralType& mapping : mappingVector) {
                printMapping(mapping, actualResult);

                try {
                    copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::NNF, actualResult, false);
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
     * Invalid mapping (missing variables)
     */
    TEST_CASE("[Circuit::CopySubcircuit] invalid mapping (missing variables)", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitInvalidMappingMissingVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(3, smooth);
            IdNodeType rootId = Circuit::createNnf(smooth, circuit, false);

            MappingFromVariableToLiteralVectorType mappingVector;
            mappingVector.push_back({ { (VarT)1, LiteralType(1, true) },
                                      { (VarT)2, LiteralType(2, true) } });
            mappingVector.push_back({ { (VarT)1, LiteralType(1, true) },
                                      { (VarT)3, LiteralType(3, true) } });
            mappingVector.push_back({ { (VarT)2, LiteralType(2, true) },
                                      { (VarT)3, LiteralType(3, true) } });

            for (const MappingFromVariableToLiteralType& mapping : mappingVector) {
                printMapping(mapping, actualResult);

                try {
                    copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::NNF, actualResult, false);
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
     * Identical mapping
     */
    TEST_CASE("[Circuit::CopySubcircuit] identical mapping", "[Circuit::CopySubcircuit]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitCopySubcircuitIdenticalMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            bool smooth = false;
            CircuitType circuit(6, smooth);
            IdNodeType rootId = Circuit::createNnf(smooth, circuit, false);

            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(1, true) },
                                                       { (VarT)2, LiteralType(2, true) },
                                                       { (VarT)3, LiteralType(3, true) } };
            printMapping(mapping, actualResult);

            IdNodeType newNodeId = circuit.copySubcircuit<ClauseIdT>(rootId, mapping, true);
            actualResult << "New node ID: " << std::to_string(newNodeId) << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    //    /**
    //     * Invalid mapping (more keys)
    //     */
    //    TEST_CASE("[Circuit::CopySubcircuit] invalid mapping (more keys)", "[Circuit::CopySubcircuit]") {
    //        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
    //                          circuitCopySubcircuitInvalidMappingMoreKeysResult);
    //        std::stringstream& actualResult = test.getStringStream();
    //
    //        try {
    //            bool smooth = false;
    //            CircuitType circuit(4, smooth);
    //            IdNodeType rootId = Circuit::createNnf(smooth, circuit, false);
    //
    //            MappingFromVariableToLiteralType mapping { { (VarT)1, LiteralType(4, true) },
    //                                                       { (VarT)2, LiteralType(3, true) },
    //                                                       { (VarT)3, LiteralType(2, true) },
    //                                                       { (VarT)4, LiteralType(1, true) } };
    //
    //            printMapping(mapping, actualResult);
    //            copySubcircuit(circuit, rootId, mapping, CircuitTypeEnum::NNF, actualResult, false);
    //        }
    //        catch (const std::exception& e) {
    //            actualResult << e.what() << std::endl;
    //        }
    //
    //        // test.saveActualResultToFile();
    //        REQUIRE(test.checkTest());
    //    }
    #endif
}   // namespace HydraTest::Circuit::CopySubcircuit
