#pragma once

#include <cassert>
#include <cctype>
#include <ostream>
#include <string>
#include <vector>

#include "Hydra/other/Other.hpp"

#include "Hydra/compiler/exceptions/ParserException.hpp"

namespace Hydra::Type::ArbitraryPrecisionInteger::Custom {

    using LargeNumberType = Hydra::Other::LargeNumberType;

    /**
     * Custom arbitrary-precision integer type
     * Adapted from https://www.geeksforgeeks.org/bigint-big-integers-in-c-with-example/
     * Copy methods are disabled! Move methods (default) are allowed!
     * Exception:
     *      SomethingIsExpectedButAnotherSymbolIsDetectedException
     */
    class CustomArbitraryPrecisionInteger {
    private:
        using DigitType = char8_t;
        using DigitVectorType = std::basic_string<DigitType>;

    public:
        using PositionType = DigitVectorType::size_type;

    public:
        CustomArbitraryPrecisionInteger()
            : digitVector_() {
            digitVector_.reserve(static_cast<PositionType>(1));
            digitVector_.push_back(static_cast<DigitType>(0));
        }

        explicit CustomArbitraryPrecisionInteger(const std::string& number)
            : digitVector_() {
            assert(!number.empty());   // at least one digit

            digitVector_.reserve(number.size());

            for (auto it = number.crbegin(); it != number.crend(); ++it) {
                // Not a digit
                if (!isdigit(*it))
                    throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A digit", std::string(1, *it));

                digitVector_.push_back(static_cast<DigitType>(*it - '0'));
            }

            assert((digitVector_.size() == 1) || (digitVector_.back() != static_cast<DigitType>(0)));   // no leading zeros
        }

        CustomArbitraryPrecisionInteger(const CustomArbitraryPrecisionInteger&) = delete;
        CustomArbitraryPrecisionInteger(CustomArbitraryPrecisionInteger&&) noexcept = default;

        CustomArbitraryPrecisionInteger& operator=(const CustomArbitraryPrecisionInteger&) = delete;
        CustomArbitraryPrecisionInteger& operator=(CustomArbitraryPrecisionInteger&&) noexcept = default;

    private:
        DigitVectorType digitVector_;

    public:
        inline static constexpr LargeNumberType S_DIGIT_BYTE_SIZE = static_cast<LargeNumberType>(sizeof(DigitType));

    public:
        /**
         * @return the number of digits
         */
        PositionType size() const noexcept;

        /**
         * @return true if the number is 0. Otherwise, false is returned.
         */
        bool isZero() const noexcept;

        /**
         * @return the current size (in bytes) of the number
         */
        LargeNumberType getCurrentByteSize() const noexcept;

        /**
         * Request to remove the free space
         * Note: shrink_to_fit
         */
        void requestRemoveFreeSpace();

    public:
        /**
         * ++CustomArbitraryPrecisionInteger
         */
        CustomArbitraryPrecisionInteger& operator++();

        /**
         * ostream << CustomArbitraryPrecisionInteger
         */
        friend std::ostream& operator<<(std::ostream& out, const CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger);

        /**
         * CustomArbitraryPrecisionInteger_1 += CustomArbitraryPrecisionInteger_2
         */
        friend CustomArbitraryPrecisionInteger& operator+=(CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger1,
                                                           const CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger2);

        /**
         * CustomArbitraryPrecisionInteger_1 *= CustomArbitraryPrecisionInteger_2
         */
        friend CustomArbitraryPrecisionInteger& operator*=(CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger1,
                                                           const CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger2);

        /**
         * CustomArbitraryPrecisionInteger_1 == CustomArbitraryPrecisionInteger_2
         */
        friend bool operator==(const CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger1,
                               const CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger2);

        /**
         * CustomArbitraryPrecisionInteger_1 != CustomArbitraryPrecisionInteger_2
         */
        friend bool operator!=(const CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger1,
                               const CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger2);
    };
}   // namespace Hydra::Type::ArbitraryPrecisionInteger::Custom
