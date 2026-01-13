#pragma once

#include <unordered_map>
#include <unordered_set>

#include "Hydra/external/hashMaps/flat_hash_map/bytell_hash_map.h"
#include "Hydra/external/hashMaps/flat_hash_map/flat_hash_map.h"
#include "Hydra/external/hashMaps/flat_hash_map/unordered_map.h"
#include "Hydra/external/hashMaps/robin-hood-hashing/robin_hood.h"
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
    using UnorderedDenseSetType = ankerl::unordered_dense::set<K>;
    template <typename K, typename V>
    using UnorderedDenseMapType = ankerl::unordered_dense::map<K, V>;

    // ankerl::unordered_dense::segmented
    template <typename K>
    using UnorderedDenseSegmentedSetType = ankerl::unordered_dense::segmented_set<K>;
    template <typename K, typename V>
    using UnorderedDenseSegmentedMapType = ankerl::unordered_dense::segmented_map<K, V>;

    // USED - general
    template <typename K>
    using SetType = RobinHoodFlatSetType<K>;
    template <typename K, typename V>
    using MapType = RobinHoodFlatMapType<K, V>;

    // USED - string
    template <typename K>
    using StringSetType = UnorderedDenseSetType<K>;
    template <typename K, typename V>
    using StringMapType = UnorderedDenseMapType<K, V>;
}   // namespace Hydra::Other::HashMap
