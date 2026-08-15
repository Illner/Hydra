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

        class OptionBackbone : public optree::OptionGroup {
        public:
            optree::Option<unsigned> nbConflict {
                "solver-nbConflict",
                "The number of conflicts the SAT solver used to compute the backbone is "
                "authorized to do",
                0
            };
            optree::Option<bool> reversePolarity {
                "solver-reverse-polarity",
                "When calling the solver when computing the backbone we consider in "
                "priority the negation of the polarity",
                true
            };
            optree::Option<std::string> solverName {
                "solver-name", "The SAT solver used to compute the backbone", "cadical"
            };

            OptionBackbone() : optree::OptionGroup("backbone", "Backbone options") { }

            std::vector<optree::OptionBase*> getAllOptions() override {
                return { &nbConflict, &reversePolarity, &solverName };
            }

            friend std::ostream& operator<<(std::ostream& os, const OptionBackbone& ob) {
                os << "[OPTION] Backbone option: nbConflict(" << ob.nbConflict.get()
                   << ") reversePolarity(" << ob.reversePolarity.get() << ") solverName("
                   << ob.solverName.get() << ")";
                return os;
            }
        };

    }   // namespace bipartition
}   // namespace bipe
