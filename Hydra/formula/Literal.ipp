#pragma once

#include "./Literal.hpp"

namespace Hydra::Formula {

    template <typename VarT2, typename LiteralT2>
    Literal<VarT2, LiteralT2> createZeroLiteral() noexcept {
        return Literal<VarT2, LiteralT2>();
    }

    template <typename VarT2, typename LiteralT2>
    Literal<VarT2, LiteralT2> createLiteralFromLiteralT(LiteralT2 literalT) noexcept {
        // Positive literal
        if (literalT % 2 == 0)
            return Literal<VarT2, LiteralT2>(static_cast<VarT2>(literalT / 2), true);
        // Negative literal
        else
            return Literal<VarT2, LiteralT2>(static_cast<VarT2>((literalT - 1) / 2), false);
    }

    template <typename VarT2, typename LiteralT2>
    LiteralT2 getPositiveLiteralT(VarT2 var) noexcept {
        LiteralT2 tmp = static_cast<LiteralT2>(var);
        tmp *= 2;

        return tmp;
    }

    template <typename VarT2, typename LiteralT2>
    LiteralT2 getNegativeLiteralT(VarT2 var) noexcept {
        LiteralT2 tmp = static_cast<LiteralT2>(var);
        tmp *= 2;
        tmp += 1;

        return tmp;
    }

    template <typename VarT, typename LiteralT>
    VarT Literal<VarT, LiteralT>::getVariable() const noexcept {
        return variable_;
    }

    template <typename VarT, typename LiteralT>
    bool Literal<VarT, LiteralT>::isPositive() const noexcept {
        return isPositive_;
    }

    template <typename VarT, typename LiteralT>
    bool Literal<VarT, LiteralT>::isNegative() const noexcept {
        return !isPositive_;
    }

    template <typename VarT, typename LiteralT>
    void Literal<VarT, LiteralT>::makePositive() noexcept {
        assert(variable_ && "Zero literal cannot be modified!");   // zero literal

        isPositive_ = true;
    }

    template <typename VarT, typename LiteralT>
    void Literal<VarT, LiteralT>::makeNegative() noexcept {
        assert(variable_ && "Zero literal cannot be modified!");   // zero literal

        isPositive_ = false;
    }

    template <typename VarT, typename LiteralT>
    LiteralT Literal<VarT, LiteralT>::getLiteralT() const noexcept {
        // Positive literal
        if (isPositive_)
            return getPositiveLiteralT<VarT, LiteralT>(variable_);

        // Negative literal
        return getNegativeLiteralT<VarT, LiteralT>(variable_);
    }

    template <typename VarT, typename LiteralT>
    LiteralT Literal<VarT, LiteralT>::getComplementaryLiteralT() const noexcept {
        // Negative literal
        if (isPositive_)
            return getNegativeLiteralT<VarT, LiteralT>(variable_);

        // Positive literal
        return getPositiveLiteralT<VarT, LiteralT>(variable_);
    }

    template <typename VarT, typename LiteralT>
    std::string Literal<VarT, LiteralT>::toString() const noexcept {
        if (isPositive_)
            return std::to_string(variable_);
        else
            return (std::string) "-" + std::to_string(variable_);
    }

    template <typename VarT, typename LiteralT>
    bool Literal<VarT, LiteralT>::isZeroLiteral() const noexcept {
        return (variable_ == 0);
    }

    template <typename VarT, typename LiteralT>
    void Literal<VarT, LiteralT>::printLiteral(std::ostream& out,
                                               const MappingFromVariableToOriginalVariableType& mapping) const {
        // Mapping is used
        if (auto itTmp = mapping.find(variable_); itTmp != mapping.end()) {
            auto mappedVariableTmp = itTmp->second;

            // Positive literal
            if (isPositive_)
                out << std::to_string(mappedVariableTmp);
            // Negative literal
            else
                out << "-" << std::to_string(mappedVariableTmp);
        }
        // Mapping is NOT used
        else {
            // Positive literal
            if (isPositive_)
                out << std::to_string(variable_);
            // Negative literal
            else
                out << "-" << std::to_string(variable_);
        }
    }
}   // namespace Hydra::Formula
