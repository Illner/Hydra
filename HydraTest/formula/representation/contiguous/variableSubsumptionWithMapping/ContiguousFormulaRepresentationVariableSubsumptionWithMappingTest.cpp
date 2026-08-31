#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/external/unitTesting/Catch2/catch.hpp"
#include "HydraTest/formula/representation/contiguous/variableSubsumptionWithMapping/ContiguousFormulaRepresentationVariableSubsumptionWithMappingTestResult.hpp"

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contiguous/ContiguousFormulaRepresentation.hpp"
#include "Hydra/formula/representation/contiguous/ContiguousFormulaRepresentation.tpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/computeConnectedComponents/ConnectedComponentStructure.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/formula/representation/contiguous/enums/VariableSubsumptionWithMappingTypeEnum.hpp"
#include "Hydra/hypergraphPartitioning/enums/VertexWeightTypeEnum.hpp"

namespace HydraTest::Formula::Representation::Contiguous::VariableSubsumptionWithMapping {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;
    using ClauseIdT = char8_t;

    using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
    using FormulaType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::FormulaType;
    using VectorSetType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VectorSetType;
    using VariableSetType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
    using ClauseIdSetType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdSetType;
    using LiteralVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
    using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
    using VariableVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
    using VariableVectorMapType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorMapType;
    using VertexWeightVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VertexWeightVectorType;
    using VariableSortedVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableSortedVectorType;
    using MappingFromVariableToVariableType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::MappingFromVariableToVariableType;

    using ContiguousFormulaRepresentationConfigurationType = Hydra::Formula::Representation::Contiguous::ContiguousFormulaRepresentationConfiguration;
    using ContiguousFormulaRepresentationType = Hydra::Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

    using ConnectedComponentStructure = Hydra::Container::ComputeConnectedComponents::ConnectedComponentStruct<VarT, LiteralT>;

    using IgnorePureLiteralTypeEnum = Hydra::IgnorePureLiteralTypeEnum;
    using VertexWeightTypeEnum = Hydra::HypergraphPartitioning::VertexWeightTypeEnum;
    using VariableSubsumptionWithMappingTypeEnum = Hydra::Formula::Representation::Contiguous::VariableSubsumptionWithMappingTypeEnum;
    //endregion

    //region Functions
    void printContiguousFormulaRepresentation(const ContiguousFormulaRepresentationType& contiguousFormulaRepresentation, std::stringstream& actualResult) {
        actualResult << "Current formula: " << std::endl;
        contiguousFormulaRepresentation.printCurrentFormulaDebug(actualResult, false, false);
        actualResult << std::endl;
    }

    void printClauseIdVectorSet(VectorSetType& clauseThatVariableSubsumesSomeClauseVectorSet, std::stringstream& actualResult) {
        actualResult << "Clauses that variable subsume some clause:";
        for (std::size_t clauseId : clauseThatVariableSubsumesSomeClauseVectorSet.getAddedElementVector(true))
            actualResult << " " << std::to_string(clauseId);
        actualResult << std::endl;
    }

    void processVariableSubsumptionWithMappingCurrentComponent(ContiguousFormulaRepresentationType& contiguousFormulaRepresentation, std::stringstream& actualResult) {
        printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult);
        actualResult << "--------------------------------------------------------------------------------" << std::endl
                     << std::endl;

        std::vector<VariableSetType> currentComponentVariableSetVector { { 1, 2 }, { 3, 4 }, { 5, 6, 7 }, { 8, 9, 10 }, { 1, 2, 3, 4 }, { 5, 6, 7, 8, 9, 10 }, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } };

        VectorSetType clauseThatVariableSubsumesSomeClauseVectorSet(contiguousFormulaRepresentation.getNumberOfOriginalClauses());

        for (const VariableSetType& currentComponentVariableSet : currentComponentVariableSetVector) {
            actualResult << "Current component:";
            VariableSortedVectorType variableSortedVector = Hydra::Other::sortUnorderedSet(currentComponentVariableSet);
            for (VarT var : variableSortedVector)
                actualResult << " " << std::to_string(var);
            actualResult << std::endl;

            ConnectedComponentStructure connectedComponentStructure(currentComponentVariableSet.size());
            connectedComponentStructure.variableSet.insert(currentComponentVariableSet.cbegin(), currentComponentVariableSet.cend());

            contiguousFormulaRepresentation.setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);
            printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult);

            VertexWeightVectorType vertexWeightVector;
            contiguousFormulaRepresentation.getCurrentComponentClausesThatVariableSubsumeSomeClause(currentComponentVariableSet,
                                                                                                    clauseThatVariableSubsumesSomeClauseVectorSet,
                                                                                                    VariableVectorMapType(), IgnorePureLiteralTypeEnum::NONE,
                                                                                                    VertexWeightTypeEnum::NONE, vertexWeightVector);
            printClauseIdVectorSet(clauseThatVariableSubsumesSomeClauseVectorSet, actualResult);

            contiguousFormulaRepresentation.popPreviousComponent(connectedComponentStructure, {});
            actualResult << "--------------------" << std::endl
                         << std::endl;
        }
    }

    void processVariableSubsumptionWithMappingVariableMapping(const ContiguousFormulaRepresentationType& contiguousFormulaRepresentation, std::stringstream& actualResult) {
        printContiguousFormulaRepresentation(contiguousFormulaRepresentation, actualResult);
        actualResult << "--------------------------------------------------------------------------------" << std::endl
                     << std::endl;

        std::vector<MappingFromVariableToVariableType> variableMappingVector { {}, { { (VarT)1, (VarT)2 } }, { { (VarT)2, (VarT)1 } }, { { (VarT)3, (VarT)4 }, { (VarT)4, (VarT)3 } }, { { (VarT)1, (VarT)3 }, { (VarT)2, (VarT)5 } }, { { (VarT)3, (VarT)5 }, { (VarT)4, (VarT)6 } }, { { (VarT)8, (VarT)9 } }, { { (VarT)9, (VarT)8 }, { (VarT)10, (VarT)8 } } };

        VectorSetType clauseThatVariableSubsumesSomeClauseVectorSet(contiguousFormulaRepresentation.getNumberOfOriginalClauses());
        VariableVectorMapType variableVectorMap(contiguousFormulaRepresentation.getNumberOfVariablesInOriginalFormulaUsedForIndexing(), 0);

        for (const MappingFromVariableToVariableType& variableMapping : variableMappingVector) {
            variableVectorMap.clear();

            for (auto [key, value] : variableMapping)
                variableVectorMap.insert(key, value);

            actualResult << "Variable mapping:";
            for (VarT var : variableVectorMap.getAddedKeyVector(true))
                actualResult << " " << std::to_string(var) << " -> " << std::to_string(variableVectorMap[var]) << ", ";
            actualResult << std::endl;

            VertexWeightVectorType vertexWeightVector;
            contiguousFormulaRepresentation.getCurrentComponentClausesThatVariableSubsumeSomeClause({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                                                                                                    clauseThatVariableSubsumesSomeClauseVectorSet,
                                                                                                    variableVectorMap, IgnorePureLiteralTypeEnum::NONE,
                                                                                                    VertexWeightTypeEnum::NONE, vertexWeightVector);
            printClauseIdVectorSet(clauseThatVariableSubsumesSomeClauseVectorSet, actualResult);

            actualResult << "--------------------" << std::endl
                         << std::endl;
        }
    }
    //endregion

    //region ContiguousFormulaRepresentation
    ContiguousFormulaRepresentationType createContiguousFormulaRepresentation(VariableSubsumptionWithMappingTypeEnum variableSubsumptionWithMappingType) {
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
        LiteralType litPos7(7, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg9(9, false);
        LiteralType litPos10(10, true);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, zeroLit,   // 0
            litNeg2, zeroLit,   // 1

            litNeg3, litNeg4, zeroLit,   // 2
            litNeg3, litPos4, zeroLit,   // 3
            litPos3, litNeg4, zeroLit,   // 4
            litPos3, litPos4, zeroLit,   // 5

            litPos5, litPos6, zeroLit,            // 6
            litPos5, litNeg7, zeroLit,            // 7
            litNeg6, litNeg7, zeroLit,            // 8
            litNeg5, litPos6, litPos7, zeroLit,   // 9

            litPos8, litNeg9, litPos10, zeroLit,   // 10
            litPos8, litNeg9, litPos10, zeroLit    // 11
        };

        VarT numberOfVariables = 10;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contiguous::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contiguous::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContiguousFormulaRepresentationConfigurationType configuration;
        configuration.variableSubsumptionWithMappingType = variableSubsumptionWithMappingType;

        ContiguousFormulaRepresentationType contiguousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences,
                                                                            configuration);
        return contiguousFormulaRepresentation;
    }

    ContiguousFormulaRepresentationType createContiguousFormulaRepresentationForIgnorePureLiteralType(VariableSubsumptionWithMappingTypeEnum variableSubsumptionWithMappingType) {
        LiteralType litPos1(1, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, zeroLit,                     // 0
            litNeg2, zeroLit,                     // 1
            litNeg5, litPos8, zeroLit,            // 2
            litPos1, litPos3, litPos4, zeroLit,   // 3
            litPos1, litNeg4, litPos5, zeroLit,   // 4
            litNeg2, litNeg6, litNeg7, zeroLit,   // 5
            litNeg2, litPos7, litNeg8, zeroLit    // 6
        };

        VarT numberOfVariables = 8;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contiguous::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contiguous::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContiguousFormulaRepresentationConfigurationType configuration;
        configuration.variableSubsumptionWithMappingType = variableSubsumptionWithMappingType;

        ContiguousFormulaRepresentationType contiguousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences,
                                                                            configuration);
        return contiguousFormulaRepresentation;
    }
    //endregion

    /**
     * Forward variable subsumption with mapping detection
     */
    TEST_CASE("[Formula::Representation::Contiguous::VariableSubsumptionWithMapping] forward variable subsumption with mapping detection", "[Formula::Representation::Contiguous::VariableSubsumptionWithMapping]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationVariableSubsumptionWithMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION);
            printContiguousFormulaRepresentation(formula, actualResult);

            VertexWeightVectorType vertexWeightVector;
            VectorSetType clauseThatVariableSubsumesSomeClauseVectorSet(formula.getNumberOfOriginalClauses());
            formula.getCurrentComponentClausesThatVariableSubsumeSomeClause({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, clauseThatVariableSubsumesSomeClauseVectorSet, VariableVectorMapType(),
                                                                            IgnorePureLiteralTypeEnum::NONE, VertexWeightTypeEnum::NONE, vertexWeightVector);
            printClauseIdVectorSet(clauseThatVariableSubsumesSomeClauseVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption with mapping detection (current component)
     */
    TEST_CASE("[Formula::Representation::Contiguous::VariableSubsumptionWithMapping] forward variable subsumption with mapping detection (current component)", "[Formula::Representation::Contiguous::VariableSubsumptionWithMapping]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationVariableSubsumptionWithMappingCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION);
            processVariableSubsumptionWithMappingCurrentComponent(formula, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption with mapping detection (variable mapping)
     */
    TEST_CASE("[Formula::Representation::Contiguous::VariableSubsumptionWithMapping] forward variable subsumption with mapping detection (variable mapping)", "[Formula::Representation::Contiguous::VariableSubsumptionWithMapping]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationVariableSubsumptionWithMappingVariableMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION);
            processVariableSubsumptionWithMappingVariableMapping(formula, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    #if defined(BELLA_COMPILER)
    /**
     * Forward variable subsumption with mapping detection (ignore positive pure literals)
     */
    TEST_CASE("[Formula::Representation::Contiguous::VariableSubsumptionWithMapping] forward variable subsumption with mapping detection (ignore positive pure literals)", "[Formula::Representation::Contiguous::VariableSubsumptionWithMapping]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationVariableSubsumptionWithMappingIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentationForIgnorePureLiteralType(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION);
            printContiguousFormulaRepresentation(formula, actualResult);

            VertexWeightVectorType vertexWeightVector;
            VectorSetType clauseThatVariableSubsumesSomeClauseVectorSet(formula.getNumberOfOriginalClauses());
            formula.getCurrentComponentClausesThatVariableSubsumeSomeClause({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseThatVariableSubsumesSomeClauseVectorSet, VariableVectorMapType(),
                                                                            IgnorePureLiteralTypeEnum::ONLY_POSITIVE, VertexWeightTypeEnum::NONE, vertexWeightVector);
            printClauseIdVectorSet(clauseThatVariableSubsumesSomeClauseVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption with mapping detection (ignore negative pure literals)
     */
    TEST_CASE("[Formula::Representation::Contiguous::VariableSubsumptionWithMapping] forward variable subsumption with mapping detection (ignore negative pure literals)", "[Formula::Representation::Contiguous::VariableSubsumptionWithMapping]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationVariableSubsumptionWithMappingIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentationForIgnorePureLiteralType(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION);
            printContiguousFormulaRepresentation(formula, actualResult);

            VertexWeightVectorType vertexWeightVector;
            VectorSetType clauseThatVariableSubsumesSomeClauseVectorSet(formula.getNumberOfOriginalClauses());
            formula.getCurrentComponentClausesThatVariableSubsumeSomeClause({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseThatVariableSubsumesSomeClauseVectorSet, VariableVectorMapType(),
                                                                            IgnorePureLiteralTypeEnum::ONLY_NEGATIVE, VertexWeightTypeEnum::NONE, vertexWeightVector);
            printClauseIdVectorSet(clauseThatVariableSubsumesSomeClauseVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption with mapping detection (ignore pure literals)
     */
    TEST_CASE("[Formula::Representation::Contiguous::VariableSubsumptionWithMapping] forward variable subsumption with mapping detection (ignore pure literals)", "[Formula::Representation::Contiguous::VariableSubsumptionWithMapping]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationVariableSubsumptionWithMappingIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentationForIgnorePureLiteralType(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION);
            printContiguousFormulaRepresentation(formula, actualResult);

            VertexWeightVectorType vertexWeightVector;
            VectorSetType clauseThatVariableSubsumesSomeClauseVectorSet(formula.getNumberOfOriginalClauses());
            formula.getCurrentComponentClausesThatVariableSubsumeSomeClause({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseThatVariableSubsumesSomeClauseVectorSet, VariableVectorMapType(),
                                                                            IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE, VertexWeightTypeEnum::NONE, vertexWeightVector);
            printClauseIdVectorSet(clauseThatVariableSubsumesSomeClauseVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif

    /**
     * Forward variable subsumption with mapping detection (not ignore pure literals)
     */
    TEST_CASE("[Formula::Representation::Contiguous::VariableSubsumptionWithMapping] forward variable subsumption with mapping detection (not ignore pure literals)", "[Formula::Representation::Contiguous::VariableSubsumptionWithMapping]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationVariableSubsumptionWithMappingNotIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentationForIgnorePureLiteralType(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION);
            printContiguousFormulaRepresentation(formula, actualResult);

            VertexWeightVectorType vertexWeightVector;
            VectorSetType clauseThatVariableSubsumesSomeClauseVectorSet(formula.getNumberOfOriginalClauses());
            formula.getCurrentComponentClausesThatVariableSubsumeSomeClause({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseThatVariableSubsumesSomeClauseVectorSet, VariableVectorMapType(),
                                                                            IgnorePureLiteralTypeEnum::NONE, VertexWeightTypeEnum::NONE, vertexWeightVector);
            printClauseIdVectorSet(clauseThatVariableSubsumesSomeClauseVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm with mapping
     */
    TEST_CASE("[Formula::Representation::Contiguous::VariableSubsumptionWithMapping] one-literal watching algorithm with mapping", "[Formula::Representation::Contiguous::VariableSubsumptionWithMapping]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationVariableSubsumptionWithMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING);
            printContiguousFormulaRepresentation(formula, actualResult);

            VertexWeightVectorType vertexWeightVector;
            VectorSetType clauseThatVariableSubsumesSomeClauseVectorSet(formula.getNumberOfOriginalClauses());
            formula.getCurrentComponentClausesThatVariableSubsumeSomeClause({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, clauseThatVariableSubsumesSomeClauseVectorSet, VariableVectorMapType(),
                                                                            IgnorePureLiteralTypeEnum::NONE, VertexWeightTypeEnum::NONE, vertexWeightVector);
            printClauseIdVectorSet(clauseThatVariableSubsumesSomeClauseVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm with mapping (current component)
     */
    TEST_CASE("[Formula::Representation::Contiguous::VariableSubsumptionWithMapping] one-literal watching algorithm with mapping (current component)", "[Formula::Representation::Contiguous::VariableSubsumptionWithMapping]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationVariableSubsumptionWithMappingCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING);
            processVariableSubsumptionWithMappingCurrentComponent(formula, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm with mapping (variable mapping)
     */
    TEST_CASE("[Formula::Representation::Contiguous::VariableSubsumptionWithMapping] one-literal watching algorithm with mapping (variable mapping)", "[Formula::Representation::Contiguous::VariableSubsumptionWithMapping]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationVariableSubsumptionWithMappingVariableMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING);
            processVariableSubsumptionWithMappingVariableMapping(formula, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    #if defined(BELLA_COMPILER)
    /**
     * One-literal watching algorithm with mapping (ignore positive pure literals)
     */
    TEST_CASE("[Formula::Representation::Contiguous::VariableSubsumptionWithMapping] one-literal watching algorithm with mapping (ignore positive pure literals)", "[Formula::Representation::Contiguous::VariableSubsumptionWithMapping]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationVariableSubsumptionWithMappingIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentationForIgnorePureLiteralType(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING);
            printContiguousFormulaRepresentation(formula, actualResult);

            VertexWeightVectorType vertexWeightVector;
            VectorSetType clauseThatVariableSubsumesSomeClauseVectorSet(formula.getNumberOfOriginalClauses());
            formula.getCurrentComponentClausesThatVariableSubsumeSomeClause({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseThatVariableSubsumesSomeClauseVectorSet, VariableVectorMapType(),
                                                                            IgnorePureLiteralTypeEnum::ONLY_POSITIVE, VertexWeightTypeEnum::NONE, vertexWeightVector);
            printClauseIdVectorSet(clauseThatVariableSubsumesSomeClauseVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm with mapping (ignore negative pure literals)
     */
    TEST_CASE("[Formula::Representation::Contiguous::VariableSubsumptionWithMapping] one-literal watching algorithm with mapping (ignore negative pure literals)", "[Formula::Representation::Contiguous::VariableSubsumptionWithMapping]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationVariableSubsumptionWithMappingIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentationForIgnorePureLiteralType(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING);
            printContiguousFormulaRepresentation(formula, actualResult);

            VertexWeightVectorType vertexWeightVector;
            VectorSetType clauseThatVariableSubsumesSomeClauseVectorSet(formula.getNumberOfOriginalClauses());
            formula.getCurrentComponentClausesThatVariableSubsumeSomeClause({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseThatVariableSubsumesSomeClauseVectorSet, VariableVectorMapType(),
                                                                            IgnorePureLiteralTypeEnum::ONLY_NEGATIVE, VertexWeightTypeEnum::NONE, vertexWeightVector);
            printClauseIdVectorSet(clauseThatVariableSubsumesSomeClauseVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm with mapping (ignore pure literals)
     */
    TEST_CASE("[Formula::Representation::Contiguous::VariableSubsumptionWithMapping] one-literal watching algorithm with mapping (ignore pure literals)", "[Formula::Representation::Contiguous::VariableSubsumptionWithMapping]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationVariableSubsumptionWithMappingIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentationForIgnorePureLiteralType(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING);
            printContiguousFormulaRepresentation(formula, actualResult);

            VertexWeightVectorType vertexWeightVector;
            VectorSetType clauseThatVariableSubsumesSomeClauseVectorSet(formula.getNumberOfOriginalClauses());
            formula.getCurrentComponentClausesThatVariableSubsumeSomeClause({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseThatVariableSubsumesSomeClauseVectorSet, VariableVectorMapType(),
                                                                            IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE, VertexWeightTypeEnum::NONE, vertexWeightVector);
            printClauseIdVectorSet(clauseThatVariableSubsumesSomeClauseVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif

    /**
     * One-literal watching algorithm with mapping (not ignore pure literals)
     */
    TEST_CASE("[Formula::Representation::Contiguous::VariableSubsumptionWithMapping] one-literal watching algorithm with mapping (not ignore pure literals)", "[Formula::Representation::Contiguous::VariableSubsumptionWithMapping]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationVariableSubsumptionWithMappingNotIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentationForIgnorePureLiteralType(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING);
            printContiguousFormulaRepresentation(formula, actualResult);

            VertexWeightVectorType vertexWeightVector;
            VectorSetType clauseThatVariableSubsumesSomeClauseVectorSet(formula.getNumberOfOriginalClauses());
            formula.getCurrentComponentClausesThatVariableSubsumeSomeClause({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseThatVariableSubsumesSomeClauseVectorSet, VariableVectorMapType(),
                                                                            IgnorePureLiteralTypeEnum::NONE, VertexWeightTypeEnum::NONE, vertexWeightVector);
            printClauseIdVectorSet(clauseThatVariableSubsumesSomeClauseVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Formula::Representation::Contiguous::VariableSubsumptionWithMapping
