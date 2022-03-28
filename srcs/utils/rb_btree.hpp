#ifndef RB_BTREE_HPP
# define RB_BTREE_HPP

namespace ft {

    template <typename T>
    class Node {
        T data_;

        Node *right_;
        Node *left_;
        Node *parent_;
        bool black_;

        Node(const bool black, const T data, Node *right = NULL, Node *left = NULL, Node *parent = NULL) 
            : black_(black), data_(data), right_(right), left_(left), parent_(parent) {}
    };
}

#endif