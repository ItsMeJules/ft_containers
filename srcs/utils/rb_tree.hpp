#ifndef RB_BTREE_HPP
# define RB_BTREE_HPP

# include <memory>
# include "functional.hpp"
# include "ft_containers/srcs/iterators/rb_tree_iterator.hpp"
# include "ft_containers/srcs/iterators/reverse_iterator.hpp"

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

    // https://www.programiz.com/dsa/red-black-tree
    template <typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> >
    class rb_btree {
        public:
            typedef	T															value_type;
			typedef rb_node<value_type>										    node_type;
			typedef	Compare														comp;
			typedef	Alloc														allocator_type;
			typedef typename Alloc::template rebind<node_type>::other 			node_allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;			
			typedef	rb_btree<value_type>									    iterator;
			typedef	rb_tree_const_iterator<value_type>							const_iterator;
			typedef	ft::reverse_iterator<iterator>								reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>						const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
			typedef	size_t														size_type;

            iterator begin(void) {
                return (root_ ? iterator(leftMostNode(root_)) : end());
			}

			const_iterator begin(void) const {
                return (root_ ? const_iterator(leftMostNode(root_)) : end());
			}

			iterator end(void) {
				return iterator(end_);
			}

			const_iterator end(void) const {
				return const_iterator(end_);
			}

			reverse_iterator rbegin(void) {
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin(void) const {
				return const_reverse_iterator(end());
			}

			reverse_iterator rend(void) {
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend(void) const {
				return const_reverse_iterator(begin());
			}

			allocator_type get_allocator() const {
				return value_alloc_;
			}

			compare_type get_comparator() const {
				return compare_type_;
			}

			bool empty(void) const {
				return (root_ ? false : true);
			}

			size_type size(void) const {
				return (root_ ? nodesAmount(root_) : 0);
			}

			size_type max_size(void) const {
				return node_alloc_.max_size();
			}
        private:
            node_type *root_;
            /*
            * This node is the end of the tree.
            * When you run through it using iterators it will end up going back to the root parent's node.
            */
            node_type *end_;
            allocator_type value_alloc_;
            node_allocator_type node_alloc_;
            comp compare_type_;

            void rotateLeft(node_type *x) {
                node_type *y = x->right_;

                x->right_ = y->left_;
                if (y->left_ != NULL)
                    y->left_->parent_ = x;

                y->parent = x->parent;
                if (x->parent == NULL)
                    this->root = y;
                else if (x == x->parent->left)
                    x->parent->left = y;
                else
                    x->parent->right = y;
                y->left = x;
                x->parent = y;
            }

            void rotateRight(node_type *x) {
                node_type *y = x->left;
                
                x->left = y->right;
                if (y->right != NULL)
                    y->right->parent = x;

                y->parent = x->parent;
                if (x->parent == nullptr)
                    this->root = y;
                else if (x == x->parent->right)
                    x->parent->right = y;
                else
                    x->parent->left = y;
                y->right = x;
                x->parent = y;
            }

            void insertNode(node_type *n) {
				node_type	*y = NULL;
				node_type	*temp = root_;

				while (temp) {
  					y = temp;
					if (comp(z->value, temp->value))
    					temp = temp->left;
  					else
    					temp = temp->right;
				}
				z->parent = y;
				if (!y)
 					root_ = z;
				else if (comp(z->value, y->value))
  					y->left = z;
				else
					y->right = z;
				z->right = NULL;
				z->left = NULL;
				insertFix(z);
			}

            void insertFix(node_type *n) {
				node_type *parent = NULL;
    			node_type *grandParent = NULL;
           	 	node_type *uncle = NULL;
                int colorTmp;
                
    			while (n != root_ && !n->black_  && !n->parent->black_) {

        			parent = n->parent;
        			grandParent = getGrandParent(n);
        			if (parent == grandParent->left) {

           	 			uncle = grandParent->right;
            			if (uncle && !uncle->black_) {
                			grandParent->black_ = 0;
                			parent->black_ = 1;
            			    uncle->black_ = 1;
            			    n = grandParent;
            			} else {
                			if (n == parent->right) {
                			    rotateLeft(parent);
                    			n = parent;
                    			parent = n->parent;
                			}
                			rotateRight(grandParent);
                			colorTmp = parent->black_;
                			parent->black_ = grandParent->black_;
                			grandParent->black_ = colorTmp;
                			n = parent;
            			}
        			} else {

            			uncle = grandParent->left;
            			if (uncle && !uncle->black_) {
            			    grandParent->black_ = 0;
            			    parent->black_ = 1;
            			    uncle->black_ = 1;
            			    n = grandParent;
            			} else {
                			if (n == parent->left) {
                 			   rotateRight(parent);
                    			n = parent;
                    			parent = n->parent;
                			}
                			rotateLeft(grandParent);
                			colorTmp = parent->black_;
                			parent->black_ = grandParent->black_;
                			grandParent->black_ = colorTmp;
                			n = parent;
            			}
        			}
    			}
    			root_->black_ = 1;
            }

            node_type *getGrandParent(const node_type *node) const {
				return (node->parent == NULL ? NULL : node->parent->parent);
			}

			size_type nodesAmount(node_type *root) const {
				if (!root)
					return 0;
				return 1 + _size(root->left) + _size(root->right);
			}
    };


}

#endif