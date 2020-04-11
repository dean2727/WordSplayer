/**************************************************************
 * File:    SplayTree.h
 * Project: CMSC 341 - Project 3 - Word Frequency
 * Author : Dean Orenstein
 * Date   : 04/10/2020
 * Section: 518
 * E-mail:  dean27@tamu.edu
 *
 * SplayTree Class definition.
 * 
 *************************************************************/

#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include "DS_EXCEPTIONS.h"
#include "Node.h"
#include <typeinfo>
#include <iostream>  // For NULL

using namespace std;

template <typename Comparable>
class SplayTree
{
public:
    /**********************************************************************
     * Name: SplayTree (Constructor)
     * PreCondition: None. Non parameter constructor required for
     * node initialization
     * 
     * PostCondition: NULL root with NULL children
     *********************************************************************/
    SplayTree();

    /**********************************************************************
     * Name: SplayTree (Constructor)
     * PreCondition: SplayTree to be copied to the current SplayTree
     * 
     * PostCondition: SplayTree that is equal to rhs
     *********************************************************************/
    SplayTree(const SplayTree & rhs);

    /**********************************************************************
     * Name: SplayTree (Destructor)
     * PreCondition: None
     * 
     * PostCondition: Emptied tree and nullNode deleted from heap
     *********************************************************************/
    ~SplayTree();

    /**********************************************************************
     * Name: findMin
     * PreCondition: None
     * 
     * PostCondition: Minimum Comparable node in the tree
     *********************************************************************/
    const Comparable & findMin();

    /**********************************************************************
     * Name: findMax
     * PreCondition: None
     * 
     * PostCondition: Maximum Comparable node in the tree
     *********************************************************************/
    const Comparable & findMax();

    /**********************************************************************
     * Name: contains
     * PreCondition: Comparable element
     * 
     * PostCondition: true if the tree contains it; else false
     *********************************************************************/
    bool contains(const Comparable & x);

    /**********************************************************************
     * Name: isEmpty
     * PreCondition: None
     * 
     * PostCondition: true if empty; else false
     *********************************************************************/
    bool isEmpty() const;

    /**********************************************************************
     * Name: printTree (Bootstrap)
     * PreCondition: None
     * 
     * PostCondition: Call to the recursive version, outputting
     * tree's nodes
     *********************************************************************/
    void printTree() const;

    /**********************************************************************
     * Name: printRoot (Bootstrap)
     * PreCondition: None
     * 
     * PostCondition: Call to the return function, outputting root node
     *********************************************************************/
    void printRoot() const;

    /**********************************************************************
     * Name: makeEmpty
     * PreCondition: None
     * 
     * PostCondition: Emptied tree with no nodes
     *********************************************************************/
    void makeEmpty();

    /**********************************************************************
     * Name: insert (Bootstrap)
     * PreCondition: Comparable value whose node will be inserted
     * 
     * PostCondition: Call to iterative version, inserted node
     *********************************************************************/
    void insert(const Comparable& x);

    /**********************************************************************
     * Name: remove
     * PreCondition: Comparable value whose node will be removed
     * 
     * PostCondition: NULL root with NULL children
     *********************************************************************/
    void remove(const Comparable & x);

    /**********************************************************************
     * Name: Overload operator =
     * PreCondition: SplayTree to compare
     * 
     * PostCondition: New SplayTree via deep copy
     *********************************************************************/
    const SplayTree & operator=(const SplayTree & rhs);

    /**********************************************************************
     * Name: getSize
     * PreCondition: None
     * 
     * PostCondition: Int. Number of nodes in the tree
     *********************************************************************/
    int getSize();

    /**********************************************************************
     * Name: checkSubstrings (Bootstrap)
     * PreCondition: Substring to be checked in each word of each node
     * 
     * PostCondition: Call to internal method
     *********************************************************************/
    void checkSubstrings(string inPart);

    // Tracks the number of splays the tree has performed
    int m_numSplayed;
    
private:
    // Our data structure for the nodes of the tree, has element, left child, and right child
    struct BinaryNode {
        Comparable  element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode() : left(NULL), right(NULL) { }
        BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
            : element(theElement), left(lt), right(rt) { }
    };

    // Root node
    BinaryNode *root;

    // nullNode represents a NULL node
    BinaryNode *nullNode;

    // Tracks the number of nodes in the tree
    int m_size;

    /**********************************************************************
     * Name: insert (Iterative version)
     * PreCondition: Comparable element to insert, root node
     * 
     * PostCondition: Tree with node inserted and/or splayed
     *********************************************************************/
    void insert(const Comparable& x, BinaryNode*& t);

    /**********************************************************************
     * Name: reclaimMemory
     * PreCondition: Subtree t
     * 
     * PostCondition: Reclaimed (deleted) internal nodes in subtree t
     *********************************************************************/
    void reclaimMemory(BinaryNode* t);

    /**********************************************************************
     * Name: printTree (Recursive version)
     * PreCondition: Start node
     * 
     * PostCondition: Print tree in sorted order (inorder)
     *********************************************************************/
    void printTree(BinaryNode* t) const;

    /**********************************************************************
     * Name: printRoot (Return function)
     * PreCondition: Root node
     * 
     * PostCondition: Return Comparable element at root node
     *********************************************************************/
    const Comparable & printRoot(BinaryNode* t) const;

    /**********************************************************************
     * Name: clone
     * (Since BinaryNode is defined privately and this method 
     * returns a BinaryNode, we define it here)
     * PreCondition: None.  Non parameter constructor required for
     * node initialization \
     * 
     * PostCondition: Tree with the cloned a subtree
     *********************************************************************/
    BinaryNode * clone(BinaryNode* t) const {
        // Cannot test against nullNode!!!
        if (t == t -> left)
            return nullNode;
        else
            return new BinaryNode(t -> element, clone(t -> left), clone(t -> right));
    }

    /**********************************************************************
     * Name: rotateWithLeftChild
     * PreCondition: Node to be zigged right
     * 
     * PostCondition: Tree after zigging k2 right
     *********************************************************************/
    void rotateWithLeftChild(BinaryNode*& k2);

    /**********************************************************************
     * Name: rotateWithRightChild
     * PreCondition: Node to be zigged left
     * 
     * PostCondition: Tree after zigging k1 left
     *********************************************************************/
    void rotateWithRightChild(BinaryNode*& k1);

    /**********************************************************************
     * Name: splay
     * PreCondition: Comparable value to be splayed and root node
     * 
     * PostCondition: Tree as a result of splaying x to the root
     * (only performs zig lefts/rights)
     *********************************************************************/
    void splay(const Comparable& x, BinaryNode*& t);

    /**********************************************************************
     * Name: checkSubstrings (Recursive version)
     * PreCondition: Node in the tree to start at and word substring
     * 
     * PostCondition: Formatted output of the nodes that contain inPart
     * (case-insensitive)
     *********************************************************************/
    void checkSubstrings(BinaryNode* t, string inPart);
};

#include "SplayTree.cpp"
#endif