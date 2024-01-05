/**
 * Pretty Printing for a BSTNode
 * Code in this file was borrowed from leetcode.com:
 * http://leetcode.com/2010/09/how-to-pretty-print-binary-tree.html
 * Thanks to http://leetcode.com/members/admin/ for the code!
 *
 * Modified 2023 by Alan Weide
 *  - Changed print_nodes to handle decorators in the output to denote
 *      duplicates or color.
 */

#include <fstream>
#include <iostream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>

#include "pretty_print.h"

using namespace std;

// Print the arm branches (eg, /    \ ) on a line
void print_branches(int branch_len,
                    int node_space_len,
                    int start_len,
                    int nodes_in_this_level,
                    const deque<BSTNode *> &nodes_queue,
                    ostream &out)
{
    deque<BSTNode *>::const_iterator iter = nodes_queue.begin();
    for (int i = 0; i < nodes_in_this_level / 2; i++)
    {
        bool has_left = (*iter) && !(*iter)->is_empty();
        iter++;
        bool has_right = (*iter) && !(*iter)->is_empty();
        iter++;
        out << ((i == 0) ? setw(start_len - 1) : setw(node_space_len - 2))
            << "" << ((has_left) ? "/" : " ");
        out << setw(2 * branch_len + 2) << "" << ((has_right) ? "\\" : " ");
    }
    out << endl;
}

bool tree_has_child(BSTNode *node, bool left)
{
    if (left)
    {
        return node && !node->is_empty() && !node->left->is_empty();
    }
    else
    {
        return node && !node->is_empty() && !node->right->is_empty();
    }
}

// Print the branches and node (eg, ___10___ )
void print_nodes(int branch_len, int node_space_len, int start_len,
                 int nodes_in_this_level, const deque<BSTNode *> &nodes_queue,
                 ostream &out)
{
    deque<BSTNode *>::const_iterator iter = nodes_queue.begin();
    for (int i = 0; i < nodes_in_this_level; i++, iter++)
    {
        bool has_left = tree_has_child(*iter, true);
        bool has_right = tree_has_child(*iter, false);
        out << setw(((i == 0) ? start_len : node_space_len))
            << ""
            << setfill(has_left ? '_' : ' ');
        out << setw(branch_len + 2)
            << (*iter)->to_string();
        out << setfill(has_right ? '_' : ' ')
            << setw(branch_len) << "" << setfill(' ');
    }
    out << endl;
}

// Print the leaves only (just for the bottom row)
void print_leaves(int indent_space, int level, int nodes_in_this_level,
                  const deque<BSTNode *> &nodes_queue, ostream &out)
{
    deque<BSTNode *>::const_iterator iter = nodes_queue.begin();
    for (int i = 0; i < nodes_in_this_level; i++, iter++)
    {
        out << setw((i == 0) ? (indent_space + 2) : (2 * level + 2))
            << (*iter)->to_string();
    }
    out << endl;
}

// Pretty formatting of a binary tree to the output stream
// @ param
// level  Control how wide you want the tree to sparse (eg, level 1 has the
//     minimum space between nodes, while level 2 has a larger space between
//     nodes)
// indent_space  Change this to add some indent space to the left (eg,
//     indent_space of 0 means the lowest level of the left node will stick to
//     the left margin)
void print_pretty(BSTNode &root, int level, int indent_space, ostream &out)
{
    int h = root.node_height() + 1;
    int nodes_in_this_level = 1;

    // eq of the length of branch for each node of each level
    int branch_len =
        2 * ((int)pow(2.0, h) - 1) - (3 - level) * (int)pow(2.0, h - 1);

    // distance between left neighbor node's right arm and right neighbor
    // node's left arm
    int node_space_len = 2 + (level + 1) * (int)pow(2.0, h);

    // starting space to the first node to print of each level (for the left
    // most node of each level only)
    int start_len = branch_len + (3 - level) + indent_space;

    deque<BSTNode *> nodes_queue;
    nodes_queue.push_back(&root);
    for (int r = 1; r < h; r++)
    {
        print_branches(branch_len,
                       node_space_len,
                       start_len,
                       nodes_in_this_level,
                       nodes_queue,
                       out);
        branch_len = branch_len / 2 - 1;
        node_space_len = node_space_len / 2 + 1;
        start_len = branch_len + (3 - level) + indent_space;
        print_nodes(branch_len,
                    node_space_len,
                    start_len,
                    nodes_in_this_level,
                    nodes_queue,
                    out);

        for (int i = 0; i < nodes_in_this_level; i++)
        {
            BSTNode *curr_node = nodes_queue.front();
            nodes_queue.pop_front();
            if (curr_node && !curr_node->is_empty())
            {
                nodes_queue.push_back(curr_node->left);
                nodes_queue.push_back(curr_node->right);
            }
            else
            {
                nodes_queue.push_back(nullptr);
                nodes_queue.push_back(nullptr);
            }
        }
        nodes_in_this_level *= 2;
    }
    print_branches(branch_len,
                   node_space_len,
                   start_len,
                   nodes_in_this_level,
                   nodes_queue,
                   out);
    print_leaves(indent_space, level, nodes_in_this_level, nodes_queue, out);
}
