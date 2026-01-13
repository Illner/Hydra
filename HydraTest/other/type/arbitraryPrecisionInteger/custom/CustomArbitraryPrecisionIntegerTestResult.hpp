#pragma once

#include <string>

namespace HydraTest::Type::ArbitraryPrecisionInteger::Custom {
    inline std::string customArbitraryPrecisionIntegerConstructorResult = "0\n";

    inline std::string customArbitraryPrecisionIntegerConstructorStringResult = "0\n"
                                                                                "1\n"
                                                                                "9\n"
                                                                                "10\n"
                                                                                "99\n"
                                                                                "100\n"
                                                                                "12345\n"
                                                                                "354224848179261915075\n"
                                                                                "896519947090131496687170070074100632420837521538745909320\n"
                                                                                "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000\n";

    inline std::string customArbitraryPrecisionIntegerSizeResult = "0: 1 digits\n"
                                                                   "1: 1 digits\n"
                                                                   "9: 1 digits\n"
                                                                   "10: 2 digits\n"
                                                                   "99: 2 digits\n"
                                                                   "100: 3 digits\n"
                                                                   "999: 3 digits\n"
                                                                   "354224848179261915075: 21 digits\n"
                                                                   "896519947090131496687170070074100632420837521538745909320: 57 digits\n"
                                                                   "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000: 158 digits\n";

    inline std::string customArbitraryPrecisionIntegerIsZeroResult = "0: 1\n"
                                                                     "10: 0\n"
                                                                     "99: 0\n"
                                                                     "100: 0\n"
                                                                     "999: 0\n"
                                                                     "1000: 0\n"
                                                                     "9999: 0\n";

    inline std::string customArbitraryPrecisionIntegerIncrementResult = "0 -> 1\n"
                                                                        "1 -> 2\n"
                                                                        "9 -> 10\n"
                                                                        "10 -> 11\n"
                                                                        "89 -> 90\n"
                                                                        "98 -> 99\n"
                                                                        "99 -> 100\n"
                                                                        "199 -> 200\n";

    inline std::string customArbitraryPrecisionIntegerAdditionAssignmentResult = "0 + 0 = 0\n"
                                                                                 "0 + 1 = 1\n"
                                                                                 "1 + 0 = 1\n"
                                                                                 "5 + 4 = 9\n"
                                                                                 "1 + 9 = 10\n"
                                                                                 "9 + 1 = 10\n"
                                                                                 "1 + 998 = 999\n"
                                                                                 "998 + 1 = 999\n"
                                                                                 "999 + 1 = 1000\n"
                                                                                 "1 + 999 = 1000\n"
                                                                                 "11998 + 2 = 12000\n"
                                                                                 "2 + 11998 = 12000\n"
                                                                                 "12345 + 67890 = 80235\n";

    inline std::string customArbitraryPrecisionIntegerAdditionAssignmentBigNumbersResult = "437845991669110338052\n"
                                                                                           "896520947224732297041951999473351168962701883999835860120\n"
                                                                                           "933263146117376397766681598134068546800960840827464865953725083328230838424521965180914627451041219863285961283366976548266157749043200000000000000000000000\n";

    inline std::string customArbitraryPrecisionIntegerMultiplicationAssignmentResult = "0 * 0 = 0\n"
                                                                                       "0 * 1 = 0\n"
                                                                                       "1 * 0 = 0\n"
                                                                                       "5 * 4 = 20\n"
                                                                                       "12 * 6 = 72\n"
                                                                                       "6 * 12 = 72\n"
                                                                                       "15 * 7 = 105\n"
                                                                                       "7 * 15 = 105\n"
                                                                                       "999 * 9 = 8991\n"
                                                                                       "9 * 999 = 8991\n"
                                                                                       "12345 * 67890 = 838102050\n"
                                                                                       "99999 * 99999 = 9999800001\n";

    inline std::string customArbitraryPrecisionIntegerMultiplicationAssignmentBigNumbersResult = "11314095609359007101349623352635875567872\n"
                                                                                                 "3336348064712955638079545630499241256216976633136092548404393313529241762197397298284315300156745021047800876000\n"
                                                                                                 "906798607502512246711246682652591245954673580157464162779717660655553681147340580186316587471577756605915929107839850522995809404229464318569529627079690056055034982408264229390736159053655995598884733693803993697328552637814579609136374231512792061323756385075200000000000000000000000000000000000000000000\n";
}   // namespace HydraTest::Type::ArbitraryPrecisionInteger::Custom
