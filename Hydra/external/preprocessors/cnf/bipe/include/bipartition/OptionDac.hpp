/**
 * bipe
 *  Copyright (C) 2021  Lagniez Jean-Marie
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include <iostream>
#include <string>

#include "../optree/OptionGroup.hpp"

namespace bipe {
    namespace bipartition {

        class OptionDac : public optree::OptionGroup {
        public:
            optree::Option<std::string> nameSolver {
                "solver-name", "The SAT solver used by the DAC approach.", "glucose"
            };
            optree::Option<bool> computeEquiv { "compute-equiv", "Compute equivalences",
                                                true };
            optree::Option<bool> computeOr { "compute-or", "Compute OR gates", true };
            optree::Option<bool> computeXor { "compute-xor", "Compute XOR gates", true };
            optree::Option<unsigned> maxXorSize {
                "max-xor-size", "Maximum XOR gate size for DAC extraction.", 5
            };

            OptionDac() : optree::OptionGroup("dac", "DAC options") { }

            std::vector<optree::OptionBase*> getAllOptions() override {
                return { &nameSolver, &computeEquiv, &computeOr, &computeXor, &maxXorSize };
            }

            friend std::ostream& operator<<(std::ostream& os, const OptionDac& od) {
                os << "[OPTION] DAC options: verbosity(" << od.verbosity.get()
                   << ") sat-solver(" << od.nameSolver.get() << ")";
                return os;
            }
        };

    }   // namespace bipartition
}   // namespace bipe
