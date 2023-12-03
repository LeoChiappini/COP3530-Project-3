#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>



// Declaring a struct to store the word, its definitions, and the other data structure information
struct Node
{
    std::string word;
    std::vector<std::string>* definitions;
    
    Node* next;
    Node* prev;

    Node(std::string word_in, std::string definition_in)
    {
        this->word = word_in;

        this->definitions = new std::vector<std::string>;

        this->definitions->push_back(definition_in);

        this->next = nullptr;
        this->prev = nullptr;
    }

    ~Node()
    {
        delete this->definitions;
    }

};

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

    //Node* node_temp; // Temporary node pointer to be used to create nodes





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
        std::cout << "Enter the number of words to be inserted. Must be between 1 and 100,000: ";
        
        std::cin >> choice;

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

    for (int i = 0; i < 10 && std::getline(file, line); ++i) // Read each line from the file
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
    std::cout << "3. Exit" << std::endl;
    std::cout << "Enter your choice (1 or 2): ";

    std::cin >> choice;

    std::cout << std::endl;

    if (choice == 1) // Hash Map chosen
    {
        //MinHeap::insertFromVector(node_list);
    }
    else if (choice == 2) // Heap chosen
    {
        //HashTable::insertFromVector(node_list);
    }
    else if (choice == 3) // Exit chosen
    {
        return 0;
    }
    else // Invalid choice
    {
        std::cout << "Invalid choice" << std::endl;
        return 1;
    }

    for (int i = 0; i < num_words; i++)
    {
        std::cout << node_list[i]->word << std::endl;
        std::cout << node_list[i]->definitions->at(0) << std::endl;
        std::cout << std::endl;
    }


    file.close(); // Close the file

    return 0;
}