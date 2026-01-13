#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "HydraTest/TemplateTest.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

namespace HydraTest {
    TemplateTest::TemplateTest(const std::string& testName, const std::string& correctResult) noexcept
        : testName_(testName), correctResult_(correctResult), actualResultStringStream_() {
        std::cout << testName_ << ": ";
    }

    std::stringstream& TemplateTest::getStringStream() noexcept {
        return actualResultStringStream_;
    }

    bool TemplateTest::checkTest() const {
        // The results are identical
        if (actualResultStringStream_.str() == correctResult_) {
            std::cout << "passed" << std::endl;
            return true;
        }

        // The results differ
        // Log file does not exist
        if (!std::filesystem::exists(logFilePath))
            throw Hydra::Exception::FileDoesNotExistException(logFilePath);

        {
            std::ofstream logFile(logFilePath, std::ios_base::app);

            // Log file cannot be open
            if (!logFile.is_open())
                throw Hydra::Exception::FileCannotBeOpenedException(logFilePath);

            logFile << "Test name: " << testName_ << std::endl;
            logFile << "Actual result: " << std::endl;
            logFile << actualResultStringStream_.str() << std::endl;
            logFile << "Correct result: " << std::endl;
            logFile << correctResult_ << std::endl;
            logFile << std::endl;
        }

        std::cout << "failed" << std::endl;
        return false;
    }

    void TemplateTest::saveActualResultToFile(const std::string& filePath) const {
        {
            std::ofstream file(filePath, std::ios::out);

            if (!file.is_open())
                throw Hydra::Exception::CannotCreateFileException(filePath);

            file << actualResultStringStream_.str();
        }
    }
}   // namespace HydraTest
