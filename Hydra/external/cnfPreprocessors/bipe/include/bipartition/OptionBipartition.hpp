#pragma once

#include <iostream>
#include <string>

#include "../optree/OptionGroup.hpp"

namespace bipe {
    namespace bipartition {

        class OptionBipartition : public optree::OptionGroup {
        public:
            optree::Option<bool> useCore {
                "use-core", "Use core extraction for forcing equivalence.", true
            };
            optree::Option<bool> useModel {
                "use-model", "Use the computed model to spot new input variables.", true
            };
            optree::Option<std::string> heuristicSorting {
                "sorting",
                "The order we use for selecting the variable we first try to put in the "
                "output set (OCC_ASC - w.r.t the occurrence, RANDOM, NATURAL_ORDER or "
                "GEN_TAUTS - w.r.t. the number of tautological clause generated).",
                "OCC_ASC"
            };
            optree::Option<std::string> solverName {
                "solver-name", "The SAT solver used to compute the backbone", "cadical"
            };
            optree::Option<unsigned> solverNbConflict {
                "solver-nbConflict",
                "The number of conflicts the SAT solver used to compute the backbone is "
                "authorized to do",
                0
            };

            OptionBipartition()
                : optree::OptionGroup("bipartition", "Bipartition options") { }

            std::vector<optree::OptionBase*> getAllOptions() override {
                return { &heuristicSorting, &useCore, &useModel,
                         &solverName, &solverNbConflict };
            }

            friend std::ostream& operator<<(std::ostream& os,
                                            const OptionBipartition& ob) {
                os << "[OPTION] Bipartition Options: use-model(" << ob.useModel.get()
                   << ") use-core(" << ob.useCore.get() << ") sorting-heuristic("
                   << ob.heuristicSorting.get() << ") sat-solver(" << ob.solverName.get()
                   << ",";

                if (ob.solverNbConflict.get())
                    os << ob.solverNbConflict.get();
                else
                    os << "\u221E";
                os << ")";
                return os;
            }
        };

    }   // namespace bipartition
}   // namespace bipe
