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

#include <vector>

#include "OptionPreproc.hpp"

namespace bipe {

    /**
 * @brief Factory and entry point for all preprocessing methods.
 *
 * `run` converts the caller's integer-encoded CNF into a `Problem`, delegates
 * to the appropriate `PreprocBase` subclass, and converts the result back.
 *
 * Weight-preservation contract (for weighted model counting):
 *   For the SHARP_EQUIV and EQUIV_ORDERED methods, variables whose two-polarity
 *   weights differ must appear in the `protect` vector.  They will never be
 *   placed in the output set and will therefore never be eliminated.
 */
    class PreprocManager {
    public:
        /**
   * @brief Run the configured preprocessing method on a CNF formula.
   *
   * @param nbVar          Total number of variables.
   * @param[in,out] clauses The CNF clauses in DIMACS integer encoding;
   *                        replaced in-place with the simplified formula.
   * @param projected      Variables the problem is projected onto.
   *                       Only these are candidates for the bipartition output.
   * @param protect        Variables that must never be eliminated.
   *                       For WMC: must include every variable with non-uniform
   *                       literal weights.
   * @param optionPreproc  Options for all sub-phases.
   * @param order          Variable ordering for EQUIV_ORDERED.
   *                       order[v] is the position of variable v.
   *                       If empty, natural order (order[v] = v) is used.
   *                       Ignored for all other preprocessing methods.
   */
        void run(unsigned& nbVar, std::vector<std::vector<int>>& clauses,
                 std::vector<int>& projected, std::vector<int> protect,
                 const OptionPreproc& optionPreproc,
                 const std::vector<unsigned>& order = {});
    };

}   // namespace bipe
