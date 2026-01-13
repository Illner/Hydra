#pragma once

#include <sstream>
#include <string>

namespace HydraTest {
    const inline std::string logFilePath = "./log.txt";   // Log location

    class TemplateTest {
    public:
        TemplateTest(const std::string& testName, const std::string& correctResult) noexcept;

    private:
        std::string testName_;
        const std::string& correctResult_;
        std::stringstream actualResultStringStream_;

    public:
        std::stringstream& getStringStream() noexcept;

        /**
         * Compare the correct result with the actual result.
         * If the results are not the same, the results will be saved to the log file.
         * @return false if the results differ. Otherwise, true is returned.
         */
        bool checkTest() const;

        /**
         * Save the actual result to a file
         */
        void saveActualResultToFile(const std::string& filePath = "/Users/illner/CLionProjects/Hydra/temp.txt") const;
    };
}   // namespace HydraTest
