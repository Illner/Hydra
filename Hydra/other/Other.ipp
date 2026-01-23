#pragma once

#include "./Other.hpp"

namespace Hydra::Other {

    template <typename TypeT>
    TypeT computeNumberOfLiteralsDesignedForMethodsOfTypeCanBeSavedAs(TypeT numberOfVariables) noexcept {
        return (TypeT)1 + (TypeT)2 * numberOfVariables;
    }

    template <typename TypeT>
    bool variablesCanBeSavedAsTypeT(LargeNumberType numberOfVariables) noexcept {
        LargeNumberType tmp = std::numeric_limits<TypeT>::max();   // 0, which is not a valid value, is not included

        if (numberOfVariables <= tmp)
            return true;

        return false;
    }

    template <typename TypeT>
    bool literalsCanBeSavedAsTypeT(LargeNumberType numberOfVariables) noexcept {
        return variablesCanBeSavedAsTypeT<TypeT>(computeNumberOfLiteralsDesignedForMethodsOfTypeCanBeSavedAs(numberOfVariables));
    }

    template <typename TypeT>
    bool clauseIdCanBeSavedAsTypeT(LargeNumberType numberOfClauseId) noexcept {
        LargeNumberType tmp = std::numeric_limits<TypeT>::max();   // O, which can be "considered" as the separator (ContagiousOccurrenceList), is not included

        if (numberOfClauseId <= tmp)
            return true;

        return false;
    }

    template <typename TypeT>
    bool unsignedValueCanBeSavedAsTypeT(LargeNumberType unsignedValue) noexcept {
        LargeNumberType tmp = std::numeric_limits<TypeT>::max();

        if (unsignedValue <= tmp)
            return true;

        return false;
    }

    template <typename TypeT>
    bool unsignedValueCanBeSavedAsInt(TypeT unsignedValue) noexcept {
        LargeNumberType maxValueInt = std::numeric_limits<int>::max();

        if (unsignedValue <= maxValueInt)
            return true;

        return false;
    }

    template <typename TypeT>
    bool unsignedValueCanBeSavedAsStdSizeT(TypeT unsignedValue, LargeNumberType increase) noexcept {
        LargeNumberType maxValueStdSizeT = std::numeric_limits<std::size_t>::max();

        // The increase
        maxValueStdSizeT -= increase;

        if (unsignedValue <= maxValueStdSizeT)
            return true;

        return false;
    }

    template <typename TypeT>
    bool emptyIntersectionSortedVectors(const std::vector<TypeT>& x, const std::vector<TypeT>& y) {
        auto xIterator = x.cbegin();
        auto yIterator = y.cbegin();

        while (xIterator != x.cend() && yIterator != y.cend()) {
            if (*xIterator == *yIterator)
                return false;
            else if (*xIterator < *yIterator)
                ++xIterator;
            else
                ++yIterator;
        }

        return true;
    }

    template <typename TypeT>
    std::vector<TypeT> sortUnorderedSet(const HashMap::SetType<TypeT>& unorderedSet) {
        std::vector<TypeT> vector;
        vector.reserve(unorderedSet.size());

        for (const TypeT& element : unorderedSet)
            vector.push_back(element);

        std::sort(vector.begin(), vector.end());

        return vector;
    }

    template <typename K, typename V>
    std::vector<K> extractKeysFromMap(const HashMap::MapType<K, V>& map, bool sort) {
        std::vector<K> keyVector;
        keyVector.reserve(map.size());

        for (const auto& [key, value] : map)
            keyVector.push_back(key);

        if (sort)
            std::sort(keyVector.begin(), keyVector.end());

        return keyVector;
    }

    template <typename K, typename V>
    std::vector<K> extractKeysFromVectorMapping(const std::vector<V>& vectorMapping, const V& noValueRepresentative) {
        std::vector<K> keyVector;
        keyVector.reserve(vectorMapping.size());

        for (K key = 0; key < static_cast<K>(vectorMapping.size()); ++key) {
            if (vectorMapping[key] != noValueRepresentative)
                keyVector.push_back(key);
        }

        return keyVector;
    }

    template <typename K, typename V>
    HashMap::MapType<V, K> invertMap(const HashMap::MapType<K, V>& map) {
        HashMap::MapType<V, K> invertedMap(map.size());

        for (const auto& [key, value] : map)
            invertedMap[value] = key;

        return invertedMap;
    }

    template <typename K, typename V>
    bool isMapBijective(const HashMap::MapType<K, V>& map) {
        HashMap::SetType<V> valueSet(map.size());

        for (const auto& [key, value] : map)
            valueSet.insert(value);

        if (map.size() == valueSet.size())
            return true;

        return false;
    }

    template <typename TypeT>
    bool containInSet(const HashMap::SetType<TypeT>& set, TypeT key) {
        return set.find(key) != set.end();
    }

    template <typename TypeT>
    bool containInStringSet(const HashMap::StringSetType<TypeT>& set, const TypeT& stringKey) {
        return set.find(stringKey) != set.end();
    }

    template <typename K, typename V>
    bool containInMap(const HashMap::MapType<K, V>& map, K key) {
        return map.find(key) != map.end();
    }

    template <typename TypeT>
    bool containInVector(const std::vector<TypeT>& vector, TypeT element) {
        return std::find(vector.cbegin(), vector.cend(), element) != vector.cend();
    }

    template <typename TypeT>
    bool containInSortedVector(const std::vector<TypeT>& sortedVector, TypeT element) {
        return std::binary_search(sortedVector.cbegin(), sortedVector.cend(), element);
    }

    template <std::input_iterator InputIterator>
    std::stringstream createStringStreamFromContainer(const InputIterator& begin, const InputIterator& end) {
        bool firstElement = true;
        std::stringstream stringStream;

        for (std::input_iterator auto it = begin; it != end; ++it) {
            if (firstElement) {
                stringStream << *it;
                firstElement = false;
            }
            else
                stringStream << ", " << *it;
        }

        return stringStream;
    }

    template <std::input_iterator InputIterator>
    std::stringstream createStringStreamFromContainerWithToStringConversion(const InputIterator& begin, const InputIterator& end) {
        bool firstElement = true;
        std::stringstream stringStream;

        for (std::input_iterator auto it = begin; it != end; ++it) {
            if (firstElement) {
                stringStream << std::to_string(*it);
                firstElement = false;
            }
            else
                stringStream << ", " << std::to_string(*it);
        }

        return stringStream;
    }

    template <typename K, typename V>
    std::stringstream createStringStreamFromMapWithToStringConversion(const HashMap::MapType<K, V>& map) {
        bool firstElement = true;
        std::stringstream stringStream;

        std::vector<K> keySortedVector;
        keySortedVector.reserve(map.size());

        for (const auto& [key, value] : map)
            keySortedVector.push_back(key);

        std::sort(keySortedVector.begin(), keySortedVector.end());

        for (const K& key : keySortedVector) {
            if (firstElement) {
                stringStream << std::to_string(key) << " -> " << map.at(key);
                firstElement = false;
            }
            else
                stringStream << ", " << std::to_string(key) << " -> " << map.at(key);
        }

        return stringStream;
    }

    template <typename TypeT>
    bool smartRemoveElementFromVector(std::vector<TypeT>& vector, TypeT element) {
        for (std::size_t i = 0; i < vector.size(); ++i) {
            // The element has been found
            if (vector[i] == element) {
                if (i != (vector.size() - 1))
                    vector[i] = std::move(vector.back());

                vector.pop_back();
                return true;
            }
        }

        // The element does not exist in the vector
        return false;
    }

    template <typename TypeT>
    void smartRemoveElementsFromVector(std::vector<TypeT>& vector, const HashMap::SetType<TypeT>& removeElementSet) {
        std::size_t i = 0;

        while (i < vector.size()) {
            if (containInSet(removeElementSet, vector[i])) {
                if (i != (vector.size() - 1))
                    vector[i] = std::move(vector.back());

                vector.pop_back();
            }
            else {
                ++i;
            }
        }
    }

    void printWarningAboutAdjustedConfiguration(const std::string& name, const std::string& adjustedValue) {
        std::cerr << "WARNING: the following configuration has been adjusted: ";
        std::cerr << name << " = " << adjustedValue << std::endl;
    }

    void printWarningAboutIgnoringRemainingArgumentsExceptOne(const Parser::CommandLineArguments::ArgumentNameType& notIgnoredArgumentName) {
        std::cerr << "WARNING: only the argument \"" << notIgnoredArgumentName << "\" is considered; the remaining arguments are ignored!" << std::endl;
        std::cerr << std::endl;
    }

    void printTitle(std::ostream& out, const std::string& title, int numberOfDelimiters, char delimiter, char prefix, bool printTop, bool printBottom) {
        printTitle(out, title, numberOfDelimiters, delimiter, std::string_view(&prefix, 1), printTop, printBottom);
    }

    void printTitle(std::ostream& out, const std::string& title, int numberOfDelimiters, char delimiter,
                    const std::string_view& prefix, bool printTop, bool printBottom) {
        assert(static_cast<int>(title.size()) <= numberOfDelimiters);

        // Top
        if (printTop) {
            if (!prefix.empty())
                out << prefix << " ";
            for (int i = 0; i < numberOfDelimiters; ++i)
                out << delimiter;
            out << std::endl;
        }

        int remaining = numberOfDelimiters - static_cast<int>(title.size());
        int half = remaining / 2;

        // Mid
        if (!prefix.empty())
            out << prefix << " ";
        for (int i = 0; i < half; ++i)
            out << delimiter;
        out << title;
        for (int i = 0; i < half; ++i)
            out << delimiter;
        if (remaining % 2 == 1)
            out << delimiter;
        out << std::endl;

        // Bottom
        if (printBottom) {
            if (!prefix.empty())
                out << prefix << " ";
            for (int i = 0; i < numberOfDelimiters; ++i)
                out << delimiter;
            out << std::endl;
        }
    }

    void printBuildType(std::ostream& out) {
        #ifndef NDEBUG
        out << "Build type: Debug" << std::endl;
        #endif
        #ifdef NDEBUG
        out << "Build type: Release" << std::endl;
        #endif
    }

    void printMacros(std::ostream& out) {
        // TEST
        #if defined(TEST)
        out << "MACRO: TEST" << std::endl;
        #else
        out << "MACRO: no TEST" << std::endl;
        #endif

        // BELLA_COMPILER
        #if defined(BELLA_COMPILER)
        out << "MACRO: BELLA_COMPILER" << std::endl;
        #else
        out << "MACRO: no BELLA_COMPILER" << std::endl;
        #endif

        // BELLA_COMPILER_TEST
        #if defined(BELLA_COMPILER_TEST)
        out << "MACRO: BELLA_COMPILER_TEST" << std::endl;
        #else
        out << "MACRO: no BELLA_COMPILER_TEST" << std::endl;
        #endif

        // CARA_SOLVER
        #if defined(CARA_SOLVER)
        out << "MACRO: CARA_SOLVER" << std::endl;
        #else
        out << "MACRO: no CARA_SOLVER" << std::endl;
        #endif

        // CARA_SOLVER_TEST
        #if defined(CARA_SOLVER_TEST)
        out << "MACRO: CARA_SOLVER_TEST" << std::endl;
        #else
        out << "MACRO: no CARA_SOLVER_TEST" << std::endl;
        #endif
    }

    template <typename TypeT, typename SortFunctorT>
    void mergeSort(std::vector<TypeT>& vector, SortFunctorT sortFunctor,
                   bool removeDuplicateElements, std::size_t estimatedNumberOfDuplicateElements) {
        if (vector.empty())
            return;

        #ifndef NDEBUG
        // Check if the elements in the vector are unique
        if (removeDuplicateElements) {
            HashMap::SetType<TypeT> seenElementSetTmp(vector.size());
            for (const TypeT& element : vector) {
                // The element has already been seen
                if (Other::containInSet(seenElementSetTmp, element))
                    throw Exception::UnexpectedArgumentException("the elements in the vector are not unique",
                                                                 "Hydra::Other::mergeSort");

                seenElementSetTmp.insert(element);
            }
        }
        #endif

        std::size_t size = vector.size();
        std::vector<TypeT> vectorTmp(size);
        HashMap::SetType<TypeT> duplicateElementSet(estimatedNumberOfDuplicateElements);

        processMergeSort(vector, vectorTmp, sortFunctor,
                         duplicateElementSet, removeDuplicateElements,
                         0, size - 1);

        // No duplicate elements
        if (!removeDuplicateElements || duplicateElementSet.empty())
            return;

        // Remove the duplicate elements
        vectorTmp.clear();
        for (TypeT& element : vector) {
            // The element is duplicate
            if (Other::containInSet(duplicateElementSet, element))
                continue;

            vectorTmp.push_back(std::move(element));
        }

        // Recopy
        vector.clear();
        for (TypeT& element : vectorTmp)
            vector.push_back(std::move(element));

        vector.shrink_to_fit();
    }

    template <typename TypeT, typename SortFunctorT>
    void processMergeSort(std::vector<TypeT>& vector, std::vector<TypeT>& vectorTmp, SortFunctorT sortFunctor,
                          HashMap::SetType<TypeT>& duplicateElementSet, bool removeDuplicateElements,
                          std::size_t left, std::size_t right) {
        if (left < right) {
            std::size_t center = static_cast<std::size_t>(left + ((right - left) / 2));

            // Sort (left, center)
            processMergeSort(vector, vectorTmp, sortFunctor,
                             duplicateElementSet, removeDuplicateElements,
                             left, center);
            // Sort (center + 1, right)
            processMergeSort(vector, vectorTmp, sortFunctor,
                             duplicateElementSet, removeDuplicateElements,
                             center + 1, right);

            // Merge
            processMerge(vector, vectorTmp, sortFunctor,
                         duplicateElementSet, removeDuplicateElements,
                         left, center, right);
        }
    }

    template <typename TypeT, typename SortFunctorT>
    void processMerge(std::vector<TypeT>& vector, std::vector<TypeT>& vectorTmp, SortFunctorT sortFunctor,
                      HashMap::SetType<TypeT>& duplicateElementSet, bool removeDuplicateElements,
                      std::size_t left, std::size_t center, std::size_t right) {
        std::size_t leftCurrentPosition = left;
        std::size_t rightCurrentPosition = center + 1;
        std::size_t currentPosition = leftCurrentPosition;

        // Merging
        while ((leftCurrentPosition <= center) && (rightCurrentPosition <= right)) {
            switch (sortFunctor(vector[leftCurrentPosition], vector[rightCurrentPosition])) {
                // vector[leftCurrentPosition] < vector[rightCurrentPosition]
                case -1:
                    vectorTmp[currentPosition++] = std::move(vector[leftCurrentPosition++]);
                    break;

                // vector[leftCurrentPosition] > vector[rightCurrentPosition]
                case 1:
                    vectorTmp[currentPosition++] = std::move(vector[rightCurrentPosition++]);
                    break;

                // vector[leftCurrentPosition] == vector[rightCurrentPosition]
                case 0:
                    if (removeDuplicateElements)
                        duplicateElementSet.insert(vector[rightCurrentPosition]);

                    vectorTmp[currentPosition++] = std::move(vector[leftCurrentPosition++]);
                    vectorTmp[currentPosition++] = std::move(vector[rightCurrentPosition++]);
                    break;

                default:
                    throw Exception::NotImplementedException(std::to_string(sortFunctor(vector[leftCurrentPosition], vector[rightCurrentPosition])),
                                                             "Hydra::Other::processMerge");
            }
        }

        // Copy the rest of the vector (leftCurrentPosition, center)
        while (leftCurrentPosition <= center)
            vectorTmp[currentPosition++] = std::move(vector[leftCurrentPosition++]);

        // Copy the rest of the vector (rightCurrentPosition, right)
        while (rightCurrentPosition <= right)
            vectorTmp[currentPosition++] = std::move(vector[rightCurrentPosition++]);

        // Copy
        for (std::size_t i = left; i <= right; ++i)
            vector[i] = std::move(vectorTmp[i]);
    }
}   // namespace Hydra::Other
