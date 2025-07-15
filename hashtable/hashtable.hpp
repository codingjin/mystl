#pragma once

#include <cstddef>
#include <functional>
#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include <sstream>
#include <string>


template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable {

    class HashNode {
        public:
            Key key;
            Value value;

            HashNode(const Key& key) : key{key}, value{} {}
            HashNode(const Key& key, const Value& value) : key{key}, value{value} {}

            bool operator==(const HashNode& other) const { return key == other.key; }
            bool operator!=(const HashNode& other) const { return key != other.key; }
            bool operator<(const HashNode& other) const { return key < other.key; }
            bool operator>(const HashNode& other) const { return key > other.key; }
            bool operator==(const Key& key_) const { return key == key_; }

            void print() const 
            {
                std::cout << key << " " << value << " ";
            }
    };

private:
    using Bucket = std::list<HashNode>;
    std::vector<Bucket> buckets;
    Hash hashFunction;
    size_t tableSize;
    size_t numElements;

    float maxLoadFactor = 0.7;

    size_t hash(const Key& key) const { return hashFunction(key) % tableSize; }

    void rehash(size_t newSize)
    {
        std::vector<Bucket> newBuckets(newSize);

        for (Bucket& bucket : buckets) {
            for (HashNode& hashNode : bucket) {
                size_t newIndex = hashFunction(hashNode.key) % tableSize;
                newBuckets[newIndex].push_back(hashNode);
            }
        }

        buckets = std::move(newBuckets);
        tableSize = newSize;
    }

public:
    HashTable(size_t size = 10, const Hash& hashFunc = Hash())
        : buckets{size}, hashFunction{hashFunc}, tableSize{size}, numElements{0}
    {}

    ~HashTable()
    {
        buckets.clear();
        tableSize = 0;
        numElements = 0;
    }

    void clear()
    {
        buckets.clear();
        tableSize = 0;
        numElements = 0;
    }

    void insert(const Key& key, const Value& value)
    {
        if ((numElements + 1) > maxLoadFactor * tableSize) {
            if (tableSize == 0) tableSize = 32;
            else                tableSize <<= 1;
            rehash(tableSize);
        }
        size_t index = hashFunction(key);
        std::list<HashNode> &target_bucket = buckets[index];
        if (std::find(target_bucket.begin(), target_bucket.end(), key) == target_bucket.end()) {
            target_bucket.push_back(HashNode{key, value});
            ++numElements;
        }
    }

    void insertKey(const Key& key)
    {
        insert(key, Value{});
    }

    void erase(const Key& key)
    {
        size_t index = hashFunction(key);
        std::list<HashNode>& target_bucket = buckets[index];
        auto find_it = std::find(target_bucket.begin(), target_bucket.end(), key);
        if (find_it != target_bucket.end()) {
            target_bucket.erase(find_it);
            --numElements;
        }
    }

    Value* find(const Key& key)
    {
        size_t index = hashFunction(key);
        std::list<HashNode>& target_bucket = buckets[index];
        auto find_it = std::find(target_bucket.begin(), target_bucket.end(), key);
        if (find_it != target_bucket.end()) {
            return &find_it->value;
        } else  return nullptr;
    }

    size_t size() const { return numElements; }

    void print() const
    {
        for (const auto& bucketlist : buckets) {
            for (const auto& node : bucketlist) {
                node.print();
            }
        }
        std::cout << std::endl;
    }
};
