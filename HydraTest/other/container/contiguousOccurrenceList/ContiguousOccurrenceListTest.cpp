#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/external/unitTesting/Catch2/catch.hpp"
#include "HydraTest/other/container/contiguousOccurrenceList/ContiguousOccurrenceListTestResult.hpp"

#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/contiguousOccurrenceList/ContiguousOccurrenceList.hpp"

namespace HydraTest::Container::ContiguousOccurrenceList {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;
    using ClauseIdT = char8_t;

    using LiteralType = Hydra::Formula::Literal<VarT, LiteralT>::LiteralType;
    using FormulaSizeType = Hydra::Container::ContiguousOccurrenceList::FormulaSizeType;
    using LiteralVectorType = Hydra::Formula::Literal<VarT, LiteralT>::LiteralVectorType;
    using VariableVectorType = Hydra::Formula::Literal<VarT, LiteralT>::VariableVectorType;

    using ClauseIdVectorType = std::vector<ClauseIdT>;
    using ContiguousOccurrenceListType = Hydra::Container::ContiguousOccurrenceList::ContiguousOccurrenceList<VarT, LiteralT, ClauseIdT>;
    //endregion

    //region Functions
    void printContiguousOccurrenceList(const ContiguousOccurrenceListType& contiguousOccurrenceList, std::stringstream& actualResult) {
        contiguousOccurrenceList.printContiguousOccurrenceListDebug(actualResult);
        actualResult << std::endl;
    }

    void printRemovedClauses(const ClauseIdVectorType& removedClauseVector, std::stringstream& actualResult) {
        actualResult << "Removed clauses:";
        for (ClauseIdT clauseId : removedClauseVector)
            actualResult << " " << std::to_string(clauseId);
        actualResult << std::endl;
    }

    void printGetClauseIdVectorAndSet(const ContiguousOccurrenceListType& contiguousOccurrenceList,
                                      const LiteralVectorType& literalVector, const VariableVectorType& variableVector, std::stringstream& actualResult) {
        // Variable
        actualResult << "Variable: " << std::endl;
        for (VarT var : variableVector) {
            ClauseIdT numberOfOccurrencesTmp = contiguousOccurrenceList.getNumberOfVariableOccurrences(var);
            actualResult << std::to_string(var) << ": " << std::to_string(numberOfOccurrencesTmp) << std::endl;
        }
        actualResult << std::endl;

        // Vector
        actualResult << "Vector:" << std::endl;
        for (const LiteralType& lit : literalVector) {
            ClauseIdT numberOfOccurrencesTmp = contiguousOccurrenceList.getNumberOfOccurrences(lit);
            ClauseIdVectorType clauseIdVectorTmp = contiguousOccurrenceList.getClauseIdVector(lit);
            actualResult << lit << " (" << std::to_string(numberOfOccurrencesTmp) << "): ";
            for (ClauseIdT clauseId : clauseIdVectorTmp)
                actualResult << std::to_string(clauseId) << " ";
            actualResult << std::endl;
        }
        actualResult << std::endl;

        // Set
        actualResult << "Set:" << std::endl;
        for (const LiteralType& lit : literalVector) {
            ClauseIdVectorType clauseIdVectorTmp = Hydra::Other::sortUnorderedSet(contiguousOccurrenceList.getClauseIdSet(lit));
            actualResult << lit << ": ";
            for (ClauseIdT clauseId : clauseIdVectorTmp)
                actualResult << std::to_string(clauseId) << " ";
            actualResult << std::endl;
        }
        actualResult << std::endl;
    }
    //endregion

    //region ContiguousOccurrenceList
    ContiguousOccurrenceListType createContiguousOccurrenceList() {
        ContiguousOccurrenceListType contiguousOccurrenceList(5, { 0, 0, 1, 0, 2, 3 });

        LiteralType litPos1(1, true);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);

        contiguousOccurrenceList.addOccurrence(litPos1.getLiteralT(), 0);

        contiguousOccurrenceList.addOccurrence(litPos2.getLiteralT(), 1);
        contiguousOccurrenceList.addOccurrence(litPos2.getLiteralT(), 3);

        contiguousOccurrenceList.addOccurrence(litNeg2.getLiteralT(), 0);
        contiguousOccurrenceList.addOccurrence(litNeg2.getLiteralT(), 2);
        contiguousOccurrenceList.addOccurrence(litNeg2.getLiteralT(), 4);

        return contiguousOccurrenceList;
    }
    //endregion

    /**
     * Constructor
     */
    TEST_CASE("[Container::ContiguousOccurrenceList] constructor", "[Container::ContiguousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousOccurrenceListConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            actualResult << "contiguousOccurrenceList1:" << std::endl;
            ContiguousOccurrenceListType contiguousOccurrenceList1(2, { 0, 0, 1, 1 });
            printContiguousOccurrenceList(contiguousOccurrenceList1, actualResult);

            actualResult << "contiguousOccurrenceList2:" << std::endl;
            ContiguousOccurrenceListType contiguousOccurrenceList2(4, { 0, 0, 1, 0, 2, 3 });
            printContiguousOccurrenceList(contiguousOccurrenceList2, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy and move
     */
    TEST_CASE("[Container::ContiguousOccurrenceList] copy and move", "[Container::ContiguousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousOccurrenceListCopyAndMoveResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousOccurrenceListType contiguousOccurrenceList1(4, { 0, 0, 1, 0, 2, 3 });
            printContiguousOccurrenceList(contiguousOccurrenceList1, actualResult);

            actualResult << "Copy method" << std::endl;
            ContiguousOccurrenceListType contiguousOccurrenceList2 = contiguousOccurrenceList1;
            contiguousOccurrenceList2.addOccurrence(LiteralType(1, true).getLiteralT(), 0);
            printContiguousOccurrenceList(contiguousOccurrenceList1, actualResult);
            printContiguousOccurrenceList(contiguousOccurrenceList2, actualResult);

            actualResult << "Move method" << std::endl;
            ContiguousOccurrenceListType contiguousOccurrenceList3 = std::move(contiguousOccurrenceList1);
            printContiguousOccurrenceList(contiguousOccurrenceList3, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Add occurrence
     */
    TEST_CASE("[Container::ContiguousOccurrenceList] add occurrence", "[Container::ContiguousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousOccurrenceListAddOccurrenceResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousOccurrenceListType contiguousOccurrenceList(4, { 0, 0, 1, 0, 2, 3 });
            printContiguousOccurrenceList(contiguousOccurrenceList, actualResult);

            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);

            std::vector<std::pair<LiteralType, ClauseIdT>> occurrenceVector {
                { litPos2, 1 },
                { litNeg1, 0 },   // -
                { litPos1, 0 },
                { litPos1, 1 },   // -
                { litNeg2, 0 },
                { litPos1, 0 },   // d
                { litPos2, 3 },
                { litPos2, 1 },   // -
                { litNeg2, 1 },   // d (complementary)
                { litNeg2, 0 },   // d
                { litNeg2, 2 },
                { litNeg2, 3 }   // -
            };

            for (auto occurrencePair : occurrenceVector) {
                try {
                    actualResult << "Literal: " << occurrencePair.first
                                 << ", clause ID: " << std::to_string(occurrencePair.second) << std::endl;
                    contiguousOccurrenceList.addOccurrence(occurrencePair.first, occurrencePair.second);
                    printContiguousOccurrenceList(contiguousOccurrenceList, actualResult);
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl
                                 << std::endl;
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
     * Remove occurrence
     */
    TEST_CASE("[Container::ContiguousOccurrenceList] remove occurrence", "[Container::ContiguousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousOccurrenceListRemoveOccurrenceResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousOccurrenceListType contiguousOccurrenceList = createContiguousOccurrenceList();
            printContiguousOccurrenceList(contiguousOccurrenceList, actualResult);

            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);

            std::vector<std::pair<LiteralType, ClauseIdT>> occurrenceVector { { litPos2, 3 },
                                                                              { litNeg2, 4 },
                                                                              { litNeg1, 1 },   // -
                                                                              { litPos1, 0 },
                                                                              { litPos2, 1 },
                                                                              { litPos1, 0 },   // -
                                                                              { litPos1, 1 },   // -
                                                                              { litNeg2, 4 },   // -
                                                                              { litNeg2, 3 },   // -
                                                                              { litNeg2, 0 },
                                                                              { litNeg2, 2 } };

            for (auto occurrencePair : occurrenceVector) {
                try {
                    actualResult << "Literal: " << occurrencePair.first
                                 << ", clause ID: " << std::to_string(occurrencePair.second) << std::endl;
                    contiguousOccurrenceList.removeOccurrence(occurrencePair.first, occurrencePair.second);
                    printContiguousOccurrenceList(contiguousOccurrenceList, actualResult);
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl
                                 << std::endl;
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
     * Get occurrences
     */
    TEST_CASE("[Container::ContiguousOccurrenceList] get occurrences", "[Container::ContiguousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousOccurrenceListGetOccurrencesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousOccurrenceListType contiguousOccurrenceList = createContiguousOccurrenceList();
            printContiguousOccurrenceList(contiguousOccurrenceList, actualResult);

            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);

            VariableVectorType variableVector { 1, 2 };
            LiteralVectorType literalVector { litPos1, litNeg1, litPos2, litNeg2 };

            actualResult << "Initialized:" << std::endl;
            printGetClauseIdVectorAndSet(contiguousOccurrenceList, literalVector, variableVector, actualResult);

            actualResult << "Removing:" << std::endl;
            contiguousOccurrenceList.removeOccurrence(litPos1, 0);
            contiguousOccurrenceList.removeOccurrence(litNeg2, 2);
            contiguousOccurrenceList.removeOccurrence(litPos2, 3);
            printContiguousOccurrenceList(contiguousOccurrenceList, actualResult);
            printGetClauseIdVectorAndSet(contiguousOccurrenceList, literalVector, variableVector, actualResult);

            actualResult << "Adding:" << std::endl;
            contiguousOccurrenceList.addOccurrence(litPos1, 0);
            contiguousOccurrenceList.addOccurrence(litNeg2, 2);
            contiguousOccurrenceList.addOccurrence(litPos2, 3);
            printContiguousOccurrenceList(contiguousOccurrenceList, actualResult);
            printGetClauseIdVectorAndSet(contiguousOccurrenceList, literalVector, variableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Exists
     */
    TEST_CASE("[Container::ContiguousOccurrenceList] exists", "[Container::ContiguousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousOccurrenceListExistsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousOccurrenceListType contiguousOccurrenceList = createContiguousOccurrenceList();

            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);

            contiguousOccurrenceList.removeOccurrence(litNeg2, 2);
            contiguousOccurrenceList.removeOccurrence(litPos2, 1);

            printContiguousOccurrenceList(contiguousOccurrenceList, actualResult);

            std::vector<std::pair<LiteralType, ClauseIdT>> occurrenceVector {
                { litPos1, 0 },
                { litPos1, 1 },   // -
                { litNeg1, 0 },   // -
                { litPos2, 3 },
                { litPos2, 1 },   // -
                { litPos2, 2 },   // -
                { litNeg2, 0 },
                { litNeg2, 2 },   // -
                { litNeg2, 3 }    // -
            };

            for (auto occurrencePair : occurrenceVector) {
                actualResult << "Literal: " << occurrencePair.first
                             << ", clause ID: " << std::to_string(occurrencePair.second) << std::endl;

                bool existsTmp = contiguousOccurrenceList.occurrenceExists(occurrencePair.first, occurrencePair.second);
                actualResult << "Exists: " << std::to_string(existsTmp) << std::endl;
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
     * Remove occurrences
     */
    TEST_CASE("[Container::ContiguousOccurrenceList] remove occurrences", "[Container::ContiguousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousOccurrenceListRemoveOccurrencesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousOccurrenceListType contiguousOccurrenceList = createContiguousOccurrenceList();
            printContiguousOccurrenceList(contiguousOccurrenceList, actualResult);

            LiteralType litNeg2(2, false);
            ClauseIdVectorType removedClauseVector = contiguousOccurrenceList.removeOccurrence(litNeg2, { 1, 2 });
            printRemovedClauses(removedClauseVector, actualResult);
            printContiguousOccurrenceList(contiguousOccurrenceList, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Remove occurrences (empty)
     */
    TEST_CASE("[Container::ContiguousOccurrenceList] remove occurrences (empty)", "[Container::ContiguousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousOccurrenceListRemoveOccurrencesEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousOccurrenceListType contiguousOccurrenceList = createContiguousOccurrenceList();
            printContiguousOccurrenceList(contiguousOccurrenceList, actualResult);

            LiteralType litNeg1(1, false);
            ClauseIdVectorType removedClauseVector = contiguousOccurrenceList.removeOccurrence(litNeg1, { 0, 1, 2 });
            printRemovedClauses(removedClauseVector, actualResult);
            printContiguousOccurrenceList(contiguousOccurrenceList, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Remove occurrences (keep all)
     */
    TEST_CASE("[Container::ContiguousOccurrenceList] remove occurrences (keep all)", "[Container::ContiguousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousOccurrenceListRemoveOccurrencesKeepAllResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousOccurrenceListType contiguousOccurrenceList = createContiguousOccurrenceList();
            printContiguousOccurrenceList(contiguousOccurrenceList, actualResult);

            LiteralType litPos2(2, true);
            ClauseIdVectorType removedClauseVector = contiguousOccurrenceList.removeOccurrence(litPos2, { 1, 2, 3 });
            printRemovedClauses(removedClauseVector, actualResult);
            printContiguousOccurrenceList(contiguousOccurrenceList, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Remove occurrences (remove all)
     */
    TEST_CASE("[Container::ContiguousOccurrenceList] remove occurrences (remove all)", "[Container::ContiguousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousOccurrenceListRemoveOccurrencesRemoveAllResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousOccurrenceListType contiguousOccurrenceList = createContiguousOccurrenceList();
            printContiguousOccurrenceList(contiguousOccurrenceList, actualResult);

            LiteralType litPos2(2, true);
            ClauseIdVectorType removedClauseVector = contiguousOccurrenceList.removeOccurrence(litPos2, { 0, 2, 4 });
            printRemovedClauses(removedClauseVector, actualResult);
            printContiguousOccurrenceList(contiguousOccurrenceList, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Container::ContiguousOccurrenceList
