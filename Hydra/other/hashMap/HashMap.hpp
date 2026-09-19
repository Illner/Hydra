#pragma once

#include <unordered_map>
#include <unordered_set>

#include "Hydra/external/hashMaps/flat_hash_map/bytell_hash_map.h"
#include "Hydra/external/hashMaps/flat_hash_map/flat_hash_map.h"
#include "Hydra/external/hashMaps/flat_hash_map/unordered_map.h"
#include "Hydra/external/hashMaps/robin-hood-hashing/robin_hood.h"
#include "Hydra/external/hashMaps/unordered_dense/huge_page_allocator.h"
#include "Hydra/external/hashMaps/unordered_dense/unordered_dense.h"

namespace Hydra::Other::HashMap {

    // STD
    template <typename K>
    using StdSetType = std::unordered_set<K>;
    template <typename K, typename V>
    using StdMapType = std::unordered_map<K, V>;

    // robin_hood::unordered_node
    template <typename K>
    using RobinHoodNodeSetType = robin_hood::unordered_node_set<K>;
    template <typename K, typename V>
    using RobinHoodNodeMapType = robin_hood::unordered_node_map<K, V>;

    // robin_hood::unordered_flat
    template <typename K>
    using RobinHoodFlatSetType = robin_hood::unordered_flat_set<K>;
    template <typename K, typename V>
    using RobinHoodFlatMapType = robin_hood::unordered_flat_map<K, V>;

    // ska::bytell_hash
    template <typename K>
    using SkaBytellSetType = ska::bytell_hash_set<K>;
    template <typename K, typename V>
    using SkaBytellMapType = ska::bytell_hash_map<K, V>;

    // ska::flat_hash
    template <typename K>
    using SkaFlatSetType = ska::flat_hash_set<K>;
    template <typename K, typename V>
    using SkaFlatMapType = ska::flat_hash_map<K, V>;

    // ankerl::unordered_dense
    template <typename K>
    using AnkerlUnorderedDenseSetType = ankerl::unordered_dense::set<K>;
    template <typename K, typename V>
    using AnkerlUnorderedDenseMapType = ankerl::unordered_dense::map<K, V>;

    // ankerl::unordered_dense::segmented
    template <typename K>
    using AnkerlUnorderedDenseSegmentedSetType = ankerl::unordered_dense::segmented_set<K>;
    template <typename K, typename V>
    using AnkerlUnorderedDenseSegmentedMapType = ankerl::unordered_dense::segmented_map<K, V>;

    // ankerl::unordered_dense::huge_page
    // Note: huge pages are used only on Linux (transparent hugepages). Otherwise, std::allocator is used.
    template <typename K>
    using AnkerlUnorderedDenseHugePageSetType = ankerl::unordered_dense::huge_page::set<K>;
    template <typename K, typename V>
    using AnkerlUnorderedDenseHugePageMapType = ankerl::unordered_dense::huge_page::map<K, V>;

    // ankerl::unordered_dense::huge_page::segmented
    // Note: huge pages are used only on Linux (transparent hugepages). Otherwise, std::allocator is used.
    template <typename K>
    using AnkerlUnorderedDenseHugePageSegmentedSetType = ankerl::unordered_dense::huge_page::segmented_set<K,
                                                                                                           ankerl::unordered_dense::hash<K>, std::equal_to<K>,
                                                                                                           ankerl::unordered_dense::bucket_type::group, 16 << 20>;
    template <typename K, typename V>
    using AnkerlUnorderedDenseHugePageSegmentedMapType = ankerl::unordered_dense::huge_page::segmented_map<K, V,
                                                                                                           ankerl::unordered_dense::hash<K>, std::equal_to<K>,
                                                                                                           ankerl::unordered_dense::bucket_type::group, 16 << 20>;

    // USED - general
    template <typename K>
    using SetType = RobinHoodFlatSetType<K>;
    template <typename K, typename V>
    using MapType = RobinHoodFlatMapType<K, V>;

    // USED - string
    template <typename K>
    using StringSetType = AnkerlUnorderedDenseSetType<K>;
    template <typename K, typename V>
    using StringMapType = AnkerlUnorderedDenseMapType<K, V>;
}   // namespace Hydra::Other::HashMap
