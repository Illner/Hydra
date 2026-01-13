#pragma once

#include <string>

#include "Hydra/cache/cachingScheme/enums/PreprocessingTypeEnum.hpp"

namespace Hydra::Cache::CachingScheme::Cara {

    using NumberOfSampleMomentsType = char8_t;

    /**
     * Cara caching scheme - configuration
     */
    struct CaraCachingSchemeConfiguration {
    public:
        inline static constexpr NumberOfSampleMomentsType S_NUMBER_OF_SAMPLE_MOMENTS_MINIMUM = 0;
        inline static constexpr NumberOfSampleMomentsType S_NUMBER_OF_SAMPLE_MOMENTS_DEFAULT = 2;
        inline static constexpr NumberOfSampleMomentsType S_NUMBER_OF_SAMPLE_MOMENTS_MAXIMUM = 10;

    public:
        /**
         * How many sample moments should be computed
         * E(X^k) = 1/n * sum_i X_i^k is the k-th sample moment, for k = 1, 2, ..., numberOfSampleMoments
         */
        NumberOfSampleMomentsType numberOfSampleMoments = S_NUMBER_OF_SAMPLE_MOMENTS_DEFAULT;

        /**
         * True - a variable to literal mapping
         * False - a variable to variable mapping
         */
        bool useVariableToLiteralMapping = true;

        /**
         * Note: only for PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES
         * True - invalid cache records will be discarded
         * False - if an invalid cache record occurs, PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES will be used instead
         */
        bool discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        /**
         * Preprocessing type
         * What type of clauses should be removed before computing the sample moments
         */
        PreprocessingTypeEnum preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

    public:
        /**
         * Returns a string of the following format:
         *      0 sample moments
         *      1 sample moment
         *      2+ sample moments
         * @param numberOfSampleMoments a number of sample moments
         * @return the number of sample moments as a string ending with "sample moment(s)"
         */
        static std::string getNumberOfSampleMomentsAsStringStatic(NumberOfSampleMomentsType numberOfSampleMoments) {
            std::string result;

            result.append(std::to_string(numberOfSampleMoments));
            result.append(" sample moment");

            // 0/2+ sample moments
            if (numberOfSampleMoments != 1)
                result.append("s");

            return result;
        }

        /**
         * Check if the number of sample moments is valid (that is, >= S_NUMBER_OF_SAMPLE_MOMENTS_MINIMUM and <= S_NUMBER_OF_SAMPLE_MOMENTS_MAXIMUM)
         * @param numberOfSampleMoments a number of sample moments
         * @return true if the number of sample moments is valid. Otherwise, false is returned.
         */
        static bool isValidNumberOfSampleMomentsStatic(NumberOfSampleMomentsType numberOfSampleMoments) noexcept {
            // Minimum check
            if (numberOfSampleMoments < S_NUMBER_OF_SAMPLE_MOMENTS_MINIMUM)
                return false;

            // Maximum check
            if (numberOfSampleMoments > S_NUMBER_OF_SAMPLE_MOMENTS_MAXIMUM)
                return false;

            return true;
        }
    };
}   // namespace Hydra::Cache::CachingScheme::Cara
