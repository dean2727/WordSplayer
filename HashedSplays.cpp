/**************************************************************
 * File:    HashedSplays.cpp
 * Project: CMSC 341 - Project 3 - Word Frequency
 * Author : Dean Orenstein
 * Date   : 04/10/2020
 * Section: 518
 * E-mail:  dean27@tamu.edu
 *
 * Hashed Splays Class implementation.
 * 
 *************************************************************/

#ifndef HASHEDSPLAYS_CPP
#define HASHEDSPLAYS_CPP

#include "HashedSplays.h"
#include <iostream>
#include <string>

using namespace std;


// constructor
HashedSplays::HashedSplays(int size) {
    m_trees = size;
    table = new std::vector< SplayTree<Node> >(m_trees);  // the space in > > is necessary
}


// destructor
HashedSplays::~HashedSplays() {
    delete table;
}


// FileReader
void HashedSplays::FileReader(char* inFileName) {
    // Check if file exists
    if (!Util::FileExists(inFileName))
        throw Exceptions("File does not exist!");
    // Open the file and check if successful
    ifstream inFile(inFileName);
    if (!inFile)
        throw Exceptions("Could not open file!");
    
    // Read in the lines until at the end of the file
    string line;
    while (getline(inFile, line)) {

        // If the line is just whitespace, continue
        if (line == "")
            continue;

        stringstream words(line);
        string word;
        // Read and strip the contents of the line
        while (words >> word) {
            word = Util::Strip(word);
            // Continue if theres no alpha chars in the word
            if (word == "")
                continue;
            // Otherwise, make the node and insert it into correct tree
            Node newNode(word, 1);
            int index = GetIndex(word);
            table -> at(index).insert(newNode);
        }
    }
    inFile.close();
}


// PrintTree (int)
void HashedSplays::PrintTree(int index) {
    // Throw error if out of bounds
    if (index < 0 || index > m_trees-1) {
        throw ArrayIndexOutOfBoundsException("Index out of bounds!");
    }

    // Call print tree for appropriate tree
    table -> at(index).printTree();
    cout << "This tree has had " << table -> at(index).m_numSplayed << " splays.\n";
}


// PrintTree (string)
void HashedSplays::PrintTree(string letter) {
    // Get the vector index of the splay tree corresponding to the letter first
    int index = GetIndex(letter);
    PrintTree(index);
}


// PrintHashCountResults
void HashedSplays::PrintHashCountResults() {
    for (int i = 0; i < m_trees; ++i) {
        // If tree is empty
        if (table -> at(i).isEmpty())
            cout << "This tree has no nodes\n";
        // Else, output root info and number of nodes in that tree
        else {
            cout << "This tree starts with ";
            table -> at(i).printRoot();
            cout << " and has " << table -> at(i).getSize() << " nodes\n";
        }
    }
}


// FindAll
void HashedSplays::FindAll(string inPart) {
    cout << "Printing the results of nodes that start with \'" << Util::Lower(inPart) << "\'\n";
    // Get the table index from the first letter of inPart
    int index = GetIndex(inPart);
    // Traverse through each node of the tree, checking if it has inPart substring
    table -> at(index).checkSubstrings(inPart);
}


// GetIndex
int HashedSplays::GetIndex(string inLetter) {
    // For safety, index inLetter and lowercase it to get actual letter
    char firstLetter = Util::Lower(inLetter).at(0);
    // ASCII value of 'a' is 97, 'b' is 98, etc., so return value minus 97 for index
    int ASCIIval = (int)firstLetter;
    return ASCIIval - 97;
}

#endif