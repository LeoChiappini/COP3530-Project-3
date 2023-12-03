#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

#include "node.cpp"
#include "heap.h"
#include "hashtable.cpp"

/*
std::pair<std::string, std::string> splitString(std::string& inputString) 
{
    // Create a string stream to manipulate the input string
    std::istringstream iss(inputString);

    // Use getline with ':' as the delimiter to split the string
    std::string firstPart;
    std::getline(iss, firstPart, ':');

    // Remove leading and trailing whitespaces from the first part
    firstPart.erase(firstPart.find_last_not_of(" \t\n\r\f\v") + 1);
    firstPart.erase(0, firstPart.find_first_not_of(" \t\n\r\f\v"));

    // Get the remaining part of the string
    std::string secondPart;
    std::getline(iss, secondPart);

    // Remove leading and trailing whitespaces from the second part
    secondPart.erase(secondPart.find_last_not_of(" \t\n\r\f\v") + 1);
    secondPart.erase(0, secondPart.find_first_not_of(" \t\n\r\f\v"));

    return std::make_pair(firstPart, secondPart);
}
*/


int main() 
{
    std::string filePath = "english_dictionary.txt";  // File path to the dictionary text file

    std::vector<Node*> node_list; // Vector that will be populated with nodes

    std::unordered_map<std::string, Node*> node_map; // Map that will be populated with nodes

    // Handling for menu options
    int choice;

    int num_words; // Number of words to be inserted

    std::cout << "Enter the number of words to be inserted: " << std::endl;
    std::cout << "1. All of the words in the dictionary" << std::endl;
    std::cout << "2. A specific number of words" << std::endl;
    std::cout << "Enter your choice (1 or 2): ";

    std::cin >> choice;

    std::cout << std::endl;

    if (choice == 1) // Enter all words
    {
        num_words = 117659;
    }
    if (choice == 2) // Enter a specific number of words
    {
        std::cout << "Enter the number of words to be inserted. Must be between 1 and 117,659: ";
        std::cin >> choice;
        std::cout << std::endl;

        if (choice < 1 || choice > 117659) // Checks bounds of input
        {
            std::cout << "Invalid choice" << std::endl;
            return 1;
        }
        else
        {
            num_words = choice; // Set the size to include all words
        }
    }

    // Enters the words into the vector
    std::ifstream file(filePath); // Open the file
    if (!file.is_open()) 
    {
        std::cout << "File not found" << std::endl;
        return 1;
    }

    std::string line; // String to store each line of the file

    for (int i = 0; i < num_words && std::getline(file, line); ++i) // Read each line from the file
    {
        std::string word; // String to store the word
        std::string definition; // String to store the definition

        std::istringstream iss(line); // Create a string stream to manipulate the input string

        std::getline(iss, word, ':'); // Use getline with ':' as the delimiter to split the string

        word.erase(word.find_last_not_of(" \t\n\r\f\v") + 1); // Remove leading and trailing whitespaces from the first part
        word.erase(0, word.find_first_not_of(" \t\n\r\f\v"));

        std::getline(iss, definition); // Get the remaining part of the string

        definition.erase(definition.find_last_not_of(" \t\n\r\f\v") + 1); // Remove leading and trailing whitespaces from the second part
        definition.erase(0, definition.find_first_not_of(" \t\n\r\f\v"));

        if (node_map.find(word) != node_map.end()) // If the word is already in the map
        {
            node_map[word]->definitions->push_back(definition); // Add the definition to the vector
        }
        else
        {
            node_list.push_back(new Node(word, definition)); // Add the node to the vector
        }
        
    }

    // At this point, the vector should be populated with all of the nodes


    // Asks user for input of which data structure to use
    std::cout << "Choose a data structure:" << std::endl;
    std::cout << "1. Hashmap" << std::endl;
    std::cout << "2. Heap" << std::endl;
    std::cout << "3. Compare Both" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice (1, 2, 3, or 4): ";
    std::cin >> choice;
    std::cout << std::endl;



    MinHeap heap; // Heap object
    HashTable hash_map(9); // Hash Map object

    if (choice == 1) // Hash Map chosen
    {
        hash_map.insertFromVector(node_list);
    }
    else if (choice == 2) // Heap chosen
    {
        
        heap.insertWithVector(node_list);
    }
    else if (choice == 3) // Compare both chosen
    {
        heap.insertWithVector(node_list);
        hash_map.insertFromVector(node_list);
    }
    else if (choice == 4) // Exit chosen
    {
        return 0;
    }
    else // Invalid choice
    {
        std::cout << "Invalid choice" << std::endl;
        return 1;
    }

    // Asks user whether they want to search for a word or print part of the dictionary
    std::cout << "Choose what you want to do: " << std::endl;
    std::cout << "1. Search for a word" << std::endl;
    std::cout << "2. Print a # of words" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Enter your choice (1, 2, or 3): ";

    int func_choice; // Choice of functionality
    std::cin >> func_choice;
    std::cout << std::endl;

    int sub_choice; // Choice of sub-functionality

    if (func_choice == 1) // Search for a word chosen
    {
        std::string word_search; // String to store the word to search for

        if (choice == 2 || choice == 3) // If a heap is used
        {
            std::cout << "Choose a search method for the heap: " << std::endl;
            std::cout << "1. Linear Search" << std::endl;
            std::cout << "2. Binary Search" << std::endl;
            std::cout << "3. Exit" << std::endl;
            std::cout << "Enter your choice (1 or 2): ";
            std::cin >> sub_choice;
            std::cout << std::endl;

            

            std::cout << "Enter the word to search for: " << std::endl;
            std::cin >> word_search;
            std::cout << std::endl;

            if (sub_choice == 1) // Linear Search chosen
            {
                heap.searchAndPrint(word_search);

            }
            else if (sub_choice == 2) // Binary Search Chosen
            {
                heap.searchBinary(word_search);
            }
            else if (sub_choice == 3) // Exit chosen
            {
                return 0;
            }
            else // Invalid choice
            {
                std::cout << "Invalid choice" << std::endl;
                return 1;
            }
        }
        else if (choice == 1) // Hash map is used
        {
            std::cout << "Enter the word to search for: " << std::endl;
            std::cin >> word_search;
            std::cout << std::endl;

            hash_map.search(word_search);
        }
    }
    else if (func_choice == 2) // Print a number of words chosen
    {
        std::cout << "Enter the number of words to print: ";
        std::cin >> sub_choice;

        if (sub_choice < 1 || sub_choice > 117659) // Checks bounds of input
        {
            std::cout << "Invalid choice" << std::endl;
            return 1;
        }

        for (int i = 0; i < sub_choice; i++) // Prints the words and each of its definitions
        {
            std::cout << node_list[i]->word << std::endl;
            for (int j = 0; j < node_list[i]->definitions->size(); j++)
            {
                std::cout << node_list[i]->definitions->at(j) << std::endl;
            }
            std::cout << std::endl;
        }
    }
    else if (func_choice == 3) // Exit chosen
    {
        return 0;
    }
    else // Invalid choice
    {
        std::cout << "Invalid choice" << std::endl;
        return 1;
    }   


    // for (int i = 0; i < num_words; i++) // Prints words and defitions. Used for testing purposes
    // {
    //     std::cout << node_list[i]->word << std::endl;
    //     std::cout << node_list[i]->definitions->at(0) << std::endl;
    //     std::cout << std::endl;
    // }


    file.close(); // Close the file

    return 0;
}