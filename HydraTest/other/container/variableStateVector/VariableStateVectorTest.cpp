#include <cassert>
#include <sstream>
#include <stdexcept>
#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/other/container/variableStateVector/VariableStateVectorTestResult.hpp"

#include "Hydra/other/container/variableStateVector/VariableStateVector.hpp"

#include "Hydra/other/container/exceptions/VariableStateVectorException.hpp"

namespace HydraTest::Container::VariableStateVector {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;

    using VariableStateVectorType = Hydra::Container::VariableStateVector::VariableStateVector<VarT, LiteralT>;

    using LiteralType = typename VariableStateVectorType::LiteralType;
    //endregion

    //region Functions
    void printVariableStateVector(const VariableStateVectorType& variableStateVector, std::stringstream& actualResult) {
        actualResult << "Number of variables: " << std::to_string(variableStateVector.getNumberOfVariables()) << std::endl;
        variableStateVector.printVariableStateVectorDebug(actualResult);
        actualResult << std::endl;
    }

    void printAreAllVariablesUnAssigned(const VariableStateVectorType& variableStateVector, std::stringstream& actualResult) {
        actualResult << "Are all variables assigned: " << std::to_string(variableStateVector.areAllVariablesAssigned()) << std::endl;
        actualResult << "Are all variables unassigned: " << std::to_string(variableStateVector.areAllVariablesUnassigned()) << std::endl;
        printVariableStateVector(variableStateVector, actualResult);
    }

    void assignAllVariables(VariableStateVectorType& variableStateVector) {
        bool sign = true;

        for (VarT var = 1; var <= variableStateVector.getNumberOfVariables(); ++var) {
            assert(!variableStateVector.isAssigned(var));   // not assigned

            variableStateVector.assignVariable(var, sign);

            sign = !sign;
        }
    }

    void unassignAllVariables(VariableStateVectorType& variableStateVector) {
        for (VarT var = 1; var <= variableStateVector.getNumberOfVariables(); ++var) {
            assert(variableStateVector.isAssigned(var));   // assigned

            variableStateVector.unassignVariable(var);
        }
    }

    void assignOddVariables(VariableStateVectorType& variableStateVector) {
        bool sign = true;

        for (VarT var = 1; var <= variableStateVector.getNumberOfVariables(); var += 2) {
            assert(!variableStateVector.isAssigned(var));   // not assigned

            variableStateVector.assignVariable(var, sign);

            sign = !sign;
        }
    }

    void assignEvenVariables(VariableStateVectorType& variableStateVector) {
        bool sign = true;

        for (VarT var = 2; var <= variableStateVector.getNumberOfVariables(); var += 2) {
            assert(!variableStateVector.isAssigned(var));   // not assigned

            variableStateVector.assignVariable(var, sign);

            sign = !sign;
        }
    }
    //endregion

    /**
     * Constructor
     */
    TEST_CASE("[Container::VariableStateVector] constructor", "[Container::VariableStateVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          variableStateVectorConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            for (VarT numberOfVariables = 1; numberOfVariables <= 5; ++numberOfVariables) {
                VariableStateVectorType variableStateVector(numberOfVariables);

                printVariableStateVector(variableStateVector, actualResult);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Constructor (assigned all variables)
     */
    TEST_CASE("[Container::VariableStateVector] constructor (assigned all variables)", "[Container::VariableStateVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          variableStateVectorConstructorAssignedAllVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            for (VarT numberOfVariables = 1; numberOfVariables <= 5; ++numberOfVariables) {
                VariableStateVectorType variableStateVector(numberOfVariables);
                assignAllVariables(variableStateVector);

                printVariableStateVector(variableStateVector, actualResult);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Is assigned (odd)
     */
    TEST_CASE("[Container::VariableStateVector] is assigned (odd)", "[Container::VariableStateVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          variableStateVectorIsAssignedOddResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableStateVectorType variableStateVector(6);
            assignOddVariables(variableStateVector);
            printVariableStateVector(variableStateVector, actualResult);

            for (VarT var = 1; var <= variableStateVector.getNumberOfVariables(); ++var) {
                bool isAssigned = variableStateVector.isAssigned(var);

                actualResult << std::to_string(var) << ": " << std::to_string(isAssigned) << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Is assigned (even)
     */
    TEST_CASE("[Container::VariableStateVector] is assigned (even)", "[Container::VariableStateVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          variableStateVectorIsAssignedEvenResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableStateVectorType variableStateVector(6);
            assignEvenVariables(variableStateVector);
            printVariableStateVector(variableStateVector, actualResult);

            for (VarT var = 1; var <= variableStateVector.getNumberOfVariables(); ++var) {
                bool isAssigned = variableStateVector.isAssigned(var);

                actualResult << std::to_string(var) << ": " << std::to_string(isAssigned) << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Unassign
     */
    TEST_CASE("[Container::VariableStateVector] unassign", "[Container::VariableStateVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          variableStateVectorUnassignResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableStateVectorType variableStateVector(6);
            assignOddVariables(variableStateVector);
            printVariableStateVector(variableStateVector, actualResult);

            for (VarT var = 1; var <= variableStateVector.getNumberOfVariables(); ++var) {
                actualResult << "Unassign: " << std::to_string(var) << std::endl;

                try {
                    variableStateVector.unassignVariable(var);
                }
                catch (const Hydra::Exception::Container::VariableStateVector::VariableStateVectorException& e) {
                    actualResult << e.what() << std::endl;
                }

                printVariableStateVector(variableStateVector, actualResult);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Assign
     */
    TEST_CASE("[Container::VariableStateVector] assign", "[Container::VariableStateVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          variableStateVectorAssignResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableStateVectorType variableStateVector(6);
            assignEvenVariables(variableStateVector);
            printVariableStateVector(variableStateVector, actualResult);

            bool sign = false;

            for (VarT var = 1; var <= variableStateVector.getNumberOfVariables(); ++var) {
                LiteralType lit(var, sign);
                sign = !sign;

                actualResult << "Assign: " << lit << std::endl;

                try {
                    variableStateVector.assignVariable(lit);
                }
                catch (const Hydra::Exception::Container::VariableStateVector::VariableStateVectorException& e) {
                    actualResult << e.what() << std::endl;
                }

                printVariableStateVector(variableStateVector, actualResult);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Get sign
     */
    TEST_CASE("[Container::VariableStateVector] get sign", "[Container::VariableStateVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          variableStateVectorGetSignResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableStateVectorType variableStateVector(7);
            assignOddVariables(variableStateVector);
            printVariableStateVector(variableStateVector, actualResult);

            for (VarT var = 1; var <= variableStateVector.getNumberOfVariables(); ++var) {
                actualResult << "Var: " << std::to_string(var) << std::endl;

                try {
                    bool sign = variableStateVector.getSignOfAssignedVariable(var);

                    actualResult << "Sign: " << std::to_string(sign) << std::endl;
                }
                catch (const Hydra::Exception::Container::VariableStateVector::VariableStateVectorException& e) {
                    actualResult << e.what() << std::endl;
                }

                printVariableStateVector(variableStateVector, actualResult);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Is literal satisfied
     */
    TEST_CASE("[Container::VariableStateVector] is literal satisfied", "[Container::VariableStateVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          variableStateVectorIsLiteralSatisfiedResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableStateVectorType variableStateVector(7);
            assignEvenVariables(variableStateVector);
            printVariableStateVector(variableStateVector, actualResult);

            for (VarT var = 1; var <= variableStateVector.getNumberOfVariables(); ++var) {
                for (bool sign : { true, false }) {
                    LiteralType lit(var, sign);

                    actualResult << "Literal: " << lit << std::endl;

                    try {
                        bool isSatisfied = variableStateVector.isLiteralSatisfied(lit);

                        actualResult << "Is satisfied: " << std::to_string(isSatisfied) << std::endl;
                    }
                    catch (const Hydra::Exception::Container::VariableStateVector::VariableStateVectorException& e) {
                        actualResult << e.what() << std::endl;
                    }
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
     * Are all variables (un)assigned
     */
    TEST_CASE("[Container::VariableStateVector] are all variables (un)assigned", "[Container::VariableStateVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          variableStateVectorAreAllVariablesUnAssignedResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            // Empty
            VariableStateVectorType variableStateVector(8);
            printAreAllVariablesUnAssigned(variableStateVector, actualResult);

            // Half
            assignEvenVariables(variableStateVector);
            printAreAllVariablesUnAssigned(variableStateVector, actualResult);

            // Full
            assignOddVariables(variableStateVector);
            printAreAllVariablesUnAssigned(variableStateVector, actualResult);

            // Empty
            unassignAllVariables(variableStateVector);
            printAreAllVariablesUnAssigned(variableStateVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear
     */
    TEST_CASE("[Container::VariableStateVector] clear", "[Container::VariableStateVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          variableStateVectorClearResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableStateVectorType variableStateVector(10);

            for (bool odd : { true, false }) {
                if (odd)
                    assignOddVariables(variableStateVector);
                else
                    assignEvenVariables(variableStateVector);

                printVariableStateVector(variableStateVector, actualResult);

                actualResult << "Clear" << std::endl;

                variableStateVector.clear();
                printVariableStateVector(variableStateVector, actualResult);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Container::VariableStateVector
