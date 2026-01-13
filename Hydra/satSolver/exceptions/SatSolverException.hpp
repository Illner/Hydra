#pragma once

#include <string>

#include "Hydra/formula/Literal.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/satSolver/enums/SatSolverTypeEnum.hpp"

namespace Hydra::Exception::SatSolver {

    /**
     * SAT solver exception (main)
     */
    class SatSolverException : public CompilerException {
    public:
        explicit SatSolverException(const std::string& message)
            : CompilerException(message) { }

        explicit SatSolverException(std::string&& message)
            : CompilerException(std::move(message)) { }

        SatSolverException(const std::string& message, const std::string& functionName)
            : CompilerException(message, functionName) { }
    };

    /**
     * The SAT solver does not support unit propagation
     */
    class SatSolverDoesNotSupportUnitPropagationException : public SatSolverException {
    public:
        explicit SatSolverDoesNotSupportUnitPropagationException(Hydra::SatSolver::SatSolverTypeEnum satSolverType)
            : SatSolverException("The SAT solver (" + Hydra::SatSolver::satSolverTypeEnumToString(satSolverType) + ") does not support unit propagation!") { }
    };

    /**
     * The SAT solver does not support VSIDS
     */
    class SatSolverDoesNotSupportVsidsException : public SatSolverException {
    public:
        explicit SatSolverDoesNotSupportVsidsException(Hydra::SatSolver::SatSolverTypeEnum satSolverType)
            : SatSolverException("The SAT solver (" + Hydra::SatSolver::satSolverTypeEnumToString(satSolverType) + ") does not support VSIDS!") { }
    };

    /**
     * Something went wrong while initializing the SAT solver
     */
    class SomethingWentWrongWhileInitializingSatSolverException : public SatSolverException {
    public:
        explicit SomethingWentWrongWhileInitializingSatSolverException(const std::string& message)
            : SatSolverException("Something went wrong while initializing the SAT solver (" + message + ")!") { }
    };

    /**
     * The i-th element of the assignment does not correspond to the i-th element of the partial assignment
     */
    template <typename VarT, typename LiteralT>
    class IthElementOfAssignmentDoesNotCorrespondToIthElementOfPartialAssignmentException : public SatSolverException {
    public:
        IthElementOfAssignmentDoesNotCorrespondToIthElementOfPartialAssignmentException(VarT i, const Hydra::Formula::Literal<VarT, LiteralT>& iThLiteral,
                                                                                        const Hydra::Formula::Literal<VarT, LiteralT>& iThLiteralInPartialAssignment)
            : SatSolverException("The " + std::to_string(i) + "th element (" + iThLiteral.toString() +
                                 ") of the assignment in the SAT solver does not correspond to the " + std::to_string(i) +
                                 "th element (" + iThLiteralInPartialAssignment.toString() + ") of the partial assignment in the formula representation!") { }
    };
}   // namespace Hydra::Exception::SatSolver
