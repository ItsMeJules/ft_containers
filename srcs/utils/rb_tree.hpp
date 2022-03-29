#ifndef RB_BTREE_HPP
# define RB_BTREE_HPP

# include <memory>
# include "utils/functional.hpp"

namespace ft {

    template <typename T>
    class rb_node {
        T data_;

        rb_node *right_;
        rb_node *left_;
        rb_node *parent_;
        bool black_;

        rb_node(const bool black, const T data, Node *right = NULL, Node *left = NULL) 
            : black_(black), data_(data), right_(right), left_(left)
        {
            if (right_ != NULL) right_->parent_ = this;
            if (left_ != NULL) left_->parent_ = this;
        }
    };

    template <typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> >
    class rb_btree {
        public:
            typedef	T															value_type;
			typedef rb_node<value_type>										    node_type;
			typedef	Compare														compare_type;
			typedef	Alloc														allocator_type;
			typedef typename Alloc::template rebind<node_type>::other 			node_allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;			
			typedef	btree_iterator<value_type>									iterator;
			typedef	btree_const_iterator<value_type>							const_iterator;
			typedef	ft::reverse_iterator<iterator>								reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>						const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
			typedef	size_t														size_type; 
    };
}

#endif