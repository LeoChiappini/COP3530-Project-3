#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "node.cpp"


class HashTable {
private:
    std::vector<std::list<Node*>> table;
    int numBuckets;
    int numEntries;
    //
    // Hash function
    //
    int hashFunction(const std::string& key) {
        int hash = 0;
        for (char c : key) hash += c;
        return hash % numBuckets;
    }
    //
    // Calculate Load Factor
    //
    float loadFactor() {
        return static_cast<float>(numEntries) / numBuckets;
    }
    //
    // Resize table and re-ash
    //
    void resizeTable() {
        int newSize = numBuckets * 2;
        std::vector<std::list<Node*>> newTable(newSize);

        // Rehash all entries
        for (auto& bucket : table) {
            for (auto& node : bucket) {
                int newIndex = hashFunction(node->word) % newSize;
                newTable[newIndex].push_back(node);
            }
        }

        table = std::move(newTable);
        numBuckets = newSize;
    }

public:
    HashTable(int size) : numBuckets(size), numEntries(0) {
        table.resize(numBuckets);
    }

    void insert(Node* node) {
        if (loadFactor() > 0.7) {
            resizeTable();
        }

        int index = hashFunction(node->word);
        table[index].push_back(node);
        numEntries++;
    }
    //
    // Insert from vector function
    //
    void insertFromVector(std::vector<Node*>& vec) {
        for (const auto& node: vec) {
            insert(node);
        }
    }

    void search(const std::string& key) {
        int index = hashFunction(key);
        for (const auto& node : table[index]) {
            if (node->word == key) {
                std::cout << "Definitions for " << key << ":" << std::endl;
                for (const auto& definition : node->definitions) {
                    std::cout << "-" << definition << std::endl;
                }
                return;
            }
        }
        std::cout << "Word: " << key << " not found!" << std::endl;
    }
};
