#include "./CommandLineArgumentsParser.hpp"

#include <cassert>

#include "Hydra/other/Other.hpp"
#include "Hydra/other/parser/Parser.hpp"

#include "Hydra/cache/cachingScheme/exceptions/CachingSchemeException.hpp"
#include "Hydra/compiler/exceptions/ParserException.hpp"
#include "Hydra/other/parser/exceptions/CommandLineArgumentsParserException.hpp"

namespace Hydra::Other::Parser::CommandLineArguments {

    bool argumentExists(const ArgumentsType& arguments, const ArgumentNameType& argumentName) {
        bool exists = false;

        for (auto it = arguments.cbegin(); it != arguments.cend(); ++it) {
            // Hit
            if (*it == argumentName) {
                // Multi-occurrence
                if (exists)
                    throw Exception::Other::Parser::CommandLineArguments::ArgumentIsMentionedMultipleTimesException(argumentName);

                exists = true;
            }
        }

        return exists;
    }

    ArgumentValueType getArgumentValue(const ArgumentsType& arguments, const ArgumentNameType& argumentName, bool required, bool mandatoryArgumentValue) {
        assert(mandatoryArgumentValue or required);   // !mandatoryArgumentValue => required

        bool exists = false;
        ArgumentValueType argumentValue;

        for (auto it = arguments.cbegin(); it != arguments.cend(); ++it) {
            // Hit
            if (*it == argumentName) {
                if (exists)
                    throw Exception::Other::Parser::CommandLineArguments::ArgumentIsMentionedMultipleTimesException(argumentName);

                exists = true;

                // The argument value has been found
                if (it + 1 != arguments.cend()) {
                    // The argument value starts with "-"
                    if ((*(it + 1))[0] == '-') {
                        if (mandatoryArgumentValue)
                            throw Exception::Other::Parser::CommandLineArguments::InvalidArgumentValueException(argumentName, *(it + 1));
                        else
                            continue;
                    }

                    argumentValue = *(it + 1);
                }
                // The argument value does not exist
                else {
                    if (mandatoryArgumentValue)
                        throw Exception::Other::Parser::CommandLineArguments::InvalidArgumentValueException(argumentName, "not set");
                    else
                        continue;
                }
            }
        }

        if (required && !exists)
            throw Exception::Other::Parser::CommandLineArguments::RequiredArgumentIsMissingException(argumentName);

        return argumentValue;
    }

    void getNumberOfSampleMomentsAndSetInCaraCachingSchemeConfiguration(const ArgumentsType& arguments, const ArgumentNameType& argumentName,
                                                                        Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration& caraCachingSchemeConfiguration,
                                                                        Cache::CacheTypeEnum cacheType, bool mandatoryArgumentValue) {
        using NumberOfSampleMomentsType = Hydra::Cache::CachingScheme::Cara::NumberOfSampleMomentsType;

        assert(argumentExists(arguments, argumentName));   // the argument exists

        ArgumentValueType numberOfSampleMomentsString = getArgumentValue(arguments, argumentName, true, mandatoryArgumentValue);

        // There is an argument value representing the number of sample moments
        if (!numberOfSampleMomentsString.empty()) {
            try {
                LargeNumberType numberOfSampleMoments = convertStringToPositiveNumber(numberOfSampleMomentsString);

                // The number of sample moments cannot be saved as NumberOfSampleMomentsType or is invalid
                if (!Hydra::Other::unsignedValueCanBeSavedAsTypeT<NumberOfSampleMomentsType>(numberOfSampleMoments) ||
                    (!Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::isValidNumberOfSampleMomentsStatic(static_cast<NumberOfSampleMomentsType>(numberOfSampleMoments))))
                    throw Hydra::Exception::Cache::CachingScheme::InvalidNumberOfSampleMomentsCaraCachingSchemeException(numberOfSampleMoments, cacheType);

                // Set the number of sample moments
                caraCachingSchemeConfiguration.numberOfSampleMoments = static_cast<NumberOfSampleMomentsType>(numberOfSampleMoments);
            }
            catch (const Hydra::Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException& e) {
                throw Hydra::Exception::Other::Parser::CommandLineArguments::NumberOfSampleMomentsIsNotNumberCaraCachingSchemeException(numberOfSampleMomentsString, cacheType);
            }
        }
    }
}   // namespace Hydra::Other::Parser::CommandLineArguments
