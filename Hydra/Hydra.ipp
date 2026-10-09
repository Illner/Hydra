#pragma once

#include "./Hydra.hpp"

#include "Hydra/formula/representation/contiguous/ContiguousFormulaRepresentation.hpp"
#include "Hydra/parser/cnf/CnfParser.hpp"

namespace Hydra {

    template <typename CommandLineArgumentsStructT>
    void initialAdjustmentToConfiguration(CommandLineArgumentsStructT& commandLineArgumentsStruct) {
        // No variable subsumption => no vertex weights
        if (commandLineArgumentsStruct.compilerConfiguration.vertexWeightType != HypergraphPartitioning::VertexWeightTypeEnum::NONE) {
            if (commandLineArgumentsStruct.contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType == Formula::Representation::Contiguous::VariableSubsumptionWithMappingTypeEnum::NONE) {
                commandLineArgumentsStruct.compilerConfiguration.vertexWeightType = HypergraphPartitioning::VertexWeightTypeEnum::NONE;

                Other::printWarningAboutAdjustedConfiguration("vertex weight type",
                                                              HypergraphPartitioning::vertexWeightTypeEnumToString(commandLineArgumentsStruct.compilerConfiguration.vertexWeightType));
            }
        }

        // KaHyPar/Cara => deny singleton hyperedges
        if (commandLineArgumentsStruct.compilerConfiguration.allowSingletonHyperedge) {
            if (commandLineArgumentsStruct.compilerConfiguration.hypergraphPartitioningType == HypergraphPartitioningTypeEnum::KAHYPAR ||
                commandLineArgumentsStruct.compilerConfiguration.hypergraphPartitioningType == HypergraphPartitioningTypeEnum::CARA ||
                commandLineArgumentsStruct.compilerConfiguration.hypergraphPartitioningType == HypergraphPartitioningTypeEnum::CARA_SPEED) {
                commandLineArgumentsStruct.compilerConfiguration.allowSingletonHyperedge = false;

                Other::printWarningAboutAdjustedConfiguration("allow singleton hyperedges",
                                                              "false");
            }
        }
    }

    template <typename CommandLineArgumentsStructT>
    void coreMain(CommandLineArgumentsStructT& commandLineArgumentsStruct, StatisticsPtrType statisticsPtr, AtomicBoolPtrType killedByMainThread) {
        using LargeNumberType = Other::LargeNumberType;
        using ModelCountingTypeEnum = Cara::ModelCountingTypeEnum;
        using DimacsCnfHeaderStruct = Other::Parser::DimacsCnfHeaderStruct;
        using CnfPreprocessorAbstractType = Preprocessor::Cnf::CnfPreprocessorAbstract;
        using ParsedFormulaStruct = Preprocessor::Cnf::CnfPreprocessorAbstract::ParsedFormulaStruct;

        initialAdjustmentToConfiguration(commandLineArgumentsStruct);

        // The input file does not exist
        if (!std::filesystem::exists(commandLineArgumentsStruct.inputFilePath))
            throw Exception::FileDoesNotExistException(commandLineArgumentsStruct.inputFilePath);

        std::ifstream fileStream(commandLineArgumentsStruct.inputFilePath, std::ios::in);

        // The input file cannot be opened
        if (!fileStream.is_open())
            throw Exception::FileCannotBeOpenedException(commandLineArgumentsStruct.inputFilePath);

        // Model counting type
        #if defined(BELLA_COMPILER)
        ModelCountingTypeEnum dummyModelCountingType = ModelCountingTypeEnum::UNDEFINED;
        ModelCountingTypeEnum& modelCountingType = dummyModelCountingType;
        #elif defined(CARA_SOLVER)
        ModelCountingTypeEnum& modelCountingType = commandLineArgumentsStruct.modelCountingType;
        #endif

        unsigned int line = 1;
        std::istreambuf_iterator<char> begin(fileStream);
        std::istreambuf_iterator<char> end;

        // Parse comment lines
        Other::Parser::parseCommentLines(begin, end, line, modelCountingType);

        // Parse the DIMACS CNF header
        DimacsCnfHeaderStruct dimacsCnfHeader = Other::Parser::parseDimacsCnfHeader(begin, end, line);

        // The variables cannot be saved as std::size_t
        if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(dimacsCnfHeader.numberOfVariables, 1))
            throw Exception::SomethingCannotBeSavedAsStdSizeTException("variables", dimacsCnfHeader.numberOfVariables);

        // The literals cannot be saved as std::size_t
        LargeNumberType tmp = Other::computeNumberOfLiteralsDesignedForMethodsOfTypeCanBeSavedAs(dimacsCnfHeader.numberOfVariables);
        if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(tmp, 1))
            throw Exception::SomethingCannotBeSavedAsStdSizeTException("literals", tmp);

        // The clauses cannot be saved as std::size_t
        if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(dimacsCnfHeader.numberOfClauses))
            throw Exception::SomethingCannotBeSavedAsStdSizeTException("clauses", dimacsCnfHeader.numberOfClauses);

        // The formula size cannot be saved as std::size_t
        if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(dimacsCnfHeader.size))
            throw Exception::SomethingCannotBeSavedAsStdSizeTException("formula size", dimacsCnfHeader.size);

        #if defined(CARA_SOLVER)
        commandLineArgumentsStruct.numberOfVariables = static_cast<std::size_t>(dimacsCnfHeader.numberOfVariables);
        #endif

        // The variables cannot be saved as the CNF preprocessor type
        if (!Other::variablesCanBeSavedAsTypeT<CnfPreprocessorAbstractType::VarT>(dimacsCnfHeader.numberOfVariables))
            throw Exception::FormulaHasTooManySomethingException("variables");

        // The literals cannot be saved as the CNF preprocessor type
        if (!Other::literalsCanBeSavedAsTypeT<CnfPreprocessorAbstractType::LiteralT>(dimacsCnfHeader.numberOfVariables))
            throw Exception::FormulaHasTooManySomethingException("literals");

        // The clauses cannot be saved as the CNF preprocessor type
        if (!Other::clauseIdCanBeSavedAsTypeT<CnfPreprocessorAbstractType::ClauseIdT>(dimacsCnfHeader.numberOfClauses))
            throw Exception::FormulaHasTooManySomethingException("clauses");

        ParsedFormulaStruct parsedFormulaStruct = Parser::Cnf::parseCnfFormula<CnfPreprocessorAbstractType::VarT,
                                                                               CnfPreprocessorAbstractType::LiteralT,
                                                                               CnfPreprocessorAbstractType::ClauseIdT>(begin, end,
                                                                                                                       dimacsCnfHeader, line, modelCountingType, false,
                                                                                                                       statisticsPtr ? statisticsPtr->getCnfParserStatisticsPtr() : nullptr);

        // CNF preprocessor
        CnfPreprocessorAbstractUniquePtrType cnfPreprocessorAbstractUniquePtr = initializeCnfPreprocessor(commandLineArgumentsStruct.cnfPreprocessorStruct,
                                                                                                          statisticsPtr ? statisticsPtr->getCnfPreprocessorStatisticsPtr() : nullptr);
        ParsedFormulaStruct preprocessedFormulaStruct = cnfPreprocessorAbstractUniquePtr->preprocess(std::move(parsedFormulaStruct));

        // ClauseIdT = char8_t
        if (Other::clauseIdCanBeSavedAsTypeT<char8_t>(preprocessedFormulaStruct.numberOfClauses)) {
            using ClauseIdT = char8_t;
            TemplateTypeEnum clauseIdTemplateType = TemplateTypeEnum::CHAR8_T;

            // VarT = char8_t
            if (Other::variablesCanBeSavedAsTypeT<char8_t>(preprocessedFormulaStruct.numberOfVariables)) {
                using VarT = char8_t;
                TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR8_T;

                // LiteralT = char8_t
                if (Other::literalsCanBeSavedAsTypeT<char8_t>(preprocessedFormulaStruct.numberOfVariables)) {
                    using LiteralT = char8_t;
                    TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR8_T;

                    Compiler<VarT, LiteralT, ClauseIdT> compiler(std::make_unique<Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>>(ParsedFormulaStruct::convertTypes<VarT, LiteralT, ClauseIdT>(std::move(preprocessedFormulaStruct)), commandLineArgumentsStruct.contiguousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                 commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                    fileStream.close();

                    printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                    modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                    printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                    core(compiler, commandLineArgumentsStruct);
                }

                // LiteralT = char16_t
                else {
                    assert(Other::literalsCanBeSavedAsTypeT<char16_t>(preprocessedFormulaStruct.numberOfVariables));

                    using LiteralT = char16_t;
                    TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR16_T;

                    Compiler<VarT, LiteralT, ClauseIdT> compiler(std::make_unique<Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>>(ParsedFormulaStruct::convertTypes<VarT, LiteralT, ClauseIdT>(std::move(preprocessedFormulaStruct)), commandLineArgumentsStruct.contiguousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                 commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                    fileStream.close();

                    printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                    modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                    printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                    core(compiler, commandLineArgumentsStruct);
                }
            }

            // VarT = char16_t
            else if (Other::variablesCanBeSavedAsTypeT<char16_t>(preprocessedFormulaStruct.numberOfVariables)) {
                using VarT = char16_t;
                TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR16_T;

                // LiteralT = char16_t
                if (Other::literalsCanBeSavedAsTypeT<char16_t>(preprocessedFormulaStruct.numberOfVariables)) {
                    using LiteralT = char16_t;
                    TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR16_T;

                    Compiler<VarT, LiteralT, ClauseIdT> compiler(std::make_unique<Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>>(ParsedFormulaStruct::convertTypes<VarT, LiteralT, ClauseIdT>(std::move(preprocessedFormulaStruct)), commandLineArgumentsStruct.contiguousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                 commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                    fileStream.close();

                    printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                    modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                    printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                    core(compiler, commandLineArgumentsStruct);
                }

                // LiteralT = char32_t
                else {
                    assert(Other::literalsCanBeSavedAsTypeT<char32_t>(preprocessedFormulaStruct.numberOfVariables));

                    using LiteralT = char32_t;
                    TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR32_T;

                    Compiler<VarT, LiteralT, ClauseIdT> compiler(std::make_unique<Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>>(ParsedFormulaStruct::convertTypes<VarT, LiteralT, ClauseIdT>(std::move(preprocessedFormulaStruct)), commandLineArgumentsStruct.contiguousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                 commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                    fileStream.close();

                    printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                    modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                    printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                    core(compiler, commandLineArgumentsStruct);
                }
            }

            // VarT = char32_t
            else if (Other::variablesCanBeSavedAsTypeT<char32_t>(preprocessedFormulaStruct.numberOfVariables)) {
                using VarT = char32_t;
                TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR32_T;

                // LiteralT = char32_t
                if (Other::literalsCanBeSavedAsTypeT<char32_t>(preprocessedFormulaStruct.numberOfVariables)) {
                    using LiteralT = char32_t;
                    TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR32_T;

                    Compiler<VarT, LiteralT, ClauseIdT> compiler(std::make_unique<Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>>(ParsedFormulaStruct::convertTypes<VarT, LiteralT, ClauseIdT>(std::move(preprocessedFormulaStruct)), commandLineArgumentsStruct.contiguousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                 commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                    fileStream.close();

                    printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                    modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                    printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                    core(compiler, commandLineArgumentsStruct);
                }

                // Too many literals
                else
                    throw Exception::FormulaHasTooManySomethingException("literals");
            }

            // Too many variables
            else
                throw Exception::FormulaHasTooManySomethingException("variables");
        }

        // ClauseIdT = char16_t
        else if (Other::clauseIdCanBeSavedAsTypeT<char16_t>(preprocessedFormulaStruct.numberOfClauses)) {
            using ClauseIdT = char16_t;
            TemplateTypeEnum clauseIdTemplateType = TemplateTypeEnum::CHAR16_T;

            // VarT = char8_t
            if (Other::variablesCanBeSavedAsTypeT<char8_t>(preprocessedFormulaStruct.numberOfVariables)) {
                using VarT = char8_t;
                TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR8_T;

                // LiteralT = char8_t
                if (Other::literalsCanBeSavedAsTypeT<char8_t>(preprocessedFormulaStruct.numberOfVariables)) {
                    using LiteralT = char8_t;
                    TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR8_T;

                    Compiler<VarT, LiteralT, ClauseIdT> compiler(std::make_unique<Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>>(ParsedFormulaStruct::convertTypes<VarT, LiteralT, ClauseIdT>(std::move(preprocessedFormulaStruct)), commandLineArgumentsStruct.contiguousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                 commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                    fileStream.close();

                    printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                    modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                    printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                    core(compiler, commandLineArgumentsStruct);
                }

                // LiteralT = char16_t
                else {
                    assert(Other::literalsCanBeSavedAsTypeT<char16_t>(preprocessedFormulaStruct.numberOfVariables));

                    using LiteralT = char16_t;
                    TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR16_T;

                    Compiler<VarT, LiteralT, ClauseIdT> compiler(std::make_unique<Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>>(ParsedFormulaStruct::convertTypes<VarT, LiteralT, ClauseIdT>(std::move(preprocessedFormulaStruct)), commandLineArgumentsStruct.contiguousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                 commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                    fileStream.close();

                    printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                    modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                    printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                    core(compiler, commandLineArgumentsStruct);
                }
            }

            // VarT = char16_t
            else if (Other::variablesCanBeSavedAsTypeT<char16_t>(preprocessedFormulaStruct.numberOfVariables)) {
                using VarT = char16_t;
                TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR16_T;

                // LiteralT = char16_t
                if (Other::literalsCanBeSavedAsTypeT<char16_t>(preprocessedFormulaStruct.numberOfVariables)) {
                    using LiteralT = char16_t;
                    TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR16_T;

                    Compiler<VarT, LiteralT, ClauseIdT> compiler(std::make_unique<Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>>(ParsedFormulaStruct::convertTypes<VarT, LiteralT, ClauseIdT>(std::move(preprocessedFormulaStruct)), commandLineArgumentsStruct.contiguousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                 commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                    fileStream.close();

                    printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                    modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                    printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                    core(compiler, commandLineArgumentsStruct);
                }

                // LiteralT = char32_t
                else {
                    assert(Other::literalsCanBeSavedAsTypeT<char32_t>(preprocessedFormulaStruct.numberOfVariables));

                    using LiteralT = char32_t;
                    TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR32_T;

                    Compiler<VarT, LiteralT, ClauseIdT> compiler(std::make_unique<Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>>(ParsedFormulaStruct::convertTypes<VarT, LiteralT, ClauseIdT>(std::move(preprocessedFormulaStruct)), commandLineArgumentsStruct.contiguousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                 commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                    fileStream.close();

                    printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                    modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                    printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                    core(compiler, commandLineArgumentsStruct);
                }
            }

            // VarT = char32_t
            else if (Other::variablesCanBeSavedAsTypeT<char32_t>(preprocessedFormulaStruct.numberOfVariables)) {
                using VarT = char32_t;
                TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR32_T;

                // LiteralT = char32_t
                if (Other::literalsCanBeSavedAsTypeT<char32_t>(preprocessedFormulaStruct.numberOfVariables)) {
                    using LiteralT = char32_t;
                    TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR32_T;

                    Compiler<VarT, LiteralT, ClauseIdT> compiler(std::make_unique<Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>>(ParsedFormulaStruct::convertTypes<VarT, LiteralT, ClauseIdT>(std::move(preprocessedFormulaStruct)), commandLineArgumentsStruct.contiguousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                 commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                    fileStream.close();

                    printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                    modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                    printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                    core(compiler, commandLineArgumentsStruct);
                }

                // Too many literals
                else
                    throw Exception::FormulaHasTooManySomethingException("literals");
            }

            // Too many variables
            else
                throw Exception::FormulaHasTooManySomethingException("variables");
        }

        // ClauseIdT = char32_t
        else if (Other::clauseIdCanBeSavedAsTypeT<char32_t>(preprocessedFormulaStruct.numberOfClauses)) {
            using ClauseIdT = char32_t;
            TemplateTypeEnum clauseIdTemplateType = TemplateTypeEnum::CHAR32_T;

            // VarT = char8_t
            if (Other::variablesCanBeSavedAsTypeT<char8_t>(preprocessedFormulaStruct.numberOfVariables)) {
                using VarT = char8_t;
                TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR8_T;

                // LiteralT = char8_t
                if (Other::literalsCanBeSavedAsTypeT<char8_t>(preprocessedFormulaStruct.numberOfVariables)) {
                    using LiteralT = char8_t;
                    TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR8_T;

                    Compiler<VarT, LiteralT, ClauseIdT> compiler(std::make_unique<Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>>(ParsedFormulaStruct::convertTypes<VarT, LiteralT, ClauseIdT>(std::move(preprocessedFormulaStruct)), commandLineArgumentsStruct.contiguousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                 commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                    fileStream.close();

                    printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                    modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                    printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                    core(compiler, commandLineArgumentsStruct);
                }

                // LiteralT = char16_t
                else {
                    assert(Other::literalsCanBeSavedAsTypeT<char16_t>(preprocessedFormulaStruct.numberOfVariables));

                    using LiteralT = char16_t;
                    TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR16_T;

                    Compiler<VarT, LiteralT, ClauseIdT> compiler(std::make_unique<Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>>(ParsedFormulaStruct::convertTypes<VarT, LiteralT, ClauseIdT>(std::move(preprocessedFormulaStruct)), commandLineArgumentsStruct.contiguousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                 commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                    fileStream.close();

                    printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                    modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                    printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                    core(compiler, commandLineArgumentsStruct);
                }
            }

            // VarT = char16_t
            else if (Other::variablesCanBeSavedAsTypeT<char16_t>(preprocessedFormulaStruct.numberOfVariables)) {
                using VarT = char16_t;
                TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR16_T;

                // LiteralT = char16_t
                if (Other::literalsCanBeSavedAsTypeT<char16_t>(preprocessedFormulaStruct.numberOfVariables)) {
                    using LiteralT = char16_t;
                    TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR16_T;

                    Compiler<VarT, LiteralT, ClauseIdT> compiler(std::make_unique<Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>>(ParsedFormulaStruct::convertTypes<VarT, LiteralT, ClauseIdT>(std::move(preprocessedFormulaStruct)), commandLineArgumentsStruct.contiguousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                 commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                    fileStream.close();

                    printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                    modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                    printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                    core(compiler, commandLineArgumentsStruct);
                }

                // LiteralT = char32_t
                else {
                    assert(Other::literalsCanBeSavedAsTypeT<char32_t>(preprocessedFormulaStruct.numberOfVariables));

                    using LiteralT = char32_t;
                    TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR32_T;

                    Compiler<VarT, LiteralT, ClauseIdT> compiler(std::make_unique<Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>>(ParsedFormulaStruct::convertTypes<VarT, LiteralT, ClauseIdT>(std::move(preprocessedFormulaStruct)), commandLineArgumentsStruct.contiguousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                 commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                    fileStream.close();

                    printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                    modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                    printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                    core(compiler, commandLineArgumentsStruct);
                }
            }

            // VarT = char32_t
            else if (Other::variablesCanBeSavedAsTypeT<char32_t>(preprocessedFormulaStruct.numberOfVariables)) {
                using VarT = char32_t;
                TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR32_T;

                // LiteralT = char32_t
                if (Other::literalsCanBeSavedAsTypeT<char32_t>(preprocessedFormulaStruct.numberOfVariables)) {
                    using LiteralT = char32_t;
                    TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR32_T;

                    Compiler<VarT, LiteralT, ClauseIdT> compiler(std::make_unique<Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>>(ParsedFormulaStruct::convertTypes<VarT, LiteralT, ClauseIdT>(std::move(preprocessedFormulaStruct)), commandLineArgumentsStruct.contiguousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                 commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                    fileStream.close();

                    printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                    modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                    printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                    core(compiler, commandLineArgumentsStruct);
                }

                // Too many literals
                else
                    throw Exception::FormulaHasTooManySomethingException("literals");
            }

            // Too many variables
            else
                throw Exception::FormulaHasTooManySomethingException("variables");
        }

        // Too many clauses
        else
            throw Exception::FormulaHasTooManySomethingException("clauses");
    }
}   // namespace Hydra
