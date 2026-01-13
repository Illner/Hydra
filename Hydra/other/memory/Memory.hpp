#pragma once

#include <cassert>
#include <filesystem>
#include <fstream>
#include <ios>
#include <string>
#include <string_view>

#include "Hydra/other/operatingSystem/OperatingSystem.hpp"
#include "Hydra/other/parser/Parser.hpp"

#include "Hydra/compiler/exceptions/ParserException.hpp"

namespace Hydra::Other::Memory {

    using MemorySizeType = long double;   // 128 bits

    inline constexpr std::string_view VM_SIZE_START_OF_LINE = "VmSize:";
    inline constexpr std::string_view VM_PEAK_START_OF_LINE = "VmPeak:";

    inline constexpr MemorySizeType NOT_SUPPORTED_VIRTUAL_MEMORY_SIZE_VALUE = static_cast<MemorySizeType>(-1);

    /**
     * Convert the size in megabytes to bytes
     * Assert: memorySizeInMegabytes MUST NOT be NOT_SUPPORTED_VIRTUAL_MEMORY_SIZE_VALUE
     * @param memorySizeInMegabytes a size in megabytes
     * @return the size in bytes
     */
    MemorySizeType convertMegabytesToBytes(MemorySizeType memorySizeInMegabytes);

    /**
     * Convert the size in gigabytes to bytes
     * Assert: memorySizeInGigabytes MUST NOT be NOT_SUPPORTED_VIRTUAL_MEMORY_SIZE_VALUE
     * @param memorySizeInMegabytes a size in gigabytes
     * @return the size in bytes
     */
    MemorySizeType convertGigabytesToBytes(MemorySizeType memorySizeInGigabytes);

    /**
     * macOS: https://opensource.apple.com/source/Libc/Libc-825.26/include/malloc/malloc.h.auto.html
     * Windows: https://learn.microsoft.com/en-us/windows/win32/api/psapi/ns-psapi-process_memory_counters_ex
     */

    /**
     * Adapted from https://stackoverflow.com/questions/48417499/programmatically-retrieve-peak-virtual-memory-of-a-process
     * Adapted from https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
     * Note: in MB
     * Note: NOT_SUPPORTED_VIRTUAL_MEMORY_SIZE_VALUE is returned if the operating system does not support it
     * @return the peak virtual memory space the process has used
     */
    MemorySizeType getPeakVirtualMemorySize();

    /**
     * Adapted from https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
     * Note: in MB
     * Note: NOT_SUPPORTED_VIRTUAL_MEMORY_SIZE_VALUE is returned if the operating system does not support it
     * @return the current virtual memory space the process has used
     */
    MemorySizeType getCurrentVirtualMemorySize();

    #if OPERATING_SYSTEM_LINUX
    /**
     * Read the "/proc/self/status" file and return the (peak/current) memory size
     * Note: in MB
     * @param startLine the start of line (VM_SIZE_START_OF_LINE or VM_PEAK_START_OF_LINE)
     * @return the (peak/current) virtual memory space the process has used
     */
    MemorySizeType readProcSelfStatusFile(std::string_view startLine);
    #endif
}   // namespace Hydra::Other::Memory
