#ifndef RB_BTREE_HPP
# define RB_BTREE_HPP

# include <memory>
# include "functional.hpp"
# include "../iterators/rb_tree_iterator.hpp"
# include "../iterators/reverse_iterator.hpp"

namespace ft {

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
			typedef ft::rb_tree_iterator<value_type>				 			iterator;
			typedef ft::rb_tree_const_iterator<value_type>						const_iterator;
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
				: root_(NULL), end_(newNode(value_type(), 0)), value_alloc_(value_alloc), node_alloc_(n_alloc), compare_type_(c)
			{}

			rb_btree(const rb_btree& src)
				: root_(NULL), end_(newNode(value_type(), 0)), value_alloc_(src.value_alloc_), node_alloc_(src.node_alloc_), compare_type_(src.compare_type_)
			{
				for (const_iterator it = src.begin(); it != src.end(); it++)
					insert(*it);
			}

			~rb_btree() {
				clear();
				destroyNode(end_);
			}

			//OPERATOR
			rb_btree& operator=(const rb_btree& x) {
				if (this != &x) {
					clear();
					for (const_iterator it = x.begin(); it != x.end(); it++)
						insert(*it);
				}
				return *this;
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

				root_->parent_ = NULL;
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
					root_->parent_ = NULL;
					deleteNode(node);
					updateRootEnd();
				}
			}
			
			void erase(iterator first, iterator last) {
				while (first != last)
					erase(first++);
			}

			void swap(rb_btree & x) {
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
					end_->parent_ = NULL;
					end_->left_ = NULL;
					end_->right_ = NULL;
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
				while (tmp->left_)
					tmp = tmp->left_;
				return (tmp->data_);
			}

			iterator find(const value_type& value) {
				node_type *node = findNode(root_, value);
	
				return (node ? iterator(node) : end());
			}

			const_iterator find(const value_type& value) const {
				node_type *node = findNode(root_, value);
	
				return (node ? const_iterator(node) : end());
			}

			// GETTERS
			allocator_type get_allocator() const {
				return value_alloc_;
			}

			comp get_comparator() const {
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
			node_type *smallest(node_type *node) const {
				if (!node)
					return (NULL);
				while (node->left_)
					node = node->left_;
				return node;
			}

			node_type *leftMostNode(node_type *node) const {
				if (!node)
					return (NULL);
				while (node->left_)
					node = node->left_;
				return (node);
			}

			void updateRootEnd() {
				end_->parent_ = root_;
				end_->left_ = root_;
				end_->right_ = root_;
				if (root_)
					root_->parent_ = end_;
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
				if (compare_type_(val, root->data_))
					return findNode(root->left_, val);
				else if (compare_type_(root->data_, val))
					return findNode(root->right_, val);
				else
					return root;
			}

			node_type *newNode(const value_type data, const bool black) {
				node_type *node = NULL;
				
				try {
					node = node_alloc_.allocate(1);
					value_alloc_.construct(&node->data_, data);
					node->black_ = black;
					node->parent_ = NULL;
					node->left_ = NULL;
					node->right_ = NULL;
				} catch (std::bad_alloc& e) {
					destroyNode(node);
					node = NULL;
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

    			if (!z->left_) {
        			x = z->right_;
        			rbTransplant(z, z->right_);
    			} else if (!z->right_) {
     		   		x = z->left_;
        			rbTransplant(z, z->left_);
    			} else {
        			y = smallest(z->right_);
        			blackTmp = y->black_;
        			x = y->right_;
        			if (x && y->parent_ == z)
            			x->parent_ = y;
        			else if (y->parent_ != z) {
            			rbTransplant(y, y->right_);
            			y->right_ = z->right_;
            			y->right_->parent_ = y;
        			}	
        			rbTransplant(z, y);
        			y->left_ = z->left_;
        			y->left_->parent_ = y;
        			y->black_ = z->black_;
    			}
    			if (blackTmp == 1)
    		    	deleteFix(x); 
    			destroyNode(z);
			}

			void deleteFix(node_type *node) {
				node_type *s = NULL;

				while (node && node != root_ && node->black_ == 1) {
        			if (node == node->parent_->left_) {

            			s = node->parent_->right_;
            			if (s->black_ == 0) {
                			s->black_ = 1;
                			node->parent_->black_ = 0;
                			rotateLeft(node->parent_);
                			s = node->parent_->right_;
            			}
            			if (s->left_->black_ == 1 && s->right_->black_ == 1) {
            				s->black_ = 0;
            	    		node = node->parent_;
            			} else if (s->right_->black_ == 1) {
            			    s->left_->black_ = 1;
            			    s->black_ = 0;
            			    rotateRight(s);
            			    s = node->parent_->right_;
            			} else {
            				s->black_ = node->parent_->black_;
                			node->parent_->black_ = 1;
                			s->right_->black_ = 1;
                			rotateLeft(node->parent_);
                			node = root_;
            			}
        			} else {
						
            			s = node->parent_->left_;
            			if (s->black_ == 0) {
            			    s->black_ = 1;
            			    node->parent_->black_ = 0;
            			    rotateRight(node->parent_);
            			    s = node->parent_->left_;
            			}
            			if (s->right_->black_ == 1 && s->left_->black_ == 1) {
            				s->black_ = 0;
                			node = node->parent_;
            			} else if (s->left_->black_ == 1) {
            			    s->right_->black_ = 1;
            			    s->black_ = 0;
            			    rotateLeft(s);
           		 		    s = node->parent_->left_;
            			} else {
            			    s->black_ = node->parent_->black_;
            			    node->parent_->black_ = 1;
            			    s->left_->black_ = 1;
            			    rotateRight(node->parent_);
            			    node = root_;
            			}
        			}
    			}
				if (node)
    				node->black_ = 1;
			}

			void rbTransplant(node_type *u, node_type *v) {
				if (u->parent_ == NULL)
					root_ = v;
				else if (u == u->parent_->left_)
					u->parent_->left_ = v;
				else
					u->parent_->right_ = v;
				if (v)
					v->parent_ = u->parent_;
			}

            void rotateLeft(node_type *x) {
                node_type *y = x->right_;

                x->right_ = y->left_;
                if (y->left_ != NULL)
                    y->left_->parent_ = x;

                y->parent_ = x->parent_;
                if (x->parent_ == NULL)
                    this->root_ = y;
                else if (x == x->parent_->left_)
                    x->parent_->left_ = y;
                else
                    x->parent_->right_ = y;
                y->left_ = x;
                x->parent_ = y;
            }

            void rotateRight(node_type *x) {
                node_type *y = x->left_;
                
                x->left_ = y->right_;
                if (y->right_ != NULL)
                    y->right_->parent_ = x;

                y->parent_ = x->parent_;
                if (x->parent_ == NULL)
                    this->root_ = y;
                else if (x == x->parent_->right_)
                    x->parent_->right_ = y;
                else
                    x->parent_->left_ = y;
                y->right_ = x;
                x->parent_ = y;
            }

            void insertNode(node_type *n) {
				node_type *y = NULL;
				node_type *temp = root_;

				while (temp) {
  					y = temp;
					if (compare_type_(n->data_, temp->data_))
    					temp = temp->left_;
  					else
    					temp = temp->right_;
				}
				n->parent_ = y;
				if (!y)
 					root_ = n;
				else if (compare_type_(n->data_, y->data_))
  					y->left_ = n;
				else
					y->right_ = n;
				n->right_ = NULL;
				n->left_ = NULL;
				insertFix(n);
			}

            void insertFix(node_type *n) {
				node_type *parent = NULL;
    			node_type *grandParent = NULL;
           	 	node_type *uncle = NULL;
                int colorTmp;
                
    			while (n != root_ && !n->black_  && !n->parent_->black_) {

        			parent = n->parent_;
        			grandParent = getGrandParent(n);
        			if (parent == grandParent->left_) {

           	 			uncle = grandParent->right_;
            			if (uncle && !uncle->black_) {
                			grandParent->black_ = 0;
                			parent->black_ = 1;
            			    uncle->black_ = 1;
            			    n = grandParent;
            			} else {
                			if (n == parent->right_) {
                			    rotateLeft(parent);
                    			n = parent;
                    			parent = n->parent_;
                			}
                			rotateRight(grandParent);
                			colorTmp = parent->black_;
                			parent->black_ = grandParent->black_;
                			grandParent->black_ = colorTmp;
                			n = parent;
            			}
        			} else {

            			uncle = grandParent->left_;
            			if (uncle && !uncle->black_) {
            			    grandParent->black_ = 0;
            			    parent->black_ = 1;
            			    uncle->black_ = 1;
            			    n = grandParent;
            			} else {
                			if (n == parent->left_) {
                 			   rotateRight(parent);
                    			n = parent;
                    			parent = n->parent_;
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
				return (node->parent_ == NULL ? NULL : node->parent_->parent_);
			}

			size_type nodesAmount(node_type *root) const {
				if (!root)
					return 0;
				return 1 + nodesAmount(root->left_) + nodesAmount(root->right_);
			}


    };


}

#endif