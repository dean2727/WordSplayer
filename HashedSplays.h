/**************************************************************
 * File:    HashedSplays.h
 * Project: CMSC 341 - Project 3 - Word Frequency
 * Author : Dean Orenstein
 * Date   : 04/10/2020
 * Section: 518
 * E-mail:  dean27@tamu.edu
 *
 * HashedSplays Class definition.
 * 
 *************************************************************/

#ifndef HASHED_SPLAYS_H
#define HASHED_SPLAYS_H
#define ALPHABET_SIZE 26

#include "SplayTree.h"
#include "Exceptions.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

/**
 * CONSTRUCTION: with a size parameter, vector heap allocation
 * DESTRUCTION: delete vector from heap
 * 
 * ******************PUBLIC OPERATIONS****************************************************
 * void FileReader(inFileName)  --> Open the file, filter it to the distinct words, remove
 *                                  ALL punctuation, (except – and ‘ inside words) and
 *                                  numbers, then place those words into the appropriate
 *                                  Splay Tree in the Array table
 * void PrintTree(index)        --> Print the tree at the specified index
 * void PrintTree(letter)       --> Print the tree for the specified letter
 * void PrintHashCountResults() --> Prints the root node at each index in the array
 * void FindAll(inPart)         --> Print each node whose word starts with the letters
 *                                  of inPart
 * 
 * ******************PRIVATE OPERATIONS***************************************************
 * int GetIndex(inPart) --> Return the index of the specified letter
 * 
 * ******************ERRORS***************************************************************
 * Throws UnderflowException as warranted
 **/

class HashedSplays
{
public:
    // Number of trees in the vector
    int m_trees;

    /**********************************************************************
     * Name: HashedSplays (Constructor)
     * PreCondition: Size of the vector
     * 
     * PostCondition: New SplayTree<Node> vector of size size on the heap
     *********************************************************************/
    HashedSplays(int size);

    /**********************************************************************
     * Name: SplayTree (Destructor)
     * PreCondition: None
     * 
     * PostCondition: Deleted vector on the heap
     *********************************************************************/
    ~HashedSplays();

    /**********************************************************************
     * Name: FileReader
     * PreCondition: Name of the file to read from
     * 
     * PostCondition: All words read from the file and put into their
     * corresponding splay trees in the vector
     *********************************************************************/
    void FileReader(char* inFileName);

    /**********************************************************************
     * Name: PrintTree (int)
     * PreCondition: Index value for which tree to output
     * 
     * PostCondition: Formatted output of each node in the tree
     *********************************************************************/
    void PrintTree(int index);

    /**********************************************************************
     * Name: PrintTree (string)
     * PreCondition: Letter for which tree to output
     * 
     * PostCondition: Formatted output of each node in the tree
     *********************************************************************/
    void PrintTree(string letter);

    /**********************************************************************
     * Name: PrintHashCountResults
     * PreCondition: None
     * 
     * PostCondition: Prints the root node at each index in the array
     *********************************************************************/
    void PrintHashCountResults();

    /**********************************************************************
     * Name: FindAll
     * PreCondition: Substring to be searched in each Node of a
     * tree
     * 
     * PostCondition: Print each node whose word starts with the
     * letters of inPart (case-insensitive)
     *********************************************************************/
    void FindAll(string inPart);

private:
    // The vector of SplayTrees of Nodes
    vector < SplayTree<Node> > *table;

    // The index of the splay tree corresponding to inLetter
    int GetIndex(string inLetter);
};

#endif
