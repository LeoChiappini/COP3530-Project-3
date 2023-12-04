#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "node.cpp"

// struct Node {
//     std::string word;
//     std::vector<std::string>* definitions;
    
//     Node(std::string word_in, std::string definition_in) 
//         : word(std::move(word_in)), definitions(new std::vector<std::string>) {
//         definitions->push_back(std::move(definition_in));
//     }

//     ~Node() {
//         delete definitions;
//     }
// };

class MinHeap {
private:
    std::vector<Node*> heapVec; // Storing pointers to Node objects
    // used in heapify
    int getParentIndex(int i) { return (i - 1) / 2; }

    void heapifyUp(int index) {
        int parent = getParentIndex(index);
        // perform the swap to move new nodes up
        while (index > 0 && heapVec[parent]->word > heapVec[index]->word) {
            std::swap(heapVec[parent], heapVec[index]);
            index = parent; // move the index to check up
            parent = getParentIndex(index); // this will get the new parent
        }
    }

    

public:
    // insert the node and heapify
    void insert(Node* node) { // Accepts a pointer to Node
        // add nodes to heap
        heapVec.push_back(node);
        // perform heapify so node is in the correct position
        int index = heapVec.size() - 1;
        heapifyUp(index);
    }

    // linear search
    void searchAndPrint(const std::string& target) {
        // iterate through heap vector to find target
        for (const auto& node : heapVec) {
            //std::cout << "test" << std::endl;
            if (node->word.compare(target) == 0) {
                std::cout << "Definitions for " << target << ":" << std::endl;
                // iterate through node's definition vector and display
                for (const auto& definition : *(node->definitions)) {
                    std::cout << "- " << definition << std::endl;
                }
                return;
            }
        }
        // word not found
        std::cout << "Word: " << target << " was not found!" << std::endl;
    }

    // search subtree
    bool searchSubtree(int index, const std::string& target) {
        if (index >= heapVec.size()) {
            return false; // Index out of bounds, return false
        }

        // Check if the current node contains the target word
        if (heapVec[index]->word == target) {
            std::cout << "Definitions for " << target << ":" << std::endl;
            for (const auto& definition : *(heapVec[index]->definitions)) {
                std::cout << "- " << definition << std::endl;
            }
            return true; // Target word found
        }

        // Recursively check left and right subtrees if needed
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;

        bool found = false;

        // Check left subtree if it exists and if the word might be present
        if (leftChild < heapVec.size() && heapVec[leftChild]->word <= target) {
            found = searchSubtree(leftChild, target);
        }

        // If not found in left subtree, check right subtree if it exists and if the word might be present
        if (!found && rightChild < heapVec.size() && heapVec[rightChild]->word <= target) {
            found = searchSubtree(rightChild, target);
        }

        return found;
    }

    // Search function entry point
    void SubtreeSearch(const std::string& target) {
        if (!searchSubtree(0, target)) {
            std::cout << "Word: " << target << " was not found!" << std::endl;
        }
    }

    // insert with vector
    void insertWithVector(const std::vector<Node*>& list){
        for (const auto& iter : list){
            insert(iter);
        }
    }
};