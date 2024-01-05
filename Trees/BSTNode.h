#pragma once

#include <iostream>
#include <string>

/**
 * Binary Search Tree Node:
 *    - data is the value of this node
 *    - count is the number of times the data has been inserted into the
 *      tree (minus the number of times it has been removed from the tree)
 *    - height is the height of the node within the tree, increasing
 *      from leaf up to the root.
 *    - color is the color of this node (either Color::RED or Color::BLACK)
 *    - left, right are the (possibly NULL) pointers to the left and right
 *      children, respectively
 *    - parent is the (possibly NULL) pointer to the parent node
 */
class BSTNode
{
public:
    enum Color
    {
        BLACK,
        RED
    };

    enum Direction
    {
        LEFT,
        ROOT,
        RIGHT
    };

    int data;
    int count;
    int height;
    Color color;
    BSTNode *left;
    BSTNode *right;
    BSTNode *parent;

    /**
     * Default Constructor. It is implemented for you, for your convenience.
     *
     * Input: N/A
     * Returns: a newly-created node representing an empty tree
     * Does: creates a new node with default values:
     *       - data = [uninitialized]
     *       - count = 0
     *       - height = -1
     *       - color = BLACK
     *       - left, right, parent = nullptr
     */
    BSTNode();

    /**
     * This constructor is implemented for you, for your convenience.
     *
     * Input: data (the value to store)
     * Returns: a newly-created tree node.
     * Does: creates a new node with default values:
     *       - data = value
     *       - count = 1
     *       - height = 0
     *       - color = BLACK
     *       - left, right = [empty tree]
     *       - parent = nullptr
     */
    BSTNode(int data);

    /**
     * Copy constructor
     * Input: other (the node to copy)
     * Returns: the root of a tree that is a copy of the tree rooted at other
     * Does: creates a new node with the same properties as other by performing
     *      a pre-order deep copy of the tree rooted at other. The root of the
     *      new tree has parent nullptr (it is considered the ultimate root of
     *      its tree).
     */
    BSTNode(const BSTNode &other);

    /**
     * Destructor.
     * Input: Node this - the node to free
     * Returns: N/A
     * Does: Performs a post-order delete to free all memory owned by this.
     *
     * Remember: this is automatically freed at the end of a destructor.
     */
    ~BSTNode();

    /**
     * This function is implemented for you, for your convenience.
     *
     * Input: Node this - the node to print
     * Returns: a string that is the concatenation of the node's data and its
     *      "decorator", which is either "", "*", "r", or "R" (computed as
     *      the node is BLACK with count=1, BLACK with count>1, RED with count
     *      1, or RED with count>1). This does not produce a recursive "pretty
     *      print" output. If this is empty, returns empty string.
     */
    std::string to_string() const;

    /**
     * Input: Node this - the root of the tree
     * Returns: a pointer to the node with the minimum value in the tree rooted
     *      at this
     * Assumes: this is not an empty tree
     */
    const BSTNode *minimum_value() const;

    /**
     * Input: Node this - the root of the tree
     * Returns: a pointer to the node with the maximum value in the tree rooted
     *      at this.
     * Assumes: this is not an empty tree
     */
    const BSTNode *maximum_value() const;

    /**
     * Input: Node this - the root of the tree
     *        int value - the value for which to search in the tree
     * Returns: a pointer to the node with value in the tree rooted at this
     * Does: performs a search in the tree rooted at this and returns the
     *      node with that value in the tree, or an empty tree if the value
     *      does not appear in the tree rooted at this.
     */
    const BSTNode *search(int value) const;

    /**
     * Input: Node this - the root of the tree
     *        int value - the value to insert
     * Returns: a pointer to the root of the tree into which value has just
     *      been inserted, with parent `nullptr`
     * Does: inserts (a single occurrence of) value into the tree rooted at
     *      this. Uses the "naive BST" insertion algorithm.
     */
    BSTNode *insert(int value);

    /**
     * Input: Node this - the root of the tree
     *        int value - the value to insert
     * Returns: a pointer to the root of the tree into which value has just
     *      been inserted, with parent `nullptr`. The returned tree is an AVL
     *      Tree.
     * Does: inserts (a single occurrence of) value into the tree rooted at
     *      this. Uses the AVL Tree insertion algorithm.
     */
    BSTNode *avl_insert(int value);

    /**
     * Input: Node this - the root of the tree
     *        int value - the value to insert
     * Returns: a pointer to the root of the tree into which value has just
     *      been inserted, with parent `nullptr`. The returned tree is a
     *      Red-Black Tree.
     * Does: inserts (a single occurrence of) value into the tree rooted at
     *      this. Uses the Red-Black Tree insertion algorithm.
     */
    BSTNode *rb_insert(int value);

    /**
     * Input: Node this - the root of the tree
     *        int value - the value to remove
     * Returns: a pointer to the root of the tree from which value has just
     *      been removed, whose parent pointer is `nullptr`. This method may
     *      return an empty tree.
     * Does: removes (a single occurrence of) value from the tree rooted at
     *      this. Uses the "naive BST" removal algorithm.
     */
    BSTNode *remove(int value);

    /**
     * Input: Node this - the root of the tree
     *        int value - the value to remove
     * Returns: a pointer to the root of the tree from which value has just
     *      been removed, whose parent pointer is `nullptr`. This method may
     *      return an empty tree. The returned tree is an AVL Tree.
     * Does: removes (a single occurrence of) value from the tree rooted at
     *      this. Uses the AVL Tree removal algorithm.
     */
    BSTNode *avl_remove(int value);

    /**
     * This function is implemented for you, for your convenience.
     *
     * Input: Node this - the root of the tree
     *        int value - the value to remove
     *        Neighborhood nb - reference to a BHV Neighborhood; value is
     *              replaced with the neighborhood of the removed node.
     * Returns: a pointer to the root of the tree from which value has just
     *      been removed, whose parent pointer is `nullptr`. This method may
     *      return an empty tree. The returned tree is a Red-Black Tree.
     * Does: removes (a single occurrence of) value from the tree rooted at
     *      this. Uses the Red-Black Tree removal algorithm.
     */
    BSTNode *rb_remove(int value);

    /**
     * Input: Node this - the root of the tree
     * Returns: the height of the tree rooted at this (an empty tree has height
     *      -1).
     */
    int node_height() const;

    /**
     * Input: Node this - the root of the tree
     * Returns: the number of non-empty nodes in the tree rooted at this
     */
    unsigned int node_count() const;

    /**
     * Input: Node this - the root of the tree
     * Returns: the total of all counts in the tree rooted at this
     */
    unsigned int count_total() const;

    /**
     * Input: Node this - the node whose parent we are searching for
     *        Node root - the root of the tree in which to search
     * Returns: a pointer to the parent of this in the tree rooted at root, or
     *      nullptr if this is the root of the tree
     * Does: Searches the tree rooted at root for this, then returns that
     *      node's parent.
     * Assumes: this.data has nonzero count in the tree rooted at root
     */
    const BSTNode *parent_in(BSTNode *root) const;

    /**
     * This function is implemented for you, for your convenience.
     *
     * Input: Node this - the root of a BST
     * Returns: true iff this is an empty tree
     */
    bool is_empty() const;

    /**
     * Input: Node this - the node to get the child of
     *        Direction dir - the direction to go
     * Returns: the child of node in the direction matching dir, and returns
     *      this if dir is ROOT.
     */
    BSTNode *child(Direction dir) const;

    /**
     * This function is implemented for you, for your convenience.
     *
     * Input: Node this - the node to get the child of
     *        Direction dir - the direction to go
     *        Node child - the node to replace as a child
     * Returns: N/A
     * Does: sets the child of node in the direction matching dir to child, and
     *      sets child's parent to this. Does nothing if dir is ROOT.
     */
    void set_child(Direction dir, BSTNode *child);

private:
    enum Shape
    {
        SHAPE_NONE,
        LL,
        LR,
        RL,
        RR
    };

    /**
     * You should use this struct in your code to help manage the complexity of
     *  insertion into a Red-Black Tree.
     *
     * Struct representing the neighborhood of a node with a possible red-red
     *  violation, organized in one of the following shapes (? trees are
     *  possibly empty, and the red-red violation is between [p] and [x]):
     *
     * Shape LL:
     *      __g__
     *     /     \
     *   [p]     y?
     *   / \
     * [x]  ?
     *
     * Shape LR:
     *      __g__
     *     /     \
     *   [p]     y?
     *   / \
     *  ?  [x]
     *
     * Shape RL:
     *      __g__
     *     /     \
     *    y?     [p]
     *           / \
     *         [x]  ?
     *
     * Shape RR:
     *      __g__
     *     /     \
     *    y?     [p]
     *           / \
     *          ?  [x]
     *
     */
    struct RRVNeighborhood
    {
        BSTNode *g;
        BSTNode *p;
        BSTNode *x;
        BSTNode *y;
        Shape shape;

        /**
         * This constructor is implemented for you, for your convenience.
         *
         * Input: Node g - the root of the neighborhood
         * Returns: A new neighborhood with given root g. If g is not BLACK or
         *  has height <= 1 or if there is no red-red-violation or if there is
         *  more than one red-red violation, the constructor produces a
         *  neighborhood with SHAPE_NONE and p, x, and y pointers that have
         *  undefined value.
         */
        RRVNeighborhood(BSTNode *g);
    };

    enum Case
    {
        CASE_NONE,
        CASE_1,
        CASE_2,
        CASE_3,
        CASE_4,
        CASE_5,
        CASE_6
    };

    /**
     * You should not use this struct in your code. It is used in rb_remove,
     *  which is implemented for you.
     *
     * Struct representing the neighborhood of a node with a possible
     *  black-height violation, organized in one of the following shapes or
     *  their reflections (? trees are possibly empty or missing, red nodes
     *  have [], nodes of possibly either color have ()). The dir field is the
     *  direction of n relative to its parent, p. The neighborhood of n may not
     *  match any of these cases, in which case it must not be a BLACK leaf and
     *  therefore does not require any special treatment for removal from a
     *  Red-Black Tree; its deletion case is CASE_NONE and all pointers except
     *  for n are nullptr.
     *
     * Case CASE_1:
     *        n?
     *
     * Case CASE_2:
     *      __p__
     *     /     \
     *    n       s?
     *   / \     / \
     *  ?   ?   c?  d?
     *
     * Case CASE_3:
     *      __p__
     *     /     \
     *    n      [s]
     *   / \     / \
     *  ?   ?   c?  d?
     *
     * Case CASE_4:
     *      _[p]_
     *     /     \
     *    n       s?
     *   / \     / \
     *  ?   ?   c?  d?
     *
     * Case CASE_5:
     *      _(p)_
     *     /     \
     *    n       s
     *   / \     / \
     *  ?   ?  [c]  d?
     *
     * Case CASE_6:
     *      _(p)_
     *     /     \
     *    n       s
     *   / \     / \
     *  ?   ?   c? [d]
     *
     */
    struct BHVNeighborhood
    {
        BSTNode *n;
        BSTNode *p;
        BSTNode *s;
        BSTNode *c;
        BSTNode *d;
        Case del_case;
        Direction dir;

        /**
         * This constructor is implemented for you, for your conveience.
         *
         * Input: Node n - the node that is about to be deleted
         *        Direction dir - the direction of n from its parent
         * Returns: a new neighborhood with given Node n, which is in one of
         *  the 6 possible deletion cases described above, each of which may be
         *  in one of two directions. If n has no parent, the direction of the
         *  new neighborhood will be ROOT, otherwise the direction of the new
         *  neighborhood will match dir, the parameter to this constructor.
         */
        BHVNeighborhood(BSTNode *p, Direction dir);

        /**
         * This function is implemented for you, for your convenience.
         *
         * Input: Neighborhood this - the neighborhood of the node that is
         *          about to be deleted from its tree, or was just deleted from
         *          its tree.
         * Returns: N/A
         * Does: Eliminates the black-height violation (if there is one) in the
         *      tree containing nb by "bubbling up" from Neighborhood nb.
         */
        void fix_blackheight_imbalance();
    };

    /**
     * This function is implemented for you, for your convenience.
     *
     * Input: Node this - the root of the tree
     *        int value - the value to remove
     *        Neighborhood nb - reference to a BHV Neighborhood; value is
     *              replaced with the neighborhood of the removed node (after
     *              this function, nb.n and nb.p's child to nb.dir are each an
     *              invalid pointer, pointing to the deleted node).
     * Returns: a pointer to the root of the tree from which value has just
     *      been removed, whose parent pointer is `nullptr`. This method may
     *      return an empty tree. The returned tree is a Red-Black Tree.
     * Does: removes (a single occurrence of) value from the tree rooted at
     *      this. Uses the Red-Black Tree removal algorithm.
     */
    BSTNode *rb_remove_helper(int value, BHVNeighborhood &nb);

    /**
     * This function is implemented for you, for your convenience.
     *
     * Input: Node this - the root of the tree.
     *        Direction dir - the direction in which to rotate
     * Returns: pointer to the root of rotated tree, whose parent pointer is
     *      undefined.
     * Does: rotates tree rooted at this in the direction dir. If dir is ROOT,
     *      this function does nothing.
     * Assumes: this has a non-empty subtree in the opposite direction of dir
     */
    BSTNode *dir_rotate(Direction dir);

    /**
     * Input: Node this - the root of the tree.
     * Returns: pointer to the root of rotated tree, whose parent pointer is
     *      the parent of this.
     * Does: right rotate tree rooted at this
     * Assumes: this has a non-empty left subtree
     * Runtime Complexity: O(1)
     */
    BSTNode *right_rotate();

    /**
     * Input: Node this - the root of the tree.
     * Returns: pointer to the root of rotated tree, whose parent pointer is
     *      the parent of this.
     * Does: left rotate tree rooted at this
     * Assumes: this has a non-empty right subtree
     */
    BSTNode *left_rotate();

    /**
     * Input: Node this - the root of an almost-balanced AVL Tree.
     * Returns: the balanced tree.
     * Does: If unbalanced, balances the tree rooted at node.
     * Assumes: the height difference between this's left and right children
     *      is no more than 2.
     */
    BSTNode *avl_balance();

    /**
     * Input: Node this - the root of a Red-Black tree.
     * Returns: A pointer to the root of the balanced tree
     * Does: Eliminates the red-red violation (if there is one) in the
     *      neighborhood of this, meaning this and its children and one of its
     *      grandchildren (the grandchild that is the cause of a red-red
     *      violation, if there is one). The black-height of the returned tree
     *      is the same as the black-height of this and the returned node is
     *      the root of a Red-Black tree, with the possible exception that it
     *      is RED. If there is no violation, return this unchanged.
     * Assumes: the only violation of Red-Black tree invariants in this appear
     *      in the neighborhood of this, and that violation is a single red-red
     *      violation, or that there are no violations at all in the tree
     *      rooted at this.
     */
    BSTNode *rb_eliminate_red_red_violation();

    /**
     * This function is implemented for you, for your convenience.
     *
     * Input: Node this - the root of the tree.
     * Returns: integer value signifying the height difference.
     * Does: calculates the difference in the height of the left and right
     *      subtree of this, computed as (this.right.height - this.left.height)
     */
    int height_diff() const;

    /**
     * Input: Node this - the root of the tree to make consistent
     * Returns: N/A
     * Does: Updates the tree rooted at this to be locally consistent, in the
     *      following way:
     *        - this.height = 1 + MAX(this.left.height, this.right.height)
     *        - this.left.parent = this
     *        - this.right.parent = this
     *  If this is empty, this.height is set to -1 and nothing is done to its
     *      children.
     */
    void make_locally_consistent();
};
