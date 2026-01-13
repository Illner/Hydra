#include "./StatisticsAbstract.hpp"

namespace Hydra::Statistics {

    void StatisticsAbstract::printStatistics(std::ostream& out, bool addLabels) const {
        if (addLabels)
            Other::printTitle(out, name_, 75, '-');

        processPrintStatistics(out, name_, addLabels);
    }
}   // namespace Hydra::Statistics
