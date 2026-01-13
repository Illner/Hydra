#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "Hydra/cache/enums/CacheTypeEnum.hpp"

#include "Hydra/cache/cachingScheme/cara/CaraCachingScheme.tpp"

namespace Hydra::Other::Parser::CommandLineArguments {

    using ArgumentValueType = std::string;
    using ArgumentNameType = std::string_view;
    using ArgumentsType = std::vector<std::string>;

    /**
     * Check if the argument exists
     * @param arguments the arguments
     * @param argumentName an argument name
     * @return true if the argument exists. Otherwise, false is returned.
     * @throw ArgumentIsMentionedMultipleTimesException if the argument is mentioned multiple times
     */
    bool argumentExists(const ArgumentsType& arguments, const ArgumentNameType& argumentName);

    /**
     * Assert: if the argument value is optional, the argument MUST be required
     * @param arguments the arguments
     * @param argumentName an argument name
     * @param required is the argument required
     * @param mandatoryArgumentValue is the argument value mandatory
     * @return the argument value.
     *       mandatoryArgumentValue: if the argument does not exist, an empty string is returned.
     *      !mandatoryArgumentValue: if the argument value does not exist, an empty string is returned.
     * @throw RequiredArgumentIsMissingException [required] if the argument is missing
     * @throw InvalidArgumentValueException if the argument value starts with "-"
     * @throw ArgumentIsMentionedMultipleTimesException if the argument is mentioned multiple times
     */
    ArgumentValueType getArgumentValue(const ArgumentsType& arguments, const ArgumentNameType& argumentName, bool required, bool mandatoryArgumentValue = true);

    /**
     * Set the number of sample moments based on the argument value.
     * If no argument value is provided, the number of sample moments is NOT set (that is, the default value is kept).
     * Assert: the argument MUST exist in the arguments
     * @param arguments the arguments
     * @param argumentName an argument name
     * @param caraCachingSchemeConfiguration a Cara caching scheme configuration
     * @param cacheType a cache type
     * @param mandatoryArgumentValue is the argument value mandatory
     * @throw NumberOfSampleMomentsIsNotNumberCaraCachingSchemeException if the argument value is not a number
     * @throw InvalidNumberOfSampleMomentsCaraCachingSchemeException if the number of sample moments is invalid
     */
    void getNumberOfSampleMomentsAndSetInCaraCachingSchemeConfiguration(const ArgumentsType& arguments, const ArgumentNameType& argumentName,
                                                                        Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration& caraCachingSchemeConfiguration,
                                                                        Cache::CacheTypeEnum cacheType, bool mandatoryArgumentValue);
}   // namespace Hydra::Other::Parser::CommandLineArguments
