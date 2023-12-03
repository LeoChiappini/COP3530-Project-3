#include <iostream>
#include <vector>

#pragma once

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