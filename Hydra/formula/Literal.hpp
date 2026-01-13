#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"
#include "Hydra/other/std/Std.hpp"

namespace Hydra::Formula {

    using OriginalLiteralType = long int;        // signed
    using OriginalVarType = unsigned long int;   // unsigned

    // Forward declaration
    template <typename VarT2, typename LiteralT2>
    class Literal;

    /**
     * @return a new zero literal
     */
    template <typename VarT2, typename LiteralT2>
    inline Literal<VarT2, LiteralT2> createZeroLiteral() noexcept;

    /**
     * @return a new literal based on the LiteralT
     */
    template <typename VarT2, typename LiteralT2>
    inline Literal<VarT2, LiteralT2> createLiteralFromLiteralT(LiteralT2 literalT) noexcept;

    /**
     * @return the positive literal as a type LiteralT
     */
    template <typename VarT2, typename LiteralT2>
    inline LiteralT2 getPositiveLiteralT(VarT2 var) noexcept;

    /**
     * @return the negative literal as a type LiteralT
     */
    template <typename VarT2, typename LiteralT2>
    inline LiteralT2 getNegativeLiteralT(VarT2 var) noexcept;

    /**
     * Literal representation
     * Copy (default) and move (default = copy) methods are allowed!
     * Note: zero literal (+0) represents the end of a clause
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class Literal {
    public:
        using LiteralType = Literal<VarT, LiteralT>;
        using VariableVectorType = std::vector<VarT>;
        using LiteralVectorType = std::vector<LiteralType>;
        using VariableSortedVectorType = std::vector<VarT>;
        using LiteralSortedVectorType = std::vector<LiteralType>;
        using VariableSetType = Other::HashMap::SetType<VarT>;
        using LiteralTSetType = Other::HashMap::SetType<LiteralT>;
        using LiteralSetType = Other::HashMap::SetType<LiteralType>;
        using OriginalVariableSetType = Other::HashMap::SetType<OriginalVarType>;
        using OriginalLiteralSetType = Other::HashMap::SetType<OriginalLiteralType>;
        using MappingFromVariableToVariableType = Other::HashMap::MapType<VarT, VarT>;
        using MappingFromVariableToLiteralType = Other::HashMap::MapType<VarT, LiteralType>;
        using MappingFromVariableToOriginalVariableType = Other::HashMap::MapType<VarT, OriginalVarType>;
        using MappingFromOriginalVariableToVariableType = Other::HashMap::MapType<OriginalVarType, VarT>;

    public:
        using isValidVarT = std::bool_constant<(std::is_same<VarT, char8_t>::value ||
                                                std::is_same<VarT, char16_t>::value ||
                                                std::is_same<VarT, char32_t>::value)>;
        using isValidLiteralT = std::bool_constant<(std::is_same<LiteralT, char8_t>::value ||
                                                    std::is_same<LiteralT, char16_t>::value ||
                                                    std::is_same<LiteralT, char32_t>::value)>;

        static_assert(isValidVarT::value, "Invalid VarT type!");
        static_assert(isValidLiteralT::value, "Invalid LiteralT type!");

    public:
        /**
         * Standard literal
         */
        explicit Literal(VarT var, bool isPositive = true) noexcept
            : variable_(var), isPositive_(isPositive) {
            assert(var > 0);
        }

        Literal(const Literal&) = default;
        Literal(Literal&&) noexcept = default;

        Literal& operator=(const Literal&) = default;
        Literal& operator=(Literal&&) noexcept = default;

    private:
        /**
         * Zero literal
         */
        Literal() noexcept
            : variable_(0), isPositive_(true) { }

    private:
        VarT variable_;
        bool isPositive_;

    public:
        /**
         * Getter
         * @return the variable
         */
        VarT getVariable() const noexcept;

        /**
         * Getter
         * @return true if the literal is positive. Otherwise, false is returned.
         */
        bool isPositive() const noexcept;

        /**
         * Getter
         * @return true if the literal is negative. Otherwise, false is returned.
         */
        bool isNegative() const noexcept;

        /**
         * Setter
         * Make the literal positive
         */
        void makePositive() noexcept;

        /**
         * Setter
         * Make the literal negative
         */
        void makeNegative() noexcept;

        /**
         * Note: used mainly for generating keys
         * @return the literal as a type LiteralT
         */
        LiteralT getLiteralT() const noexcept;

        /**
         * @return the complementary literal as a type LiteralT
         */
        LiteralT getComplementaryLiteralT() const noexcept;

        /**
         * @return the literal as a string
         */
        std::string toString() const noexcept;

        /**
         * @return true if the literal is a zero literal. Otherwise, false is returned.
         */
        bool isZeroLiteral() const noexcept;

        /**
         * Print the literal
         */
        void printLiteral(std::ostream& out, const MappingFromVariableToOriginalVariableType& mapping) const;

    public:
        /**
         * ostream << Literal
         */
        friend std::ostream& operator<<(std::ostream& out, const Literal& lit) {
            lit.printLiteral(out, {});
            return out;
        }

        /**
         * Negation (~Literal)
         */
        friend Literal<VarT, LiteralT> operator~(const Literal<VarT, LiteralT>& lit) noexcept {
            assert(lit.variable_);   // zero literal

            return Literal<VarT, LiteralT>(lit.variable_, !(lit.isPositive_));
        }

        /**
         * Negation (!Literal)
         */
        friend Literal<VarT, LiteralT> operator!(const Literal<VarT, LiteralT>& lit) noexcept {
            assert(lit.variable_);   // zero literal

            return Literal<VarT, LiteralT>(lit.variable_, !(lit.isPositive_));
        }

        /**
         * Literal_1 == Literal_2
         */
        friend bool operator==(const Literal<VarT, LiteralT>& lit1, const Literal<VarT, LiteralT>& lit2) noexcept {
            assert(lit1.variable_);
            assert(lit2.variable_);   // zero literal

            return (lit1.variable_ == lit2.variable_) && (lit1.isPositive_ == lit2.isPositive_);
        }

        /**
         * Literal_1 != Literal_2
         */
        friend bool operator!=(const Literal<VarT, LiteralT>& lit1, const Literal<VarT, LiteralT>& lit2) noexcept {
            // assert(lit1.variable_);
            // assert(lit2.variable_);   // zero literal

            return (lit1.variable_ != lit2.variable_) || (lit1.isPositive_ != lit2.isPositive_);
        }

        /**
         * Literal_1 < Literal_2
         * Note: -1 < 1
         */
        friend bool operator<(const Literal<VarT, LiteralT>& lit1, const Literal<VarT, LiteralT>& lit2) noexcept {
            assert(lit1.variable_);
            assert(lit2.variable_);   // zero literal

            if (lit1.variable_ < lit2.variable_)
                return true;

            if (lit1.variable_ > lit2.variable_)
                return false;

            return lit1.isPositive_ < lit2.isPositive_;
        }

        /**
         * Literal_1 > Literal_2
         * Note: 1 > -1
         */
        friend bool operator>(const Literal<VarT, LiteralT>& lit1, const Literal<VarT, LiteralT>& lit2) noexcept {
            assert(lit1.variable_);
            assert(lit2.variable_);   // zero literal

            if (lit1.variable_ > lit2.variable_)
                return true;

            if (lit1.variable_ < lit2.variable_)
                return false;

            return lit1.isPositive_ > lit2.isPositive_;
        }

    private:
        template <typename VarT2, typename LiteralT2>
        friend Literal<VarT2, LiteralT2> createZeroLiteral() noexcept;
    };
}   // namespace Hydra::Formula

#include "./Literal.ipp"
