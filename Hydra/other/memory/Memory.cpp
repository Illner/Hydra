#include "./Memory.hpp"

namespace Hydra::Other::Memory {

    MemorySizeType convertMegabytesToBytes(MemorySizeType memorySizeInMegabytes) {
        assert(memorySizeInMegabytes != NOT_SUPPORTED_VIRTUAL_MEMORY_SIZE_VALUE);   // valid size

        return memorySizeInMegabytes * static_cast<MemorySizeType>(1'048'576);   // 1024 * 1024
    }

    MemorySizeType convertGigabytesToBytes(MemorySizeType memorySizeInGigabytes) {
        assert(memorySizeInGigabytes != NOT_SUPPORTED_VIRTUAL_MEMORY_SIZE_VALUE);   // valid size

        return memorySizeInGigabytes * static_cast<MemorySizeType>(1'073'741'824);   // 1024 * 1024 * 1024
    }

    #if OPERATING_SYSTEM_WINDOWS
    #include "windows.h"   // MUST be before "psapi.h"

    #include "psapi.h"

    MemorySizeType getPeakVirtualMemorySize() {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc), sizeof(pmc));
        return MemorySizeType(pmc.PeakPagefileUsage) / MemorySizeType(1024 * 1024);
    }

    MemorySizeType getCurrentVirtualMemorySize() {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc), sizeof(pmc));
        return MemorySizeType(pmc.PrivateUsage) / MemorySizeType(1024 * 1024);
    }
    #elif OPERATING_SYSTEM_MACOS
    #include <malloc/malloc.h>

    MemorySizeType getPeakVirtualMemorySize() {
        return NOT_SUPPORTED_VIRTUAL_MEMORY_SIZE_VALUE;
    }

    MemorySizeType getCurrentVirtualMemorySize() {
        malloc_statistics_t stats;
        malloc_zone_statistics(nullptr, &stats);
        return MemorySizeType(stats.max_size_in_use) / MemorySizeType(1024 * 1024);
    }
    #elif OPERATING_SYSTEM_LINUX
    MemorySizeType getPeakVirtualMemorySize() {
        return readProcSelfStatusFile(VM_PEAK_START_OF_LINE);
    }

    MemorySizeType getCurrentVirtualMemorySize() {
        return readProcSelfStatusFile(VM_SIZE_START_OF_LINE);
    }

    MemorySizeType readProcSelfStatusFile(std::string_view startLine) {
        assert(startLine == VM_SIZE_START_OF_LINE || startLine == VM_PEAK_START_OF_LINE);   // valid start of the line

        const std::string fileName = "/proc/self/status";
        MemorySizeType memorySize = NOT_SUPPORTED_VIRTUAL_MEMORY_SIZE_VALUE;

        // The file does not exist
        if (!std::filesystem::exists(fileName))
            return memorySize;

        {
            std::ifstream fileStream(fileName, std::ios::in);

            // The file cannot be opened
            if (!fileStream.is_open())
                return memorySize;

            std::string line;
            while (std::getline(fileStream, line)) {
                if (line.starts_with(startLine)) {
                    assert(line.ends_with("kB"));

                    const char* begin = line.data();
                    const char* end = line.data() + line.size();

                    while (begin != end) {
                        if (!Parser::isDigit(*begin))
                            ++begin;
                        else
                            break;
                    }

                    try {
                        memorySize = Parser::parsePositiveNumber<MemorySizeType>(begin, end, 0, false);
                        memorySize /= MemorySizeType(1024);
                    }
                    catch (const Exception::Parser::ParserException& e) {
                    }

                    break;
                }
            }
        }

        return memorySize;
    }
    #else
    MemorySizeType getPeakVirtualMemorySize() {
        return NOT_SUPPORTED_VIRTUAL_MEMORY_SIZE_VALUE;
    }

    MemorySizeType getCurrentVirtualMemorySize() {
        return NOT_SUPPORTED_VIRTUAL_MEMORY_SIZE_VALUE;
    }
    #endif
}   // namespace Hydra::Other::Memory
