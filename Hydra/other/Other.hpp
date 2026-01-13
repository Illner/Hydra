#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "Hydra/other/hashMap/HashMap.hpp"
#include "Hydra/other/std/Std.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

namespace Hydra::Other {

    using LargeFloatingNumberType = long double;      // 128 bits
    using LargeNumberType = unsigned long long int;   // at least 64 bits

    /**
     * Note: designed only for the methods of type "...CanBeSavedAs..."
     * @return the number of literals based on the number of variables
     */
    template <typename TypeT>
    inline TypeT computeNumberOfLiteralsDesignedForMethodsOfTypeCanBeSavedAs(TypeT numberOfVariables) noexcept;

    /**
     * @return true if TypeT can be used for saving variables. Otherwise, false is returned.
     */
    template <typename TypeT>
    inline bool variablesCanBeSavedAsTypeT(LargeNumberType numberOfVariables) noexcept;

    /**
     * @return true if TypeT can be used for saving literals. Otherwise, false is returned.
     */
    template <typename TypeT>
    inline bool literalsCanBeSavedAsTypeT(LargeNumberType numberOfVariables) noexcept;

    /**
     * @return true if TypeT can be used for saving clause identifiers. Otherwise, false is returned.
     */
    template <typename TypeT>
    inline bool clauseIdCanBeSavedAsTypeT(LargeNumberType numberOfClauseId) noexcept;

    /**
     * @return true if TypeT can be used for saving unsignedValue. Otherwise, false is returned.
     */
    template <typename TypeT>
    inline bool unsignedValueCanBeSavedAsTypeT(LargeNumberType unsignedValue) noexcept;

    /**
     * @return true if int can be used for saving unsignedValue. Otherwise, false is returned.
     */
    template <typename TypeT>
    inline bool unsignedValueCanBeSavedAsInt(TypeT unsignedValue) noexcept;

    /**
     * @param increase an increase
     * @return true if std::size_t can be used for saving (unsignedValue + increase). Otherwise, false is returned.
     */
    template <typename TypeT>
    inline bool unsignedValueCanBeSavedAsStdSizeT(TypeT unsignedValue, LargeNumberType increase = 0) noexcept;

    /**
     * @return true if two SORTED vectors are disjoint. Otherwise, false is returned.
     */
    template <typename TypeT>
    inline bool emptyIntersectionSortedVectors(const std::vector<TypeT>& x, const std::vector<TypeT>& y);

    /**
     * @return sorted vector containing all elements from the unordered set
     */
    template <typename TypeT>
    inline std::vector<TypeT> sortUnorderedSet(const HashMap::SetType<TypeT>& unorderedSet);

    /**
     * @return (sorted) vector containing all keys from the map
     */
    template <typename K, typename V>
    inline std::vector<K> extractKeysFromMap(const HashMap::MapType<K, V>& map, bool sort);

    /**
     * Note: it is assumed that K is easy to copy
     * @return a sorted vector containing all keys from the vector mapping
     */
    template <typename K, typename V>
    inline std::vector<K> extractKeysFromVectorMapping(const std::vector<V>& vectorMapping, const V& noValueRepresentative);

    /**
     * Note: it is expected that values are different
     * @return an inverted map
     */
    template <typename K, typename V>
    inline HashMap::MapType<V, K> invertMap(const HashMap::MapType<K, V>& map);

    /**
     * @return true if the map is bijective. Otherwise, false is returned.
     */
    template <typename K, typename V>
    inline bool isMapBijective(const HashMap::MapType<K, V>& map);

    /**
     * @return true if the key exists in the set. Otherwise, false is returned.
     */
    template <typename TypeT>
    inline bool containInSet(const HashMap::SetType<TypeT>& set, TypeT key);

    /**
     * @return true if the key exists in the set. Otherwise, false is returned.
     */
    template <typename TypeT>
    inline bool containInStringSet(const HashMap::StringSetType<TypeT>& set, const TypeT& stringKey);

    /**
     * @return true if the key exists in the map. Otherwise, false is returned.
     */
    template <typename K, typename V>
    inline bool containInMap(const HashMap::MapType<K, V>& map, K key);

    /**
     * @return true if the element exists in the vector. Otherwise, false is returned.
     */
    template <typename TypeT>
    inline bool containInVector(const std::vector<TypeT>& vector, TypeT element);

    /**
     * @return true if the element exists in the SORTED vector. Otherwise, false is returned.
     */
    template <typename TypeT>
    inline bool containInSortedVector(const std::vector<TypeT>& sortedVector, TypeT element);

    /**
     * Note: e_1, e_2, ..., e_N
     * @return a string stream containing the content of the container
     */
    template <std::input_iterator InputIterator>
    inline std::stringstream createStringStreamFromContainer(const InputIterator& begin, const InputIterator& end);

    /**
     * Note: std::to_string(e_1), std::to_string(e_2), ..., std::to_string(e_N)
     * @return a string stream containing the content of the container
     */
    template <std::input_iterator InputIterator>
    inline std::stringstream createStringStreamFromContainerWithToStringConversion(const InputIterator& begin, const InputIterator& end);

    /**
     * Note: std::to_string(k_1) -> v_1, ..., std::to_string(k_N) -> v_N
     * Note: the keys will be sorted
     * Time complexity: O(N x log(N))
     * @return a string stream containing the content of the map
     */
    template <typename K, typename V>
    inline std::stringstream createStringStreamFromMapWithToStringConversion(const HashMap::MapType<K, V>& map);

    /**
     * Time complexity: O(|vector|)
     * The element we want to remove will be swapped with the last element in the vector, and then the last element will be erased
     * Note: only the first occurrence of that element will be removed
     * @return true if the element has been successfully removed from the vector. Otherwise, false is returned.
     */
    template <typename TypeT>
    inline bool smartRemoveElementFromVector(std::vector<TypeT>& vector, TypeT element);

    /**
     * Time complexity: O(|vector|)
     * The elements we want to remove will be swapped with the last element in the vector, and then the last element will be erased
     * Note: all the occurrences of the elements will be removed
     */
    template <typename TypeT>
    inline void smartRemoveElementsFromVector(std::vector<TypeT>& vector, const HashMap::SetType<TypeT>& removeElementSet);

    /**
     * Print a warning about the adjusted configuration
     * @param name a configuration name
     * @param adjustedValue an adjusted value
     */
    inline void printWarningAboutAdjustedConfiguration(const std::string& name, const std::string& adjustedValue);

    /**
     * prefix --------------------
     * prefix -------Title--------
     * prefix --------------------
     */
    inline void printTitle(std::ostream& out, const std::string& title, int numberOfDelimiters, char delimiter,
                           char prefix, bool printTop = true, bool printBottom = true);
    inline void printTitle(std::ostream& out, const std::string& title, int numberOfDelimiters, char delimiter,
                           const std::string_view& prefix = "", bool printTop = true, bool printBottom = true);

    /**
     * Print the build type
     * Build types: Debug, and Release
     */
    inline void printBuildType(std::ostream& out);

    /**
     * Print the macros
     * Considered macros: BELLA_COMPILER, CARA_SOLVER, TEST, BELLA_COMPILER_TEST, and CARA_SOLVER_TEST
     */
    inline void printMacros(std::ostream& out);

    /**
     * Merge sort algorithm
     * Note: used mainly for sorting clauses
     * @param vector [input/output] a vector that needs to be sorted
     * @param sortFunctor operator()(TypeT t_1, TypeT t_2)
     *      -1 - t_1 < t_2
     *       0 - t_1 = t_2
     *       1 - t_1 > t_2
     * @param removeDuplicateElements should the duplicate elements be removed? The elements in the vector MUST be unique!
     * @param estimatedNumberOfDuplicateElements estimated number of duplicate elements
     * @throw UnexpectedArgumentException (debug) (removeDuplicateElements) if the elements in the vector are not unique
     */
    template <typename TypeT, typename SortFunctorT>
    inline void mergeSort(std::vector<TypeT>& vector, SortFunctorT sortFunctor,
                          bool removeDuplicateElements = false, std::size_t estimatedNumberOfDuplicateElements = 1);

    template <typename TypeT, typename SortFunctorT>
    inline void processMergeSort(std::vector<TypeT>& vector, std::vector<TypeT>& vectorTmp, SortFunctorT sortFunctor,
                                 HashMap::SetType<TypeT>& duplicateElementSet, bool removeDuplicateElements,
                                 std::size_t left, std::size_t right);

    template <typename TypeT, typename SortFunctorT>
    inline void processMerge(std::vector<TypeT>& vector, std::vector<TypeT>& vectorTmp, SortFunctorT sortFunctor,
                             HashMap::SetType<TypeT>& duplicateElementSet, bool removeDuplicateElements,
                             std::size_t left, std::size_t center, std::size_t right);
}   // namespace Hydra::Other

#include "./Other.ipp"
