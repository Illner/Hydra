#include <cassert>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/other/container/computeConnectedComponents/ComputeConnectedComponentsTestResult.hpp"

#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/computeConnectedComponents/ComputeConnectedComponents.hpp"

namespace HydraTest::Container::ComputeConnectedComponents {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;

    using VariableSetType = typename Hydra::Formula::Literal<VarT, LiteralT>::VariableSetType;
    using VariableVectorType = typename Hydra::Formula::Literal<VarT, LiteralT>::VariableVectorType;
    using ComputeConnectedComponentsType = Hydra::Container::ComputeConnectedComponents::ComputeConnectedComponents<VarT, LiteralT>;
    using ConnectedComponentType = typename Hydra::Container::ComputeConnectedComponents::ComputeConnectedComponents<VarT, LiteralT>::ConnectedComponentType;
    using ConnectedComponentStruct = typename Hydra::Container::ComputeConnectedComponents::ComputeConnectedComponents<VarT, LiteralT>::ConnectedComponentStruct;
    //endregion

    //region Functions
    void printComputeConnectedComponents(const ComputeConnectedComponentsType& computeConnectedComponents, std::stringstream& actualResult) {
        computeConnectedComponents.printComputeConnectedComponents(actualResult);
        actualResult << std::endl;
    }

    void printIsEmpty(const ComputeConnectedComponentsType& computeConnectedComponents, std::stringstream& actualResult) {
        bool isEmpty = computeConnectedComponents.isEmpty();

        actualResult << "Is empty: " << std::to_string(isEmpty) << std::endl;
        actualResult << std::endl;
    }

    void printConnectedComponent(const ConnectedComponentType& connectedComponent, std::stringstream& actualResult) {
        actualResult << "Connected components" << std::endl;

        for (const ConnectedComponentStruct& connectedComponentStruct : connectedComponent) {
            actualResult << "\t";
            for (VarT var : Hydra::Other::sortUnorderedSet(connectedComponentStruct.variableSet))
                actualResult << std::to_string(var) << " ";
            actualResult << std::endl;
        }

        actualResult << std::endl;
    }

    void processAddConnections(ComputeConnectedComponentsType& computeConnectedComponents, const std::vector<VariableVectorType>& edges,
                               std::stringstream& actualResult, bool print = true) {
        for (const VariableVectorType& edge : edges) {
            assert(edge.size() == 2);

            VarT var1 = edge[0];
            VarT var2 = edge[1];

            if (print)
                actualResult << "Add connection: " << std::to_string(var1) << " - " << std::to_string(var2) << std::endl;

            computeConnectedComponents.addConnection(var1, var2);

            if (print)
                printComputeConnectedComponents(computeConnectedComponents, actualResult);
        }
    }
    //endregion

    /**
     * Constructor
     */
    TEST_CASE("[Container::ComputeConnectedComponents] constructor", "[Container::ComputeConnectedComponents]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          computeConnectedComponentsConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ComputeConnectedComponentsType computeConnectedComponents = ComputeConnectedComponentsType(3);
            printComputeConnectedComponents(computeConnectedComponents, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Is empty
     */
    TEST_CASE("[Container::ComputeConnectedComponents] is empty", "[Container::ComputeConnectedComponents]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          computeConnectedComponentsIsEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ComputeConnectedComponentsType computeConnectedComponents = ComputeConnectedComponentsType(5);
            printComputeConnectedComponents(computeConnectedComponents, actualResult);

            printIsEmpty(computeConnectedComponents, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Add connection
     */
    TEST_CASE("[Container::ComputeConnectedComponents] add connection", "[Container::ComputeConnectedComponents]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          computeConnectedComponentsAddConnectionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ComputeConnectedComponentsType computeConnectedComponents = ComputeConnectedComponentsType(3);
            printComputeConnectedComponents(computeConnectedComponents, actualResult);

            processAddConnections(computeConnectedComponents, { { 1, 2 }, { 2, 1 }, { 2, 3 }, { 3, 2 }, { 1, 3 }, { 3, 1 } }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Path compression
     */
    TEST_CASE("[Container::ComputeConnectedComponents] path compression", "[Container::ComputeConnectedComponents]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          computeConnectedComponentsPathCompressionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ComputeConnectedComponentsType computeConnectedComponents = ComputeConnectedComponentsType(8);

            computeConnectedComponents.addConnection(VarT(1), VarT(2));
            computeConnectedComponents.addConnection(VarT(3), VarT(4));
            computeConnectedComponents.addConnection(VarT(5), VarT(6));
            computeConnectedComponents.addConnection(VarT(7), VarT(8));

            computeConnectedComponents.addConnection(VarT(1), VarT(3));
            computeConnectedComponents.addConnection(VarT(6), VarT(8));

            computeConnectedComponents.addConnection(VarT(2), VarT(7));

            printComputeConnectedComponents(computeConnectedComponents, actualResult);

            computeConnectedComponents.addConnection(VarT(8), VarT(1));
            printComputeConnectedComponents(computeConnectedComponents, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Rank
     */
    TEST_CASE("[Container::ComputeConnectedComponents] rank", "[Container::ComputeConnectedComponents]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          computeConnectedComponentsRankResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ComputeConnectedComponentsType computeConnectedComponents = ComputeConnectedComponentsType(6);
            printComputeConnectedComponents(computeConnectedComponents, actualResult);

            processAddConnections(computeConnectedComponents, { { 1, 2 }, { 1, 3 }, { 4, 1 }, { 5, 6 }, { 1, 5 } }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Compute connected components
     */
    TEST_CASE("[Container::ComputeConnectedComponents] compute connected components", "[Container::ComputeConnectedComponents]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          computeConnectedComponentsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ComputeConnectedComponentsType computeConnectedComponents = ComputeConnectedComponentsType(10);
            printComputeConnectedComponents(computeConnectedComponents, actualResult);

            processAddConnections(computeConnectedComponents, { { 1, 2 }, { 3, 4 }, { 2, 4 }, { 6, 7 }, { 8, 9 }, { 8, 10 }, { 9, 10 } }, actualResult, false);
            printComputeConnectedComponents(computeConnectedComponents, actualResult);
            printIsEmpty(computeConnectedComponents, actualResult);

            ConnectedComponentType connectedComponent = computeConnectedComponents.computeConnectedComponents({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
            printConnectedComponent(connectedComponent, actualResult);
            printIsEmpty(computeConnectedComponents, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Compute connected components (discontinuous)
     */
    TEST_CASE("[Container::ComputeConnectedComponents] compute connected components (discontinuous)", "[Container::ComputeConnectedComponents]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          computeConnectedComponentsDiscontinuousResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ComputeConnectedComponentsType computeConnectedComponents = ComputeConnectedComponentsType(12);
            printComputeConnectedComponents(computeConnectedComponents, actualResult);

            processAddConnections(computeConnectedComponents, { { 4, 3 }, { 9, 10 }, { 8, 9 } }, actualResult, false);
            printComputeConnectedComponents(computeConnectedComponents, actualResult);
            printIsEmpty(computeConnectedComponents, actualResult);

            ConnectedComponentType connectedComponent = computeConnectedComponents.computeConnectedComponents({ 2, 3, 4, 6, 8, 9, 10, 12 });
            printConnectedComponent(connectedComponent, actualResult);
            printIsEmpty(computeConnectedComponents, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Container::ComputeConnectedComponents
