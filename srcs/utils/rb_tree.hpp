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
	// This website carried me like Sam carries Frodo
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

		public:
			rb_btree(const comp& c = comp(), const allocator_type& value_alloc = allocator_type(), const node_allocator_type& n_alloc = node_allocator_type())
				: root_(NULL), end_(newNode(value_type())), node_alloc_(n_alloc), value_alloc_(value_alloc), compare_type_(c)
			{}

			rb_btree(const btree& src)
				: root_(NULL), end_(newNode(value_type())), value_alloc_(src.value_alloc_), node_alloc_(src.node_alloc_), compare_type_(src.compare_type_)
			{
				insert(src.begin(), src.end());
			}

			~rb_btree() {
				clear();
				destroyNode(end_);
			}

			// MODIFIERS
			iterator insert(const value_type& value) {
				if (root_ == NULL) {
					root_ = newNode(value, 1);
					updateRootEnd();
					return iterator(root_);
				} else {
					root_->parent_ = NULL;
					node_type *node = newNode(value, 0);
					insertNode(node);
					updateRootEnd();
					return find(value);
				}
			}

			iterator insert(iterator position, const value_type& value) {
				(void)position;
				return insert(value);
			}

			size_type erase(const value_type& value) {
				size_type amount = 0;
				node_type *node = findNode(root_, value);

				root_->parent = NULL;
				while (node) {
					deleteNode(node);
					amount++;
					node = findNode(root_, value);
				}
				updateRootEnd();
				return amount;
			}

			void erase(iterator position) {
				node_type *node = position.base();

				if (node && node != end_) {
					root_->parent = NULL;
					deleteNode(node);
					updateRootEnd();
				}
			}
			
			void erase(iterator first, iterator last) {
				while (first != last)
					erase(first++);
			}

			void swap(btree & x) {
				node_type *tmpr = root_;
				node_type *tmpe = end_;

				root_ = x.root_;
				end_ = x.end_;
				x.root_ = tmpr;
				x.end_ = tmpe;
			}

			void clear(void) {
				if (root_) {
					clearTree(root_);
					root_ = NULL;
					end_->parent = NULL;
					end_->left = NULL;
					end_->right = NULL;
				}
			}

			// ITERATORS
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

			value_type min() const {
				if (!root_)
					return (NULL);

				node_type *tmp = root_;
				while (tmp->left)
					tmp = tmp->left;
				return (tmp->data_);
			}

			// GETTERS
			allocator_type get_allocator() const {
				return value_alloc_;
			}

			compare_type get_comparator() const {
				return compare_type_;
			}

			// CAPACITY
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
			void updateRootEnd() {
				end_->parent_ = root_;
				end_->left_ = root_;
				end_->right_ = root_;
				if (root_)
					root_->parent = end_;
			}

			void clearTree(node_type *root) {
				if (!root)
					return;
				clearTree(root->left_);
				clearTree(root->right_);
				destroyNode(root);
			}
			
			node_type *findNode(node_type *root, const value_type& val) const {
				if (!root)
					return NULL;
				if (compare_type_(val, root->data))
					return findNode(root->left_, val);
				else if (compare_type_(root->data, val))
					return findNode(root->right_, val);
				else
					return root;
			}

			node_type *newNode(const value_type data, const bool black) {
				node_type *node = NULL;
				
				try {
					node = node_alloc_.allocate(1);
					value_alloc_.construct(&node->data_, data);
					node->black = black;
					node->parent = NULL;
					node->left = NULL;
					node->right = NULL;
				} catch (std::bad_alloc& e) {
					destroyNode(node);
					node = NULL;
					std::cout << "Error when trying to make a new node.\n" << e.what() << std::endl;
				}
				return node;
			}

			void destroyNode(node_type *node) {
				if (node) {
					value_alloc_.destroy(&node->data_);
					node_alloc_.deallocate(node, 1);
				}
			}

			void deleteNode(node_type *z) {
				node_type *x;
    			node_type *y = z;
    			int blackTmp = y->black_;

    			if (!z->left) {
        			x = z->right;
        			rbTransplant(z, z->right);
    			} else if (!z->right) {
     		   		x = z->left;
        			rbTransplant(z, z->left);
    			} else {
        			y = min(z->right);
        			blackTmp = y->color;
        			x = y->right;
        			if (x && y->parent == z)
            			x->parent = y;
        			else if (y->parent != z) {
            			rbTransplant(y, y->right);
            			y->right = z->right;
            			y->right->parent = y;
        			}	
        			rbTransplant(z, y);
        			y->left = z->left;
        			y->left->parent = y;
        			y->color = z->color;
    			}
    			if (blackTmp == 1)
    		    	deleteFix(x); 
    			destroyNode(z);
			}

			void deleteFix(node_type *node) {
				node_type *s = NULL;

				while (node && node != root_ && node->black_ == 1) {
        			if (node == node->parent->left) {

            			s = node->parent->right;
            			if (s->black_ == 0) {
                			s->black_ = 1;
                			node->parent->black_ = 0;
                			rotateLeft(node->parent);
                			s = node->parent->right;
            			}
            			if (s->left->black_ == 1 && s->right->black_ == 1) {
            				s->black_ = 0;
            	    		node = node->parent;
            			} else if (s->right->black_ == 1) {
            			    s->left->black_ = 1;
            			    s->black_ = 0;
            			    rotateRight(s);
            			    s = node->parent->right;
            			} else {
            				s->black_ = node->parent->black_;
                			node->parent->black_ = 1;
                			s->right->black_ = 1;
                			rotateLeft(node->parent);
                			node = root_;
            			}
        			} else {
						
            			s = node->parent->left;
            			if (s->black_ == 0) {
            			    s->black_ = 1;
            			    node->parent->black_ = 0;
            			    rotateRight(node->parent);
            			    s = node->parent->left;
            			}
            			if (s->right->black_ == 1 && s->left->black_ == 1) {
            				s->black_ = 0;
                			node = node->parent;
            			} else if (s->left->black_ == 1) {
            			    s->right->black_ = 1;
            			    s->black_ = 0;
            			    rotateLeft(s);
           		 		    s = node->parent->left;
            			} else {
            			    s->black_ = node->parent->black_;
            			    node->parent->black_ = 1;
            			    s->left->black_ = 1;
            			    rotateRight(node->parent);
            			    node = root_;
            			}
        			}
    			}
				if (node)
    				node->black_ = 1;
			}

			void rbTransplant(node_type *u, node_type *v) {
				if (u->parent == NULL)
					root_ = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

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
				return 1 + nodesAmount(root->left) + nodesAmount(root->right);
			}


    };


}

#endif