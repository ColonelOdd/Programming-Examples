/*
 * Filename: BSTree.h
 * Contains: Interface of Naive Binary Search Trees for CPSC 223
 * Part of: Homework assignment "Trees" for CPSC 223
 * Author: Alan Weide
 * 
 */

#pragma once

#include <iostream>
#include "BSTNode.h"

class BSTree
{
private:
    /**
     * The root of this tree.
     */
    BSTNode *root;

public:
    /**
     * Default constructor. Creates an empty tree.
     */
    BSTree();

    /**
     * Copy constructor. Creates a new tree as a deep copy of source
     */
    BSTree(const BSTree &source);

    /**
     * Destructor. Frees all memory owned by this.
     */
    ~BSTree();

    /**
     * Assignment overload. Assigns rhs to this by deep copy.
     */
    BSTree &operator=(const BSTree &rhs);

    /**
     * Input: BSTree this - the tree
     * Returns: the minimum value in this
     * Does: Searches this for its minimum value, and returns it. Behavior is
     *      undefined if this is empty
     */
    int minimum_value() const;

    /**
     * Input: BSTree this - the tree
     * Returns: the maximum value in this
     * Does: Searches this for its maximum value, and returns it. Behavior is
     *      undefined if this is empty
     */
    int maximum_value() const;

    /**
     * Input: BSTree this - the tree
     *        int value - value to search for
     * Returns: the number of occurences of value in this, or 0 if value is not
     *      in this
     * Does: searches the tree for value
     */
    unsigned int count_of(int value) const;

    /**
     * Input: BSTree this - the tree
     *        int value - value to insert
     * Returns: N/A
     * Does: Inserts value into this, either by creating a new node or, if
     *      value is already in this, by incrementing that node's count
     */
    void insert(int value);

    /**
     * Input: BSTree this - the tree
     *        int value - the value to remove
     * Returns: N/A
     * Does: Removes value from the tree. If a node's count is greater than
     *      1, the count is decremented and the node is not removed. Nodes
     *      with a count of 1 are removed according to the algorithm
     *      discussed in class, with arbitrary decisions made in the same way
     *      as the reference implementation.
     */
    void remove(int value);

    /**
     * Input: BSTree this - the tree
     * Returns: the height of this
     * Does: computes and returns the height of this tree. (An empty tree has
     *      height -1.)
     */
    int tree_height() const;

    /**
     * Input: BSTree this - the tree
     * Returns: The number of nodes in this tree
     * Does: Counts and returns the number of nodes in this
     */
    int node_count() const;

    /**
     * Input: BSTree this - the tree
     * Returns: the total of all node values, including duplicates.
     * Does: Computes and returns the sum of all nodes and duplicates in
     *      this
     */
    int count_total() const;

    /**
     * Input: BSTree this - the tree
     * Returns: N/A
     * Does: Pretty-prints the tree
     */
    void print_tree() const;
};
