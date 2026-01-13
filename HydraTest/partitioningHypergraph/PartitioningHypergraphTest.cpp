#include <algorithm>
#include <cassert>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/partitioningHypergraph/PartitioningHypergraphTestResult.hpp"

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.hpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.tpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/computeConnectedComponents/ConnectedComponentStructure.hpp"
#include "Hydra/other/operatingSystem/OperatingSystem.hpp"
#include "Hydra/partitioningHypergraph/PartitioningHypergraphAbstract.hpp"
#include "Hydra/partitioningHypergraph/hmetis/HmetisPartitioningHypergraph.hpp"
#include "Hydra/partitioningHypergraph/kahypar/KahyparPartitioningHypergraph.hpp"
#include "Hydra/partitioningHypergraph/patoh/PatohPartitioningHypergraph.hpp"
#include "Hydra/satSolver/EquivalencePreprocessingStructure.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/partitioningHypergraph/exceptions/PartitioningHypergraphException.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/compiler/enums/PartitioningHypergraphTypeEnum.hpp"
#include "Hydra/formula/representation/contagious/enums/VariableSubsumptionWithMappingTypeEnum.hpp"
#include "Hydra/partitioningHypergraph/enums/VertexWeightTypeEnum.hpp"

namespace HydraTest::PartitioningHypergraph {

    using FormulaSizeType = Hydra::Formula::Representation::FormulaSizeType;

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;
    using ClauseIdT = char8_t;

    using LiteralType = typename Hydra::Formula::Literal<VarT, LiteralT>::LiteralType;
    using VariableSetType = typename Hydra::Formula::Literal<VarT, LiteralT>::VariableSetType;
    using LiteralVectorType = typename Hydra::Formula::Literal<VarT, LiteralT>::LiteralVectorType;
    using VariableVectorType = typename Hydra::Formula::Literal<VarT, LiteralT>::VariableVectorType;
    using VariableSortedVectorType = typename Hydra::Formula::Literal<VarT, LiteralT>::VariableSortedVectorType;
    using PartvecType = typename Hydra::PartitioningHypergraph::PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::PartvecType;
    using ClauseIdSetType = typename Hydra::PartitioningHypergraph::PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdSetType;
    using VertexWeightType = typename Hydra::PartitioningHypergraph::PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VertexWeightType;
    using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
    using ClauseIdVectorType = typename Hydra::PartitioningHypergraph::PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
    using OccurrenceListStruct = typename Hydra::PartitioningHypergraph::PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::OccurrenceListStruct;
    using ClauseIdVectorMapType = typename Hydra::PartitioningHypergraph::PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorMapType;
    using VariableVectorMapType = typename Hydra::PartitioningHypergraph::PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorMapType;
    using VertexWeightVectorType = typename Hydra::PartitioningHypergraph::PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VertexWeightVectorType;
    using ClauseIdSortedVectorType = typename Hydra::PartitioningHypergraph::PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdSortedVectorType;
    using OccurrenceListVectorType = typename Hydra::PartitioningHypergraph::PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::OccurrenceListVectorType;
    using VariableReusableVectorType = typename Hydra::PartitioningHypergraph::PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VariableReusableVectorType;
    using EquivalenceStructureVectorType = typename Hydra::PartitioningHypergraph::PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::EquivalenceStructureVectorType;

    using FormulaRepresentationAbstractType = Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>;
    using PatohPartitioningHypergraphType = Hydra::PartitioningHypergraph::Patoh::PatohPartitioningHypergraph<VarT, LiteralT, ClauseIdT>;
    using HmetisPartitioningHypergraphType = Hydra::PartitioningHypergraph::Hmetis::HmetisPartitioningHypergraph<VarT, LiteralT, ClauseIdT>;
    using KahyparPartitioningHypergraphType = Hydra::PartitioningHypergraph::Kahypar::KahyparPartitioningHypergraph<VarT, LiteralT, ClauseIdT>;
    using FormulaRepresentationAbstractPtrType = const Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;
    using PartitioningHypergraphAbstractPtrType = const Hydra::PartitioningHypergraph::PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>*;
    using ContagiousFormulaRepresentationConfiguration = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration;
    using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
    using EquivalencePreprocessingStructureType = Hydra::SatSolver::EquivalencePreprocessingStruct<VarT, LiteralT>::EquivalencePreprocessingStructureType;
    using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;
    using PartitioningHypergraphAbstractUniquePtrType = std::unique_ptr<Hydra::PartitioningHypergraph::PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>>;

    using EquivalencePreprocessingStruct = Hydra::SatSolver::EquivalencePreprocessingStruct<VarT, LiteralT>;
    using ConnectedComponentStruct = Hydra::Container::ComputeConnectedComponents::ConnectedComponentStruct<VarT, LiteralT>;

    using PinType = int;
    using XpinType = int;
    using PinVectorType = std::vector<PinType>;
    using XpinVectorType = std::vector<XpinType>;
    using IgnorePureLiteralTypeEnum = Hydra::IgnorePureLiteralTypeEnum;
    using PartitioningHypergraphTypeEnum = Hydra::PartitioningHypergraphTypeEnum;
    using VertexWeightTypeEnum = Hydra::PartitioningHypergraph::VertexWeightTypeEnum;
    using VariableSubsumptionWithMappingTypeEnum = Hydra::Formula::Representation::Contagious::VariableSubsumptionWithMappingTypeEnum;
    //endregion

    struct EquivalenceStruct {
        VariableVectorMapType equivalenceVectorMap;
        VariableReusableVectorType variableOrderReusableVector;
        EquivalenceStructureVectorType equivalenceStructureVector;
    };

    //region Functions
    void printEquivalenceStructure(VariableVectorMapType& equivalenceVectorMap, VariableReusableVectorType& variableOrderReusableVector,
                                   EquivalenceStructureVectorType& equivalenceStructureVector, std::stringstream& actualResult) {
        // Equivalence structure
        actualResult << "Equivalence structure" << std::endl;
        for (VarT i = 0; i < variableOrderReusableVector.size(); ++i) {
            actualResult << "\t" << std::to_string(variableOrderReusableVector[i]) << ":";

            std::stable_sort(equivalenceStructureVector[i].begin(), equivalenceStructureVector[i].end());

            for (VarT var : equivalenceStructureVector[i])
                actualResult << " " << std::to_string(var);
            actualResult << std::endl;
        }

        // Equivalence mapping
        actualResult << "Equivalence mapping" << std::endl;
        for (VarT var : equivalenceVectorMap.getAddedKeyVector(true))
            actualResult << "\t" << std::to_string(var) << " -> " << std::to_string(equivalenceVectorMap[var]) << std::endl;
        actualResult << std::endl;
    }

    void printEquivalenceStructure(EquivalenceStruct& equivalenceStruct, std::stringstream& actualResult) {
        printEquivalenceStructure(equivalenceStruct.equivalenceVectorMap, equivalenceStruct.variableOrderReusableVector,
                                  equivalenceStruct.equivalenceStructureVector, actualResult);
    }

    void printEquivalencePreprocessingStructure(const EquivalencePreprocessingStruct& equivalencePreprocessingStruct, std::stringstream& actualResult) {
        actualResult << "Equivalence preprocessing structure" << std::endl;

        for (const VariableVectorType& variableVector : equivalencePreprocessingStruct.equivalencePreprocessingStructure) {
            assert(variableVector.size() > 1);

            // Representant
            actualResult << std::to_string(variableVector[0]) << " |";

            for (VarT var : variableVector)
                actualResult << " " << std::to_string(var);
            actualResult << std::endl;
        }

        actualResult << std::endl;
    }

    void printOccurrenceList(const OccurrenceListStruct& occurrenceListStruct, std::stringstream& actualResult, bool useRemapping = true) {
        ClauseIdVectorMapType fromIndexToClauseIdVectorMap(occurrenceListStruct.fromClauseIdToIndexVectorMap.size(), 0);

        for (ClauseIdT clauseId : occurrenceListStruct.fromClauseIdToIndexVectorMap.getAddedKeyVector())
            fromIndexToClauseIdVectorMap.insert(occurrenceListStruct.fromClauseIdToIndexVectorMap[clauseId], clauseId);

        actualResult << "Occurrence list" << std::endl;
        actualResult << "Size: " << std::to_string(occurrenceListStruct.occurrenceListSize) << std::endl;
        actualResult << "Number of different clauses: " << std::to_string(occurrenceListStruct.numberOfDifferentClausesInOccurrenceList) << std::endl;

        for (VarT i = 0; i < occurrenceListStruct.variableOrderReusableVector.size(); ++i) {
            actualResult << "\t" << std::to_string(occurrenceListStruct.variableOrderReusableVector[i]) << ":";

            for (ClauseIdT j : occurrenceListStruct.occurrenceListVector[i]) {
                if (useRemapping)
                    actualResult << " " << std::to_string(fromIndexToClauseIdVectorMap[j]);
                else
                    actualResult << " " << std::to_string(j);
            }

            actualResult << std::endl;
        }

        actualResult << std::endl;
    }

    void printXpinsAndPins(const XpinVectorType& xpins, const PinVectorType& pins, std::stringstream& actualResult) {
        actualResult << "Xpins:";
        for (XpinType i : xpins)
            actualResult << " " << std::to_string(i);
        actualResult << std::endl;

        actualResult << "Pins:";
        for (PinType i : pins)
            actualResult << " " << std::to_string(i);
        actualResult << std::endl
                     << std::endl;
    }

    void printCut(const VariableSetType& cut, std::stringstream& actualResult) {
        actualResult << "Cut:";
        for (VarT var : Hydra::Other::sortUnorderedSet(cut))
            actualResult << " " << std::to_string(var);
        actualResult << std::endl
                     << std::endl;
    }

    void printFromClauseIdToIndexVectorMap(ClauseIdVectorMapType& fromClauseIdToIndexVectorMap, std::stringstream& actualResult) {
        actualResult << "Mapping (clauseId -> index)" << std::endl;
        for (ClauseIdT clauseId : fromClauseIdToIndexVectorMap.getAddedKeyVector(true))
            actualResult << "\t" << std::to_string(clauseId) << " -> " << std::to_string(fromClauseIdToIndexVectorMap[clauseId]) << std::endl;
        actualResult << std::endl;
    }

    void printFormula(FormulaRepresentationAbstractPtrType formulaRepresentationPtr, std::stringstream& actualResult) {
        actualResult << "Formula: ";
        formulaRepresentationPtr->printCurrentFormulaDebug(actualResult);
        actualResult << std::endl
                     << std::endl;
    }

    void printCurrentComponent(const VariableSetType& currentComponentVariableSet, std::stringstream& actualResult) {
        VariableSortedVectorType currentComponentVariableSortedVector = Hydra::Other::sortUnorderedSet(currentComponentVariableSet);

        actualResult << "Current component:";
        for (VarT var : currentComponentVariableSortedVector)
            actualResult << " " << std::to_string(var);
        actualResult << std::endl
                     << std::endl;
    }

    void printPartvec(const PartvecType& partvec, std::stringstream& actualResult) {
        actualResult << "Partvec:";
        for (int part : partvec)
            actualResult << " " << std::to_string(part);
        actualResult << std::endl
                     << std::endl;
    }

    EquivalencePreprocessingStruct createEquivalencePreprocessingStructure() {
        EquivalencePreprocessingStruct equivalencePreprocessingStructure;
        equivalencePreprocessingStructure.ignoreMultiOccurrentIgnoredVariables = false;

        EquivalencePreprocessingStructureType& equivalence = equivalencePreprocessingStructure.equivalencePreprocessingStructure;

        // x_1 = {x_1, x_2}
        equivalence.push_back({ (VarT)1, (VarT)2 });

        // x_3 = {x_3, x_4}
        equivalence.push_back({ (VarT)3, (VarT)4 });

        // x_10 = {x_10, x_3}
        equivalence.push_back({ (VarT)10, (VarT)3 });

        // x_5 = {x_5, x_3, x_11}
        equivalence.push_back({ (VarT)5, (VarT)3, (VarT)11 });

        // x_7 = {x_7, x_12, x_13}
        equivalence.push_back({ (VarT)7, (VarT)12, (VarT)13 });

        // x_14 = {x_14, x_5, x_15}
        equivalence.push_back({ (VarT)14, (VarT)5, (VarT)15 });

        // x_16 = {x_16, x_1, x_7}
        equivalence.push_back({ (VarT)16, (VarT)1, (VarT)7 });

        // x_17 = {x_17, x_6, x_18}
        equivalence.push_back({ (VarT)17, (VarT)6, (VarT)18 });

        // x_19 = {x_19, x_8, x_17, x_20}
        equivalence.push_back({ (VarT)19, (VarT)8, (VarT)17, (VarT)20 });

        // x_21 = {x_21, x_22, x_23}
        equivalence.push_back({ (VarT)21, (VarT)22, (VarT)23 });

        // x_24 = {x_24, x_2, x_4, x_22}
        equivalence.push_back({ (VarT)24, (VarT)2, (VarT)4, (VarT)22 });

        return equivalencePreprocessingStructure;
    }

    EquivalencePreprocessingStruct createEquivalencePreprocessingStructureForIgnore() {
        EquivalencePreprocessingStruct equivalencePreprocessingStructure;
        equivalencePreprocessingStructure.ignoreMultiOccurrentIgnoredVariables = true;

        EquivalencePreprocessingStructureType& equivalence = equivalencePreprocessingStructure.equivalencePreprocessingStructure;

        // x_1 = {x_1, x_2}
        equivalence.push_back({ (VarT)1, (VarT)2 });

        // x_3 = {x_3, x_4}
        equivalence.push_back({ (VarT)3, (VarT)4 });

        // x_10 = {x_10, x_3}
        equivalence.push_back({ (VarT)10, (VarT)3 });

        // x_5 = {x_5, x_19}
        equivalence.push_back({ (VarT)5, (VarT)19 });

        // x_7 = {x_7, x_20}
        equivalence.push_back({ (VarT)7, (VarT)20 });

        // x_11 = {x_11, x_5}
        equivalence.push_back({ (VarT)11, (VarT)5 });

        // x_12 = {x_12, x_7}
        equivalence.push_back({ (VarT)12, (VarT)7 });

        // x_13 = {x_13, x_14}
        equivalence.push_back({ (VarT)13, (VarT)14 });

        // x_15 = {x_15, x_6, x_13, x_16}
        equivalence.push_back({ (VarT)15, (VarT)6, (VarT)13, (VarT)16 });

        // x_17 = {x_17, x_8, x_15, x_18}
        equivalence.push_back({ (VarT)17, (VarT)8, (VarT)15, (VarT)18 });

        // x_21 = {x_21, x_1, x_23, x_24}
        equivalence.push_back({ (VarT)21, (VarT)1, (VarT)23, (VarT)24 });

        return equivalencePreprocessingStructure;
    }

    EquivalenceStruct createEquivalenceStructureForSingletonHyperedges() {
        EquivalenceStruct equivalenceStruct;

        equivalenceStruct.variableOrderReusableVector = VariableReusableVectorType(5);
        equivalenceStruct.variableOrderReusableVector.copySet({ 1, 2, 4, 5 });

        equivalenceStruct.equivalenceVectorMap = VariableVectorMapType(6, 0);
        equivalenceStruct.equivalenceVectorMap.insert(3, 5);

        equivalenceStruct.equivalenceStructureVector = { { 1 }, { 2 }, { 4 }, { 5, 3 } };

        return equivalenceStruct;
    }
    //endregion

    //region Formulae
    FormulaRepresentationAbstractUniquePtrType createFormula(VariableSetType& variableSet) {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litPos2(2, true);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litNeg4(4, false);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula { litPos1, litPos2, zeroLit,
                              litPos1, litNeg3, zeroLit,
                              litPos2, litPos3, zeroLit,
                              litNeg4, litNeg5, zeroLit,
                              litNeg4, litPos6, zeroLit,
                              litNeg5, litNeg6, zeroLit,
                              litNeg7, litPos8, zeroLit,
                              litPos7, litNeg8, zeroLit,
                              litPos7, litPos8, zeroLit,
                              litPos3, litNeg4, litPos7, zeroLit };

        VarT numberOfVariables = 8;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        // Configuration
        ContagiousFormulaRepresentationConfiguration configuration;
        configuration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences,
                                                                                                                                 configuration);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8 };

        return formulaRepresentation;
    }

    FormulaRepresentationAbstractUniquePtrType createFormulaForSoftware() {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula { litPos1, litPos2, zeroLit,
                              litNeg1, litPos4, zeroLit,
                              litNeg4, zeroLit,
                              litPos3, litPos4, zeroLit,
                              litPos2, litNeg3, zeroLit,
                              litNeg2, litNeg3, zeroLit,
                              litPos2, zeroLit };

        VarT numberOfVariables = 4;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);
        return formulaRepresentation;
    }

    FormulaRepresentationAbstractUniquePtrType createFormulaWithEmptyCut() {
        //region Literals
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litPos3(3, true);
        LiteralType litNeg4(4, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litNeg1, litPos2, zeroLit,   // 0
            litPos3, litNeg4, zeroLit,   // 1
        };

        VarT numberOfVariables = 4;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);
        return formulaRepresentation;
    }

    FormulaRepresentationAbstractUniquePtrType createFormulaWithSingletonHyperedges(VariableSubsumptionWithMappingTypeEnum variableSubsumptionWithMappingType) {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litPos1, zeroLit,           // 0
            litPos1, zeroLit,           // 1
            litNeg2, zeroLit,           // 2
            litPos3, zeroLit,           // 3
            litNeg4, zeroLit,           // 4
            litPos4, litNeg5, zeroLit   // 5
        };

        VarT numberOfVariables = 5;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        // Configuration
        ContagiousFormulaRepresentationConfiguration configuration;
        configuration.variableSubsumptionWithMappingType = variableSubsumptionWithMappingType;

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences,
                                                                                                                                 configuration);
        return formulaRepresentation;
    }

    FormulaRepresentationAbstractUniquePtrType createFormulaForVariableSubsumptionWithMapping(VariableSubsumptionWithMappingTypeEnum variableSubsumptionWithMappingType,
                                                                                              VariableSetType& variableSet) {
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
        LiteralType litPos7(7, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType litPos9(9, true);
        LiteralType litNeg10(10, false);
        LiteralType litPos11(11, true);
        LiteralType litNeg11(11, false);
        LiteralType litPos12(12, true);
        LiteralType litNeg12(12, false);
        LiteralType litPos13(13, true);
        LiteralType litNeg13(13, false);
        LiteralType litPos14(14, true);
        LiteralType litNeg14(14, false);
        LiteralType litPos15(15, true);
        LiteralType litNeg15(15, false);
        LiteralType litPos16(16, true);
        LiteralType litNeg16(16, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litPos1, zeroLit,                              // 0
            litNeg2, zeroLit,                              // 1
            litPos1, litPos11, zeroLit,                    // 2
            litNeg2, litNeg14, zeroLit,                    // 3
            litPos3, litNeg4, zeroLit,                     // 4
            litPos5, litNeg6, zeroLit,                     // 5
            litNeg11, litPos14, zeroLit,                   // 6
            litNeg12, litPos15, zeroLit,                   // 7
            litPos12, litPos13, zeroLit,                   // 8
            litNeg13, litPos16, zeroLit,                   // 9
            litNeg15, litNeg16, zeroLit,                   // 10
            litPos1, litNeg2, litNeg3, litPos4, zeroLit,   // 11
            litNeg5, litPos6, litPos7, litNeg8, zeroLit,   // 12
            litNeg7, litPos8, litPos9, litNeg10, zeroLit   // 13
        };

        VarT numberOfVariables = 16;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        // Configuration
        ContagiousFormulaRepresentationConfiguration configuration;
        configuration.variableSubsumptionWithMappingType = variableSubsumptionWithMappingType;

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences,
                                                                                                                                 configuration);
        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

        return formulaRepresentation;
    }

    FormulaRepresentationAbstractUniquePtrType createFormulaForEquivalenceStructure(VariableSetType& currentComponentVariableSet) {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litPos2(2, true);
        LiteralType litPos3(3, true);
        LiteralType litPos4(4, true);
        LiteralType litPos5(5, true);
        LiteralType litPos6(6, true);
        LiteralType litNeg7(7, false);
        LiteralType litNeg8(8, false);
        LiteralType litPos9(9, true);
        LiteralType litNeg9(9, false);
        LiteralType litPos10(10, true);
        LiteralType litNeg10(10, false);
        LiteralType litPos11(11, true);
        LiteralType litNeg11(11, false);
        LiteralType litPos12(12, true);
        LiteralType litNeg12(12, false);
        LiteralType litPos13(13, true);
        LiteralType litNeg13(13, false);
        LiteralType litPos14(14, true);
        LiteralType litNeg14(14, false);
        LiteralType litPos15(15, true);
        LiteralType litNeg15(15, false);
        LiteralType litPos16(16, true);
        LiteralType litNeg16(16, false);
        LiteralType litPos17(17, true);
        LiteralType litNeg17(17, false);
        LiteralType litPos18(18, true);
        LiteralType litNeg18(18, false);
        LiteralType litPos19(19, true);
        LiteralType litNeg19(19, false);
        LiteralType litPos20(20, true);
        LiteralType litNeg20(20, false);
        LiteralType litPos21(21, true);
        LiteralType litNeg21(21, false);
        LiteralType litPos22(22, true);
        LiteralType litNeg22(22, false);
        LiteralType litPos23(23, true);
        LiteralType litNeg23(23, false);
        LiteralType litPos24(24, true);
        LiteralType litNeg24(24, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litPos1, litPos2, litPos3, litPos4, zeroLit,                                               // 0
            litPos5, litPos6, litNeg7, litNeg8, zeroLit,                                               // 1
            litPos5, litPos6, litNeg7, litNeg8, zeroLit,                                               // 2
            litNeg9, litNeg10, litNeg11, litNeg12, litNeg13, litNeg14, litNeg15, litNeg16, zeroLit,    // 3
            litPos9, litPos10, litPos11, litPos12, litPos13, litPos14, litPos15, litPos16, zeroLit,    // 4
            litNeg17, litNeg18, litNeg19, litNeg20, litNeg21, litNeg22, litNeg23, litNeg24, zeroLit,   // 5
            litPos17, litPos18, litPos19, litPos20, litPos21, litPos22, litPos23, litPos24, zeroLit    // 6
        };

        VarT numberOfVariables = 24;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);

        // Assign x_1, x_2, x_3, x_4
        VariableVectorType freeVariableVector;
        formulaRepresentation->addLiteralVectorToPartialAssignment({ litPos1, litPos2, litPos3, litPos4 }, freeVariableVector);

        currentComponentVariableSet = { 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };

        return formulaRepresentation;
    }

    FormulaRepresentationAbstractUniquePtrType createFormulaForVertexWeight(VariableSubsumptionWithMappingTypeEnum variableSubsumptionWithMappingType,
                                                                            VariableSetType& variableSet) {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg6(6, false);
        LiteralType litNeg7(7, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litNeg1, zeroLit,                     // 0
            litPos2, zeroLit,                     // 1
            litPos1, litNeg2, zeroLit,            // 2
            litPos1, litNeg2, zeroLit,            // 3
            litPos4, litPos5, zeroLit,            // 4
            litPos4, litNeg7, zeroLit,            // 5
            litNeg5, litPos6, zeroLit,            // 6
            litNeg5, litNeg7, zeroLit,            // 7
            litPos5, litNeg6, zeroLit,            // 8
            litNeg1, litPos2, litNeg3, zeroLit,   // 9
            litPos1, litNeg2, litPos3, zeroLit    // 10
        };

        VarT numberOfVariables = 7;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        // Configuration
        ContagiousFormulaRepresentationConfiguration configuration;
        configuration.variableSubsumptionWithMappingType = variableSubsumptionWithMappingType;

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences,
                                                                                                                                 configuration);
        variableSet = { 1, 2, 3, 4, 5, 6, 7 };

        return formulaRepresentation;
    }
    //endregion

    PartitioningHypergraphAbstractUniquePtrType createPartitioningHypergraphAbstract(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                                                                     IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                                                                     VertexWeightTypeEnum vertexWeightType,
                                                                                     bool allowEmptyHypergraphCut = true, bool allowSingletonHyperedge = true,
                                                                                     PartitioningHypergraphTypeEnum partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS) {
        switch (partitioningHypergraphType) {
            // PaToH or hMETIS
            case PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS:
                #if OPERATING_SYSTEM_WINDOWS
                return std::make_unique<HmetisPartitioningHypergraphType>(formulaRepresentationAbstractPtr,
                                                                          allowEmptyHypergraphCut, allowSingletonHyperedge,
                                                                          ignorePureLiteralType, vertexWeightType);
                #elif OPERATING_SYSTEM_MACOS
                return std::make_unique<PatohPartitioningHypergraphType>(formulaRepresentationAbstractPtr,
                                                                         allowEmptyHypergraphCut, allowSingletonHyperedge,
                                                                         ignorePureLiteralType, vertexWeightType);
                #elif OPERATING_SYSTEM_LINUX
                return std::make_unique<PatohPartitioningHypergraphType>(formulaRepresentationAbstractPtr,
                                                                         allowEmptyHypergraphCut, allowSingletonHyperedge,
                                                                         ignorePureLiteralType, vertexWeightType);
                #else
                throw Hydra::Exception::SomethingIsWrongException();
                #endif
            // KaHyPar
            case PartitioningHypergraphTypeEnum::KAHYPAR:
                return std::make_unique<KahyparPartitioningHypergraphType>(formulaRepresentationAbstractPtr,
                                                                           allowEmptyHypergraphCut, allowSingletonHyperedge,
                                                                           ignorePureLiteralType, vertexWeightType);
            default:
                throw Hydra::Exception::SomethingIsWrongException();
        }
    }

    void processVariableSubsumptionWithMapping(VariableSubsumptionWithMappingTypeEnum variableSubsumptionWithMappingType,
                                               IgnorePureLiteralTypeEnum ignorePureLiteralType, std::stringstream& actualResult) {
        VariableSetType variableSet;
        FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaForVariableSubsumptionWithMapping(variableSubsumptionWithMappingType, variableSet);
        printFormula(formulaUniquePtr.get(), actualResult);

        PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                           ignorePureLiteralType,
                                                                                                                           VertexWeightTypeEnum::NONE);

        EquivalenceStruct equivalenceStruct;
        equivalenceStruct.variableOrderReusableVector = VariableReusableVectorType(variableSet.size());
        equivalenceStruct.variableOrderReusableVector.copySet(variableSet);

        equivalenceStruct.equivalenceVectorMap = VariableVectorMapType(formulaUniquePtr->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), 0);
        equivalenceStruct.equivalenceVectorMap.insert((VarT)5, (VarT)7);
        equivalenceStruct.equivalenceVectorMap.insert((VarT)6, (VarT)8);
        equivalenceStruct.equivalenceVectorMap.insert((VarT)11, (VarT)12);
        equivalenceStruct.equivalenceVectorMap.insert((VarT)14, (VarT)15);

        equivalenceStruct.equivalenceStructureVector = EquivalenceStructureVectorType(equivalenceStruct.variableOrderReusableVector.size(), VariableVectorType());

        // Equivalence structure
        for (VarT i = 0; i < equivalenceStruct.variableOrderReusableVector.size(); ++i)
            equivalenceStruct.equivalenceStructureVector[i].emplace_back(equivalenceStruct.variableOrderReusableVector[i]);

        // x_7 = {x_5}
        equivalenceStruct.equivalenceStructureVector[7 - 1].emplace_back(5);

        // x_8 = {x_6}
        equivalenceStruct.equivalenceStructureVector[8 - 1].emplace_back(6);

        // x_12 = {x_11}
        equivalenceStruct.equivalenceStructureVector[12 - 1].emplace_back(11);

        // x_15 = {x_14}
        equivalenceStruct.equivalenceStructureVector[15 - 1].emplace_back(14);

        printEquivalenceStructure(equivalenceStruct, actualResult);

        partitioningHypergraphUniquePtr->createOccurrenceListStruct(equivalenceStruct.variableOrderReusableVector, variableSet,
                                                                    equivalenceStruct.equivalenceVectorMap, equivalenceStruct.equivalenceStructureVector);

        printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);
    }

    void processVariableSubsumptionVertexWeight(VariableSubsumptionWithMappingTypeEnum variableSubsumptionWithMappingType,
                                                IgnorePureLiteralTypeEnum ignorePureLiteralType, VertexWeightTypeEnum vertexWeightType,
                                                std::stringstream& actualResult) {
        VariableSetType variableSet;
        FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaForVertexWeight(variableSubsumptionWithMappingType, variableSet);
        printFormula(formulaUniquePtr.get(), actualResult);

        PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                           ignorePureLiteralType,
                                                                                                                           vertexWeightType);

        VariableReusableVectorType variableOrderReusableVector = VariableReusableVectorType(variableSet.size());
        variableOrderReusableVector.copySet(variableSet);

        partitioningHypergraphUniquePtr->createOccurrenceListStruct(variableOrderReusableVector, variableSet);

        printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);
        partitioningHypergraphUniquePtr->printVertexWeightVectorDebug(actualResult);
    }

    void processVariableSubsumptionVertexWeightSelectedVariables(VariableSubsumptionWithMappingTypeEnum variableSubsumptionWithMappingType,
                                                                 IgnorePureLiteralTypeEnum ignorePureLiteralType, VertexWeightTypeEnum vertexWeightType,
                                                                 std::stringstream& actualResult, bool printAllVertexWeightVector = true) {
        VariableSetType variableSet;
        FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaForVertexWeight(variableSubsumptionWithMappingType, variableSet);
        printFormula(formulaUniquePtr.get(), actualResult);

        VariableReusableVectorType variableOrderReusableVector = VariableReusableVectorType(variableSet.size());

        PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                           ignorePureLiteralType,
                                                                                                                           vertexWeightType);

        std::vector<VariableSetType> currentComponentVector { { 1, 2, 3 }, { 4, 5, 6, 7 }, { 1, 2, 3, 4, 5, 6, 7 } };

        for (const VariableSetType& currentComponent : currentComponentVector) {
            printCurrentComponent(currentComponent, actualResult);

            ConnectedComponentStruct connectedComponentStructure(currentComponent.size());
            connectedComponentStructure.variableSet.insert(currentComponent.cbegin(), currentComponent.cend());

            formulaUniquePtr->setNewComponent(connectedComponentStructure, ignorePureLiteralType);

            try {
                variableOrderReusableVector.copySet(currentComponent);
                partitioningHypergraphUniquePtr->createOccurrenceListStruct(variableOrderReusableVector, currentComponent);

                printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);

                if (printAllVertexWeightVector)
                    partitioningHypergraphUniquePtr->printVertexWeightVectorDebug(actualResult);
                else {
                    actualResult << "Vertex weights:";
                    for (VertexWeightType weight : partitioningHypergraphUniquePtr->createVertexWeightVector(partitioningHypergraphUniquePtr->getOccurrenceListStruct()))
                        actualResult << " " << std::to_string(weight);
                    actualResult << std::endl;
                }
            }
            catch (const std::exception& e) {
                actualResult << e.what() << std::endl;
            }

            formulaUniquePtr->popPreviousComponent(connectedComponentStructure, {});

            actualResult << std::endl;
        }
    }

    /**
     * Occurrence list
     */
    TEST_CASE("[PartitioningHypergraph] occurrence list", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphOccurrenceListResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormula(variableSet);
            printFormula(formulaUniquePtr.get(), actualResult);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            VariableReusableVectorType variableOrderReusableVector = VariableReusableVectorType(variableSet.size());
            variableOrderReusableVector.copySet(variableSet);
            partitioningHypergraphUniquePtr->createOccurrenceListStruct(variableOrderReusableVector, variableSet);

            printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);
            printFromClauseIdToIndexVectorMap(partitioningHypergraphUniquePtr->getOccurrenceListStruct().fromClauseIdToIndexVectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Occurrence list (current component)
     */
    TEST_CASE("[PartitioningHypergraph] occurrence list (current component)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphOccurrenceListCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormula(variableSet);
            printFormula(formulaUniquePtr.get(), actualResult);

            VariableReusableVectorType variableOrderReusableVector = VariableReusableVectorType(variableSet.size());

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            std::vector<VariableSetType> currentComponentVector { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8 }, { 1, 2, 3, 7, 8 }, { 4, 5, 6, 7, 8 } };

            for (const VariableSetType& currentComponent : currentComponentVector) {
                printCurrentComponent(currentComponent, actualResult);

                ConnectedComponentStruct connectedComponentStructure(currentComponent.size());
                connectedComponentStructure.variableSet.insert(currentComponent.cbegin(), currentComponent.cend());

                formulaUniquePtr->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);

                try {
                    variableOrderReusableVector.copySet(currentComponent);
                    partitioningHypergraphUniquePtr->createOccurrenceListStruct(variableOrderReusableVector, currentComponent);

                    printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);
                    printFromClauseIdToIndexVectorMap(partitioningHypergraphUniquePtr->getOccurrenceListStruct().fromClauseIdToIndexVectorMap, actualResult);
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                formulaUniquePtr->popPreviousComponent(connectedComponentStructure, {});
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    #if defined(BELLA_COMPILER)
    /**
     * Occurrence list (ignore positive pure literals)
     */
    TEST_CASE("[PartitioningHypergraph] occurrence list (ignore positive pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphOccurrenceListIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormula(variableSet);
            printFormula(formulaUniquePtr.get(), actualResult);

            VariableReusableVectorType variableOrderReusableVector = VariableReusableVectorType(variableSet.size());

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::ONLY_POSITIVE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            std::vector<VariableSetType> currentComponentVector { { 1, 2, 3, 4, 5, 6, 7, 8 },
                                                                  { 1, 2, 3 },
                                                                  { 4, 5, 6 },
                                                                  { 7, 8 } };

            for (const VariableSetType& currentComponent : currentComponentVector) {
                printCurrentComponent(currentComponent, actualResult);

                ConnectedComponentStruct connectedComponentStructure(currentComponent.size());
                connectedComponentStructure.variableSet.insert(currentComponent.cbegin(), currentComponent.cend());

                formulaUniquePtr->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);

                try {
                    variableOrderReusableVector.copySet(currentComponent);
                    partitioningHypergraphUniquePtr->createOccurrenceListStruct(variableOrderReusableVector, currentComponent);

                    printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);
                    printFromClauseIdToIndexVectorMap(partitioningHypergraphUniquePtr->getOccurrenceListStruct().fromClauseIdToIndexVectorMap, actualResult);
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                formulaUniquePtr->popPreviousComponent(connectedComponentStructure, {});
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Occurrence list (ignore negative pure literals)
     */
    TEST_CASE("[PartitioningHypergraph] occurrence list (ignore negative pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphOccurrenceListIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormula(variableSet);
            printFormula(formulaUniquePtr.get(), actualResult);

            VariableReusableVectorType variableOrderReusableVector = VariableReusableVectorType(variableSet.size());

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::ONLY_NEGATIVE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            std::vector<VariableSetType> currentComponentVector { { 1, 2, 3, 4, 5, 6, 7, 8 },
                                                                  { 1, 2, 3 },
                                                                  { 4, 5, 6 },
                                                                  { 7, 8 } };

            for (const VariableSetType& currentComponent : currentComponentVector) {
                printCurrentComponent(currentComponent, actualResult);

                ConnectedComponentStruct connectedComponentStructure(currentComponent.size());
                connectedComponentStructure.variableSet.insert(currentComponent.cbegin(), currentComponent.cend());

                formulaUniquePtr->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);

                try {
                    variableOrderReusableVector.copySet(currentComponent);
                    partitioningHypergraphUniquePtr->createOccurrenceListStruct(variableOrderReusableVector, currentComponent);

                    printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);
                    printFromClauseIdToIndexVectorMap(partitioningHypergraphUniquePtr->getOccurrenceListStruct().fromClauseIdToIndexVectorMap, actualResult);
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                formulaUniquePtr->popPreviousComponent(connectedComponentStructure, {});
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Occurrence list (ignore pure literals)
     */
    TEST_CASE("[PartitioningHypergraph] occurrence list (ignore pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphOccurrenceListIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormula(variableSet);
            printFormula(formulaUniquePtr.get(), actualResult);

            VariableReusableVectorType variableOrderReusableVector = VariableReusableVectorType(variableSet.size());

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            std::vector<VariableSetType> currentComponentVector { { 1, 2, 3, 4, 5, 6, 7, 8 },
                                                                  { 1, 2, 3 },
                                                                  { 4, 5, 6 },
                                                                  { 7, 8 } };

            for (const VariableSetType& currentComponent : currentComponentVector) {
                printCurrentComponent(currentComponent, actualResult);

                ConnectedComponentStruct connectedComponentStructure(currentComponent.size());
                connectedComponentStructure.variableSet.insert(currentComponent.cbegin(), currentComponent.cend());

                formulaUniquePtr->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);

                try {
                    variableOrderReusableVector.copySet(currentComponent);
                    partitioningHypergraphUniquePtr->createOccurrenceListStruct(variableOrderReusableVector, currentComponent);

                    printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);
                    printFromClauseIdToIndexVectorMap(partitioningHypergraphUniquePtr->getOccurrenceListStruct().fromClauseIdToIndexVectorMap, actualResult);
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                formulaUniquePtr->popPreviousComponent(connectedComponentStructure, {});
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif

    /**
     * Occurrence list (equivalence structure)
     */
    TEST_CASE("[PartitioningHypergraph] occurrence list (equivalence structure)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphOccurrenceListEquivalenceStructureResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormula(variableSet);
            printFormula(formulaUniquePtr.get(), actualResult);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            EquivalenceStruct equivalenceStruct;
            equivalenceStruct.variableOrderReusableVector = VariableReusableVectorType(variableSet.size());
            equivalenceStruct.variableOrderReusableVector.copySet(variableSet);

            equivalenceStruct.equivalenceVectorMap = VariableVectorMapType(formulaUniquePtr->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), 0);
            equivalenceStruct.equivalenceVectorMap.insert((VarT)4, (VarT)2);
            equivalenceStruct.equivalenceVectorMap.insert((VarT)6, (VarT)2);
            equivalenceStruct.equivalenceVectorMap.insert((VarT)8, (VarT)2);
            equivalenceStruct.equivalenceVectorMap.insert((VarT)1, (VarT)7);
            equivalenceStruct.equivalenceVectorMap.insert((VarT)5, (VarT)7);

            equivalenceStruct.equivalenceStructureVector = EquivalenceStructureVectorType(equivalenceStruct.variableOrderReusableVector.size(), VariableVectorType());

            // Equivalence structure
            for (VarT i = 0; i < equivalenceStruct.variableOrderReusableVector.size(); ++i)
                equivalenceStruct.equivalenceStructureVector[i].emplace_back(equivalenceStruct.variableOrderReusableVector[i]);

            // x_2 = {x_4, x_6, x_8}
            equivalenceStruct.equivalenceStructureVector[2 - 1].emplace_back(4);
            equivalenceStruct.equivalenceStructureVector[2 - 1].emplace_back(6);
            equivalenceStruct.equivalenceStructureVector[2 - 1].emplace_back(8);

            // x_4 = {x_6}
            equivalenceStruct.equivalenceStructureVector[4 - 1].emplace_back(6);

            // x_7 = {x_1, x_5}
            equivalenceStruct.equivalenceStructureVector[7 - 1].emplace_back(1);
            equivalenceStruct.equivalenceStructureVector[7 - 1].emplace_back(5);

            printEquivalenceStructure(equivalenceStruct, actualResult);

            partitioningHypergraphUniquePtr->createOccurrenceListStruct(equivalenceStruct.variableOrderReusableVector, variableSet,
                                                                        equivalenceStruct.equivalenceVectorMap, equivalenceStruct.equivalenceStructureVector);

            printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);
            printFromClauseIdToIndexVectorMap(partitioningHypergraphUniquePtr->getOccurrenceListStruct().fromClauseIdToIndexVectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Xpins and pins
     */
    TEST_CASE("[PartitioningHypergraph] xpins and pins", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphXpinsAndPinsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormula(variableSet);
            printFormula(formulaUniquePtr.get(), actualResult);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            VariableReusableVectorType variableOrderReusableVector = VariableReusableVectorType(variableSet.size());
            variableOrderReusableVector.copySet(variableSet);

            partitioningHypergraphUniquePtr->createOccurrenceListStruct(variableOrderReusableVector, variableSet);
            printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);

            PinVectorType pins;
            XpinVectorType xpins;

            partitioningHypergraphUniquePtr->fillXpinsAndPins(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), xpins, pins);
            printXpinsAndPins(xpins, pins, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Extract cut
     */
    TEST_CASE("[PartitioningHypergraph] extract cut", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphExtractCutResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormula(variableSet);
            printFormula(formulaUniquePtr.get(), actualResult);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            VariableReusableVectorType variableOrderReusableVector = VariableReusableVectorType(variableSet.size());
            variableOrderReusableVector.copySet(variableSet);

            partitioningHypergraphUniquePtr->createOccurrenceListStruct(variableOrderReusableVector, variableSet);
            printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);

            std::vector<ClauseIdSetType> firstPartSetVector { {}, { 3, 4, 9 }, { 3, 4, 5, 9 } };

            for (const ClauseIdSetType& firstPartSet : firstPartSetVector) {
                PartvecType partvec(partitioningHypergraphUniquePtr->getOccurrenceListStruct().numberOfDifferentClausesInOccurrenceList, 0);
                for (ClauseIdT clauseId : firstPartSet)
                    partvec[partitioningHypergraphUniquePtr->getOccurrenceListStruct().fromClauseIdToIndexVectorMap[clauseId]] = 1;

                printPartvec(partvec, actualResult);

                VariableSetType cut = partitioningHypergraphUniquePtr->extractCut(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), partvec);
                printCut(cut, actualResult);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Software (PaToH, hMETIS)
     */
    TEST_CASE("[PartitioningHypergraph] software (PaToH, hMETIS)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphSoftwareResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaForSoftware();
            printFormula(formulaUniquePtr.get(), actualResult);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            VariableSetType cut = partitioningHypergraphUniquePtr->computeCut({ 1, 2, 3, 4 });
            actualResult << "Cut (size): " << std::to_string(cut.size()) << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Software (KaHyPar)
     */
    TEST_CASE("[PartitioningHypergraph] software (KaHyPar)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphSoftwareResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaForSoftware();
            printFormula(formulaUniquePtr.get(), actualResult);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE,
                                                                                                                               true, false,
                                                                                                                               PartitioningHypergraphTypeEnum::KAHYPAR);

            VariableSetType cut = partitioningHypergraphUniquePtr->computeCut({ 1, 2, 3, 4 });
            actualResult << "Cut (size): " << std::to_string(cut.size()) << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Empty cut (allow)
     */
    TEST_CASE("[PartitioningHypergraph] empty cut (allow)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphAllowEmptyCutResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaWithEmptyCut();
            printFormula(formulaUniquePtr.get(), actualResult);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE,
                                                                                                                               true);

            bool validCut = true;
            VariableSetType cut = partitioningHypergraphUniquePtr->computeCut({ 1, 2, 3, 4 }, validCut);
            actualResult << "Cut (size): " << std::to_string(cut.size()) << std::endl;
            actualResult << "Valid cut: " << std::to_string(validCut) << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Empty cut (deny)
     */
    TEST_CASE("[PartitioningHypergraph] empty cut (deny)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphDenyEmptyCutResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaWithEmptyCut();
            printFormula(formulaUniquePtr.get(), actualResult);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE,
                                                                                                                               false);

            bool validCut = true;
            VariableSetType cut = partitioningHypergraphUniquePtr->computeCut({ 1, 2, 3, 4 }, validCut);
            actualResult << "Cut (size): " << std::to_string(cut.size()) << std::endl;
            actualResult << "Valid cut: " << std::to_string(validCut) << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Singleton hyperedge (allow)
     */
    TEST_CASE("[PartitioningHypergraph] singleton hyperedge (allow)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphAllowSingletonHyperedgeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaWithSingletonHyperedges(VariableSubsumptionWithMappingTypeEnum::NONE);
            printFormula(formulaUniquePtr.get(), actualResult);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE,
                                                                                                                               true, true);

            VariableSetType currentComponentVariableSet { 1, 2, 3, 4, 5 };
            VariableReusableVectorType variableOrderReusableVector = VariableReusableVectorType(currentComponentVariableSet.size());
            variableOrderReusableVector.copySet(currentComponentVariableSet);

            partitioningHypergraphUniquePtr->createOccurrenceListStruct(variableOrderReusableVector, currentComponentVariableSet);
            printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Singleton hyperedge (deny)
     */
    TEST_CASE("[PartitioningHypergraph] singleton hyperedge (deny)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphDenySingletonHyperedgeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaWithSingletonHyperedges(VariableSubsumptionWithMappingTypeEnum::NONE);
            printFormula(formulaUniquePtr.get(), actualResult);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE,
                                                                                                                               true, false);

            VariableSetType currentComponentVariableSet { 1, 2, 3, 4, 5 };
            VariableReusableVectorType variableOrderReusableVector = VariableReusableVectorType(currentComponentVariableSet.size());
            variableOrderReusableVector.copySet(currentComponentVariableSet);

            partitioningHypergraphUniquePtr->createOccurrenceListStruct(variableOrderReusableVector, currentComponentVariableSet);
            printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Singleton hyperedge (allow, variable subsumption)
     */
    TEST_CASE("[PartitioningHypergraph] singleton hyperedge (allow, variable subsumption)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphAllowSingletonHyperedgeVariableSubsumptionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaWithSingletonHyperedges(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING);
            printFormula(formulaUniquePtr.get(), actualResult);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE,
                                                                                                                               true, true);

            VariableSetType currentComponentVariableSet { 1, 2, 3, 4, 5 };
            VariableReusableVectorType variableOrderReusableVector = VariableReusableVectorType(currentComponentVariableSet.size());
            variableOrderReusableVector.copySet(currentComponentVariableSet);

            partitioningHypergraphUniquePtr->createOccurrenceListStruct(variableOrderReusableVector, currentComponentVariableSet);
            printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Singleton hyperedge (deny, variable subsumption)
     */
    TEST_CASE("[PartitioningHypergraph] singleton hyperedge (deny, variable subsumption)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphDenySingletonHyperedgeVariableSubsumptionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaWithSingletonHyperedges(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING);
            printFormula(formulaUniquePtr.get(), actualResult);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE,
                                                                                                                               true, false);

            VariableSetType currentComponentVariableSet { 1, 2, 3, 4, 5 };
            VariableReusableVectorType variableOrderReusableVector = VariableReusableVectorType(currentComponentVariableSet.size());
            variableOrderReusableVector.copySet(currentComponentVariableSet);

            partitioningHypergraphUniquePtr->createOccurrenceListStruct(variableOrderReusableVector, currentComponentVariableSet);
            printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Singleton hyperedge (allow, equivalence simplification method)
     */
    TEST_CASE("[PartitioningHypergraph] singleton hyperedge (allow, equivalence simplification method)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphAllowSingletonHyperedgeEquivalenceSimplificationMethodResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaWithSingletonHyperedges(VariableSubsumptionWithMappingTypeEnum::NONE);
            printFormula(formulaUniquePtr.get(), actualResult);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE,
                                                                                                                               true, true);

            VariableSetType currentComponentVariableSet { 1, 2, 3, 4, 5 };
            EquivalenceStruct equivalenceStruct = createEquivalenceStructureForSingletonHyperedges();

            partitioningHypergraphUniquePtr->createOccurrenceListStruct(equivalenceStruct.variableOrderReusableVector, currentComponentVariableSet,
                                                                        equivalenceStruct.equivalenceVectorMap, equivalenceStruct.equivalenceStructureVector);
            printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Singleton hyperedge (deny, equivalence simplification method)
     */
    TEST_CASE("[PartitioningHypergraph] singleton hyperedge (deny, equivalence simplification method)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphDenySingletonHyperedgeEquivalenceSimplificationMethodResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaWithSingletonHyperedges(VariableSubsumptionWithMappingTypeEnum::NONE);
            printFormula(formulaUniquePtr.get(), actualResult);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE,
                                                                                                                               true, false);

            VariableSetType currentComponentVariableSet { 1, 2, 3, 4, 5 };
            EquivalenceStruct equivalenceStruct = createEquivalenceStructureForSingletonHyperedges();

            partitioningHypergraphUniquePtr->createOccurrenceListStruct(equivalenceStruct.variableOrderReusableVector, currentComponentVariableSet,
                                                                        equivalenceStruct.equivalenceVectorMap, equivalenceStruct.equivalenceStructureVector);
            printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Singleton hyperedge (allow, equivalence simplification method, variable subsumption)
     */
    TEST_CASE("[PartitioningHypergraph] singleton hyperedge (allow, equivalence simplification method, variable subsumption)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphAllowSingletonHyperedgeEquivalenceSimplificationMethodVariableSubsumptionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaWithSingletonHyperedges(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING);
            printFormula(formulaUniquePtr.get(), actualResult);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE,
                                                                                                                               true, true);

            VariableSetType currentComponentVariableSet { 1, 2, 3, 4, 5 };
            EquivalenceStruct equivalenceStruct = createEquivalenceStructureForSingletonHyperedges();

            partitioningHypergraphUniquePtr->createOccurrenceListStruct(equivalenceStruct.variableOrderReusableVector, currentComponentVariableSet,
                                                                        equivalenceStruct.equivalenceVectorMap, equivalenceStruct.equivalenceStructureVector);
            printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Singleton hyperedge (deny, equivalence simplification method, variable subsumption)
     */
    TEST_CASE("[PartitioningHypergraph] singleton hyperedge (deny, equivalence simplification method, variable subsumption)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphDenySingletonHyperedgeEquivalenceSimplificationMethodVariableSubsumptionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaWithSingletonHyperedges(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING);
            printFormula(formulaUniquePtr.get(), actualResult);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE,
                                                                                                                               true, false);

            VariableSetType currentComponentVariableSet { 1, 2, 3, 4, 5 };
            EquivalenceStruct equivalenceStruct = createEquivalenceStructureForSingletonHyperedges();

            partitioningHypergraphUniquePtr->createOccurrenceListStruct(equivalenceStruct.variableOrderReusableVector, currentComponentVariableSet,
                                                                        equivalenceStruct.equivalenceVectorMap, equivalenceStruct.equivalenceStructureVector);
            printOccurrenceList(partitioningHypergraphUniquePtr->getOccurrenceListStruct(), actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Vertex weight (none)
     */
    TEST_CASE("[PartitioningHypergraph] vertex weight (none)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVertexWeightNoneResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeightSelectedVariables(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING,
                                                                    IgnorePureLiteralTypeEnum::NONE,
                                                                    VertexWeightTypeEnum::NONE,
                                                                    actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Vertex weight (standard)
     */
    TEST_CASE("[PartitioningHypergraph] vertex weight (standard)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVertexWeightStandardResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeightSelectedVariables(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING,
                                                                    IgnorePureLiteralTypeEnum::NONE,
                                                                    VertexWeightTypeEnum::STANDARD,
                                                                    actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Vertex weight (clause length)
     */
    TEST_CASE("[PartitioningHypergraph] vertex weight (clause length)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVertexWeightClauseLengthResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeightSelectedVariables(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING,
                                                                    IgnorePureLiteralTypeEnum::NONE,
                                                                    VertexWeightTypeEnum::CLAUSE_LENGTH,
                                                                    actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption with mapping detection
     */
    TEST_CASE("[PartitioningHypergraph] forward variable subsumption with mapping detection", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionWithMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionWithMapping(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION,
                                                  IgnorePureLiteralTypeEnum::NONE,
                                                  actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption
     *      vertex weight: standard
     */
    TEST_CASE("[PartitioningHypergraph] forward variable subsumption (vertex weight: standard)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionVertexWeightStandardResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeight(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION,
                                                   IgnorePureLiteralTypeEnum::NONE,
                                                   VertexWeightTypeEnum::STANDARD,
                                                   actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption
     *      vertex weight: clause length
     */
    TEST_CASE("[PartitioningHypergraph] forward variable subsumption (vertex weight: clause length)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionVertexWeightClauseLengthResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeight(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION,
                                                   IgnorePureLiteralTypeEnum::NONE,
                                                   VertexWeightTypeEnum::CLAUSE_LENGTH,
                                                   actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption (selected variables)
     *      vertex weight: standard
     */
    TEST_CASE("[PartitioningHypergraph] forward variable subsumption (vertex weight: standard) (selected variables)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionVertexWeightStandardSelectedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeightSelectedVariables(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION,
                                                                    IgnorePureLiteralTypeEnum::NONE,
                                                                    VertexWeightTypeEnum::STANDARD,
                                                                    actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption (selected variables)
     *      vertex weight: clause length
     */
    TEST_CASE("[PartitioningHypergraph] forward variable subsumption (vertex weight: clause length) (selected variables)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionVertexWeightClauseLengthSelectedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeightSelectedVariables(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION,
                                                                    IgnorePureLiteralTypeEnum::NONE,
                                                                    VertexWeightTypeEnum::CLAUSE_LENGTH,
                                                                    actualResult);
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
    TEST_CASE("[PartitioningHypergraph] forward variable subsumption with mapping detection (ignore positive pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionWithMappingIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionWithMapping(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION,
                                                  IgnorePureLiteralTypeEnum::ONLY_POSITIVE,
                                                  actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption
     *      vertex weight: standard
     *      ignore positive pure literals
     */
    TEST_CASE("[PartitioningHypergraph] forward variable subsumption (vertex weight: standard, ignore positive pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionIgnorePositivePureLiteralsVertexWeightStandardResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeight(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION,
                                                   IgnorePureLiteralTypeEnum::ONLY_POSITIVE,
                                                   VertexWeightTypeEnum::STANDARD,
                                                   actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption
     *      vertex weight: clause length
     *      ignore positive pure literals
     */
    TEST_CASE("[PartitioningHypergraph] forward variable subsumption (vertex weight: clause length, ignore positive pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionIgnorePositivePureLiteralsVertexWeightClauseLengthResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeight(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION,
                                                   IgnorePureLiteralTypeEnum::ONLY_POSITIVE,
                                                   VertexWeightTypeEnum::CLAUSE_LENGTH,
                                                   actualResult);
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
    TEST_CASE("[PartitioningHypergraph] forward variable subsumption with mapping detection (ignore negative pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionWithMappingIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionWithMapping(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION,
                                                  IgnorePureLiteralTypeEnum::ONLY_NEGATIVE,
                                                  actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption
     *      vertex weight: standard
     *      ignore negative pure literals
     */
    TEST_CASE("[PartitioningHypergraph] forward variable subsumption (vertex weight: standard, ignore negative pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionIgnoreNegativePureLiteralsVertexWeightStandardResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeight(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION,
                                                   IgnorePureLiteralTypeEnum::ONLY_NEGATIVE,
                                                   VertexWeightTypeEnum::STANDARD,
                                                   actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption
     *      vertex weight: clause length
     *      ignore negative pure literals
     */
    TEST_CASE("[PartitioningHypergraph] forward variable subsumption (vertex weight: clause length, ignore negative pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionIgnoreNegativePureLiteralsVertexWeightClauseLengthResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeight(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION,
                                                   IgnorePureLiteralTypeEnum::ONLY_NEGATIVE,
                                                   VertexWeightTypeEnum::CLAUSE_LENGTH,
                                                   actualResult);
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
    TEST_CASE("[PartitioningHypergraph] forward variable subsumption with mapping detection (ignore pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionWithMappingIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionWithMapping(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION,
                                                  IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE,
                                                  actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption
     *      vertex weight: standard
     *      ignore pure literals
     */
    TEST_CASE("[PartitioningHypergraph] forward variable subsumption (vertex weight: standard, ignore pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionIgnorePureLiteralsVertexWeightStandardResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeight(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION,
                                                   IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE,
                                                   VertexWeightTypeEnum::STANDARD,
                                                   actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption
     *      vertex weight: clause length
     *      ignore pure literals
     */
    TEST_CASE("[PartitioningHypergraph] forward variable subsumption (vertex weight: clause length, ignore pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionIgnorePureLiteralsVertexWeightClauseLengthResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeight(VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION,
                                                   IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE,
                                                   VertexWeightTypeEnum::CLAUSE_LENGTH,
                                                   actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif

    /**
     * One-literal watching algorithm with mapping
     */
    TEST_CASE("[PartitioningHypergraph] one-literal watching algorithm with mapping", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionWithMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionWithMapping(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING,
                                                  IgnorePureLiteralTypeEnum::NONE,
                                                  actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm
     *      vertex weight: standard
     */
    TEST_CASE("[PartitioningHypergraph] one-literal watching algorithm (vertex weight: standard)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionVertexWeightStandardResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeight(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING,
                                                   IgnorePureLiteralTypeEnum::NONE,
                                                   VertexWeightTypeEnum::STANDARD,
                                                   actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm (selected variables)
     *      vertex weight: standard
     */
    TEST_CASE("[PartitioningHypergraph] one-literal watching algorithm (vertex weight: standard) (selected variables)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionVertexWeightStandardSelectedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeightSelectedVariables(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING,
                                                                    IgnorePureLiteralTypeEnum::NONE,
                                                                    VertexWeightTypeEnum::STANDARD,
                                                                    actualResult);
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
    TEST_CASE("[PartitioningHypergraph] one-literal watching algorithm with mapping (ignore positive pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionWithMappingIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionWithMapping(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING,
                                                  IgnorePureLiteralTypeEnum::ONLY_POSITIVE,
                                                  actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm
     *      vertex weight: standard
     *      ignore positive pure literals
     */
    TEST_CASE("[PartitioningHypergraph] one-literal watching algorithm (vertex weight: standard, ignore positive pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionIgnorePositivePureLiteralsVertexWeightStandardResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeight(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING,
                                                   IgnorePureLiteralTypeEnum::ONLY_POSITIVE,
                                                   VertexWeightTypeEnum::STANDARD,
                                                   actualResult);
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
    TEST_CASE("[PartitioningHypergraph] one-literal watching algorithm with mapping (ignore negative pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionWithMappingIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionWithMapping(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING,
                                                  IgnorePureLiteralTypeEnum::ONLY_NEGATIVE,
                                                  actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm
     *      vertex weight: standard
     *      ignore negative pure literals
     */
    TEST_CASE("[PartitioningHypergraph] one-literal watching algorithm (vertex weight: standard, ignore negative pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionIgnoreNegativePureLiteralsVertexWeightStandardResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeight(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING,
                                                   IgnorePureLiteralTypeEnum::ONLY_NEGATIVE,
                                                   VertexWeightTypeEnum::STANDARD,
                                                   actualResult);
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
    TEST_CASE("[PartitioningHypergraph] one-literal watching algorithm with mapping (ignore pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionWithMappingIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionWithMapping(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING,
                                                  IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE,
                                                  actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm
     *      vertex weight: standard
     *      ignore pure literals
     */
    TEST_CASE("[PartitioningHypergraph] one-literal watching algorithm (vertex weight: standard, ignore pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphVariableSubsumptionIgnorePureLiteralsVertexWeightStandardResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            processVariableSubsumptionVertexWeight(VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING,
                                                   IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE,
                                                   VertexWeightTypeEnum::STANDARD,
                                                   actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif

    /**
     * Equivalence structure (ignore)
     */
    TEST_CASE("[PartitioningHypergraph] equivalence structure (ignore)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphEquivalenceStructureIgnoreResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaForEquivalenceStructure(currentComponentVariableSet);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            EquivalencePreprocessingStruct equivalencePreprocessingStructure = createEquivalencePreprocessingStructureForIgnore();
            printEquivalencePreprocessingStructure(equivalencePreprocessingStructure, actualResult);

            partitioningHypergraphUniquePtr->createEquivalenceStruct(currentComponentVariableSet, equivalencePreprocessingStructure);
            printEquivalenceStructure(partitioningHypergraphUniquePtr->getEquivalenceVectorMap(),
                                      partitioningHypergraphUniquePtr->getVariableOrderReusableVector(),
                                      partitioningHypergraphUniquePtr->getEquivalenceStructureVector(),
                                      actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    #if defined(BELLA_COMPILER)
    /**
     * Equivalence structure (ignore, ignore positive pure literals)
     */
    TEST_CASE("[PartitioningHypergraph] equivalence structure (ignore, ignore positive pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphEquivalenceStructureIgnoreIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaForEquivalenceStructure(currentComponentVariableSet);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::ONLY_POSITIVE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            EquivalencePreprocessingStruct equivalencePreprocessingStructure = createEquivalencePreprocessingStructureForIgnore();
            printEquivalencePreprocessingStructure(equivalencePreprocessingStructure, actualResult);

            partitioningHypergraphUniquePtr->createEquivalenceStruct(currentComponentVariableSet, equivalencePreprocessingStructure);
            printEquivalenceStructure(partitioningHypergraphUniquePtr->getEquivalenceVectorMap(),
                                      partitioningHypergraphUniquePtr->getVariableOrderReusableVector(),
                                      partitioningHypergraphUniquePtr->getEquivalenceStructureVector(),
                                      actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Equivalence structure (ignore, ignore negative pure literals)
     */
    TEST_CASE("[PartitioningHypergraph] equivalence structure (ignore, ignore negative pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphEquivalenceStructureIgnoreIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaForEquivalenceStructure(currentComponentVariableSet);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::ONLY_NEGATIVE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            EquivalencePreprocessingStruct equivalencePreprocessingStructure = createEquivalencePreprocessingStructureForIgnore();
            printEquivalencePreprocessingStructure(equivalencePreprocessingStructure, actualResult);

            partitioningHypergraphUniquePtr->createEquivalenceStruct(currentComponentVariableSet, equivalencePreprocessingStructure);
            printEquivalenceStructure(partitioningHypergraphUniquePtr->getEquivalenceVectorMap(),
                                      partitioningHypergraphUniquePtr->getVariableOrderReusableVector(),
                                      partitioningHypergraphUniquePtr->getEquivalenceStructureVector(),
                                      actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Equivalence structure (ignore, ignore pure literals)
     */
    TEST_CASE("[PartitioningHypergraph] equivalence structure (ignore, ignore pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphEquivalenceStructureIgnoreIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaForEquivalenceStructure(currentComponentVariableSet);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            EquivalencePreprocessingStruct equivalencePreprocessingStructure = createEquivalencePreprocessingStructureForIgnore();
            printEquivalencePreprocessingStructure(equivalencePreprocessingStructure, actualResult);

            partitioningHypergraphUniquePtr->createEquivalenceStruct(currentComponentVariableSet, equivalencePreprocessingStructure);
            printEquivalenceStructure(partitioningHypergraphUniquePtr->getEquivalenceVectorMap(),
                                      partitioningHypergraphUniquePtr->getVariableOrderReusableVector(),
                                      partitioningHypergraphUniquePtr->getEquivalenceStructureVector(),
                                      actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif

    /**
     * Equivalence structure
     */
    TEST_CASE("[PartitioningHypergraph] equivalence structure", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphEquivalenceStructureResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaForEquivalenceStructure(currentComponentVariableSet);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::NONE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            EquivalencePreprocessingStruct equivalencePreprocessingStructure = createEquivalencePreprocessingStructure();
            printEquivalencePreprocessingStructure(equivalencePreprocessingStructure, actualResult);

            partitioningHypergraphUniquePtr->createEquivalenceStruct(currentComponentVariableSet, equivalencePreprocessingStructure);
            printEquivalenceStructure(partitioningHypergraphUniquePtr->getEquivalenceVectorMap(),
                                      partitioningHypergraphUniquePtr->getVariableOrderReusableVector(),
                                      partitioningHypergraphUniquePtr->getEquivalenceStructureVector(),
                                      actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    #if defined(BELLA_COMPILER)
    /**
     * Equivalence structure (ignore positive pure literals)
     */
    TEST_CASE("[PartitioningHypergraph] equivalence structure (ignore positive pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphEquivalenceStructureIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaForEquivalenceStructure(currentComponentVariableSet);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::ONLY_POSITIVE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            EquivalencePreprocessingStruct equivalencePreprocessingStructure = createEquivalencePreprocessingStructure();
            printEquivalencePreprocessingStructure(equivalencePreprocessingStructure, actualResult);

            partitioningHypergraphUniquePtr->createEquivalenceStruct(currentComponentVariableSet, equivalencePreprocessingStructure);
            printEquivalenceStructure(partitioningHypergraphUniquePtr->getEquivalenceVectorMap(),
                                      partitioningHypergraphUniquePtr->getVariableOrderReusableVector(),
                                      partitioningHypergraphUniquePtr->getEquivalenceStructureVector(),
                                      actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Equivalence structure (ignore negative pure literals)
     */
    TEST_CASE("[PartitioningHypergraph] equivalence structure (ignore negative pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphEquivalenceStructureIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaForEquivalenceStructure(currentComponentVariableSet);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::ONLY_NEGATIVE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            EquivalencePreprocessingStruct equivalencePreprocessingStructure = createEquivalencePreprocessingStructure();
            printEquivalencePreprocessingStructure(equivalencePreprocessingStructure, actualResult);

            partitioningHypergraphUniquePtr->createEquivalenceStruct(currentComponentVariableSet, equivalencePreprocessingStructure);
            printEquivalenceStructure(partitioningHypergraphUniquePtr->getEquivalenceVectorMap(),
                                      partitioningHypergraphUniquePtr->getVariableOrderReusableVector(),
                                      partitioningHypergraphUniquePtr->getEquivalenceStructureVector(),
                                      actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Equivalence structure (ignore pure literals)
     */
    TEST_CASE("[PartitioningHypergraph] equivalence structure (ignore pure literals)", "[PartitioningHypergraph]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          partitioningHypergraphEquivalenceStructureIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = createFormulaForEquivalenceStructure(currentComponentVariableSet);

            PartitioningHypergraphAbstractUniquePtrType partitioningHypergraphUniquePtr = createPartitioningHypergraphAbstract(formulaUniquePtr.get(),
                                                                                                                               IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE,
                                                                                                                               VertexWeightTypeEnum::NONE);

            EquivalencePreprocessingStruct equivalencePreprocessingStructure = createEquivalencePreprocessingStructure();
            printEquivalencePreprocessingStructure(equivalencePreprocessingStructure, actualResult);

            partitioningHypergraphUniquePtr->createEquivalenceStruct(currentComponentVariableSet, equivalencePreprocessingStructure);
            printEquivalenceStructure(partitioningHypergraphUniquePtr->getEquivalenceVectorMap(),
                                      partitioningHypergraphUniquePtr->getVariableOrderReusableVector(),
                                      partitioningHypergraphUniquePtr->getEquivalenceStructureVector(),
                                      actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif
}   // namespace HydraTest::PartitioningHypergraph
