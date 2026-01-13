#include <memory>
#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/cache/cachingScheme/CachingScheme.hpp"
#include "HydraTest/cache/cachingScheme/CreateFormula.hpp"
#include "HydraTest/cache/cachingScheme/cara/CaraCachingSchemeTestResult.hpp"
#include "HydraTest/catch.hpp"

#include "Hydra/cache/cachingScheme/cara/CaraCachingScheme.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/Other.hpp"

#include "Hydra/cache/exceptions/CacheException.hpp"

#include "Hydra/cache/cachingScheme/enums/CachingSchemeTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/PreprocessingTypeEnum.hpp"
#include "Hydra/cache/enums/CacheTypeEnum.hpp"

#include "Hydra/cache/cachingScheme/cara/CaraCachingScheme.tpp"

namespace HydraTest::Cache::CachingScheme::Cara {

    using FormulaSizeType = Hydra::Cache::FormulaSizeType;
    using LargeNumberType = Hydra::Cache::LargeNumberType;

    //region Types
    using VarT = HydraTest::Cache::CachingScheme::VarT;
    using LiteralT = HydraTest::Cache::CachingScheme::LiteralT;
    using ClauseIdT = HydraTest::Cache::CachingScheme::ClauseIdT;

    using SampleMomentType = typename Hydra::Cache::CachingScheme::Cara::CaraCachingScheme<VarT, LiteralT, ClauseIdT>::SampleMomentType;
    using SampleMomentVectorType = typename Hydra::Cache::CachingScheme::Cara::CaraCachingScheme<VarT, LiteralT, ClauseIdT>::SampleMomentVectorType;

    using CaraCachingSchemeType = Hydra::Cache::CachingScheme::Cara::CaraCachingScheme<VarT, LiteralT, ClauseIdT>;

    using ConnectedComponentStructure = HydraTest::Cache::CachingScheme::ConnectedComponentStructure;

    using CacheTypeEnum = Hydra::Cache::CacheTypeEnum;
    using CachingSchemeTypeEnum = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum;
    using PreprocessingTypeEnum = Hydra::Cache::CachingScheme::PreprocessingTypeEnum;
    using IgnorePureLiteralTypeEnum = HydraTest::Cache::CachingScheme::IgnorePureLiteralTypeEnum;

    using CaraCachingSchemeConfigurationType = Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration;
    //endregion

    //region Functions
    CachingSchemeAbstractUniquePtrType createCaraCachingScheme(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, CacheTypeEnum cacheType,
                                                               char8_t numberOfSampleMoments, bool useVariableToLiteralMapping = true,
                                                               PreprocessingTypeEnum preprocessingType = PreprocessingTypeEnum::NONE) {
        CaraCachingSchemeConfigurationType configuration;
        configuration.preprocessingType = preprocessingType;
        configuration.numberOfSampleMoments = numberOfSampleMoments;
        configuration.useVariableToLiteralMapping = useVariableToLiteralMapping;
        configuration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        return std::make_unique<CaraCachingSchemeType>(formulaRepresentationAbstractPtr, cacheType, configuration);
    }

    void printSampleMomentDataStructure(const VariableSetType& currentComponentVariableSet, const SampleMomentVectorType& sampleMomentVector,
                                        const VariableVectorType& variableToIndexVectorMapping,
                                        ClauseSizeType maxClauseSize, FormulaSizeType totalClausesSize, std::stringstream& actualResult) {
        actualResult << "Sample moments" << std::endl;
        for (std::size_t i = 0; i < currentComponentVariableSet.size(); ++i) {
            const SampleMomentType& sampleMoment = sampleMomentVector[i];
            actualResult << "\t" << std::to_string(sampleMoment.back()) << ":";
            for (LargeNumberType value : sampleMoment)
                actualResult << " " << std::to_string(value);
            actualResult << std::endl;
        }

        actualResult << "Variable to index mapping" << std::endl;
        for (VarT var : Hydra::Other::sortUnorderedSet(currentComponentVariableSet))
            actualResult << "\t" << std::to_string(var) << " -> " << std::to_string(variableToIndexVectorMapping[var]) << std::endl;

        actualResult << "Maximum clause size: " << std::to_string(maxClauseSize) << std::endl;
        actualResult << "The total size of the clauses: " << std::to_string(totalClausesSize) << std::endl;
        actualResult << std::endl;
    }

    void processSampleMoments(CachingSchemeAbstractPtrType cachingSchemeAbstractPtr, std::stringstream& actualResult,
                              const VariableSetType& currentComponentVariableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }) {
        printCachingScheme(cachingSchemeAbstractPtr, actualResult, true);

        const CaraCachingSchemeType* caraPtr = dynamic_cast<const CaraCachingSchemeType*>(cachingSchemeAbstractPtr);

        ClauseSizeType maxClauseSize = 0;
        FormulaSizeType totalClausesSize = 0;
        cachingSchemeAbstractPtr->getFormulaRepresentationAbstractPtr()->getCurrentComponentClauses(currentComponentVariableSet,
                                                                                                    caraPtr->getClauseIdReusableVector());

        caraPtr->createSampleMomentDataStructure(currentComponentVariableSet, maxClauseSize, totalClausesSize);

        printSampleMomentDataStructure(currentComponentVariableSet, caraPtr->getSampleMomentVector(), caraPtr->getVariableToIndexVectorMapping(),
                                       maxClauseSize, totalClausesSize, actualResult);
    }

    void processSampleMomentsCurrentComponent(CachingSchemeAbstractPtrType cachingSchemeAbstractPtr, std::stringstream& actualResult) {
        printCachingScheme(cachingSchemeAbstractPtr, actualResult, true);

        std::vector<VariableSetType> currentComponentVariableSetVector { { 1, 2, 3, 4, 5, 6, 7 }, { 8, 9 } };

        for (const VariableSetType& currentComponentVariableSet : currentComponentVariableSetVector) {
            printCurrentComponentVariables(currentComponentVariableSet, actualResult);

            ConnectedComponentStructure connectedComponentStructure(currentComponentVariableSet.size());
            connectedComponentStructure.variableSet.insert(currentComponentVariableSet.cbegin(), currentComponentVariableSet.cend());

            FormulaRepresentationAbstractType* formulaRepresentationAbstractPtr = const_cast<FormulaRepresentationAbstractType*>(cachingSchemeAbstractPtr->getFormulaRepresentationAbstractPtr());
            formulaRepresentationAbstractPtr->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);

            processSampleMoments(cachingSchemeAbstractPtr, actualResult, currentComponentVariableSet);

            formulaRepresentationAbstractPtr->popPreviousComponent(connectedComponentStructure, {});
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;
        }
    }

    void processCurrentComponent(const CacheType& cache, FormulaRepresentationAbstractType* formulaRepresentationAbstractPtr, std::stringstream& actualResult) {
        printCachingScheme(cache, actualResult, true);

        std::vector<VariableSetType> currentComponentVariableSetVector { { 1, 2, 3, 4, 5, 6, 7 }, { 8, 9 } };

        for (const VariableSetType& currentComponentVariableSet : currentComponentVariableSetVector) {
            ConnectedComponentStructure connectedComponentStructure(currentComponentVariableSet.size());
            connectedComponentStructure.variableSet.insert(currentComponentVariableSet.cbegin(), currentComponentVariableSet.cend());

            formulaRepresentationAbstractPtr->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);

            processCachingScheme(cache, currentComponentVariableSet, actualResult);

            formulaRepresentationAbstractPtr->popPreviousComponent(connectedComponentStructure, {});
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;
        }
    }

    void processSampleMomentsAssignment(CachingSchemeAbstractPtrType cachingSchemeAbstractPtr, std::stringstream& actualResult) {
        printCachingScheme(cachingSchemeAbstractPtr, actualResult, true);

        VariableSetType currentComponentVariableSet { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::vector<LiteralType> assignmentVector { LiteralType(4, true), LiteralType(9, false) };
        FormulaRepresentationAbstractType* formulaRepresentationAbstractPtr = const_cast<FormulaRepresentationAbstractType*>(cachingSchemeAbstractPtr->getFormulaRepresentationAbstractPtr());

        for (const LiteralType& lit : assignmentVector) {
            actualResult << "Add assignment: " << lit << std::endl;
            currentComponentVariableSet.erase(lit.getVariable());

            VariableVectorType tmp;
            formulaRepresentationAbstractPtr->addLiteralToPartialAssignment(lit, tmp);

            for (VarT var : tmp)
                currentComponentVariableSet.erase(var);

            processSampleMoments(cachingSchemeAbstractPtr, actualResult, currentComponentVariableSet);

            actualResult << "----------------------------------------" << std::endl
                         << std::endl;
        }

        actualResult << std::endl
                     << "----------------------------------------" << std::endl
                     << "----------------------------------------" << std::endl
                     << std::endl;

        for (auto it = assignmentVector.rbegin(); it != assignmentVector.rend(); ++it) {
            const LiteralType& lit = *it;
            currentComponentVariableSet.emplace(lit.getVariable());

            actualResult << "Remove assignment: " << lit << std::endl;

            VariableVectorType tmp;
            formulaRepresentationAbstractPtr->removeLiteralFromPartialAssignment(lit, tmp);

            for (VarT var : tmp)
                currentComponentVariableSet.emplace(var);

            processSampleMoments(cachingSchemeAbstractPtr, actualResult, currentComponentVariableSet);

            actualResult << "----------------------------------------" << std::endl
                         << std::endl;
        }
    }

    void processAssignment(const CacheType& cache, FormulaRepresentationAbstractType* formulaRepresentationAbstractPtr, std::stringstream& actualResult) {
        VariableVectorType tmp;
        formulaRepresentationAbstractPtr->addLiteralVectorToPartialAssignment({ LiteralType(4, true), LiteralType(9, false) }, tmp);

        VariableSetType currentComponentVariableSet { 1, 2, 3, 5, 6, 7, 8 };
        for (VarT var : tmp)
            currentComponentVariableSet.erase(var);

        printCachingScheme(cache, actualResult, true);

        processCachingScheme(cache, currentComponentVariableSet, actualResult);
    }
    //endregion

    //region FormulaRepresentation
    FormulaRepresentationAbstractUniquePtrType createFormulaForCara() {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg6(6, false);
        LiteralType litNeg7(7, false);
        LiteralType litNeg8(8, false);
        LiteralType litPos9(9, true);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litPos4, zeroLit,                             // 0
            litNeg7, zeroLit,                             // 1
            litPos1, litPos5, zeroLit,                    // 2
            litNeg8, litPos9, zeroLit,                    // 3
            litNeg8, litPos9, zeroLit,                    // 4
            litNeg3, litNeg4, litPos6, zeroLit,           // 5
            litPos3, litNeg6, litNeg7, zeroLit,           // 6
            litNeg2, litNeg3, litPos4, litNeg5, zeroLit   // 7
        };

        VarT numberOfVariables = 9;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    FormulaRepresentationAbstractUniquePtrType createFormulaForCaraNotSubsumedClausesUsedVariables() {
        //region Literals
        LiteralType litPos1(1, true);
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
        LiteralType litNeg7(7, false);
        LiteralType litNeg8(8, false);
        LiteralType litPos9(9, true);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litPos4, zeroLit,                             // 0
            litNeg7, zeroLit,                             // 1
            litPos1, litPos5, zeroLit,                    // 2
            litNeg8, litPos9, zeroLit,                    // 3
            litNeg8, litPos9, zeroLit,                    // 4
            litPos2, litPos3, litPos6, zeroLit,           // 5
            litNeg3, litNeg4, litPos6, zeroLit,           // 6
            litPos3, litNeg6, litNeg7, zeroLit,           // 7
            litNeg2, litNeg3, litPos4, litNeg5, zeroLit   // 8
        };

        VarT numberOfVariables = 9;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    FormulaRepresentationAbstractUniquePtrType createFormulaForCaraMoreSampleMoments(VariableSetType& variableSet) {
        //region Literals
        LiteralType litPos2(2, true);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos6(6, true);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType litPos10(10, true);
        LiteralType litPos12(12, true);
        LiteralType litNeg12(12, false);
        LiteralType litPos14(14, true);
        LiteralType litNeg14(14, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litPos2, litPos6, zeroLit,                       // 0
            litPos2, litPos12, zeroLit,                      // 1
            litNeg4, litNeg14, zeroLit,                      // 2
            litPos4, litNeg8, litPos10, zeroLit,             // 3
            litPos4, litPos8, litPos10, zeroLit,             // 4
            litPos6, litNeg8, litPos10, zeroLit,             // 5
            litPos6, litPos8, litPos10, zeroLit,             // 6
            litPos2, litNeg4, litPos12, litNeg14, zeroLit,   // 7
            litPos2, litPos6, litNeg12, litPos14, zeroLit    // 8
        };

        VarT numberOfVariables = 14;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 2, 4, 6, 8, 10, 12, 14 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }
    //endregion

    /**
     * Sample moments - component caching (no moment)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] sample moments - component caching (no moment)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeSampleMomentsComponentCachingNoMomentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 0);

            processSampleMoments(cachingSchemeAbstractUniquePtr.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sample moments - component caching (1 moment)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] sample moments - component caching (1 moment)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeSampleMomentsComponentCachingOneMomentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 1);

            processSampleMoments(cachingSchemeAbstractUniquePtr.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sample moments - component caching (2 moments)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] sample moments - component caching (2 moments)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeSampleMomentsComponentCachingTwoMomentsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 2);

            processSampleMoments(cachingSchemeAbstractUniquePtr.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sample moments - component caching (5 moments)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] sample moments - component caching (5 moments)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeSampleMomentsComponentCachingFiveMomentsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCaraMoreSampleMoments(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 5);

            processSampleMoments(cachingSchemeAbstractUniquePtr.get(), actualResult, variableSet);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        //test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sample moments - component caching (current component)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] sample moments - component caching (current component)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeSampleMomentsComponentCachingCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 2);

            processSampleMomentsCurrentComponent(cachingSchemeAbstractUniquePtr.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sample moments - component caching (assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] sample moments - component caching (assignment)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeSampleMomentsComponentCachingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 2);

            processSampleMomentsAssignment(cachingSchemeAbstractUniquePtr.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sample moments - hypergraph cut caching (no moment)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] sample moments - hypergraph cut caching (no moment)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeSampleMomentsHypergraphCutCachingNoMomentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 0);

            processSampleMoments(cachingSchemeAbstractUniquePtr.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sample moments - hypergraph cut caching (1 moment)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] sample moments - hypergraph cut caching (1 moment)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeSampleMomentsHypergraphCutCachingOneMomentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 1);

            processSampleMoments(cachingSchemeAbstractUniquePtr.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sample moments - hypergraph cut caching (2 moments)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] sample moments - hypergraph cut caching (2 moments)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeSampleMomentsHypergraphCutCachingTwoMomentsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 2);

            processSampleMoments(cachingSchemeAbstractUniquePtr.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sample moments - hypergraph cut caching (5 moments)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] sample moments - hypergraph cut caching (5 moments)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeSampleMomentsHypergraphCutCachingFiveMomentsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCaraMoreSampleMoments(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 5);

            processSampleMoments(cachingSchemeAbstractUniquePtr.get(), actualResult, variableSet);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sample moments - hypergraph cut caching (current component)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] sample moments - hypergraph cut caching (current component)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeSampleMomentsHypergraphCutCachingCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 2);

            processSampleMomentsCurrentComponent(cachingSchemeAbstractUniquePtr.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sample moments - hypergraph cut caching (assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] sample moments - hypergraph cut caching (assignment)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeSampleMomentsHypergraphCutCachingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 2);

            processSampleMomentsAssignment(cachingSchemeAbstractUniquePtr.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cara - component caching (var -> lit)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - component caching (var -> lit)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeComponentCachingVarToLitMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 2, true,
                                                                                                        PreprocessingTypeEnum::NONE);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cara - component caching (not duplicate clauses, var -> lit)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - component caching (not duplicate clauses, var -> lit)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeComponentCachingNotDuplicateClausesVarToLitMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 2, true,
                                                                                                        PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES);

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
     * Cara - component caching (not subsumed clauses, var -> lit)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - component caching (not subsumed clauses, var -> lit)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeComponentCachingNotSubsumedClausesVarToLitMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 2, true,
                                                                                                        PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES);

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
     * Cara - component caching (not subsumed clauses, var -> lit, used variables)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - component caching (not subsumed clauses, var -> lit, used variables)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeComponentCachingNotSubsumedClausesVarToLitMappingUsedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCaraNotSubsumedClausesUsedVariables();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 2, true,
                                                                                                        PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES);

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
     * Cara - component caching (var -> var)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - component caching (var -> var)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeComponentCachingVarToVarMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 2, false,
                                                                                                        PreprocessingTypeEnum::NONE);

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
     * Cara - component caching (not duplicate clauses, var -> var)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - component caching (not duplicate clauses, var -> var)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeComponentCachingNotDuplicateClausesVarToVarMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 2, false,
                                                                                                        PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES);

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
     * Cara - component caching (not subsumed clauses, var -> var)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - component caching (not subsumed clauses, var -> var)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeComponentCachingNotSubsumedClausesVarToVarMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 2, false,
                                                                                                        PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES);

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
     * Cara - component caching (not subsumed clauses, var -> var, used variables)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - component caching (not subsumed clauses, var -> var, used variables)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeComponentCachingNotSubsumedClausesVarToVarMappingUsedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCaraNotSubsumedClausesUsedVariables();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 2, false,
                                                                                                        PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES);

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
     * Cara - component caching (var -> lit, current component)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - component caching (var -> lit, current component)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeComponentCachingVarToLitMappingCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 2, true,
                                                                                                        PreprocessingTypeEnum::NONE);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            processCurrentComponent(cache, formulaRepresentation.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cara - component caching (var -> var, current component)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - component caching (var -> var, current component)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeComponentCachingVarToVarMappingCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 2, false,
                                                                                                        PreprocessingTypeEnum::NONE);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            processCurrentComponent(cache, formulaRepresentation.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cara - component caching (var -> lit, assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - component caching (var -> lit, assignment)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeComponentCachingVarToLitMappingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 2, true,
                                                                                                        PreprocessingTypeEnum::NONE);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            processAssignment(cache, formulaRepresentation.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cara - component caching (var -> var, assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - component caching (var -> var, assignment)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeComponentCachingVarToVarMappingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::COMPONENT, 2, false,
                                                                                                        PreprocessingTypeEnum::NONE);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            processAssignment(cache, formulaRepresentation.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cara - hypergraph cut caching (var -> lit)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - hypergraph cut caching (var -> lit)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeHypergraphCutCachingVarToLitMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 2, true,
                                                                                                        PreprocessingTypeEnum::NONE);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cara - hypergraph cut caching (not duplicate clauses, var -> lit)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - hypergraph cut caching (not duplicate clauses, var -> lit)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeHypergraphCutCachingNotDuplicateClausesVarToLitMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 2, true,
                                                                                                        PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES);

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
     * Cara - hypergraph cut caching (not subsumed clauses, var -> lit)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - hypergraph cut caching (not subsumed clauses, var -> lit)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeHypergraphCutCachingNotSubsumedClausesVarToLitMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 2, true,
                                                                                                        PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES);

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
     * Cara - hypergraph cut caching (not subsumed clauses, var -> lit, used variables)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - hypergraph cut caching (not subsumed clauses, var -> lit, used variables)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeHypergraphCutCachingNotSubsumedClausesVarToLitMappingUsedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCaraNotSubsumedClausesUsedVariables();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 2, true,
                                                                                                        PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES);

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
     * Cara - hypergraph cut caching (var -> var)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - hypergraph cut caching (var -> var)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeHypergraphCutCachingVarToVarMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 2, false,
                                                                                                        PreprocessingTypeEnum::NONE);

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
     * Cara - hypergraph cut caching (not duplicate clauses, var -> var)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - hypergraph cut caching (not duplicate clauses, var -> var)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeHypergraphCutCachingNotDuplicateClausesVarToVarMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 2, false,
                                                                                                        PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES);

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
     * Cara - hypergraph cut caching (not subsumed clauses, var -> var)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - hypergraph cut caching (not subsumed clauses, var -> var)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeHypergraphCutCachingNotSubsumedClausesVarToVarMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 2, false,
                                                                                                        PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES);

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
     * Cara - hypergraph cut caching (not subsumed clauses, var -> var, used variables)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - hypergraph cut caching (not subsumed clauses, var -> var, used variables)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeHypergraphCutCachingNotSubsumedClausesVarToVarMappingUsedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCaraNotSubsumedClausesUsedVariables();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 2, false,
                                                                                                        PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES);

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
     * Cara - hypergraph cut caching (var -> lit, current component)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - hypergraph cut caching (var -> lit, current component)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeHypergraphCutCachingVarToLitMappingCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 2, true,
                                                                                                        PreprocessingTypeEnum::NONE);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            processCurrentComponent(cache, formulaRepresentation.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cara - hypergraph cut caching (var -> var, current component)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - hypergraph cut caching (var -> var, current component)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeHypergraphCutCachingVarToVarMappingCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 2, false,
                                                                                                        PreprocessingTypeEnum::NONE);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            processCurrentComponent(cache, formulaRepresentation.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cara - hypergraph cut caching (var -> lit, assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - hypergraph cut caching (var -> lit, assignment)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeHypergraphCutCachingVarToLitMappingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 2, true,
                                                                                                        PreprocessingTypeEnum::NONE);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            processAssignment(cache, formulaRepresentation.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cara - hypergraph cut caching (var -> var, assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Cara] cara - hypergraph cut caching (var -> var, assignment)", "[Cache::CachingScheme::Cara]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          caraCachingSchemeHypergraphCutCachingVarToVarMappingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForCara();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createCaraCachingScheme(formulaRepresentation.get(),
                                                                                                        CacheTypeEnum::HYPERGRAPH_CUT, 2, false,
                                                                                                        PreprocessingTypeEnum::NONE);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            processAssignment(cache, formulaRepresentation.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Cache::CachingScheme::Cara
