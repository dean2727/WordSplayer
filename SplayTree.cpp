/**************************************************************
 * File:    SplayTree.cpp
 * Project: CMSC 341 - Project 3 - Word Frequency
 * Author : Dean Orenstein
 * Date   : 04/10/2020
 * Section: 518
 * E-mail:  dean27@tamu.edu
 *
 * Splay Tree Class implementation.
 * 
 *************************************************************/

#ifndef SPLAY_TREE_CPP
#define SPLAY_TREE_CPP

#include "SplayTree.h"

using namespace std;

// constructor
template <typename Comparable>
SplayTree<Comparable>::SplayTree()
{
    nullNode = new BinaryNode;
    nullNode -> left = nullNode -> right = nullNode;
    root = nullNode;
    m_size = 0;
    m_numSplayed = 0;
}


// copy constructor
template <typename Comparable>
SplayTree<Comparable>::SplayTree(const SplayTree & rhs)
{
    nullNode = new BinaryNode;
    nullNode -> left = nullNode -> right = nullNode;
    root = nullNode;
    m_numSplayed = rhs.m_numSplayed;
    m_size = rhs.m_size;
    *this = rhs;
}


// destructor
template <typename Comparable>
SplayTree<Comparable>::~SplayTree() {
    makeEmpty();
    delete nullNode;
}


// makeEmpty
template <typename Comparable>
void SplayTree<Comparable>::makeEmpty() {
    // Splay max item to root and delete, over and over
    while(!isEmpty())
    {
        findMax();
        remove(root -> element);
    }
}


// findMin
template <typename Comparable>
const Comparable & SplayTree<Comparable>::findMin() {
    // UnderflowException if empty tree
    if (isEmpty())
        throw UnderflowException("Tree has no nodes!");

    BinaryNode *current = root;
    // Get to leftmost node
    while(current -> left != nullNode)
        current = current -> left;
    // Splay and return
    splay(current -> element, root);
    return current -> element;
}


// findMax
template <typename Comparable>
const Comparable & SplayTree<Comparable>::findMax() {
    // UnderflowException if empty tree
    if (isEmpty())
        throw UnderflowException("Tree has no nodes!");

    BinaryNode *current = root;
    // Get to rightmost node
    while (current -> right != nullNode)
        current = current -> right;
    // Splay and return
    splay(current -> element, root);
    return current -> element;
}


// contains
template <typename Comparable>
bool SplayTree<Comparable>::contains(const Comparable & x) {
    if (isEmpty())
        return false;
    // If we splay x to the root and then root -> element = x, then it contains x
    splay(x, root);
    return root -> element == x;
}


// isEmpty
template <typename Comparable>
bool SplayTree<Comparable>::isEmpty() const {
    return root == nullNode;
}


// printTree (Bootstrap)
template <typename Comparable>
void SplayTree<Comparable>::printTree() const {
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        printTree(root);
}


// printTree (Recursive version)
template <typename Comparable>
void SplayTree<Comparable>::printTree(BinaryNode* t) const {
    if (t != t -> left)
    {
        printTree(t -> left);
        cout << t -> element << endl;
        printTree(t -> right);
    }
}


// printRoot (Bootstrap)
template <typename Comparable>
void SplayTree<Comparable>::printRoot() const {
    // UnderflowException if empty tree
    if (isEmpty())
        throw UnderflowException("Tree has no nodes!");

    cout << printRoot(root);
}


// printRoot (Return function)
template <typename Comparable>
const Comparable & SplayTree<Comparable>::printRoot(BinaryNode* t) const {
    return t -> element;
}


// insert (Bootstrap) and iterative version
template <typename Comparable>
void SplayTree<Comparable>::insert(const Comparable& x) {
    m_size++;
    insert(x, root);
}


// insert (Iterative version)
template <typename Comparable>
void SplayTree<Comparable>::insert(const Comparable& x, BinaryNode*& t) {
    // Start with making new static binary node with element set to x
    static BinaryNode *newNode = NULL;
    if (newNode == NULL) {
        newNode = new BinaryNode;
    }
    newNode -> element = x;

    // First insert (insert to root)
    if (root == nullNode) {
        newNode -> left = newNode -> right = nullNode;
        root = newNode;
    }

    // Otherwise, splay to the root
    else {
        splay(x, root);
        // Determine whether to put original root as right child or left child
        if (x < root -> element) {
            newNode -> left = root -> left;
            newNode -> right = root;
            root -> left = nullNode;
            root = newNode;
        }
        else {
            if (root -> element < x) {
                newNode -> right = root -> right;
                newNode -> left = root;
                root -> right = nullNode;
                root = newNode;
            }
            // If x == original root element (duplicate), decrement the frequency (which was just incremented)
            else {
                root -> element.IncrementFrequency();
                m_size--;
                return;
            }
        }
    }
    // So next insert will call new
    newNode = NULL;
}


// remove
template <typename Comparable>
void SplayTree<Comparable>::remove(const Comparable & x) {
    BinaryNode *newTree;
    // If the tree doesnt contain x, dont proceed
    if (!contains(x))
        return;
    // If left child of root is NULL, assign new node memory location to right child
    if (root -> left == nullNode)
        newTree = root -> right;
    // Else, find the max in the left subtree, splay it to the root, and attach right child
    else {
        newTree = root -> left;
        splay(x, newTree);
        newTree -> right = root -> right;
    }
    // Delete old root, assign new root, and decrement size
    delete root;
    root = newTree;
    m_size--;
}


// copy assignment operator
template <typename Comparable>
const SplayTree<Comparable> & SplayTree<Comparable>::operator=(const SplayTree& rhs) {
    // If rhs isnt the same reference, empty tree and clone it from root
    if (this != &rhs) {
        makeEmpty();
        root = clone(rhs.root);
        m_numSplayed = rhs.m_numSplayed;
        m_size = rhs.m_size;
    }
    return *this;
}


// reclaimMemory
template <typename Comparable>
void SplayTree<Comparable>::reclaimMemory(BinaryNode* t) {
    if (t != t -> left) {
        reclaimMemory(t -> left);
        reclaimMemory(t -> right);
        delete t;
    }
}


// rotateWithLeftChild (zig right)
template <typename Comparable>
void SplayTree<Comparable>::rotateWithLeftChild(BinaryNode*& k2) {
    // k1 is the left subtree of k2 (the root)
    BinaryNode *k1 = k2 -> left;
    // The left of root is now the right of this subtree
    k2 -> left = k1 -> right;
    // The right of k1 (new root) is k2 (original root)
    k1 -> right = k2;
    // k2 (original root) is the memory location of k1 (new root)
    k2 = k1;
}


// rotateWithRightChild (zig left)
template <typename Comparable>
void SplayTree<Comparable>::rotateWithRightChild(BinaryNode*& k1) {
    // k2 is the right subtree of k1 (the root)
    BinaryNode *k2 = k1 -> right;
    // The right of root is now the left of this subtree
    k1 -> right = k2 -> left;
    // The left of k2 (new root) is k1 (original root)
    k2 -> left = k1;
    // k1 (original root) is the memory location of k2 (new root)
    k1 = k2;
}


// splay (only performs zig lefts/rights)
template <typename Comparable>
void SplayTree<Comparable>::splay(const Comparable& x, BinaryNode*& t) {
    BinaryNode *leftTreeMax, *rightTreeMin;
    static BinaryNode header;  // Everything is null
    header.left = header.right = nullNode;
    // If leftTreeMax or rightTreeMin change, so does value of header
    leftTreeMax = rightTreeMin = &header;
    // Guarantee a match
    nullNode -> element = x;

    // Loop breaks if x gets to level 2 of the tree (e.g. depth of root -> left -> right)
    for (; ;) {
        // If x is to be found in the left subtree
        if (x < t -> element) {
            /* If x is greater than current t's left child, then it is found at least a generation
            past t's children and thus we perform a zig right with t */
            if (x < t -> left -> element)
                rotateWithLeftChild(t);
            if (t -> left == nullNode) {
                break;
            }
            // Link Right
            rightTreeMin -> left = t;
            rightTreeMin = t;
            t = t -> left;
        }
        // If x is to be found in the right subtree
        else if (t -> element < x) {
            /* If x is less than current t's right child, then it is found at least a generation
            past t's children and thus we perform a zig left with t */
            if (t -> right -> element < x)
                rotateWithRightChild(t);
            if (t -> right == nullNode) {
                break;
            }
            // Link Left
            leftTreeMax -> right = t;
            leftTreeMax = t;
            t = t -> right;
        }
        // Otherwise, x equals t element and we break
        else {
            break;
        }
    }

    // Last rotation to get x to the root
    leftTreeMax -> right = t -> left;
    rightTreeMin -> left = t -> right;
    t -> left = header.right;
    t -> right = header.left;
    // Increment numSplayed
    m_numSplayed++;
}


// getSize
template <typename Comparable>
int SplayTree<Comparable>::getSize() {
    return m_size;
}


// checkSubstrings (Bootstrap)
template <typename Comparable>
void SplayTree<Comparable>::checkSubstrings(string inPart) {
    // UnderflowException if empty tree
    if (isEmpty())
        throw UnderflowException("Tree has no nodes!");

    checkSubstrings(root, inPart);
}


// checkSubstrings (Recursive)
template <typename Comparable>
void SplayTree<Comparable>::checkSubstrings(BinaryNode* t, string inPart) {
    // Inorder traversal (left -> process -> right)
    if (t != t -> left) {
        checkSubstrings(t -> left, inPart);
        // Need to cast inPart to some dummy Node so that % works
        Node rhs(inPart, 1);
        if (t -> element % rhs)
            cout << t -> element << endl;
        checkSubstrings(t -> right, inPart);
    }
}

#endif