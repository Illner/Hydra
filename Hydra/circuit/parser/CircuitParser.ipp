#pragma once

#include "./CircuitParser.hpp"

namespace Hydra::Circuit::Parser {

    template <std::input_iterator InputIterator>
    DimacsNnfHeaderStruct parseDimacsNnfHeader(InputIterator& begin, const InputIterator& end, unsigned int& line) {
        bool isDimacsNnfHeaderParsed = false;
        DimacsNnfHeaderStruct dimacsNnfHeaderStruct { 0, 0, 0, 0 };

        while (begin != end) {
            if (Other::Parser::skipWhitespacesExcludingNewLineSymbol(begin, end))
                break;

            // New line
            if (*begin == '\n') {
                ++line;
                ++begin;

                if (isDimacsNnfHeaderParsed)
                    break;

                continue;
            }

            // Comment
            if (Other::Parser::toLowercase(*begin) == COMMENT) {
                Other::Parser::skipLine(begin, end);
                continue;
            }

            // DIMACS NNF header
            else if (Other::Parser::toLowercase(*begin) == NNF_HEADER_STRING[0]) {
                // Parse "nnf"
                for (char ch : NNF_HEADER_STRING) {
                    if (begin == end)
                        throw Exception::Circuit::Parser::InvalidDimacsNnfHeaderException("The DIMACS NNF header on line " + std::to_string(line) + " is invalid!");

                    if (Other::Parser::toLowercase(*begin) != ch)
                        throw Exception::Circuit::Parser::InvalidDimacsNnfHeaderException("The character (" + Other::Parser::convertCharToString(*begin) + ") in the DIMACS NNF header on line " + std::to_string(line) + " is invalid!");

                    ++begin;
                }

                // No whitespace
                if (begin == end)
                    throw Exception::Circuit::Parser::InvalidDimacsNnfHeaderException("The DIMACS NNF header on line " + std::to_string(line) + " is invalid!");
                if (!Other::Parser::isWhitespaceExcludingNewLineSymbol(*begin))
                    throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A whitespace (excluding the new line symbol (\\n)) after the string 'nnf' in the DIMACS NNF header", Other::Parser::convertCharToString(*begin), line);

                std::vector<LargeNumberType> parsedParameterVector = Other::Parser::parseAllPositiveNumbersOnLine<LargeNumberType>(begin, end, line, 4);

                // Invalid number of parameters
                if (parsedParameterVector.size() != 3 && parsedParameterVector.size() != 4)
                    throw Exception::Circuit::Parser::InvalidDimacsNnfHeaderException("The DIMACS NNF header on line " + std::to_string(line) + " does not have the correct number of parameters (" + std::to_string(parsedParameterVector.size()) + ")!");

                dimacsNnfHeaderStruct.numberOfNodes = parsedParameterVector[0];
                dimacsNnfHeaderStruct.numberOfEdges = parsedParameterVector[1];
                dimacsNnfHeaderStruct.numberOfVariables = parsedParameterVector[2];

                if (parsedParameterVector.size() == 3)
                    dimacsNnfHeaderStruct.size = parsedParameterVector[1];   // size = number of edges
                else
                    dimacsNnfHeaderStruct.size = parsedParameterVector[3];   // size

                isDimacsNnfHeaderParsed = true;
                continue;
            }

            // Invalid char
            else {
                throw Exception::Circuit::Parser::InvalidDimacsNnfHeaderException("Invalid line " + std::to_string(line) + " (" + Other::Parser::convertCharToString(*begin) + "...) has occurred before the DIMACS NNF header!");
            }
        }

        if (!isDimacsNnfHeaderParsed)
            throw Exception::Circuit::Parser::InvalidDimacsNnfHeaderException("The DIMACS NNF header was not found!");

        // The variables cannot be saved as std::size_t
        if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(dimacsNnfHeaderStruct.numberOfVariables, 1))
            throw Exception::SomethingCannotBeSavedAsStdSizeTException("variables", dimacsNnfHeaderStruct.numberOfVariables);

        // The nodes cannot be saved as std::size_t
        if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(dimacsNnfHeaderStruct.numberOfNodes))
            throw Exception::SomethingCannotBeSavedAsStdSizeTException("nodes", dimacsNnfHeaderStruct.numberOfNodes);

        return dimacsNnfHeaderStruct;
    }

    template <typename VarT, typename LiteralT, std::input_iterator InputIterator>
    Circuit<VarT, LiteralT> parseCircuit(InputIterator& begin, const InputIterator& end,
                                         const DimacsNnfHeaderStruct& dimacsNnfHeaderStruct,
                                         unsigned int& line) {
        return parseCircuit<VarT, LiteralT, InputIterator>(begin, end,
                                                           static_cast<IdNodeType>(dimacsNnfHeaderStruct.numberOfNodes),
                                                           dimacsNnfHeaderStruct.numberOfEdges,
                                                           static_cast<VarT>(dimacsNnfHeaderStruct.numberOfVariables),
                                                           dimacsNnfHeaderStruct.size, line);
    }

    template <typename VarT, typename LiteralT, std::input_iterator InputIterator>
    Circuit<VarT, LiteralT> parseCircuit(InputIterator& begin, const InputIterator& end,
                                         IdNodeType numberOfNodes, LargeNumberType numberOfEdges,
                                         VarT numberOfVariables, LargeNumberType size, unsigned int& line) {
        using ClauseType = typename Circuit<VarT, LiteralT>::ClauseType;
        using FormulaType = typename Circuit<VarT, LiteralT>::FormulaType;
        using LiteralType = typename Circuit<VarT, LiteralT>::LiteralType;
        using ClauseSizeType = typename Circuit<VarT, LiteralT>::ClauseSizeType;
        using VariableSetType = typename Circuit<VarT, LiteralT>::VariableSetType;
        using IdNodeVectorType = typename Circuit<VarT, LiteralT>::IdNodeVectorType;
        using LiteralVectorType = typename Circuit<VarT, LiteralT>::LiteralVectorType;
        using VariableVectorType = typename Circuit<VarT, LiteralT>::VariableVectorType;
        using ClauseIdType = typename Node::FormulaLeafAbstract<VarT, LiteralT>::ClauseIdType;
        using MappingFromVariableToVariableType = typename Circuit<VarT, LiteralT>::MappingFromVariableToVariableType;

        using DecomposabilityTypeEnum = Node::DecomposabilityTypeEnum;

        const ClauseSizeType S_ESTIMATED_SIZE_OF_CLAUSE_IN_FORMULA_LEAF_ = 4;

        Circuit<VarT, LiteralT> circuit(numberOfVariables, numberOfNodes);

        while (begin != end) {
            if (Other::Parser::skipWhitespacesExcludingNewLineSymbol(begin, end))
                break;

            // New line
            if (*begin == '\n') {
                ++line;
                ++begin;
                continue;
            }

            // Comment
            if (Other::Parser::toLowercase(*begin) == COMMENT) {
                Other::Parser::skipLine(begin, end);
                continue;
            }

            // Literal leaf
            else if (Other::Parser::toUppercase(*begin) == Node::LITERAL_LEAF) {
                ++begin;   // L

                if (begin == end)
                    throw Exception::Circuit::Parser::CircuitParserException("The literal leaf on line " + std::to_string(line) + " is invalid!");

                if (!Other::Parser::isWhitespaceExcludingNewLineSymbol(*begin))
                    throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A whitespace (excluding \\n)",
                                                                                                    Other::Parser::convertCharToString(*begin), line);

                LiteralType literal = Other::Parser::parseLiteral<VarT, LiteralT>(begin, end, line);
                circuit.createLiteralLeaf(literal);

                if (Other::Parser::skipWhitespacesExcludingNewLineSymbol(begin, end))
                    break;

                if (*begin != '\n')
                    throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A new line (\\n)",
                                                                                                    Other::Parser::convertCharToString(*begin), line);

                continue;
            }

            // AND inner node
            // A c i_1, ...i_c
            // B c i_1, ...i_c
            // P c i_1, ...i_c
            // N c i_1, ...i_c
            else if (Other::Parser::toUppercase(*begin) == Node::AND_INNER_NODE_CLASSICAL_DECOMPOSABILITY ||
                     Other::Parser::toUppercase(*begin) == Node::AND_INNER_NODE_BELLA_DECOMPOSABILITY ||
                     Other::Parser::toUppercase(*begin) == Node::AND_INNER_NODE_POS_BELLA_DECOMPOSABILITY ||
                     Other::Parser::toUppercase(*begin) == Node::AND_INNER_NODE_NEG_BELLA_DECOMPOSABILITY) {
                DecomposabilityTypeEnum decomposabilityTypeEnum;

                switch (Other::Parser::toUppercase(*begin)) {
                    // (classical) decomposability
                    case Node::AND_INNER_NODE_CLASSICAL_DECOMPOSABILITY:
                        decomposabilityTypeEnum = DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY;
                        break;
                    // Bella decomposability
                    case Node::AND_INNER_NODE_BELLA_DECOMPOSABILITY:
                        decomposabilityTypeEnum = DecomposabilityTypeEnum::BELLA_DECOMPOSABILITY;
                        break;
                    // posBella decomposability
                    case Node::AND_INNER_NODE_POS_BELLA_DECOMPOSABILITY:
                        decomposabilityTypeEnum = DecomposabilityTypeEnum::posBELLA_DECOMPOSABILITY;
                        break;
                    // negBella decomposability
                    case Node::AND_INNER_NODE_NEG_BELLA_DECOMPOSABILITY:
                        decomposabilityTypeEnum = DecomposabilityTypeEnum::negBELLA_DECOMPOSABILITY;
                        break;
                    default:
                        throw Exception::NotImplementedException(Other::Parser::convertCharToString(*begin),
                                                                 "Hydra::Circuit::Parser::parseCircuit");
                }

                ++begin;   // A/B/P/N

                if (begin == end)
                    throw Exception::Circuit::Parser::CircuitParserException("The AND node on line " + std::to_string(line) + " is invalid!");

                if (!Other::Parser::isWhitespaceExcludingNewLineSymbol(*begin))
                    throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A whitespace (excluding \\n)",
                                                                                                    Other::Parser::convertCharToString(*begin), line);

                SizeNodeType numberOfChildren = Other::Parser::parsePositiveNumber<SizeNodeType>(begin, end, line);

                // True leaf
                if (numberOfChildren == 0) {
                    circuit.createConstantLeaf(true);

                    if (Other::Parser::skipWhitespacesExcludingNewLineSymbol(begin, end))
                        break;

                    if (*begin != '\n')
                        throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A new line (\\n)",
                                                                                                        Other::Parser::convertCharToString(*begin), line);

                    continue;
                }

                IdNodeVectorType childrenVector = Other::Parser::parseAllPositiveNumbersOnLine<IdNodeType>(begin, end, line,
                                                                                                           numberOfChildren);

                // Invalid number of children
                if (numberOfChildren != childrenVector.size())
                    throw Exception::Circuit::Parser::CircuitParserException("The AND node on line " + std::to_string(line) + " has an invalid number of children!");

                circuit.createAndInnerNode(childrenVector, decomposabilityTypeEnum);

                continue;
            }

            // (Binary) OR inner node
            // O j c i_1 ... i_c
            else if (Other::Parser::toUppercase(*begin) == Node::OR_INNER_NODE) {
                ++begin;   // O

                if (begin == end)
                    throw Exception::Circuit::Parser::CircuitParserException("The OR node on line " + std::to_string(line) + " is invalid!");

                if (!Other::Parser::isWhitespaceExcludingNewLineSymbol(*begin))
                    throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A whitespace (excluding \\n)",
                                                                                                    Other::Parser::convertCharToString(*begin), line);

                VarT decisionVariable = Other::Parser::parsePositiveNumber<VarT>(begin, end, line);
                SizeNodeType numberOfChildren = Other::Parser::parsePositiveNumber<SizeNodeType>(begin, end, line);

                // False leaf
                if (numberOfChildren == 0) {
                    // Decision variable should not be mentioned
                    if (decisionVariable != 0)
                        throw Exception::Circuit::Parser::CircuitParserException("The OR node (= constant leaf) on line " + std::to_string(line) + " has set a decision variable!");

                    circuit.createConstantLeaf(false);

                    if (Other::Parser::skipWhitespacesExcludingNewLineSymbol(begin, end))
                        break;

                    if (*begin != '\n')
                        throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A new line (\\n)",
                                                                                                        Other::Parser::convertCharToString(*begin), line);

                    continue;
                }

                IdNodeVectorType childrenVector = Other::Parser::parseAllPositiveNumbersOnLine<IdNodeType>(begin, end, line,
                                                                                                           numberOfChildren);

                // Invalid number of children
                if (numberOfChildren != childrenVector.size())
                    throw Exception::Circuit::Parser::CircuitParserException("The OR node on line " + std::to_string(line) + " has an invalid number of children!");

                // Binary OR inner node
                if ((numberOfChildren == 2) && (decisionVariable > 0))
                    circuit.createBinaryOrInnerNode(decisionVariable, childrenVector[0], childrenVector[1]);
                // OR inner node
                else
                    circuit.createOrInnerNode(childrenVector);

                continue;
            }

            // Krom-C leaf
            // K l n v_1 ... v_n
            else if (Other::Parser::toUppercase(*begin) == Node::KROM_C_LEAF) {
                ++begin;   // K

                if (begin == end)
                    throw Exception::Circuit::Parser::CircuitParserException("The Krom-C leaf on line " + std::to_string(line) + " is invalid!");

                if (!Other::Parser::isWhitespaceExcludingNewLineSymbol(*begin))
                    throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A whitespace (excluding \\n)",
                                                                                                    Other::Parser::convertCharToString(*begin), line);

                unsigned int beginLineTmp = line;

                ClauseIdType numberOfLinesTmp = Other::Parser::parsePositiveNumber<ClauseIdType>(begin, end, line);
                VarT numberOfVariablesTmp = Other::Parser::parsePositiveNumber<VarT>(begin, end, line);

                if (numberOfVariablesTmp == 0)
                    throw Exception::Circuit::Parser::CircuitParserException("The Krom-C leaf on line " + std::to_string(line) + " must have at least one variable!");

                VariableVectorType variableVector = Other::Parser::parseAllPositiveNumbersOnLine<VarT, InputIterator>(begin, end, line, numberOfVariablesTmp);

                // Invalid number of variables
                if (numberOfVariablesTmp != variableVector.size())
                    throw Exception::Circuit::Parser::CircuitParserException("The Krom-C leaf on line " + std::to_string(line) + " has an invalid number of variables!");

                // Set a mapping function
                VariableSetType seenVariableSet(variableVector.size());
                MappingFromVariableToVariableType mappingFromIndexToVar(variableVector.size());
                for (VarT i = 0; i < variableVector.size(); ++i) {
                    VarT var = variableVector[i];

                    // The variable has already been seen
                    if (Other::containInSet(seenVariableSet, var))
                        throw Exception::Circuit::Parser::CircuitParserException("The variable (" + std::to_string(var) + ") is mentioned multiple times on line " + std::to_string(line) + " in the mapping!");

                    seenVariableSet.emplace(var);

                    // Mapping function is needed
                    if (var != (i + 1))
                        mappingFromIndexToVar[(i + 1)] = var;
                }

                if (Other::Parser::parseNewLineSymbol(begin, end, line))
                    throw Exception::Parser::SomethingIsExpectedButEndOfStreamIsDetectedException("A new line (\\n)");

                DimacsCnfHeaderStruct dimacsCnfHeaderTmp = Other::Parser::parseDimacsCnfHeader(begin, end, line);
                VarT numberOfVariablesDimacsCnfHeader = static_cast<VarT>(dimacsCnfHeaderTmp.numberOfVariables);
                ClauseIdType numberOfClausesDimacsCnfHeader = static_cast<ClauseIdType>(dimacsCnfHeaderTmp.numberOfClauses);

                if (numberOfVariablesTmp != numberOfVariablesDimacsCnfHeader)
                    std::cerr << "WARNING: the number of variables does not match the DIMACS CNF header value on line " << std::to_string(line) << "!" << std::endl;

                FormulaType formula;
                formula.reserve(numberOfClausesDimacsCnfHeader);

                for (ClauseIdType idClause = 0; idClause < numberOfClausesDimacsCnfHeader; ++idClause) {
                    // The end of the stream
                    if (begin == end)
                        throw Exception::Parser::SomethingIsExpectedButEndOfStreamIsDetectedException("A clause");

                    LiteralVectorType clauseTmp = Other::Parser::parseDimacsClause<VarT, LiteralT, InputIterator>(begin, end, line,
                                                                                                                  S_ESTIMATED_SIZE_OF_CLAUSE_IN_FORMULA_LEAF_,
                                                                                                                  mappingFromIndexToVar);
                    ClauseType clause(std::move(clauseTmp));
                    formula.push_back(std::move(clause));
                }

                // Invalid number of lines
                if (line != (beginLineTmp + numberOfLinesTmp + 1))
                    std::cerr << "WARNING: the number of lines does not match on line " << std::to_string(beginLineTmp) << "!" << std::endl;

                circuit.createKromCLeaf(std::move(formula));
                continue;
            }

            // renH-C leaf
            // R l n l_1 ... l_n
            else if (Other::Parser::toUppercase(*begin) == Node::RENH_C_LEAF) {
                ++begin;   // R

                if (begin == end)
                    throw Exception::Circuit::Parser::CircuitParserException("The renH-C leaf on line " + std::to_string(line) + " is invalid!");

                if (!Other::Parser::isWhitespaceExcludingNewLineSymbol(*begin))
                    throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A whitespace (excluding \\n)",
                                                                                                    Other::Parser::convertCharToString(*begin), line);

                unsigned int beginLineTmp = line;

                ClauseIdType numberOfLinesTmp = Other::Parser::parsePositiveNumber<ClauseIdType>(begin, end, line);
                VarT numberOfVariablesTmp = Other::Parser::parsePositiveNumber<VarT>(begin, end, line);

                if (numberOfVariablesTmp == 0)
                    throw Exception::Circuit::Parser::CircuitParserException("The renH-C leaf on line " + std::to_string(line) + " must have at least one variable!");

                LiteralVectorType literalVector = Other::Parser::parseAllLiteralsOnLine<VarT, LiteralT, InputIterator>(begin, end, line, numberOfVariablesTmp);

                // Invalid number of variables
                if (numberOfVariablesTmp != literalVector.size())
                    throw Exception::Circuit::Parser::CircuitParserException("The renH-C leaf on line " + std::to_string(line) + " has an invalid number of variables!");

                // Set a mapping function and switched variables
                VariableSetType seenVariableSet(literalVector.size());
                VariableSetType switchedVariables(literalVector.size());
                MappingFromVariableToVariableType mappingFromIndexToVar(literalVector.size());
                for (VarT i = 0; i < literalVector.size(); ++i) {
                    VarT var = literalVector[i].getVariable();

                    // The variable has already been seen
                    if (Other::containInSet(seenVariableSet, var))
                        throw Exception::Circuit::Parser::CircuitParserException("The variable (" + std::to_string(var) + ") is mentioned multiple times on line " + std::to_string(line) + " in the mapping!");

                    seenVariableSet.emplace(var);

                    // Switched variable
                    if (literalVector[i].isNegative())
                        switchedVariables.emplace(var);

                    // Mapping function is needed
                    if (var != (i + 1))
                        mappingFromIndexToVar[(i + 1)] = var;
                }

                if (Other::Parser::parseNewLineSymbol(begin, end, line))
                    throw Exception::Parser::SomethingIsExpectedButEndOfStreamIsDetectedException("A new line (\\n)");

                DimacsCnfHeaderStruct dimacsCnfHeaderTmp = Other::Parser::parseDimacsCnfHeader(begin, end, line);
                VarT numberOfVariablesDimacsCnfHeader = static_cast<VarT>(dimacsCnfHeaderTmp.numberOfVariables);
                ClauseIdType numberOfClausesDimacsCnfHeader = static_cast<ClauseIdType>(dimacsCnfHeaderTmp.numberOfClauses);

                if (numberOfVariablesTmp != numberOfVariablesDimacsCnfHeader)
                    std::cerr << "WARNING: the number of variables does not match the DIMACS CNF header value on line " << std::to_string(line) << "!" << std::endl;

                FormulaType formula;
                formula.reserve(numberOfClausesDimacsCnfHeader);

                for (ClauseIdType idClause = 0; idClause < numberOfClausesDimacsCnfHeader; ++idClause) {
                    // The end of the stream
                    if (begin == end)
                        throw Exception::Parser::SomethingIsExpectedButEndOfStreamIsDetectedException("A clause");

                    LiteralVectorType clauseTmp = Other::Parser::parseDimacsClause<VarT, LiteralT, InputIterator>(begin, end, line,
                                                                                                                  S_ESTIMATED_SIZE_OF_CLAUSE_IN_FORMULA_LEAF_,
                                                                                                                  mappingFromIndexToVar);
                    ClauseType clause(std::move(clauseTmp));
                    formula.push_back(std::move(clause));
                }

                // Invalid number of lines
                if (line != (beginLineTmp + numberOfLinesTmp + 1))
                    std::cerr << "WARNING: the number of lines does not match on line " << std::to_string(beginLineTmp) << "!" << std::endl;

                // switchedVariables.shrink_to_fit();
                circuit.createRenHCLeaf(std::move(formula), std::move(switchedVariables));
                continue;
            }

            // Invalid char
            else {
                throw Exception::Circuit::Parser::CircuitParserException("Invalid line " + std::to_string(line) + " (" + Other::Parser::convertCharToString(*begin) + "...) has occurred!");
            }
        }

        if (circuit.getNumberOfNodes() != numberOfNodes)
            std::cerr << "WARNING: the number of nodes does not match the header value!" << std::endl;
        if (circuit.getNumberOfEdges() != numberOfEdges)
            std::cerr << "WARNING: the number of edges does not match the header value!" << std::endl;
        if (circuit.getCircuitSize() != size)
            std::cerr << "WARNING: the size does not match the header value!" << std::endl;

        circuit.setRoot();
        return circuit;
    }

    Circuit<char32_t, char32_t> parseCircuitFromFile(const std::string& fileName) {
        // File does not exist
        if (!std::filesystem::exists(fileName))
            throw Exception::FileDoesNotExistException(fileName);

        {
            std::ifstream fileStream(fileName, std::ios::in);

            // File cannot be opened
            if (!fileStream.is_open())
                throw Exception::FileCannotBeOpenedException(fileName);

            std::istreambuf_iterator<char> begin(fileStream);
            std::istreambuf_iterator<char> end;

            unsigned int line = 1;

            DimacsNnfHeaderStruct header = parseDimacsNnfHeader(begin, end, line);
            return parseCircuit<char32_t, char32_t, std::istreambuf_iterator<char>>(begin, end, header, line);
        }
    }
}   // namespace Hydra::Circuit::Parser
