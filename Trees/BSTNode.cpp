/*
 * BSTNode.cpp
 * CPSC 223 Pset 6
 *
 * Implementation of BSTNode for Trees Problem Set
 *
 * Author: Aidan Gibson
 * Problem Set: 6
 * Last Modified: 12/11
 */

#include "BSTNode.h"

#include <cassert>
#include <algorithm>
#include <string>

/**
 * A pseudo-assert macro that immediately returns from the enclosing function
 *  if e is false.
 */
#define ABORT_UNLESS(e) \
    if (!(e))           \
    {                   \
        return;         \
    }

/**
 * This function is implemented for you, for your convenience.
 *
 * Input: Node node - the node to decorate
 * Returns: the decorator to print with this node using its to_string function.
 *      The decorator is either nothing, '*', 'r', or 'R' (computed as node is
 *      BLACK with count <=1, BLACK with count >1, RED with count =1, or RED
 *      with count >1).
 */
std::string decorator_string(const BSTNode *node)
{
    std::string dec = "";
    if (node && node->node_height() >= 0)
    {
        if (node->color == BSTNode::Color::RED)
        {
            if (node->count > 1)
            {
                dec = "R";
            }
            else
            {
                dec = "r";
            }
        }
        else
        {
            if (node->count > 1)
            {
                dec = "*";
            }
        }
    }
    return dec;
}

/**
 * This function is implemented for you, for your convenience.
 *
 * Input: Node node - the node to get the value label for
 * Returns: node's data as a string, or empty_string if node is an empty tree.
 */
std::string value_string(const BSTNode *node)
{
    std::string value = "";
    if (node && node->node_height() >= 0)
    {
        value = std::to_string(node->data);
    }
    return value;
}

/**
 * This function is implemented for you, for your conveninence.
 *
 * Input: Node a
 *        Node b
 * Returns: N/A
 * Does: Swaps the colors of Nodes a and b.
 * Assumes: a and b are both non-null
 */
void swap_colors(BSTNode *a, BSTNode *b)
{
    BSTNode::Color t = a->color;
    a->color = b->color;
    b->color = t;
}

/**
 * This function is implemented for you, for your convenience.
 *
 * It is implemented in two different ways (one of them commented out):
 *    - The commented-out version makes explicit that LEFT is the opposite of
 *      RIGHT, and that ROOT has no opposite
 *    - The uncommented version uses the fact that enum values in C++ are given
 *      integer values in increasing order starting at 0 and can be implicitly
 *      converted into an int. Since the Direction enum is defined in order
 *      LEFT, ROOT, RIGHT, the values are LEFT=0, ROOT=1, RIGHT=2.
 * Both exhibit constant time and space complexity so are asymptotically
 *  equivalent.
 *
 * Input: Direction dir
 * Returns: the opposite of dir, or ROOT if dir is ROOT.
 */
BSTNode::Direction opposite_direction(BSTNode::Direction dir)
{
    // BSTNode::Direction opp = dir;
    // if (dir == BSTNode::Direction::LEFT)
    // {
    //     opp = BSTNode::Direction::RIGHT;
    // }
    // else if (dir == BSTNode::Direction::RIGHT)
    // {
    //     opp = BSTNode::Direction::LEFT;
    // }
    // return opp;
    return BSTNode::Direction(BSTNode::Direction::RIGHT - dir);
}

/*
 * These BSTNode constructors use intializer lists. They are complete and you
 *  may not modify them.
 *
 * More info here: https://en.cppreference.com/w/cpp/language/constructor
 */
BSTNode::BSTNode() : count(0), height(-1), color(BLACK),
                     left(nullptr), right(nullptr), parent(nullptr) {}
BSTNode::BSTNode(int data)
    : data(data), count(1), height(0), color(BLACK),
      left(new BSTNode()), right(new BSTNode()), parent(nullptr) {}

/*
 * TODO: The BSTNode copy constructor is incomplete. You must complete it. You
 *  may use an initializer list, or you may write a traditional constructor
 *  function, or both.
 */
BSTNode::BSTNode(const BSTNode &other){
    // Make a pointer out of other.
    const BSTNode* other_pointer = &other;
    // Initializes data of node using BSTNode's info.
    this->data = other_pointer->data;
    this->count = other_pointer->count;
    this->height = other_pointer->height;
    this->color = other_pointer->color;

    // Recursively creates new nodes.
    // Check left to see if need to create new nodes.
    if (!other_pointer->left->is_empty())
    {
        this->left = new BSTNode(*other_pointer->left);
        this->left->parent = this;
    }
    else
    {
        this->left = new BSTNode();
    }
    // Check right to see if need to create new nodes.
    if (!other_pointer->right->is_empty())
    {
        this->right = new BSTNode(*other_pointer->right);
        this->right->parent = this;
    }
    else
    {
        this->right = new BSTNode();
    }

    // If root, then make parent the nullprt.
    if (other_pointer->parent == nullptr)
    {
        this->parent = nullptr;
    }
}

BSTNode::~BSTNode(){
    // Recursively deleted every node int ree.
    delete this->right;
    delete this->left;
}

std::string BSTNode::to_string() const
{
    return value_string(this) + decorator_string(this);
}

const BSTNode *BSTNode::minimum_value() const
{
    // Checks to see if can go further left
    const BSTNode *cursor = this;
    while (!cursor->left->is_empty())
    {
        cursor = cursor->left;
    }
    // Returns value furthest left.
    return cursor;
}

const BSTNode *BSTNode::maximum_value() const
{
    // Checks to see if can go further right
    const BSTNode *cursor = this;
    while (!cursor->right->is_empty())
    {
        cursor = cursor->right;
    }
    // Returns value furthest right.
    return cursor;
}

const BSTNode *BSTNode::search(int value) const
{
    // Set a cursor equal to this.
    const BSTNode *cursor = this;
    // Keep searching until at leaf.
    while (!cursor->is_empty())
    {
        // Searches through tree for value matching input, if value matches return node.
        if (cursor->data < value)
        {
            cursor = cursor->right;
        }
        else if (cursor->data > value)
        {
            cursor = cursor->left;
        }
        else
        {
            return cursor;
        }
    }
    // If searched and not found tree, return empty node.
    return cursor;
}

BSTNode *BSTNode::insert(int value)
{
    // Sets up two cursors to go through list.
    BSTNode *cursor = this;
    BSTNode *prev = this;
    // Keep searching until at leaf.
    while (!cursor->is_empty())
    {
        // Keeps descending tree, updates count if runs into value already.
        if (cursor->data < value)
        {
            prev = cursor;
            cursor = cursor->right;
        }
        else if (cursor->data > value)
        {
            prev = cursor;
            cursor = cursor->left;
        }
        else
        {
            cursor->count++;
            return this;
        }
    }
    // Found location, insert!
    cursor->data = value;
    cursor->count = 1;
    cursor->height = 0;
    cursor->left = new BSTNode();
    cursor->right = new BSTNode();
    cursor->height = 0;
    if (prev->data != cursor->data)
    {
        cursor->parent = prev;
    }
    else
    {
        cursor->parent = nullptr;
        return this;
    }
    // Check to see if heights need to be updated.
    if (prev->left->is_empty() || prev->right->is_empty())
    {
        // Keeps updating height over and over again.
        while (prev != nullptr)
        {
            prev->height = std::max(prev->left->height, prev->right->height) + 1;
            prev = prev->parent;
        }
    }
    // Return root once inserted.
    BSTNode* root = this;
    while (root->parent != nullptr)
    {
        root = root->parent;
    }
    return root;
}

BSTNode *BSTNode::avl_insert(int value)
{
    /********************************
     ***** BST Insertion Begins *****
     ********************************/

    // Basic insertion, retrieve inserted node.
    this->insert(value);
    const BSTNode *path_start = search(value);
    /********************************
     ****** BST Insertion Ends ******
     ********************************/

    /********************************
     **** AVL Maintenance Begins ****
     ********************************/

    // Catches edge case that this is first insertion.
    BSTNode* child = path_start->parent;
    if (child == nullptr)
    {
        return this;
    }
    // Start looking for violators of height.
    BSTNode* parent = path_start->parent->parent;
    BSTNode *violator = nullptr;
    while (parent != nullptr)
    {
        // If difference greater than 1, caught violator 
        if (abs(parent->height_diff()) > 1)
        {
            // Set violator and balance!
            violator = parent;
            violator = violator->avl_balance();
            // Update heights accordingly
            while (violator != nullptr)
            {
                violator->height = std::max(violator->left->height, violator->right->height) + 1;
                violator = violator->parent;
            }
        }
        // Iterate 
        parent = parent->parent;
    }
    
    /********************************
     ***** AVL Maintenance Ends *****
     ********************************/

    // Ensure the root is the top node and return
    BSTNode* root = this;
    while (root->parent != nullptr)
    {
        root = root->parent;
    }
    return root;
}

BSTNode *BSTNode::rb_insert(int value)
{

    /********************************
     ***** BST Insertion Begins *****
     ********************************/
    // Insert into tree and then find the node.
    this->insert(value);
    const BSTNode *start = search(value);
    // If node count increased or first node, end.
    if (start->parent == nullptr || start->count > 1)
    {
        return this;
    }
    // Starting pathing from inserted node.
    BSTNode* path = start->parent;
    BSTNode *prev = nullptr;
    // Set up child as red and initial path.
    if (start == path->left)
    {
        path->left->color = RED;
        prev = path->left;
    }
    else
    {
        path->right->color = RED;
        prev = path->right;
    }
    /********************************
     ****** BST Insertion Ends ******
     ********************************/

    /********************************
     ***** RB Maintenance Begins ****
     ********************************/
    // Check for red/black violaiton.
    BSTNode *violator = nullptr;
    while (path != nullptr)
    {
        // If RED RED violation
        if (path->color == prev->color && prev->color == RED)
        {
            // If violator found, go to grandparent then fix.
            violator = path->parent;
            violator->rb_eliminate_red_red_violation();
            // Update heights.
            while (violator != nullptr)
            {
                violator->height = std::max(violator->left->height, violator->right->height) + 1;
                violator = violator->parent;
            }
        }
        // Iterate
        prev = path;
        path = path->parent;
    }

    /********************************
     ****** RB Maintenance Ends *****
     ********************************/

    // Ensure this is root or find new root, then return.
    BSTNode* root = this;
    while (root->parent != nullptr)
    {
        root = root->parent;
    }
    return root;
}

BSTNode *BSTNode::remove(int value)
{
    // Obtains node to remove.
    BSTNode *node_to_remove = const_cast<BSTNode *>(search(value));
    // If not found, return the empty tree. If count above 1, remove count and return.
    if (node_to_remove->is_empty())
    {
        return this;
    }
    else if (node_to_remove->count > 1)
    {
        node_to_remove->count--;
        return this;
    }
    // Finds successor to the node.
    BSTNode *parent = node_to_remove->parent;
    BSTNode *successor = nullptr;
    BSTNode *successor_child = nullptr;
    // Consider 4 possible cases of removal
    if (node_to_remove->height == 0)
    {
        // Case 1: Node has no children, set to new BSTNode
        successor = new BSTNode();
    }
    else if (node_to_remove->left->is_empty())
    {
        // Case 2: Node has one child as successor, right
        successor = node_to_remove->right;
    }
    else if (node_to_remove->right->is_empty())
    {
        // Case 3: Node has one child as successor, left
        successor = node_to_remove->left;
    }
    else
    {
        // Case 4: node_to_remove has multiple children to consider, search for successor
        // Go right once, then repeatedly left to obtain valid successor.
        successor = node_to_remove->right;
        while (!successor->left->is_empty())
        {
            successor = successor->left;
        }
        // If successor has children, store them; left is always newNode, so delete.
        successor_child = successor->right;
        delete successor->left;
        // Found successor, remove it from its parent.
        if (successor->parent->right == successor)
        {
            successor->parent->right = successor_child;
            // If successor isn't a dummy node, set its parent to successor's parent.
            if (!successor_child->is_empty())
            {
                successor_child->parent = successor->parent;
            }
        }
        else
        {
            successor->parent->left = successor_child;
            // If successor isn't a dummy node, set its parent to successor's parent.
            if (!successor_child->is_empty())
            {
                successor_child->parent = successor->parent;
            }
        }
        // Pass on children to successor, not right side if successor is immediately right.
        if (node_to_remove->right != successor)
        {
            successor->right = node_to_remove->right;
            node_to_remove->right->parent = successor;
        }
        successor->left = node_to_remove->left;
        node_to_remove->left->parent = successor;
    }
    // Set successor's parent to parent of removed node.
    successor->parent = parent;
    // If not root
    if (parent != nullptr)
    {
        // Update parent to reference successor.
        if (parent->right == node_to_remove)
        {
            parent->right = successor;
        }
        else
        {
            parent->left = successor;
        }
    }
    // Delete node_to_remove with no parent, only deleting unused dummy nodes.
    if (node_to_remove->left->is_empty() && node_to_remove->left != successor->left)
    {
        delete node_to_remove->left;
    }
    if (node_to_remove->right->is_empty() && node_to_remove->right != successor->right)
    {
        delete node_to_remove->right;
    }
    node_to_remove->left = nullptr;
    node_to_remove->right = nullptr;
    delete node_to_remove;
    // Picks node to use to update heights
    BSTNode* prev = nullptr;
    if ((successor_child == nullptr || successor_child->is_empty()) && !successor->is_empty())
    {
        prev = successor;
    }
    else if ((successor_child == nullptr || successor_child->is_empty()))
    {
        prev = parent;
    }
    else
    {
        prev = successor_child;
    }
    // Updates heights and determines new root.
    BSTNode* root = this;
    while (prev != nullptr)
    {
        prev->height = std::max(prev->left->height, prev->right->height) + 1;
        root = prev;
        prev = prev->parent;
    }
    // Returns root
    return root;
}

BSTNode *BSTNode::avl_remove(int value)
{
    /********************************
     ****** BST Removal Begins ******
     ********************************/

    // Store info about the node removed
    const BSTNode *node_to_remove = this->search(value);
    // If node_to_remove not found, return tree unchanged.
    if (node_to_remove->is_empty())
    {
        return this;
    }
    // Find where we need to start updating the tree.
    BSTNode *path = node_to_remove->parent;
    BSTNode *successor = nullptr;
    if (!node_to_remove->right->is_empty() && !node_to_remove->right->is_empty())
    {
        successor = node_to_remove->right;
        while (!successor->left->is_empty())
        {
            successor = successor->left;
        }
        if (successor->parent != node_to_remove)
        {
            path = successor->parent;
        }
    }
    // Get root from initial remove
    BSTNode *root = this->remove(value);
    /********************************
     ******* BST Removal Ends *******
     ********************************/

    /********************************
     **** AVL Maintenance Begins ****
     ********************************/

    // Path through to find and correct violators
    BSTNode *violator = nullptr;
    while (path != nullptr)
    {
        // If difference greater than 1, found violator.
        if (abs(path->height_diff()) > 1)
        {
            // Height violation!
            violator = path;
            violator->avl_balance();
        }
        root = path;
        path = path->parent;
    }
    /********************************
     ***** AVL Maintenance Ends *****
     ********************************/

    // Return root.
    return root;
}

BSTNode *BSTNode::rb_remove(int value)
{
    // This is implemented for you.
    BHVNeighborhood nb(this, ROOT);
    BSTNode *root = this->rb_remove_helper(value, nb);
    nb.fix_blackheight_imbalance();
    return root;
}

int BSTNode::node_height() const
{
    // Height of Node
    return this->height;
}

unsigned int BSTNode::node_count() const
{
    // Return 0 if this->height = -1.
    if (this->is_empty())
    {
        return 0;
    }
    // Otherwise count nodes recursively
    if (this->left->is_empty() && this->right->is_empty())
    {
        return 1;
    }
    else if (this->left->is_empty())
    {
        return (1 + this->right->node_count());
    }
    else if (this->right->is_empty())
    {
        return (1 + this->left->node_count());
    }
    else
    {
        return (1 + this->right->node_count() + this->left->node_count());
    }
}

unsigned int BSTNode::count_total() const
{
    // Return 0 if this->height = -1.
    if (this->height == -1)
    {
        return 0;
    }
    // Otherwise count nodes.
    if (this->left->is_empty() && this->right->is_empty())
    {
        return this->count;
    }
    else if (this->left->is_empty())
    {
        return (this->count + this->right->count_total());
    }
    else if (this->right->is_empty())
    {
        return (this->count + this->left->count_total());
    }
    else
    {
        return (this->count + this->right->count_total() + this->left->count_total());
    }
}

const BSTNode *BSTNode::parent_in(BSTNode *root) const
{
    // As per Alan's instructions
    return this->parent;
}

bool BSTNode::is_empty() const
{
    bool empty_by_count = this->count == 0;
    bool empty_by_height = this->height == -1;
    bool empty_by_children = !this->left && !this->right;

    // Assert some invariants about binary search trees
    assert(!this->left == !this->right);
    assert(empty_by_count == empty_by_height);
    assert(empty_by_height == empty_by_children);

    // Return any of the equivalent checks
    return empty_by_count;
}

BSTNode *BSTNode::child(Direction dir) const
{
    BSTNode *child = nullptr;
    if (dir == LEFT)
    {
        child = this->left;
    }
    else if (dir == RIGHT)
    {
        child = this->right;
    }
    return child;
}

void BSTNode::set_child(Direction dir, BSTNode *child)
{
    if (dir != ROOT)
    {
        if (dir == LEFT)
        {
            this->left = child;
        }
        else if (dir == RIGHT)
        {
            this->right = child;
        }
        child->parent = this;
    }
    else
    {
        assert(false);
    }
}

/*************************
 * BEGIN PRIVATE SECTION *
 *************************/

BSTNode::RRVNeighborhood::RRVNeighborhood(BSTNode *root)
    : g{root}, p{nullptr}, x{nullptr}, y{nullptr}, shape{SHAPE_NONE}
{
    // Stop if g is RED or too short
    ABORT_UNLESS((this->g->color == BLACK) &&
                 (this->g->node_height() > 1));

    if (this->g->left->color == BLACK)
    {
        // If there is a red-red violation, it's to the right
        this->y = this->g->left;
        this->p = this->g->right;

        // Stop if g has two BLACK children
        ABORT_UNLESS(this->p->color == RED);

        if (this->p->left->color == RED)
        {
            this->shape = RL;
            this->x = this->p->left;
        }
        else
        {
            // Stop if there is no red-red violation
            ABORT_UNLESS(this->p->right->color == RED);

            this->shape = RR;
            this->x = this->p->right;
        }
    }
    else if (this->g->right->color == BLACK)
    {
        // If there is a red-red violation, it's to the left
        this->y = this->g->right;
        this->p = this->g->left;

        if (this->p->left->color == RED)
        {
            this->shape = Shape::LL;
            this->x = this->p->left;
        }
        else
        {
            // Stop if there is no red-red violation
            ABORT_UNLESS(p->right->color == RED);

            this->shape = LR;
            this->x = this->p->right;
        }
    }
    else
    {
        // Both children of g are RED. Find the red-red violation
        BSTNode *lc = this->g->left;
        BSTNode *llc = lc->left;
        BSTNode *lrc = lc->right;
        BSTNode *rc = this->g->right;
        BSTNode *rlc = rc->left;
        BSTNode *rrc = rc->right;

        if (llc && llc->color == RED)
        {
            this->shape = LL;
            this->p = lc;
            this->x = llc;
            this->y = rc;
        }

        if (lrc && lrc->color == RED)
        {
            // Stop if there are multiple red-red violations
            ABORT_UNLESS(this->shape == SHAPE_NONE);

            this->shape = LR;
            this->p = lc;
            this->x = lrc;
            this->y = rc;
        }

        if (rlc && rlc->color == RED)
        {
            // Stop if there are multiple red-red violations
            ABORT_UNLESS(this->shape == Shape::SHAPE_NONE);

            this->shape = Shape::RL;
            this->p = rc;
            this->x = rlc;
            this->y = lc;
        }

        if (rrc && rrc->color == RED)
        {
            // Stop if there are multiple red-red violations
            ABORT_UNLESS(this->shape == SHAPE_NONE);

            this->shape = RR;
            this->p = rc;
            this->x = rrc;
            this->y = lc;
        }

        // Stop if there is no red-red violation
        ABORT_UNLESS(this->shape != SHAPE_NONE);
    }
}

BSTNode::BHVNeighborhood::BHVNeighborhood(BSTNode *n, Direction dir)
    : n{n}, p{nullptr}, s{nullptr}, c{nullptr}, d{nullptr},
      del_case{CASE_NONE}, dir{dir}
{
    ABORT_UNLESS(this->n && !this->n->is_empty() &&
                 this->n->color == BLACK);

    this->p = this->n->parent;

    if (!this->p)
    {
        this->del_case = CASE_1;
        assert(dir == ROOT);
        this->dir = ROOT;
    }
    else
    {
        assert(!this->p->is_empty());
        assert(this->dir != ROOT);

        this->s = this->p->child(opposite_direction(dir));
        this->c = this->s->child(dir);
        this->d = this->s->child(opposite_direction(dir));

        if (this->p->color == BLACK &&
            this->s->color == BLACK &&
            this->c && this->c->color == BLACK &&
            this->d && this->d->color == BLACK)
        {
            this->del_case = CASE_2;
        }
        else if (this->p->color == BLACK &&
                 this->s->color == RED)
        {
            assert(this->c && this->c->color == BLACK &&
                   this->d && this->d->color == BLACK);

            this->del_case = CASE_3;
        }
        else if (this->p->color == RED &&
                 this->s->color == BLACK &&
                 this->c->color == BLACK &&
                 this->d->color == BLACK)
        {
            this->del_case = CASE_4;
        }
        else if (this->s->color == BLACK &&
                 this->c->color == RED &&
                 this->d->color == BLACK)
        {
            this->del_case = CASE_5;
        }
        else if (this->s->color == BLACK &&
                 this->d->color == RED)
        {
            this->del_case = CASE_6;
        }
        else
        {
            this->del_case = CASE_NONE;
        }
    }
}

void BSTNode::BHVNeighborhood::fix_blackheight_imbalance()
{
    /*
     * This is implemented for you. Study it carefully so you understand what
     *  is going on when a node is deleted from a Red-Black Tree.
     */
    BSTNode::BHVNeighborhood nb = *this;
    while (nb.p)
    {
        BSTNode::Direction pdir = ROOT;
        if (nb.p->parent)
        {
            if (nb.p == nb.p->parent->left)
            {
                pdir = LEFT;
            }
            else if (nb.p == nb.p->parent->right)
            {
                pdir = RIGHT;
            }
            else
            {
                // Should never happen: nb.p is non-null.
                assert(false);
            }
        }
        BSTNode *grandparent = nb.p->parent;

        switch (nb.del_case)
        {
        case CASE_2:
            nb.s->color = RED;
            nb.n = nb.p;
            nb = BSTNode::BHVNeighborhood(nb.n->parent, nb.dir);
            break;
        case CASE_3:
            nb.s = nb.p->dir_rotate(nb.dir);
            if (pdir != ROOT)
            {
                grandparent->set_child(pdir, nb.s);
            }
            swap_colors(nb.p, nb.s);
            nb = BSTNode::BHVNeighborhood(nb.p, nb.dir);
            assert(nb.del_case >= CASE_4);
            break;
        case CASE_4:
            swap_colors(nb.p, nb.s);
            return;
        case CASE_5:
            nb.p->set_child(opposite_direction(nb.dir),
                            nb.s->dir_rotate(opposite_direction(nb.dir)));
            swap_colors(nb.c, nb.s);
            nb = BSTNode::BHVNeighborhood(nb.p, nb.dir);
            assert(nb.del_case == CASE_6);
            break;
        case CASE_6:
            nb.s = nb.p->dir_rotate(nb.dir);
            if (pdir != ROOT)
            {
                grandparent->set_child(pdir, nb.s);
            }
            swap_colors(nb.p, nb.s);
            nb.d->color = BLACK;
            return;
        default:
            // CASE_NONE or CASE_1 (should never happen; nb.p is non-null)
            assert(false);
            break;
        }
    }
}

BSTNode *BSTNode::rb_remove_helper(int value, BHVNeighborhood &nb)
{
    // This is implemented for you
    BSTNode *root = this;
    if (root->height >= 0)
    {
        if (value < root->data)
        {
            nb.dir = LEFT;
            root->left = root->left->rb_remove_helper(value, nb);
        }
        else if (value > root->data)
        {
            nb.dir = RIGHT;
            root->right = root->right->rb_remove_helper(value, nb);
        }
        else
        {
            // We found the value. Remove it.
            if (root->count > 1)
            {
                root->count--;
            }
            else
            {
                if (root->left->is_empty() &&
                    root->right->is_empty())
                {
                    // root has no children. We may have to do extra work.

                    // Get its neighborhood
                    nb = BHVNeighborhood(this, nb.dir);

                    // Delete it
                    delete this;
                    root = new BSTNode();
                }
                else if (!root->left->is_empty() &&
                         root->right->is_empty())
                {
                    // this has one (left) child. Promote this's child
                    this->left->color = root->color;
                    root = this->left;
                    this->left = nullptr;
                    delete this;
                }
                else if (root->left->is_empty() &&
                         !root->right->is_empty())
                {
                    // this has one (right) child. Promote this's child
                    this->right->color = root->color;
                    root = this->right;
                    this->right = nullptr;
                    delete this;
                }
                else
                {
                    /*
                     * this has two children.
                     *
                     * Find the successor to use as a replacement, then remove it
                     * entirely from this's right subtree. This requires setting
                     * the replacement's count to 1 so that the node is entirely
                     * removed rather than simply having its count decremented.
                     * Removal is the only place a const-to-non-const cast should
                     * appear in your solution.
                     *
                     * TODO: (optional) Rewrite this section of code to eliminate
                     *  the const-to-non-const cast.
                     */

                    BSTNode *replacement = (BSTNode *)root->right->minimum_value();
                    root->data = replacement->data;
                    root->count = replacement->count;
                    replacement->count = 1;
                    nb.dir = RIGHT;
                    root->right = root->right->rb_remove_helper(replacement->data, nb);
                }
            }
        }
    }

    root->make_locally_consistent();

    return root;
}

BSTNode *BSTNode::dir_rotate(Direction dir)
{
    // This is implemented for you.
    BSTNode *root = this;
    if (dir == LEFT)
    {
        root = root->left_rotate();
    }
    else if (dir == RIGHT)
    {
        root = root->right_rotate();
    }
    return root;
}

BSTNode *BSTNode::right_rotate()
{
    // Update parents
    this->left->parent = this->parent;
    this->parent = this->left;
    if (this->left->parent != nullptr)
    {
        if (this->left->parent->left == this)
        {
            this->left->parent->left = this->parent;
        }
        else
        {
            this->left->parent->right = this->parent;
        }
    }
    this->left = this->parent->right;
    this->parent->right->parent = this;
    this->parent->right = this;
    // Update heights
    this->height = std::max(this->left->height, this->right->height) + 1;
    this->parent->height = std::max(this->parent->left->height, this->parent->right->height) + 1;
    // Returns the tree.
    return this->parent;
}

BSTNode *BSTNode::left_rotate()
{
    // Update parents
    this->right->parent = this->parent;
    this->parent = this->right;
    // Update the parent of the root if not nullptr
    if (this->right->parent != nullptr)
    {
        // Find direction and update accordingly
        if (this->right->parent->left == this)
        {
            this->right->parent->left = this->parent;
        }
        else
        {
            this->right->parent->right = this->parent;
        }
    }
    this->right = this->parent->left;
    this->parent->left->parent = this;
    this->parent->left = this;
    // Update heights
    this->height = std::max(this->left->height, this->right->height) + 1;
    this->parent->height = std::max(this->parent->left->height, this->parent->right->height) + 1;
    // Return sorted subtree
    return this->parent;
}

BSTNode *BSTNode::avl_balance()
{
    // Balance the tree!
    BSTNode *parent = this;
    BSTNode *child = nullptr;
    BSTNode *grandchild = nullptr;
    // Set directions for later use.
    Direction first = ROOT;
    Direction second = ROOT;
    // Determine child
    if (parent->left->height > parent->right->height)
    {
        child = parent->left;
    }
    else 
    {
        child = parent->right;
    }
    // Determine direction of child from parent.
    if (parent->left == child)
    {
        first = LEFT;
    }
    else
    {
        first = RIGHT;
    }
    // Determine grandchild, using direction as a tiebreaker if necessary.
    if (child->left->height > child->right->height)
    {
        grandchild = child->left;
    }
    else if (child->left->height < child->right->height)
    {
        grandchild = child->right;
    }
    else
    {
        grandchild = child->child(first);
    }
    // Determine direction of grandchild from child.
    if (child->left == grandchild)
    {
        second = LEFT;
    }
    else
    {
        second = RIGHT;
    }
    // Determine cases
    if (first == second)
    {
        // Case 1: Simple line, just one rotation of parent.
        parent->dir_rotate(opposite_direction(first));
    }
    else
    {
        // Case 2: Correct to simple line, two rotations
        child->dir_rotate(opposite_direction(second));
        parent->dir_rotate(opposite_direction(first));
    }
    // return
    return this;
}

BSTNode *BSTNode::rb_eliminate_red_red_violation()
{
    /*
     * Get this's neighborhood (children + grandchildren), which might have
     *  shape NONE if this is BLACK or this.height <= 1 or there is no red-red
     *  violation in the neighborhood of this.
     */
    RRVNeighborhood nb(this);
    if (nb.shape != SHAPE_NONE)
    {
        /*
         * There is a red-red violation somewhere in the neighborhood of this
         *  Fix it.
         */
        // Determine which case the nature of violation is
        if (nb.y->color == RED)
        {
            // Uncle is red, no twist necessary. 
            nb.y->color = BLACK;
            nb.p->color = BLACK;
            nb.x->color = RED;
            if (nb.g->parent != nullptr)
            {
                nb.g->color = RED;
            }
        }
        else
        {
            // Do rotations based off shape if Uncle is Black.
           if (nb.shape == LR)
           {
                nb.x->color = BLACK;
                nb.p->left_rotate();
           }

           if (nb.shape == RL)
           {
                nb.x->color = BLACK;
                nb.p->right_rotate();
           }

           if (nb.shape == LR || nb.shape == LL)
           {
                nb.g->right_rotate();
           }

           if (nb.shape == RL || nb.shape == RR)
           {
                nb.g->left_rotate();
           }
            // Correct for colors.
           if (nb.x->color != BLACK)
           {
                nb.p->color = BLACK;
           }
           else
           {
                nb.p->color = RED;
           }
           nb.g->color = RED;

        }
    }
    return this;
}

int BSTNode::height_diff() const
{
    /*
     * This is implemented for you. Note the use of the node_height() function
     *  rather than the height property. Why do you think is it written in this
     *  way?
     */
    int diff = 0;
    if (!this->is_empty())
    {
        diff = this->right->node_height() - this->left->node_height();
    }

    return diff;
}

void BSTNode::make_locally_consistent()
{
    // Checks to make sure this is not empty.
    if (this->is_empty())
    {
        this->height = -1;
        return;
    }
    // Updates height to max of the two children.
    this->height = std::max(this->left->height, this->right->height) + 1;
    // Make locally consistent.
    if (!this->left->is_empty())
    {
        this->left->parent = this;
    }
    if (!this->right->is_empty())
    {
        this->right->parent = this;
    }
    return;
}
