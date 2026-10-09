#pragma once

#include <string>

namespace HydraTest::Other::CanBeSavedAsTypeT {
    inline std::string canBeSavedAsTypeTVariablesResult = "char8_t - 254: 1\n"
                                                          "char8_t - 255: 0\n"
                                                          "\n"
                                                          "char16_t - 65534: 1\n"
                                                          "char16_t - 65535: 0\n"
                                                          "\n"
                                                          "char32_t - 4294967294: 1\n"
                                                          "char32_t - 4294967295: 0\n"
                                                          "\n";

    inline std::string canBeSavedAsTypeTVariablesForCacheResult = "char8_t - 255: 1\n"
                                                                  "char8_t - 256: 0\n"
                                                                  "\n"
                                                                  "char16_t - 65535: 1\n"
                                                                  "char16_t - 65536: 0\n"
                                                                  "\n"
                                                                  "char32_t - 4294967295: 1\n"
                                                                  "char32_t - 4294967296: 0\n"
                                                                  "\n";

    inline std::string canBeSavedAsTypeTLiteralsResult = "char8_t - 126: 1\n"
                                                         "char8_t - 127: 0\n"
                                                         "\n"
                                                         "char16_t - 32766: 1\n"
                                                         "char16_t - 32767: 0\n"
                                                         "\n"
                                                         "char32_t - 2147483646: 1\n"
                                                         "char32_t - 2147483647: 0\n"
                                                         "\n";

    inline std::string canBeSavedAsTypeTLiteralsForCacheResult = "char8_t - 127: 1\n"
                                                                 "char8_t - 128: 0\n"
                                                                 "\n"
                                                                 "char16_t - 32767: 1\n"
                                                                 "char16_t - 32768: 0\n"
                                                                 "\n"
                                                                 "char32_t - 2147483647: 1\n"
                                                                 "char32_t - 2147483648: 0\n"
                                                                 "\n";

    inline std::string canBeSavedAsTypeTClauseIdentifiersResult = "char8_t - 255: 1\n"
                                                                  "char8_t - 256: 0\n"
                                                                  "\n"
                                                                  "char16_t - 65535: 1\n"
                                                                  "char16_t - 65536: 0\n"
                                                                  "\n"
                                                                  "char32_t - 4294967295: 1\n"
                                                                  "char32_t - 4294967296: 0\n"
                                                                  "\n";
}   // namespace HydraTest::Other::CanBeSavedAsTypeT
