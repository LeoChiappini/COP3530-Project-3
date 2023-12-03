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

    int binarySearch(const std::string& target) {
        // get the starting index and the final index
        int left = 0, right = heapVec.size() - 1;
        while (left <= right) {
            // get middle value
            int mid = left + (right - left) / 2;
            if (heapVec[mid]->word == target) {
                // return the index of the target word
                return mid;
            } else if (heapVec[mid]->word < target) {
                // if target > mid look into second half
                left = mid + 1;
            } else {
                // if target < mid look into first half
                right = mid - 1; 
            }  
        }
        return -1; // if item never found
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
            if (node->word == target) {
                std::cout << "Definitions for " << target << ":" << std::endl;
                // iterate through node's definition vector and display
                for (const auto& definition : *(node->definitions)) {
                    std::cout << "-" << definition << std::endl;
                }
                return;
            }
        }
        // word not found
        std::cout << "Word: " << target << " was not found!" << std::endl;
    }

    // binary search for better complexity
    void searchBinary(const std::string& target) {
        // perform binary search
        int index = binarySearch(target);
        // if the element exists print out and look into node and print definitions
        if (index != -1) {
            std::cout << "Definitions for " << target << ":" << std::endl;
            for (const auto& iter : *(heapVec[index]->definitions)) {
                std::cout << "-" << iter << std::endl;
            }
        }
        // word not found
        std::cout << "Word: " << target << " was not found!" << std::endl;
    }

    // insert with vector
    void insertWithVector(const std::vector<Node*>& list){
        for (const auto& iter : list){
            insert(iter);
        }
    }
};
