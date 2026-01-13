#pragma once

#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <utility>

#include "Hydra/circuit/Circuit.hpp"
#include "Hydra/circuit/node/NodeAbstract.hpp"
#include "Hydra/circuit/node/leafNode/formulaLeaf/Clause.hpp"
#include "Hydra/circuit/node/leafNode/formulaLeaf/FormulaLeafAbstract.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"
#include "Hydra/other/parser/Parser.hpp"

#include "Hydra/circuit/exceptions/CircuitParserException.hpp"
#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/circuit/node/enums/DecomposabilityTypeEnum.hpp"

namespace Hydra::Circuit::Parser {

    using IdNodeType = Hydra::Circuit::Node::IdNodeType;
    using SizeNodeType = Hydra::Circuit::Node::SizeNodeType;
    using LargeNumberType = Hydra::Circuit::Node::LargeNumberType;

    // number_of_variables number_of_clauses size
    using DimacsCnfHeaderStruct = Other::Parser::DimacsCnfHeaderStruct;

    struct DimacsNnfHeaderStruct {
        LargeNumberType numberOfNodes;
        LargeNumberType numberOfEdges;
        LargeNumberType numberOfVariables;
        LargeNumberType size;
    };

    /**
     * Parse a DIMACS NNF header
     * @return DimacsNnfHeaderStruct(number of nodes, number of edges, number of variables, size)
     * @throw InvalidDimacsNnfHeaderException if the DIMACS NNF header is invalid
     * @throw SomethingCannotBeSavedAsStdSizeTException if the nodes/variables cannot be saved as std::size_t
     */
    template <std::input_iterator InputIterator>
    inline DimacsNnfHeaderStruct parseDimacsNnfHeader(InputIterator& begin, const InputIterator& end, unsigned int& line);

    /**
     * Parse a circuit in the DIMACS NNF format
     * Note: DIMACS NNF header must be already processed
     * @return the parsed circuit
     * @throw ParserCircuitException, SomethingIsExpectedButEndOfStreamIsDetectedException,
     * SomethingIsExpectedButAnotherSymbolIsDetectedException if the DIMACS NNF format is invalid
     */
    template <typename VarT, typename LiteralT, std::input_iterator InputIterator>
    inline Circuit<VarT, LiteralT> parseCircuit(InputIterator& begin, const InputIterator& end,
                                                const DimacsNnfHeaderStruct& dimacsNnfHeaderStruct,
                                                unsigned int& line);

    template <typename VarT, typename LiteralT, std::input_iterator InputIterator>
    inline Circuit<VarT, LiteralT> parseCircuit(InputIterator& begin, const InputIterator& end,
                                                IdNodeType numberOfNodes, LargeNumberType numberOfEdges,
                                                VarT numberOfVariables, LargeNumberType size, unsigned int& line);

    /**
     * Create a circuit from the file
     * Note: VarT = LiteralT = char32_t are implicitly used!
     * @return a circuit
     * @throw FileDoesNotExistException if the file does not exist
     * @throw FileCannotBeOpenedException if the file cannot be opened
     * @throw ParserCircuitException, SomethingIsExpectedButEndOfStreamIsDetectedException,
     * SomethingIsExpectedButAnotherSymbolIsDetectedException if the DIMACS NNF format in the file is invalid
     */
    inline Circuit<char32_t, char32_t> parseCircuitFromFile(const std::string& fileName);
}   // namespace Hydra::Circuit::Parser

#include "./CircuitParser.ipp"
