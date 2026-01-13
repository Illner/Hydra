#pragma once

#include "./Hydra.hpp"

template <typename CommandLineArgumentsStructT>
void initialAdjustmentToConfiguration(CommandLineArgumentsStructT& commandLineArgumentsStruct) {
    // No variable subsumption => no vertex weights
    if (commandLineArgumentsStruct.compilerConfiguration.vertexWeightType != Hydra::PartitioningHypergraph::VertexWeightTypeEnum::NONE) {
        if (commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType == Hydra::Formula::Representation::Contagious::VariableSubsumptionWithMappingTypeEnum::NONE) {
            commandLineArgumentsStruct.compilerConfiguration.vertexWeightType = Hydra::PartitioningHypergraph::VertexWeightTypeEnum::NONE;

            Hydra::Other::printWarningAboutAdjustedConfiguration("vertex weight type",
                                                                 Hydra::PartitioningHypergraph::vertexWeightTypeEnumToString(commandLineArgumentsStruct.compilerConfiguration.vertexWeightType));
        }
    }

    // KaHyPar/Cara => deny singleton hyperedges
    if (commandLineArgumentsStruct.compilerConfiguration.allowSingletonHyperedge) {
        if (commandLineArgumentsStruct.compilerConfiguration.partitioningHypergraphType == Hydra::PartitioningHypergraphTypeEnum::KAHYPAR ||
            commandLineArgumentsStruct.compilerConfiguration.partitioningHypergraphType == Hydra::PartitioningHypergraphTypeEnum::CARA ||
            commandLineArgumentsStruct.compilerConfiguration.partitioningHypergraphType == Hydra::PartitioningHypergraphTypeEnum::CARA_SPEED) {
            commandLineArgumentsStruct.compilerConfiguration.allowSingletonHyperedge = false;

            Hydra::Other::printWarningAboutAdjustedConfiguration("allow singleton hyperedges",
                                                                 "false");
        }
    }
}

template <typename CommandLineArgumentsStructT>
void coreMain(CommandLineArgumentsStructT& commandLineArgumentsStruct, StatisticsPtrType statisticsPtr, AtomicBoolPtrType killedByMainThread) {
    using LargeNumberType = Hydra::Other::LargeNumberType;
    using ModelCountingTypeEnum = Cara::ModelCountingTypeEnum;
    using DimacsCnfHeaderStruct = Hydra::Other::Parser::DimacsCnfHeaderStruct;

    initialAdjustmentToConfiguration(commandLineArgumentsStruct);

    // The input file does not exist
    if (!std::filesystem::exists(commandLineArgumentsStruct.inputFilePath))
        throw Hydra::Exception::FileDoesNotExistException(commandLineArgumentsStruct.inputFilePath);

    std::ifstream fileStream(commandLineArgumentsStruct.inputFilePath, std::ios::in);

    // The input file cannot be opened
    if (!fileStream.is_open())
        throw Hydra::Exception::FileCannotBeOpenedException(commandLineArgumentsStruct.inputFilePath);

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
    Hydra::Other::Parser::parseCommentLines(begin, end, line, modelCountingType);

    // Parse the DIMACS CNF header
    DimacsCnfHeaderStruct dimacsCnfHeader = Hydra::Other::Parser::parseDimacsCnfHeader(begin, end, line);

    // The variables cannot be saved as std::size_t
    if (!Hydra::Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(dimacsCnfHeader.numberOfVariables, 1))
        throw Hydra::Exception::SomethingCannotBeSavedAsStdSizeTException("variables", dimacsCnfHeader.numberOfVariables);

    // The literals cannot be saved as std::size_t
    LargeNumberType tmp = Hydra::Other::computeNumberOfLiteralsDesignedForMethodsOfTypeCanBeSavedAs(dimacsCnfHeader.numberOfVariables);
    if (!Hydra::Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(tmp))
        throw Hydra::Exception::SomethingCannotBeSavedAsStdSizeTException("literals", tmp);

    // The clauses cannot be saved as std::size_t
    if (!Hydra::Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(dimacsCnfHeader.numberOfClauses))
        throw Hydra::Exception::SomethingCannotBeSavedAsStdSizeTException("clauses", dimacsCnfHeader.numberOfClauses);

    // The formula size cannot be saved as std::size_t
    if (!Hydra::Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(dimacsCnfHeader.size))
        throw Hydra::Exception::SomethingCannotBeSavedAsStdSizeTException("formula size", dimacsCnfHeader.size);

    #if defined(CARA_SOLVER)
    commandLineArgumentsStruct.numberOfVariables = static_cast<std::size_t>(dimacsCnfHeader.numberOfVariables);
    #endif

    // ClauseIdT = char8_t
    if (Hydra::Other::clauseIdCanBeSavedAsTypeT<char8_t>(dimacsCnfHeader.numberOfClauses)) {
        using ClauseIdT = char8_t;
        TemplateTypeEnum clauseIdTemplateType = TemplateTypeEnum::CHAR8_T;

        // VarT = char8_t
        if (Hydra::Other::variablesCanBeSavedAsTypeT<char8_t>(dimacsCnfHeader.numberOfVariables)) {
            using VarT = char8_t;
            TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR8_T;

            // LiteralT = char8_t
            if (Hydra::Other::literalsCanBeSavedAsTypeT<char8_t>(dimacsCnfHeader.numberOfVariables)) {
                using LiteralT = char8_t;
                TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR8_T;

                Hydra::Compiler<VarT, LiteralT, ClauseIdT> compiler(Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, dimacsCnfHeader, line, modelCountingType, false, commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                    commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                fileStream.close();

                printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                core(compiler, commandLineArgumentsStruct);
            }

            // LiteralT = char16_t
            else {
                assert(Hydra::Other::literalsCanBeSavedAsTypeT<char16_t>(dimacsCnfHeader.numberOfVariables));

                using LiteralT = char16_t;
                TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR16_T;

                Hydra::Compiler<VarT, LiteralT, ClauseIdT> compiler(Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, dimacsCnfHeader, line, modelCountingType, false, commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                    commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                fileStream.close();

                printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                core(compiler, commandLineArgumentsStruct);
            }
        }

        // VarT = char16_t
        else if (Hydra::Other::variablesCanBeSavedAsTypeT<char16_t>(dimacsCnfHeader.numberOfVariables)) {
            using VarT = char16_t;
            TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR16_T;

            // LiteralT = char16_t
            if (Hydra::Other::literalsCanBeSavedAsTypeT<char16_t>(dimacsCnfHeader.numberOfVariables)) {
                using LiteralT = char16_t;
                TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR16_T;

                Hydra::Compiler<VarT, LiteralT, ClauseIdT> compiler(Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, dimacsCnfHeader, line, modelCountingType, false, commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                    commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                fileStream.close();

                printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                core(compiler, commandLineArgumentsStruct);
            }

            // LiteralT = char32_t
            else {
                assert(Hydra::Other::literalsCanBeSavedAsTypeT<char32_t>(dimacsCnfHeader.numberOfVariables));

                using LiteralT = char32_t;
                TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR32_T;

                Hydra::Compiler<VarT, LiteralT, ClauseIdT> compiler(Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, dimacsCnfHeader, line, modelCountingType, false, commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                    commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                fileStream.close();

                printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                core(compiler, commandLineArgumentsStruct);
            }
        }

        // VarT = char32_t
        else if (Hydra::Other::variablesCanBeSavedAsTypeT<char32_t>(dimacsCnfHeader.numberOfVariables)) {
            using VarT = char32_t;
            TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR32_T;

            // LiteralT = char32_t
            if (Hydra::Other::literalsCanBeSavedAsTypeT<char32_t>(dimacsCnfHeader.numberOfVariables)) {
                using LiteralT = char32_t;
                TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR32_T;

                Hydra::Compiler<VarT, LiteralT, ClauseIdT> compiler(Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, dimacsCnfHeader, line, modelCountingType, false, commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                    commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                fileStream.close();

                printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                core(compiler, commandLineArgumentsStruct);
            }

            // Too many literals
            else
                throw Hydra::Exception::FormulaHasTooManySomethingException("literals");
        }

        // Too many variables
        else
            throw Hydra::Exception::FormulaHasTooManySomethingException("variables");
    }

    // ClauseIdT = char16_t
    else if (Hydra::Other::clauseIdCanBeSavedAsTypeT<char16_t>(dimacsCnfHeader.numberOfClauses)) {
        using ClauseIdT = char16_t;
        TemplateTypeEnum clauseIdTemplateType = TemplateTypeEnum::CHAR16_T;

        // VarT = char8_t
        if (Hydra::Other::variablesCanBeSavedAsTypeT<char8_t>(dimacsCnfHeader.numberOfVariables)) {
            using VarT = char8_t;
            TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR8_T;

            // LiteralT = char8_t
            if (Hydra::Other::literalsCanBeSavedAsTypeT<char8_t>(dimacsCnfHeader.numberOfVariables)) {
                using LiteralT = char8_t;
                TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR8_T;

                Hydra::Compiler<VarT, LiteralT, ClauseIdT> compiler(Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, dimacsCnfHeader, line, modelCountingType, false, commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                    commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                fileStream.close();

                printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                core(compiler, commandLineArgumentsStruct);
            }

            // LiteralT = char16_t
            else {
                assert(Hydra::Other::literalsCanBeSavedAsTypeT<char16_t>(dimacsCnfHeader.numberOfVariables));

                using LiteralT = char16_t;
                TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR16_T;

                Hydra::Compiler<VarT, LiteralT, ClauseIdT> compiler(Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, dimacsCnfHeader, line, modelCountingType, false, commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                    commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                fileStream.close();

                printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                core(compiler, commandLineArgumentsStruct);
            }
        }

        // VarT = char16_t
        else if (Hydra::Other::variablesCanBeSavedAsTypeT<char16_t>(dimacsCnfHeader.numberOfVariables)) {
            using VarT = char16_t;
            TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR16_T;

            // LiteralT = char16_t
            if (Hydra::Other::literalsCanBeSavedAsTypeT<char16_t>(dimacsCnfHeader.numberOfVariables)) {
                using LiteralT = char16_t;
                TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR16_T;

                Hydra::Compiler<VarT, LiteralT, ClauseIdT> compiler(Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, dimacsCnfHeader, line, modelCountingType, false, commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                    commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                fileStream.close();

                printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                core(compiler, commandLineArgumentsStruct);
            }

            // LiteralT = char32_t
            else {
                assert(Hydra::Other::literalsCanBeSavedAsTypeT<char32_t>(dimacsCnfHeader.numberOfVariables));

                using LiteralT = char32_t;
                TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR32_T;

                Hydra::Compiler<VarT, LiteralT, ClauseIdT> compiler(Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, dimacsCnfHeader, line, modelCountingType, false, commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                    commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                fileStream.close();

                printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                core(compiler, commandLineArgumentsStruct);
            }
        }

        // VarT = char32_t
        else if (Hydra::Other::variablesCanBeSavedAsTypeT<char32_t>(dimacsCnfHeader.numberOfVariables)) {
            using VarT = char32_t;
            TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR32_T;

            // LiteralT = char32_t
            if (Hydra::Other::literalsCanBeSavedAsTypeT<char32_t>(dimacsCnfHeader.numberOfVariables)) {
                using LiteralT = char32_t;
                TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR32_T;

                Hydra::Compiler<VarT, LiteralT, ClauseIdT> compiler(Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, dimacsCnfHeader, line, modelCountingType, false, commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                    commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                fileStream.close();

                printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                core(compiler, commandLineArgumentsStruct);
            }

            // Too many literals
            else
                throw Hydra::Exception::FormulaHasTooManySomethingException("literals");
        }

        // Too many variables
        else
            throw Hydra::Exception::FormulaHasTooManySomethingException("variables");
    }

    // ClauseIdT = char32_t
    else if (Hydra::Other::clauseIdCanBeSavedAsTypeT<char32_t>(dimacsCnfHeader.numberOfClauses)) {
        using ClauseIdT = char32_t;
        TemplateTypeEnum clauseIdTemplateType = TemplateTypeEnum::CHAR32_T;

        // VarT = char8_t
        if (Hydra::Other::variablesCanBeSavedAsTypeT<char8_t>(dimacsCnfHeader.numberOfVariables)) {
            using VarT = char8_t;
            TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR8_T;

            // LiteralT = char8_t
            if (Hydra::Other::literalsCanBeSavedAsTypeT<char8_t>(dimacsCnfHeader.numberOfVariables)) {
                using LiteralT = char8_t;
                TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR8_T;

                Hydra::Compiler<VarT, LiteralT, ClauseIdT> compiler(Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, dimacsCnfHeader, line, modelCountingType, false, commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                    commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                fileStream.close();

                printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                core(compiler, commandLineArgumentsStruct);
            }

            // LiteralT = char16_t
            else {
                assert(Hydra::Other::literalsCanBeSavedAsTypeT<char16_t>(dimacsCnfHeader.numberOfVariables));

                using LiteralT = char16_t;
                TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR16_T;

                Hydra::Compiler<VarT, LiteralT, ClauseIdT> compiler(Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, dimacsCnfHeader, line, modelCountingType, false, commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                    commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                fileStream.close();

                printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                core(compiler, commandLineArgumentsStruct);
            }
        }

        // VarT = char16_t
        else if (Hydra::Other::variablesCanBeSavedAsTypeT<char16_t>(dimacsCnfHeader.numberOfVariables)) {
            using VarT = char16_t;
            TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR16_T;

            // LiteralT = char16_t
            if (Hydra::Other::literalsCanBeSavedAsTypeT<char16_t>(dimacsCnfHeader.numberOfVariables)) {
                using LiteralT = char16_t;
                TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR16_T;

                Hydra::Compiler<VarT, LiteralT, ClauseIdT> compiler(Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, dimacsCnfHeader, line, modelCountingType, false, commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                    commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                fileStream.close();

                printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                core(compiler, commandLineArgumentsStruct);
            }

            // LiteralT = char32_t
            else {
                assert(Hydra::Other::literalsCanBeSavedAsTypeT<char32_t>(dimacsCnfHeader.numberOfVariables));

                using LiteralT = char32_t;
                TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR32_T;

                Hydra::Compiler<VarT, LiteralT, ClauseIdT> compiler(Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, dimacsCnfHeader, line, modelCountingType, false, commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                    commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                fileStream.close();

                printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                core(compiler, commandLineArgumentsStruct);
            }
        }

        // VarT = char32_t
        else if (Hydra::Other::variablesCanBeSavedAsTypeT<char32_t>(dimacsCnfHeader.numberOfVariables)) {
            using VarT = char32_t;
            TemplateTypeEnum varTemplateType = TemplateTypeEnum::CHAR32_T;

            // LiteralT = char32_t
            if (Hydra::Other::literalsCanBeSavedAsTypeT<char32_t>(dimacsCnfHeader.numberOfVariables)) {
                using LiteralT = char32_t;
                TemplateTypeEnum literalTemplateType = TemplateTypeEnum::CHAR32_T;

                Hydra::Compiler<VarT, LiteralT, ClauseIdT> compiler(Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, dimacsCnfHeader, line, modelCountingType, false, commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration, statisticsPtr ? statisticsPtr->getFormulaRepresentationStatisticsPtr() : nullptr),
                                                                    commandLineArgumentsStruct.compilerConfiguration, statisticsPtr, killedByMainThread);
                fileStream.close();

                printTemplateTypes(varTemplateType, literalTemplateType, clauseIdTemplateType);

                modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
                printConfigurationBeforeCompilation(commandLineArgumentsStruct);

                core(compiler, commandLineArgumentsStruct);
            }

            // Too many literals
            else
                throw Hydra::Exception::FormulaHasTooManySomethingException("literals");
        }

        // Too many variables
        else
            throw Hydra::Exception::FormulaHasTooManySomethingException("variables");
    }

    // Too many clauses
    else
        throw Hydra::Exception::FormulaHasTooManySomethingException("clauses");
}
