#include <iostream>
#include <vector>
#include <string>
#include <list>

struct Node {
    std::string word;
    std::vector<std::string> definitions;
};

class HashTable {
private:
    std::vector<std::list<Node>> table;
    int numBuckets; // Total number of buckets
    int numEntries; // Total number of entries

    int hashFunction(const std::string& key) {
        int hash = 0;
        for (char c : key) hash += c;
        return hash % numBuckets;
    }

    float loadFactor() {
        return static_cast<float>(numEntries) / numBuckets;
    }

    void resizeTable() {
        int newSize = numBuckets * 2;
        std::vector<std::list<Node>> newTable(newSize);

        // Rehash all entries
        for (auto& bucket : table) {
            for (auto& node : bucket) {
                int newIndex = hashFunction(node.word) % newSize;
                newTable[newIndex].push_back(std::move(node));
            }
        }

        table = std::move(newTable);
        numBuckets = newSize;
    }

public:
    HashTable(int size) : numBuckets(size), numEntries(0) {
        table.resize(numBuckets);
    }

    void insert(Node node) {
        if (loadFactor() > 0.7) {
            resizeTable();
        }

        int index = hashFunction(node.word);
        table[index].push_back(node);
        numEntries++;
    }

    void search(const std::string& key) {
        int index = hashFunction(key);
        for (const auto& node : table[index]) {
            if (node.word == key) {
                std::cout << "Definitions for " << key << ":" << std::endl;
                for (const auto& definition : node.definitions) {
                    std::cout << "-" << definition << std::endl;
                }
                return;
            }
        }
        std::cout << "Word: " << key << " not found!" << std::endl;
    }

.};
