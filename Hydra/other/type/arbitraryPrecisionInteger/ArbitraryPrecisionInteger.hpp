#pragma once

#include <boost/multiprecision/gmp.hpp>

#include "Hydra/other/type/arbitraryPrecisionInteger/custom/CustomArbitraryPrecisionInteger.hpp"

namespace Hydra::Type::ArbitraryPrecisionInteger {

    // mpz_int
    using MpzIntType = boost::multiprecision::mpz_int;

    // Custom
    using CustomType = Hydra::Type::ArbitraryPrecisionInteger::Custom::CustomArbitraryPrecisionInteger;
}   // namespace Hydra::Type::ArbitraryPrecisionInteger
