#include "hash_table.hpp"

#include <stdexcept>

namespace itis {

  int HashTable::hash(int key) const {
    return utils::hash(key, static_cast<int>(buckets_.size()));
  }

  HashTable::HashTable(int capacity, double load_factor) : load_factor_{load_factor} {
    if (capacity <= 0) {
      throw std::logic_error("hash table capacity must be greater than zero");
    }

    if (load_factor <= 0.0 || load_factor > 1.0) {
      throw std::logic_error("hash table load factor must be in range [0...1]");
    }

    // Tip: allocate hash-table buckets
      buckets_ = std::vector<Bucket>{};
      buckets_.resize(capacity);
  }

  std::optional<std::string> HashTable::Search(int key) const {
    // Tip: compute hash code (index) and use linear search
        int hash = HashTable::hash(key);
        for (auto & pr : buckets_[hash]) {
            if (pr.first == key) {
                return pr.second;
            }
        }
    return std::nullopt;
  }

  void HashTable::Put(int key, const std::string &value) {
    // Tip 1: compute hash code (index) to determine which bucket to use
    // Tip 2: consider the case when the key exists (read the docs in the header file)
    int hash = HashTable::hash(key);
    for (auto & pr : buckets_[hash]) {
        if (pr.first == key) {
            pr.second = value;
            return;
        }
    }
        buckets_[hash].push_back(std::pair(key, value));
        num_keys_++;

    if (static_cast<double>(num_keys_) / buckets_.size() >= load_factor_) {
      // Tip 3: recompute hash codes (indices) for key-value pairs (create a new hash-table)
      // Tip 4: use utils::hash(key, size) to compute new indices for key-value pairs
        std::vector<Bucket> new_bucket_arr;
        auto new_size = buckets_.size() * kGrowthCoefficient;
        new_bucket_arr.resize(new_size);
        for (Bucket& bucket : buckets_){
            for (std::pair<int, std::string> pr : bucket){
                auto new_hash = utils::hash(pr.first, new_size);
                new_bucket_arr[new_hash].push_back(pr);
            }
        }
        buckets_ = new_bucket_arr;

    }
  }

  std::optional<std::string> HashTable::Remove(int key) {
    // Tip 1: compute hash code (index) to determine which bucket to use
    // TIp 2: find the key-value pair to remove and make a copy of value to return
    int hash = HashTable::hash(key);
    std::optional<std::string> result;
    for (auto pr : buckets_[hash]) {
        if (pr.first==key) {
            result = pr.second;
            buckets_[hash].remove(pr);
            break;
        }
    }
    return result;
  }

  bool HashTable::ContainsKey(int key) const {
    // Note: uses Search(key) which is not initially implemented
    return Search(key).has_value();
  }

  bool HashTable::empty() const {
    return size() == 0;
  }

  int HashTable::size() const {
    return num_keys_;
  }

  int HashTable::capacity() const {
    return static_cast<int>(buckets_.size());
  }

  double HashTable::load_factor() const {
    return load_factor_;
  }

  std::unordered_set<int> HashTable::keys() const {
    std::unordered_set<int> keys(num_keys_);
    for (const auto &bucket : buckets_) {
      for (const auto &[key, _] : bucket) {
        keys.insert(key);
      }
    }
    return keys;
  }

  std::vector<std::string> HashTable::values() const {
    std::vector<std::string> values;
    for (const auto &bucket : buckets_) {
      for (const auto &[_, value] : bucket) {
        values.push_back(value);
      }
    }
    return values;
  }

}  // namespace itis