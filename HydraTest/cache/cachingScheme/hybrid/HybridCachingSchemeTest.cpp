#include <memory>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/cache/cachingScheme/CachingScheme.hpp"
#include "HydraTest/cache/cachingScheme/CreateFormula.hpp"
#include "HydraTest/cache/cachingScheme/hybrid/HybridCachingSchemeTestResult.hpp"
#include "HydraTest/catch.hpp"

#include "Hydra/cache/cachingScheme/hybrid/HybridCachingScheme.hpp"

#include "Hydra/cache/exceptions/CacheException.hpp"

#include "Hydra/cache/cachingScheme/enums/CachingSchemeTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/OmitClauseTypeEnum.hpp"
#include "Hydra/cache/enums/CacheTypeEnum.hpp"

#include "Hydra/cache/cachingScheme/hybrid/HybridCachingScheme.tpp"

namespace HydraTest::Cache::CachingScheme::Hybrid {

    //region Types
    using VarT = HydraTest::Cache::CachingScheme::VarT;
    using LiteralT = HydraTest::Cache::CachingScheme::LiteralT;
    using ClauseIdT = HydraTest::Cache::CachingScheme::ClauseIdT;

    using HybridCachingSchemeType = Hydra::Cache::CachingScheme::Hybrid::HybridCachingScheme<VarT, LiteralT, ClauseIdT>;

    using ConnectedComponentStructure = HydraTest::Cache::CachingScheme::ConnectedComponentStructure;

    using CacheTypeEnum = Hydra::Cache::CacheTypeEnum;
    using OmitClauseTypeEnum = Hydra::Cache::CachingScheme::OmitClauseTypeEnum;
    using CachingSchemeTypeEnum = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum;
    using IgnorePureLiteralTypeEnum = HydraTest::Cache::CachingScheme::IgnorePureLiteralTypeEnum;

    using HybridCachingSchemeConfigurationType = Hydra::Cache::CachingScheme::Hybrid::HybridCachingSchemeConfiguration;
    //endregion

    //region Functions
    CachingSchemeAbstractUniquePtrType createHybridCachingScheme(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                                                 CacheTypeEnum cacheType, OmitClauseTypeEnum omitClauseType) {
        HybridCachingSchemeConfigurationType configuration;
        configuration.omitClauseType = omitClauseType;

        return std::make_unique<HybridCachingSchemeType>(formulaRepresentationAbstractPtr, cacheType, configuration);
    }
    //endregion

    /**
     * Hybrid
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::NONE);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 3, 4, 5, 6, 7 }, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid (current component variables)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid (current component variables)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeCurrentComponentVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::NONE);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);

            std::vector<VariableSetType> currentComponentVariablesVector { { 1, 2, 3, 4 }, { 5, 6, 7 } };

            for (const VariableSetType& currentComponentVariables : currentComponentVariablesVector) {
                ConnectedComponentStructure connectedComponentStructure(currentComponentVariables.size());
                connectedComponentStructure.variableSet.insert(currentComponentVariables.cbegin(), currentComponentVariables.cend());

                formulaRepresentation->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);

                processCachingScheme(cache, currentComponentVariables, actualResult);

                formulaRepresentation->popPreviousComponent(connectedComponentStructure, {});
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid (assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid (assignment)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::NONE);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(2, false), LiteralType(6, true) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 3, 4, 5, 7 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid (unit clause)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid (unit clause)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeUnitClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaUnitClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::NONE);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, false) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid (char8)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid (char8)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeChar8Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar8<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::NONE);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid (char16 low)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid (char16 low)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeChar16LowResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar16Low<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::NONE);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid (char16 high)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid (char16 high)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeChar16HighResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar16High<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::NONE);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid (char32)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid (char32)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeChar32Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar32<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::NONE);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid omitting binary clauses
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid omitting binary clauses", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeOmittingBinaryClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForOmittingClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::ORIGINAL_BINARY);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid omitting binary clauses (current component variables)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid omitting binary clauses (current component variables)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeOmittingBinaryClausesCurrentComponentVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForOmittingClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::ORIGINAL_BINARY);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);

            std::vector<VariableSetType> currentComponentVariablesVector { { 1, 2, 3, 4, 5 }, { 6, 7, 8, 9 } };

            for (const VariableSetType& currentComponentVariables : currentComponentVariablesVector) {
                ConnectedComponentStructure connectedComponentStructure(currentComponentVariables.size());
                connectedComponentStructure.variableSet.insert(currentComponentVariables.cbegin(), currentComponentVariables.cend());

                formulaRepresentation->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);

                processCachingScheme(cache, currentComponentVariables, actualResult);

                formulaRepresentation->popPreviousComponent(connectedComponentStructure, {});
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid omitting binary clauses (assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid omitting binary clauses (assignment)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeOmittingBinaryClausesAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForOmittingClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::ORIGINAL_BINARY);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, false), LiteralType(5, false), LiteralType(7, true) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 4, 6, 8, 9 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid omitting binary clauses (unit clause)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid omitting binary clauses (unit clause)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeOmittingBinaryClausesUnitClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaUnitClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::ORIGINAL_BINARY);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, false) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid omitting binary clauses (char8)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid omitting binary clauses (char8)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeOmittingBinaryClausesChar8Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar8<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::ORIGINAL_BINARY);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid omitting binary clauses (char16 low)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid omitting binary clauses (char16 low)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeOmittingBinaryClausesChar16LowResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar16Low<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::ORIGINAL_BINARY);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid omitting binary clauses (char16 high)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid omitting binary clauses (char16 high)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeOmittingBinaryClausesChar16HighResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar16High<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::ORIGINAL_BINARY);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid omitting binary clauses (char32)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid omitting binary clauses (char32)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeOmittingBinaryClausesChar32Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar32<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::ORIGINAL_BINARY);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid omitting untouched clauses
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid omitting untouched clauses", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeOmittingUntouchedClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForOmittingClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::UNTOUCHED);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid omitting untouched clauses (current component variables)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid omitting untouched clauses (current component variables)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeOmittingUntouchedClausesCurrentComponentVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForOmittingClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::UNTOUCHED);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);

            std::vector<VariableSetType> currentComponentVariablesVector { { 1, 2, 3, 4, 5 }, { 6, 7, 8, 9 } };

            for (const VariableSetType& currentComponentVariables : currentComponentVariablesVector) {
                ConnectedComponentStructure connectedComponentStructure(currentComponentVariables.size());
                connectedComponentStructure.variableSet.insert(currentComponentVariables.cbegin(), currentComponentVariables.cend());

                formulaRepresentation->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);

                processCachingScheme(cache, currentComponentVariables, actualResult);

                formulaRepresentation->popPreviousComponent(connectedComponentStructure, {});
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid omitting untouched clauses (assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid omitting untouched clauses (assignment)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeOmittingUntouchedClausesAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForOmittingClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::UNTOUCHED);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, false), LiteralType(5, false), LiteralType(7, true) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 4, 6, 8, 9 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid omitting untouched clauses (unit clause)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid omitting untouched clauses (unit clause)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeOmittingUntouchedClausesUnitClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaUnitClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::UNTOUCHED);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, false) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid omitting untouched clauses (char8)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid omitting untouched clauses (char8)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeOmittingUntouchedClausesChar8Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar8<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::UNTOUCHED);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid omitting untouched clauses (char16 low)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid omitting untouched clauses (char16 low)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeOmittingUntouchedClausesChar16LowResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar16Low<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::UNTOUCHED);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid omitting untouched clauses (char16 high)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid omitting untouched clauses (char16 high)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeOmittingUntouchedClausesChar16HighResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar16High<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::UNTOUCHED);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Hybrid omitting untouched clauses (char32)
     */
    TEST_CASE("[Cache::CachingScheme::Hybrid] hybrid omitting untouched clauses (char32)", "[Cache::CachingScheme::Hybrid]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          hybridCachingSchemeOmittingUntouchedClausesChar32Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar32<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createHybridCachingScheme(formulaRepresentation.get(),
                                                                                                          CacheTypeEnum::COMPONENT,
                                                                                                          OmitClauseTypeEnum::UNTOUCHED);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Cache::CachingScheme::Hybrid
