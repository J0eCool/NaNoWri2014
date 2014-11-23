#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

typedef std::string String;
template <typename T> using Vector = std::vector<T>;
template <typename T> using Set = std::unordered_set<T>;
template <typename T1, typename T2> using Pair = std::pair<T1, T2>;
template <typename K, typename V> using Dict = std::map<K, V>;
template <typename K, typename V> using Hash = std::unordered_map<K, V>;
