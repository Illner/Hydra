#include <algorithm>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/cache/cachingScheme/CachingScheme.hpp"
#include "HydraTest/cache/cachingScheme/CachingSchemeTestResult.hpp"
#include "HydraTest/catch.hpp"

#include "Hydra/cache/cachingScheme/CachingSchemeAbstract.hpp"
#include "Hydra/cache/cachingScheme/none/NoneCachingScheme.hpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.tpp"
#include "Hydra/other/Other.hpp"

#include "Hydra/cache/exceptions/CacheException.hpp"

#include "Hydra/cache/enums/CacheTypeEnum.hpp"
#include "Hydra/formula/representation/contagious/enums/SubsumptionTypeEnum.hpp"

namespace HydraTest::Cache::CachingScheme {

    using FormulaSizeType = Hydra::Cache::FormulaSizeType;

    //region Types
    using KeyT = char32_t;

    using VarT = HydraTest::Cache::CachingScheme::VarT;
    using LiteralT = HydraTest::Cache::CachingScheme::LiteralT;
    using ClauseIdT = HydraTest::Cache::CachingScheme::ClauseIdT;

    using KeyType = std::basic_string<KeyT>;
    using NoneCachingSchemeType = Hydra::Cache::CachingScheme::None::NoneCachingScheme<VarT, LiteralT, ClauseIdT>;
    using VectorSetType = Hydra::Cache::CachingScheme::CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::VectorSetType;
    using ClauseIdReusableVectorType = Hydra::Cache::CachingScheme::CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdReusableVectorType;

    using ConnectedComponentStructure = HydraTest::Cache::CachingScheme::ConnectedComponentStructure;

    using CacheTypeEnum = Hydra::Cache::CacheTypeEnum;
    using SubsumptionTypeEnum = Hydra::Formula::Representation::Contagious::SubsumptionTypeEnum;
    using IgnorePureLiteralTypeEnum = HydraTest::Cache::CachingScheme::IgnorePureLiteralTypeEnum;
    //endregion

    //region Functions
    CachingSchemeAbstractUniquePtrType createCachingScheme(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, CacheTypeEnum cacheType) {
        return std::make_unique<NoneCachingSchemeType>(formulaRepresentationAbstractPtr, cacheType);
    }

    LiteralType createZeroLiteral() {
        return Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
    }

    void printKey(const KeyType& key, std::stringstream& actualResult) {
        actualResult << "Key:";
        for (KeyT k : key)
            actualResult << " " << std::to_string(k);
        actualResult << std::endl;
    }

    void printVectorMapping(const LiteralVectorType& variableToLiteralVectorMapping, std::stringstream& actualResult) {
        actualResult << "Mapping:" << std::endl;
        for (VarT var : Hydra::Other::extractKeysFromVectorMapping<VarT, LiteralType>(variableToLiteralVectorMapping, createZeroLiteral()))
            actualResult << "\t" << std::to_string(var) << " -> " << variableToLiteralVectorMapping[var] << std::endl;
        actualResult << std::endl;
    }

    void printClauseIdReusableVector(ClauseIdReusableVectorType& clauseIdReusableVector, std::stringstream& actualResult) {
        actualResult << "Clause IDs:";
        clauseIdReusableVector.sort();
        for (ClauseIdT clauseId : clauseIdReusableVector)
            actualResult << " " << std::to_string(clauseId);
        actualResult << std::endl;
    }

    FormulaSizeType computeTotalClausesSize(CachingSchemeAbstractPtrType cachingSchemeAbstractPtr, const ClauseIdReusableVectorType& clauseIdReusableVector) {
        FormulaSizeType totalClausesSize = 0;
        for (ClauseIdT clauseId : clauseIdReusableVector)
            totalClausesSize += cachingSchemeAbstractPtr->getFormulaRepresentationAbstractPtr()->getCurrentClauseSize(clauseId);

        return totalClausesSize;
    }

    void processSortedKeyWithMapping(CachingSchemeAbstractPtrType cachingSchemeAbstractPtr, ClauseIdReusableVectorType& clauseIdReusableVector,
                                     const LiteralVectorType& variableToLiteralVectorMapping, std::stringstream& actualResult) {
        printCachingScheme(cachingSchemeAbstractPtr, actualResult, true);
        printClauseIdReusableVector(clauseIdReusableVector, actualResult);
        printVectorMapping(variableToLiteralVectorMapping, actualResult);

        FormulaSizeType totalClausesSize = computeTotalClausesSize(cachingSchemeAbstractPtr, clauseIdReusableVector);

        KeyType key;
        cachingSchemeAbstractPtr->createSortedKeyWithMapping(key, clauseIdReusableVector, variableToLiteralVectorMapping, totalClausesSize);
        printKey(key, actualResult);
    }

    void processSortedKeyWithMapping(CachingSchemeAbstractPtrType cachingSchemeAbstractPtr, const LiteralVectorType& variableToLiteralVectorMapping,
                                     std::stringstream& actualResult) {
        ClauseIdReusableVectorType clauseIdReusableVector(cachingSchemeAbstractPtr->getFormulaRepresentationAbstractPtr()->getNumberOfOriginalClauses());
        cachingSchemeAbstractPtr->getFormulaRepresentationAbstractPtr()->getCurrentComponentClauses({}, clauseIdReusableVector);
        processSortedKeyWithMapping(cachingSchemeAbstractPtr, clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
    }

    void processSortedKeyWithMappingCurrentComponent(CachingSchemeAbstractPtrType cachingSchemeAbstractPtr,
                                                     const LiteralVectorType& variableToLiteralVectorMapping, std::stringstream& actualResult) {
        printCachingScheme(cachingSchemeAbstractPtr, actualResult, true);
        printVectorMapping(variableToLiteralVectorMapping, actualResult);

        std::vector<VariableSetType> currentComponentVariableSetVector { { 1, 2, 3 }, { 4, 5, 6, 7, 8 } };

        FormulaRepresentationAbstractType* formulaRepresentationAbstractPtr = const_cast<FormulaRepresentationAbstractType*>(cachingSchemeAbstractPtr->getFormulaRepresentationAbstractPtr());

        ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentationAbstractPtr->getNumberOfOriginalClauses());

        for (const VariableSetType& currentComponentVariableSet : currentComponentVariableSetVector) {
            printCurrentComponentVariables(currentComponentVariableSet, actualResult);

            ConnectedComponentStructure connectedComponentStructure(currentComponentVariableSet.size());
            connectedComponentStructure.variableSet.insert(currentComponentVariableSet.cbegin(), currentComponentVariableSet.cend());

            formulaRepresentationAbstractPtr->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);
            printCachingScheme(cachingSchemeAbstractPtr, actualResult, true);

            formulaRepresentationAbstractPtr->getCurrentComponentClauses(currentComponentVariableSet, clauseIdReusableVector, true);
            FormulaSizeType totalClausesSize = computeTotalClausesSize(cachingSchemeAbstractPtr, clauseIdReusableVector);
            printClauseIdReusableVector(clauseIdReusableVector, actualResult);

            KeyType key;
            cachingSchemeAbstractPtr->createSortedKeyWithMapping(key, clauseIdReusableVector, variableToLiteralVectorMapping, totalClausesSize);
            printKey(key, actualResult);

            formulaRepresentationAbstractPtr->popPreviousComponent(connectedComponentStructure, {});
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;
        }
    }

    void processSortedKeyWithMappingAssignment(CachingSchemeAbstractPtrType cachingSchemeAbstractPtr, const LiteralVectorType& variableToLiteralVectorMapping,
                                               bool notDuplicateClauses, bool notSubsumedClauses, bool considerOnlyVariables, std::stringstream& actualResult) {
        printCachingScheme(cachingSchemeAbstractPtr, actualResult, true);
        printVectorMapping(variableToLiteralVectorMapping, actualResult);

        VariableSetType currentComponentVariableSet { 1, 2, 3, 4, 5, 6, 7, 8 };
        std::vector<LiteralType> assignmentVector { LiteralType(3, true), LiteralType(4, true), LiteralType(8, false) };
        FormulaRepresentationAbstractType* formulaRepresentationAbstractPtr = const_cast<FormulaRepresentationAbstractType*>(cachingSchemeAbstractPtr->getFormulaRepresentationAbstractPtr());

        VectorSetType usedVariableVectorSet;
        ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentationAbstractPtr->getNumberOfOriginalClauses());

        for (const LiteralType& lit : assignmentVector) {
            actualResult << "Add assignment: " << lit << std::endl;

            VariableVectorType tmp;
            formulaRepresentationAbstractPtr->addLiteralToPartialAssignment(lit, tmp);
            printCachingScheme(cachingSchemeAbstractPtr, actualResult, true);

            // Clause IDs
            if (notSubsumedClauses) {
                formulaRepresentationAbstractPtr->getCurrentComponentNotSubsumedClauses(currentComponentVariableSet, clauseIdReusableVector,
                                                                                        usedVariableVectorSet, false, considerOnlyVariables, true);
            }
            else if (notDuplicateClauses)
                formulaRepresentationAbstractPtr->getCurrentComponentNotDuplicateClauses(currentComponentVariableSet, clauseIdReusableVector,
                                                                                         considerOnlyVariables, true);
            else
                formulaRepresentationAbstractPtr->getCurrentComponentClauses(currentComponentVariableSet, clauseIdReusableVector, true);

            FormulaSizeType totalClausesSize = computeTotalClausesSize(cachingSchemeAbstractPtr, clauseIdReusableVector);
            printClauseIdReusableVector(clauseIdReusableVector, actualResult);

            KeyType key;
            cachingSchemeAbstractPtr->createSortedKeyWithMapping(key, clauseIdReusableVector, variableToLiteralVectorMapping, totalClausesSize);
            printKey(key, actualResult);

            actualResult << "----------------------------------------" << std::endl
                         << std::endl;
        }

        actualResult << std::endl
                     << "----------------------------------------" << std::endl
                     << "----------------------------------------" << std::endl
                     << std::endl;

        for (auto it = assignmentVector.rbegin(); it != assignmentVector.rend(); ++it) {
            const LiteralType& lit = *it;

            actualResult << "Remove assignment: " << lit << std::endl;

            VariableVectorType tmp;
            formulaRepresentationAbstractPtr->removeLiteralFromPartialAssignment(lit, tmp);
            printCachingScheme(cachingSchemeAbstractPtr, actualResult, true);

            // Clause IDs
            if (notSubsumedClauses) {
                formulaRepresentationAbstractPtr->getCurrentComponentNotSubsumedClauses(currentComponentVariableSet, clauseIdReusableVector,
                                                                                        usedVariableVectorSet, false, considerOnlyVariables, true);
            }
            else if (notDuplicateClauses)
                formulaRepresentationAbstractPtr->getCurrentComponentNotDuplicateClauses(currentComponentVariableSet, clauseIdReusableVector,
                                                                                         considerOnlyVariables, true);
            else
                formulaRepresentationAbstractPtr->getCurrentComponentClauses(currentComponentVariableSet, clauseIdReusableVector, true);

            FormulaSizeType totalClausesSize = computeTotalClausesSize(cachingSchemeAbstractPtr, clauseIdReusableVector);
            printClauseIdReusableVector(clauseIdReusableVector, actualResult);

            KeyType key;
            cachingSchemeAbstractPtr->createSortedKeyWithMapping(key, clauseIdReusableVector, variableToLiteralVectorMapping, totalClausesSize);
            printKey(key, actualResult);

            actualResult << "----------------------------------------" << std::endl
                         << std::endl;
        }
    }

    LiteralVectorType generateIdentityMapping(bool negate) {
        return { createZeroLiteral(),
                 LiteralType(1, !negate),
                 LiteralType(2, !negate),
                 LiteralType(3, !negate),
                 LiteralType(4, !negate),
                 LiteralType(5, !negate),
                 LiteralType(6, !negate),
                 LiteralType(7, !negate),
                 LiteralType(8, !negate) };
    }

    LiteralVectorType generateReversedMapping(bool negate) {
        return { createZeroLiteral(),
                 LiteralType(8, !negate),
                 LiteralType(7, !negate),
                 LiteralType(6, !negate),
                 LiteralType(5, !negate),
                 LiteralType(4, !negate),
                 LiteralType(3, !negate),
                 LiteralType(2, !negate),
                 LiteralType(1, !negate) };
    }

    LiteralVectorType generateNontrivialMapping() {
        return { createZeroLiteral(),
                 LiteralType(2, true),
                 LiteralType(3, false),
                 LiteralType(1, true),
                 LiteralType(4, true),
                 LiteralType(5, false),
                 LiteralType(7, false),
                 LiteralType(8, true),
                 LiteralType(6, false) };
    }

    LiteralVectorType generateNontrivialMapping2() {
        return { createZeroLiteral(),
                 LiteralType(16, false),
                 LiteralType(15, true),
                 LiteralType(14, false),
                 LiteralType(13, false),
                 LiteralType(12, true),
                 LiteralType(11, true),
                 LiteralType(10, false),
                 LiteralType(9, true) };
    }
    //endregion

    //region FormulaRepresentation
    FormulaRepresentationAbstractUniquePtrType createFormulaForSortedKeyWithMapping() {
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
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litPos1, litNeg2, zeroLit,            // 4
            litPos7, litPos8, zeroLit,            // 14
            litNeg1, litNeg2, zeroLit,            // 0
            litPos4, litNeg5, litPos6, zeroLit,   // 17
            litNeg1, litNeg2, zeroLit,            // 1
            litNeg4, litNeg5, zeroLit,            // 8
            litPos1, litPos2, litPos3, zeroLit,   // 16
            litNeg4, litPos5, zeroLit,            // 9
            litNeg1, litNeg2, litNeg3, zeroLit,   // 15
            litNeg6, litPos7, litNeg8, zeroLit,   // 18
            litPos1, litPos2, zeroLit,            // 6
            litNeg7, litNeg8, zeroLit,            // 13
            litPos1, litNeg2, zeroLit,            // 5
            litNeg4, litPos7, zeroLit,            // 10
            litPos1, litPos2, zeroLit,            // 7
            litPos4, litPos5, zeroLit,            // 11
            litNeg1, litPos2, zeroLit,            // 2
            litNeg1, litPos2, zeroLit,            // 3
            litPos4, litNeg6, zeroLit             // 12
        };

        VarT numberOfVariables = 8;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        // Configuration
        ContagiousFormulaRepresentationConfigurationType configuration;
        configuration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences,
                                                                     configuration);
    }
    //endregion

    /**
     * Sorted key with mapping - component caching (identity mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (identity mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingIdentityMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            LiteralVectorType variableToLiteralVectorMapping = generateIdentityMapping(false);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - component caching (negated identity mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (negated identity mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingNegatedIdentityMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            LiteralVectorType variableToLiteralVectorMapping = generateIdentityMapping(true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - component caching (reversed mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (reversed mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingReversedMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            LiteralVectorType variableToLiteralVectorMapping = generateReversedMapping(false);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - component caching (negated reversed mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (negated reversed mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingNegatedReversedMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            LiteralVectorType variableToLiteralVectorMapping = generateReversedMapping(true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - component caching (assignment)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (assignment)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            LiteralVectorType variableToLiteralVectorMapping = generateNontrivialMapping();
            processSortedKeyWithMappingAssignment(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping,
                                                  false, false, false, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - component caching (not duplicate clauses, identity mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (not duplicate clauses, identity mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingNotDuplicateClausesIdentityMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            LiteralVectorType variableToLiteralVectorMapping = generateIdentityMapping(false);
            ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentation->getNumberOfOriginalClauses());
            formulaRepresentation->getCurrentComponentNotDuplicateClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector, false, true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - component caching (not duplicate clauses, negated identity mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (not duplicate clauses, negated identity mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingNotDuplicateClausesNegatedIdentityMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            LiteralVectorType variableToLiteralVectorMapping = generateIdentityMapping(true);
            ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentation->getNumberOfOriginalClauses());
            formulaRepresentation->getCurrentComponentNotDuplicateClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector, false, true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - component caching (not duplicate clauses, reversed mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (not duplicate clauses, reversed mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingNotDuplicateClausesReversedMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            LiteralVectorType variableToLiteralVectorMapping = generateReversedMapping(false);
            ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentation->getNumberOfOriginalClauses());
            formulaRepresentation->getCurrentComponentNotDuplicateClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector, false, true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - component caching (not duplicate clauses, negated reversed mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (not duplicate clauses, negated reversed mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingNotDuplicateClausesNegatedReversedMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            LiteralVectorType variableToLiteralVectorMapping = generateReversedMapping(true);
            ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentation->getNumberOfOriginalClauses());
            formulaRepresentation->getCurrentComponentNotDuplicateClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector, false, true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - component caching (not duplicate clauses, assignment)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (not duplicate clauses, assignment)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingNotDuplicateClausesAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            LiteralVectorType variableToLiteralVectorMapping = generateNontrivialMapping();
            processSortedKeyWithMappingAssignment(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping,
                                                  true, false, false, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - component caching (not subsumed clauses, identity mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (not subsumed clauses, identity mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingNotSubsumedClausesIdentityMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            VectorSetType usedVariableVectorSet;
            LiteralVectorType variableToLiteralVectorMapping = generateIdentityMapping(false);
            ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentation->getNumberOfOriginalClauses());
            formulaRepresentation->getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                                         usedVariableVectorSet, false, false, true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - component caching (not subsumed clauses, negated identity mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (not subsumed clauses, negated identity mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingNotSubsumedClausesNegatedIdentityMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            VectorSetType usedVariableVectorSet;
            LiteralVectorType variableToLiteralVectorMapping = generateIdentityMapping(true);
            ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentation->getNumberOfOriginalClauses());
            formulaRepresentation->getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                                         usedVariableVectorSet, false, false, true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - component caching (not subsumed clauses, reversed mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (not subsumed clauses, reversed mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingNotSubsumedClausesReversedMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            VectorSetType usedVariableVectorSet;
            LiteralVectorType variableToLiteralVectorMapping = generateReversedMapping(false);
            ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentation->getNumberOfOriginalClauses());
            formulaRepresentation->getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                                         usedVariableVectorSet, false, false, true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - component caching (not subsumed clauses, negated reversed mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (not subsumed clauses, negated reversed mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingNotSubsumedClausesNegatedReversedMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            VectorSetType usedVariableVectorSet;
            LiteralVectorType variableToLiteralVectorMapping = generateReversedMapping(true);
            ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentation->getNumberOfOriginalClauses());
            formulaRepresentation->getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                                         usedVariableVectorSet, false, false, true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - component caching (not subsumed clauses, assignment)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (not subsumed clauses, assignment)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingNotSubsumedClausesAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            LiteralVectorType variableToLiteralVectorMapping = generateNontrivialMapping();
            processSortedKeyWithMappingAssignment(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping,
                                                  false, true, false, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (identity mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (identity mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingIdentityMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            LiteralVectorType variableToLiteralVectorMapping = generateIdentityMapping(false);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (negated identity mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (negated identity mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingNegatedIdentityMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            LiteralVectorType variableToLiteralVectorMapping = generateIdentityMapping(true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (reversed mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (reversed mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingReversedMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            LiteralVectorType variableToLiteralVectorMapping = generateReversedMapping(false);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (negated reversed mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (negated reversed mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingNegatedReversedMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            LiteralVectorType variableToLiteralVectorMapping = generateReversedMapping(true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (assignment)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (assignment)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            LiteralVectorType variableToLiteralVectorMapping = generateNontrivialMapping();
            processSortedKeyWithMappingAssignment(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping,
                                                  false, false, true, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (not duplicate clauses, identity mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (not duplicate clauses, identity mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingNotDuplicateClausesIdentityMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            LiteralVectorType variableToLiteralVectorMapping = generateIdentityMapping(false);
            ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentation->getNumberOfOriginalClauses());
            formulaRepresentation->getCurrentComponentNotDuplicateClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector, true, true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (not duplicate clauses, negated identity mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (not duplicate clauses, negated identity mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingNotDuplicateClausesNegatedIdentityMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            LiteralVectorType variableToLiteralVectorMapping = generateIdentityMapping(true);
            ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentation->getNumberOfOriginalClauses());
            formulaRepresentation->getCurrentComponentNotDuplicateClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector, true, true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (not duplicate clauses, reversed mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (not duplicate clauses, reversed mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingNotDuplicateClausesReversedMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            LiteralVectorType variableToLiteralVectorMapping = generateReversedMapping(false);
            ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentation->getNumberOfOriginalClauses());
            formulaRepresentation->getCurrentComponentNotDuplicateClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector, true, true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (not duplicate clauses, negated reversed mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (not duplicate clauses, negated reversed mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingNotDuplicateClausesNegatedReversedMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            LiteralVectorType variableToLiteralVectorMapping = generateReversedMapping(true);
            ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentation->getNumberOfOriginalClauses());
            formulaRepresentation->getCurrentComponentNotDuplicateClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector, true, true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (not duplicate clauses, assignment)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (not duplicate clauses, assignment)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingNotDuplicateClausesAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            LiteralVectorType variableToLiteralVectorMapping = generateNontrivialMapping();
            processSortedKeyWithMappingAssignment(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping,
                                                  true, false, true, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (not subsumed clauses, identity mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (not subsumed clauses, identity mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingNotSubsumedClausesIdentityMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            VectorSetType usedVariableVectorSet;
            LiteralVectorType variableToLiteralVectorMapping = generateIdentityMapping(false);
            ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentation->getNumberOfOriginalClauses());
            formulaRepresentation->getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                                         usedVariableVectorSet, false, true, true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (not subsumed clauses, negated identity mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (not subsumed clauses, negated identity mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingNotSubsumedClausesNegatedIdentityMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            VectorSetType usedVariableVectorSet;
            LiteralVectorType variableToLiteralVectorMapping = generateIdentityMapping(true);
            ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentation->getNumberOfOriginalClauses());
            formulaRepresentation->getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                                         usedVariableVectorSet, false, true, true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (not subsumed clauses, reversed mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (not subsumed clauses, reversed mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingNotSubsumedClausesReversedMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            VectorSetType usedVariableVectorSet;
            LiteralVectorType variableToLiteralVectorMapping = generateReversedMapping(false);
            ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentation->getNumberOfOriginalClauses());
            formulaRepresentation->getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                                         usedVariableVectorSet, false, true, true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (not subsumed clauses, negated reversed mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (not subsumed clauses, negated reversed mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingNotSubsumedClausesNegatedReversedMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            VectorSetType usedVariableVectorSet;
            LiteralVectorType variableToLiteralVectorMapping = generateReversedMapping(true);
            ClauseIdReusableVectorType clauseIdReusableVector(formulaRepresentation->getNumberOfOriginalClauses());
            formulaRepresentation->getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                                         usedVariableVectorSet, false, true, true);
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), clauseIdReusableVector, variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (not subsumed clauses, assignment)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (not subsumed clauses, assignment)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingNotSubsumedClausesAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            LiteralVectorType variableToLiteralVectorMapping = generateNontrivialMapping();
            processSortedKeyWithMappingAssignment(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping,
                                                  false, true, true, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - component caching (current component)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (current component)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            LiteralVectorType variableToLiteralVectorMapping = generateNontrivialMapping();
            processSortedKeyWithMappingCurrentComponent(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (current component)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (current component)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            LiteralVectorType variableToLiteralVectorMapping = generateNontrivialMapping();
            processSortedKeyWithMappingCurrentComponent(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - component caching (nontrivial mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - component caching (nontrivial mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingComponentCachingNontrivialMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::COMPONENT);

            LiteralVectorType variableToLiteralVectorMapping = generateNontrivialMapping2();
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sorted key with mapping - hypergraph cut caching (nontrivial mapping)
     */
    TEST_CASE("[Cache::CachingScheme] sorted key with mapping - hypergraph cut caching (nontrivial mapping)", "[Cache::CachingScheme]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cachingSchemeSortedKeyWithMappingHypergraphCutCachingNontrivialMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForSortedKeyWithMapping();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCachingScheme(formulaRepresentation.get(),
                                                                                                    CacheTypeEnum::HYPERGRAPH_CUT);

            LiteralVectorType variableToLiteralVectorMapping = generateNontrivialMapping2();
            processSortedKeyWithMapping(cachingSchemeAbstractUniquePtr.get(), variableToLiteralVectorMapping, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Cache::CachingScheme
