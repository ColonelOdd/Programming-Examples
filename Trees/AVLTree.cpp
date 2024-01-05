/*
 * Filename: AVLTree.cpp
 * Contains: Implementation of AVL Trees for CPSC 223
 * Part of: Homework assignment "AVL Trees" for CPSC 223
 * Modified by: Aidan Gibson
 * Problem Set: 6
 * Last Modified: 12/10
 */

#include <iostream>

#include "AVLTree.h"
#include "pretty_print.h"

using namespace std;

/********************************
 * BEGIN PUBLIC AVLTREE SECTION *
 ********************************/

/*
 * The AVLTree constructors use intializer lists. They are complete and you
 *  should not modify them.
 *
 * More info here: https://en.cppreference.com/w/cpp/language/constructor
 */
AVLTree::AVLTree() : root(new BSTNode()) {}

AVLTree::AVLTree(const AVLTree &source)
    : root(new BSTNode(*source.root)) {}

AVLTree::~AVLTree()
{
    delete this->root;
}

AVLTree &AVLTree::operator=(const AVLTree &source)
{
    // Check for self-assignment
    if (this->root == source.root)
    {
        return *this;
    }
    // Delete existing tree, if it exists
    if (this->root)
    {
        delete this->root->left;
        delete this->root->right;
    }
    BSTNode *root = source.root;
    // Copy root from source.root, if it exists
    if (root)
    {
        // Copies data to root from other.
        this->root->data = root->data;
        this->root->count = root->count;
        this->root->height = root->height;
        this->root->color = root->color;
        // Copies left and right roots.
        this->root->parent = nullptr;
        this->root->left = new BSTNode(*root->left);
        this->root->left->parent = this->root;
        this->root->right = new BSTNode(*root->right);
        this->root->right->parent = this->root;
    }
    // Don't forget to return *this
    return *this;
}

int AVLTree::minimum_value() const
{
    return this->root->minimum_value()->data;
}

int AVLTree::maximum_value() const
{
    return this->root->maximum_value()->data;
}

unsigned int AVLTree::count_of(int value) const
{
    return this->root->search(value)->count;
}

void AVLTree::insert(int value)
{
    this->root = this->root->avl_insert(value);
}

void AVLTree::remove(int value)
{
    this->root = this->root->avl_remove(value);
}

int AVLTree::tree_height() const
{
    return this->root->node_height();
}

int AVLTree::node_count() const
{
    return this->root->node_count();
}

int AVLTree::count_total() const
{
    return this->root->count_total();
}

void AVLTree::print_tree() const
{
    print_pretty(*this->root, 1, 0, std::cout);
}
