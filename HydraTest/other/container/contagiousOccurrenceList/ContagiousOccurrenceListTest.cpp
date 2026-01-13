#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/other/container/contagiousOccurrenceList/ContagiousOccurrenceListTestResult.hpp"

#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/contagiousOccurrenceList/ContagiousOccurrenceList.hpp"

namespace HydraTest::Container::ContagiousOccurrenceList {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;
    using ClauseIdT = char8_t;

    using LiteralType = Hydra::Formula::Literal<VarT, LiteralT>::LiteralType;
    using FormulaSizeType = Hydra::Container::ContagiousOccurrenceList::FormulaSizeType;
    using LiteralVectorType = Hydra::Formula::Literal<VarT, LiteralT>::LiteralVectorType;
    using VariableVectorType = Hydra::Formula::Literal<VarT, LiteralT>::VariableVectorType;

    using ClauseIdVectorType = std::vector<ClauseIdT>;
    using ContagiousOccurrenceListType = Hydra::Container::ContagiousOccurrenceList::ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>;
    //endregion

    //region Functions
    void printContagiousOccurrenceList(const ContagiousOccurrenceListType& contagiousOccurrenceList, std::stringstream& actualResult) {
        contagiousOccurrenceList.printContagiousOccurrenceListDebug(actualResult);
        actualResult << std::endl;
    }

    void printRemovedClauses(const ClauseIdVectorType& removedClauseVector, std::stringstream& actualResult) {
        actualResult << "Removed clauses:";
        for (ClauseIdT clauseId : removedClauseVector)
            actualResult << " " << std::to_string(clauseId);
        actualResult << std::endl;
    }

    void printGetClauseIdVectorAndSet(const ContagiousOccurrenceListType& contagiousOccurrenceList,
                                      const LiteralVectorType& literalVector, const VariableVectorType& variableVector, std::stringstream& actualResult) {
        // Variable
        actualResult << "Variable: " << std::endl;
        for (VarT var : variableVector) {
            ClauseIdT numberOfOccurrencesTmp = contagiousOccurrenceList.getNumberOfVariableOccurrences(var);
            actualResult << std::to_string(var) << ": " << std::to_string(numberOfOccurrencesTmp) << std::endl;
        }
        actualResult << std::endl;

        // Vector
        actualResult << "Vector:" << std::endl;
        for (const LiteralType& lit : literalVector) {
            ClauseIdT numberOfOccurrencesTmp = contagiousOccurrenceList.getNumberOfOccurrences(lit);
            ClauseIdVectorType clauseIdVectorTmp = contagiousOccurrenceList.getClauseIdVector(lit);
            actualResult << lit << " (" << std::to_string(numberOfOccurrencesTmp) << "): ";
            for (ClauseIdT clauseId : clauseIdVectorTmp)
                actualResult << std::to_string(clauseId) << " ";
            actualResult << std::endl;
        }
        actualResult << std::endl;

        // Set
        actualResult << "Set:" << std::endl;
        for (const LiteralType& lit : literalVector) {
            ClauseIdVectorType clauseIdVectorTmp = Hydra::Other::sortUnorderedSet(contagiousOccurrenceList.getClauseIdSet(lit));
            actualResult << lit << ": ";
            for (ClauseIdT clauseId : clauseIdVectorTmp)
                actualResult << std::to_string(clauseId) << " ";
            actualResult << std::endl;
        }
        actualResult << std::endl;
    }
    //endregion

    //region ContagiousOccurrenceList
    ContagiousOccurrenceListType createContagiousOccurrenceList() {
        ContagiousOccurrenceListType contagiousOccurrenceList(5, { 0, 0, 1, 0, 2, 3 });

        LiteralType litPos1(1, true);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);

        contagiousOccurrenceList.addOccurrence(litPos1.getLiteralT(), 0);

        contagiousOccurrenceList.addOccurrence(litPos2.getLiteralT(), 1);
        contagiousOccurrenceList.addOccurrence(litPos2.getLiteralT(), 3);

        contagiousOccurrenceList.addOccurrence(litNeg2.getLiteralT(), 0);
        contagiousOccurrenceList.addOccurrence(litNeg2.getLiteralT(), 2);
        contagiousOccurrenceList.addOccurrence(litNeg2.getLiteralT(), 4);

        return contagiousOccurrenceList;
    }
    //endregion

    /**
     * Constructor
     */
    TEST_CASE("[Container::ContagiousOccurrenceList] constructor", "[Container::ContagiousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousOccurrenceListConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            actualResult << "contagiousOccurrenceList1:" << std::endl;
            ContagiousOccurrenceListType contagiousOccurrenceList1(2, { 0, 0, 1, 1 });
            printContagiousOccurrenceList(contagiousOccurrenceList1, actualResult);

            actualResult << "contagiousOccurrenceList2:" << std::endl;
            ContagiousOccurrenceListType contagiousOccurrenceList2(4, { 0, 0, 1, 0, 2, 3 });
            printContagiousOccurrenceList(contagiousOccurrenceList2, actualResult);
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
    TEST_CASE("[Container::ContagiousOccurrenceList] copy and move", "[Container::ContagiousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousOccurrenceListCopyAndMoveResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousOccurrenceListType contagiousOccurrenceList1(4, { 0, 0, 1, 0, 2, 3 });
            printContagiousOccurrenceList(contagiousOccurrenceList1, actualResult);

            actualResult << "Copy method" << std::endl;
            ContagiousOccurrenceListType contagiousOccurrenceList2 = contagiousOccurrenceList1;
            contagiousOccurrenceList2.addOccurrence(LiteralType(1, true).getLiteralT(), 0);
            printContagiousOccurrenceList(contagiousOccurrenceList1, actualResult);
            printContagiousOccurrenceList(contagiousOccurrenceList2, actualResult);

            actualResult << "Move method" << std::endl;
            ContagiousOccurrenceListType contagiousOccurrenceList3 = std::move(contagiousOccurrenceList1);
            printContagiousOccurrenceList(contagiousOccurrenceList3, actualResult);
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
    TEST_CASE("[Container::ContagiousOccurrenceList] add occurrence", "[Container::ContagiousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousOccurrenceListAddOccurrenceResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousOccurrenceListType contagiousOccurrenceList(4, { 0, 0, 1, 0, 2, 3 });
            printContagiousOccurrenceList(contagiousOccurrenceList, actualResult);

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
                    contagiousOccurrenceList.addOccurrence(occurrencePair.first, occurrencePair.second);
                    printContagiousOccurrenceList(contagiousOccurrenceList, actualResult);
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
    TEST_CASE("[Container::ContagiousOccurrenceList] remove occurrence", "[Container::ContagiousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousOccurrenceListRemoveOccurrenceResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousOccurrenceListType contagiousOccurrenceList = createContagiousOccurrenceList();
            printContagiousOccurrenceList(contagiousOccurrenceList, actualResult);

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
                    contagiousOccurrenceList.removeOccurrence(occurrencePair.first, occurrencePair.second);
                    printContagiousOccurrenceList(contagiousOccurrenceList, actualResult);
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
    TEST_CASE("[Container::ContagiousOccurrenceList] get occurrences", "[Container::ContagiousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousOccurrenceListGetOccurrencesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousOccurrenceListType contagiousOccurrenceList = createContagiousOccurrenceList();
            printContagiousOccurrenceList(contagiousOccurrenceList, actualResult);

            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);

            VariableVectorType variableVector { 1, 2 };
            LiteralVectorType literalVector { litPos1, litNeg1, litPos2, litNeg2 };

            actualResult << "Initialized:" << std::endl;
            printGetClauseIdVectorAndSet(contagiousOccurrenceList, literalVector, variableVector, actualResult);

            actualResult << "Removing:" << std::endl;
            contagiousOccurrenceList.removeOccurrence(litPos1, 0);
            contagiousOccurrenceList.removeOccurrence(litNeg2, 2);
            contagiousOccurrenceList.removeOccurrence(litPos2, 3);
            printContagiousOccurrenceList(contagiousOccurrenceList, actualResult);
            printGetClauseIdVectorAndSet(contagiousOccurrenceList, literalVector, variableVector, actualResult);

            actualResult << "Adding:" << std::endl;
            contagiousOccurrenceList.addOccurrence(litPos1, 0);
            contagiousOccurrenceList.addOccurrence(litNeg2, 2);
            contagiousOccurrenceList.addOccurrence(litPos2, 3);
            printContagiousOccurrenceList(contagiousOccurrenceList, actualResult);
            printGetClauseIdVectorAndSet(contagiousOccurrenceList, literalVector, variableVector, actualResult);
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
    TEST_CASE("[Container::ContagiousOccurrenceList] exists", "[Container::ContagiousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousOccurrenceListExistsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousOccurrenceListType contagiousOccurrenceList = createContagiousOccurrenceList();

            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);

            contagiousOccurrenceList.removeOccurrence(litNeg2, 2);
            contagiousOccurrenceList.removeOccurrence(litPos2, 1);

            printContagiousOccurrenceList(contagiousOccurrenceList, actualResult);

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

                bool existsTmp = contagiousOccurrenceList.occurrenceExists(occurrencePair.first, occurrencePair.second);
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
    TEST_CASE("[Container::ContagiousOccurrenceList] remove occurrences", "[Container::ContagiousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousOccurrenceListRemoveOccurrencesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousOccurrenceListType contagiousOccurrenceList = createContagiousOccurrenceList();
            printContagiousOccurrenceList(contagiousOccurrenceList, actualResult);

            LiteralType litNeg2(2, false);
            ClauseIdVectorType removedClauseVector = contagiousOccurrenceList.removeOccurrence(litNeg2, { 1, 2 });
            printRemovedClauses(removedClauseVector, actualResult);
            printContagiousOccurrenceList(contagiousOccurrenceList, actualResult);
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
    TEST_CASE("[Container::ContagiousOccurrenceList] remove occurrences (empty)", "[Container::ContagiousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousOccurrenceListRemoveOccurrencesEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousOccurrenceListType contagiousOccurrenceList = createContagiousOccurrenceList();
            printContagiousOccurrenceList(contagiousOccurrenceList, actualResult);

            LiteralType litNeg1(1, false);
            ClauseIdVectorType removedClauseVector = contagiousOccurrenceList.removeOccurrence(litNeg1, { 0, 1, 2 });
            printRemovedClauses(removedClauseVector, actualResult);
            printContagiousOccurrenceList(contagiousOccurrenceList, actualResult);
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
    TEST_CASE("[Container::ContagiousOccurrenceList] remove occurrences (keep all)", "[Container::ContagiousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousOccurrenceListRemoveOccurrencesKeepAllResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousOccurrenceListType contagiousOccurrenceList = createContagiousOccurrenceList();
            printContagiousOccurrenceList(contagiousOccurrenceList, actualResult);

            LiteralType litPos2(2, true);
            ClauseIdVectorType removedClauseVector = contagiousOccurrenceList.removeOccurrence(litPos2, { 1, 2, 3 });
            printRemovedClauses(removedClauseVector, actualResult);
            printContagiousOccurrenceList(contagiousOccurrenceList, actualResult);
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
    TEST_CASE("[Container::ContagiousOccurrenceList] remove occurrences (remove all)", "[Container::ContagiousOccurrenceList]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousOccurrenceListRemoveOccurrencesRemoveAllResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousOccurrenceListType contagiousOccurrenceList = createContagiousOccurrenceList();
            printContagiousOccurrenceList(contagiousOccurrenceList, actualResult);

            LiteralType litPos2(2, true);
            ClauseIdVectorType removedClauseVector = contagiousOccurrenceList.removeOccurrence(litPos2, { 0, 2, 4 });
            printRemovedClauses(removedClauseVector, actualResult);
            printContagiousOccurrenceList(contagiousOccurrenceList, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Container::ContagiousOccurrenceList
