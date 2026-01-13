#include "./CustomArbitraryPrecisionInteger.hpp"

namespace Hydra::Type::ArbitraryPrecisionInteger::Custom {

    CustomArbitraryPrecisionInteger::PositionType CustomArbitraryPrecisionInteger::size() const noexcept {
        return digitVector_.size();
    }

    bool CustomArbitraryPrecisionInteger::isZero() const noexcept {
        if ((digitVector_.size() == 1) && (digitVector_[0] == static_cast<DigitType>(0)))
            return true;

        return false;
    }

    LargeNumberType CustomArbitraryPrecisionInteger::getCurrentByteSize() const noexcept {
        return S_DIGIT_BYTE_SIZE * static_cast<LargeNumberType>(digitVector_.capacity());
    }

    void CustomArbitraryPrecisionInteger::requestRemoveFreeSpace() {
        digitVector_.shrink_to_fit();
    }

    CustomArbitraryPrecisionInteger& CustomArbitraryPrecisionInteger::operator++() {
        PositionType i = 0;
        PositionType size = digitVector_.size();

        for (; (i < size) && (digitVector_[i] == static_cast<DigitType>(9)); ++i)
            digitVector_[i] = static_cast<DigitType>(0);

        if (i == size)
            digitVector_.push_back(static_cast<DigitType>(1));
        else
            ++digitVector_[i];

        return *this;
    }

    std::ostream& operator<<(std::ostream& out, const CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger) {
        for (auto it = customArbitraryPrecisionInteger.digitVector_.crbegin();
             it != customArbitraryPrecisionInteger.digitVector_.crend(); ++it)
            out << std::to_string(static_cast<int>(*it));

        return out;
    }

    CustomArbitraryPrecisionInteger& operator+=(CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger1,
                                                const CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger2) {
        using DigitType = CustomArbitraryPrecisionInteger::DigitType;
        using PositionType = CustomArbitraryPrecisionInteger::PositionType;

        DigitType s;
        bool carryFlag = false;

        PositionType size1 = customArbitraryPrecisionInteger1.size();
        PositionType size2 = customArbitraryPrecisionInteger2.size();

        assert(size1 > 0);
        assert(size2 > 0);

        if (size2 > size1) {
            customArbitraryPrecisionInteger1.digitVector_.append(size2 - size1, static_cast<DigitType>(0));
            size1 = customArbitraryPrecisionInteger1.size();
        }

        assert(customArbitraryPrecisionInteger1.size() >= customArbitraryPrecisionInteger2.size());

        for (PositionType i = 0; i < size1; ++i) {
            if (i < size2)
                s = customArbitraryPrecisionInteger1.digitVector_[i] + customArbitraryPrecisionInteger2.digitVector_[i];
            else {
                if (!carryFlag)
                    break;

                s = customArbitraryPrecisionInteger1.digitVector_[i];
            }

            if (carryFlag)
                ++s;

            carryFlag = static_cast<bool>(s / 10);
            customArbitraryPrecisionInteger1.digitVector_[i] = static_cast<DigitType>(s % 10);
        }

        if (carryFlag)
            customArbitraryPrecisionInteger1.digitVector_.push_back(static_cast<DigitType>(1));

        assert((customArbitraryPrecisionInteger1.digitVector_.size() == 1) || (customArbitraryPrecisionInteger1.digitVector_.back() != static_cast<DigitType>(0)));   // no leading zeros

        return customArbitraryPrecisionInteger1;
    }

    CustomArbitraryPrecisionInteger& operator*=(CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger1,
                                                const CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger2) {
        using DigitType = CustomArbitraryPrecisionInteger::DigitType;
        using PositionType = CustomArbitraryPrecisionInteger::PositionType;

        if (customArbitraryPrecisionInteger1.isZero())
            return customArbitraryPrecisionInteger1;

        if (customArbitraryPrecisionInteger2.isZero()) {
            customArbitraryPrecisionInteger1 = CustomArbitraryPrecisionInteger();

            assert(customArbitraryPrecisionInteger1.isZero());

            return customArbitraryPrecisionInteger1;
        }

        PositionType size1 = customArbitraryPrecisionInteger1.size();
        PositionType size2 = customArbitraryPrecisionInteger2.size();

        assert(size1 > 0);
        assert(size2 > 0);

        std::vector<LargeNumberType> tmpVector(size1 + size2, 0);

        for (PositionType i = 0; i < size1; ++i) {
            for (PositionType j = 0; j < size2; ++j)
                tmpVector[i + j] += (static_cast<LargeNumberType>(customArbitraryPrecisionInteger1.digitVector_[i]) * static_cast<LargeNumberType>(customArbitraryPrecisionInteger2.digitVector_[j]));
        }

        size1 = tmpVector.size();
        customArbitraryPrecisionInteger1.digitVector_.resize(size1, static_cast<DigitType>(0));

        LargeNumberType s;
        LargeNumberType carry = 0;

        for (PositionType i = 0; i < size1; ++i) {
            s = carry + tmpVector[i];
            tmpVector[i] = s % 10;
            carry = s / 10;
            customArbitraryPrecisionInteger1.digitVector_[i] = static_cast<DigitType>(tmpVector[i]);
        }

        for (auto it = tmpVector.crbegin(); it != tmpVector.crend(); ++it) {
            if (*it > 0)
                break;

            customArbitraryPrecisionInteger1.digitVector_.pop_back();
        }

        assert(customArbitraryPrecisionInteger1.digitVector_.back() != static_cast<DigitType>(0));   // no leading zeros

        return customArbitraryPrecisionInteger1;
    }

    bool operator==(const CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger1,
                    const CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger2) {
        return (customArbitraryPrecisionInteger1.digitVector_ == customArbitraryPrecisionInteger2.digitVector_);
    }

    bool operator!=(const CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger1,
                    const CustomArbitraryPrecisionInteger& customArbitraryPrecisionInteger2) {
        return (customArbitraryPrecisionInteger1.digitVector_ != customArbitraryPrecisionInteger2.digitVector_);
    }
}   // namespace Hydra::Type::ArbitraryPrecisionInteger::Custom
