#ifndef RB_TREE_ITERATOR_HPP
# define RB_TREE_ITERATOR_HPP

# include "iterator_utils.hpp"
# include "ft_containers/srcs/utils/rb_tree.hpp"

namespace ft {
	
	template<typename Iterator>
	class rb_tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, Iterator> { // Cannot use regular_iterator because it's specialization on pointers is random_access_iterator_tag
		public:
			typedef rb_node<Iterator>							iterator_type;
			typedef ptrdiff_t									difference_type;
			typedef Iterator									value_type;
			typedef Iterator*									pointer;
			typedef Iterator&									reference;
			typedef typename ft::bidirectionnal_iterator_tag	iterator_category;

			rb_tree_iterator() : current_(NULL) {}
			
			explicit rb_tree_iterator(iterator_type *node) : current_(node) {}

			template <typename Iter>
			rb_tree_iterator(const rb_tree_iterator<Iter>& it) : current_(it.base()) {}

			~rb_tree_iterator() {}

			iterator_type base() const {
				return current_;
			}

			pointer operator->() const {
				return &(operator*());
			}

			reference operator*() const {
				return current_->value;
			}

			// https://stackoverflow.com/questions/12684191/implementing-an-iterator-over-binary-or-arbitrary-tree-using-c-11
            rb_tree_iterator& operator++() {
				iterator_type	*tmp;

				if (current_->right_ != NULL) {
					current_ = current_->right_;

					while (current_->left_ != NULL)
						current_ = current_->left_;
				} else {
					tmp = current_->parent_;

					while (current_ == tmp->right_) {
						current_ = tmp;
						tmp = tmp->parent_;
					}
					if (current_->right_ != tmp)
						current_ = tmp;
				}
				return *this;
            }

            rb_tree_iterator operator++(int) {
                rb_tree_iterator tmp(*this);

                ++(*this);
                return tmp;
            }

			rb_tree_iterator&	operator--(void) {
				iterator_type	*tmp;

				if (current_->left_ != NULL) {
					current_ = current_->left_;

					while (current_->right_ != NULL)
						current_ = current_->right_;
				} else {
					tmp = current_->parent_;

					while (current_ == tmp->left_) {
						current_ = tmp;
						tmp = tmp->parent_;
					}
					if (current_->left_ != tmp)
						current_ = tmp;
				}
				return *this;
			}

			rb_tree_iterator operator--(int) {
				rb_tree_iterator tmp(*this);

				--(*this);
				return (tmp);
			}
		protected:
			iterator_type *current_;
		private:
	};

	template <typename T>
	bool operator==(const rb_tree_iterator<T>& lhs, const rb_tree_iterator<T>& rhs) {
		return lhs.base() == rhs.base();
	}

	template <typename T>
	bool operator!=(const rb_tree_iterator<T>& lhs, const rb_tree_iterator<T>& rhs) {
		return !(lhs == rhs);
	}

	template<typename Iterator>
	class rb_tree_const_iterator : public ft::iterator<ft::bidirectional_iterator_tag, Iterator, std::ptrdiff_t, const Iterator*, const Iterator&> { // Cannot use regular_iterator because it's specialization on pointers is random_access_iterator_tag
		public:
			typedef rb_node<Iterator>							iterator_type;
			typedef ptrdiff_t									difference_type;
			typedef Iterator									value_type;
			typedef const Iterator*								pointer;
			typedef const Iterator&								reference;
			typedef typename ft::bidirectionnal_iterator_tag	iterator_category;

			rb_tree_const_iterator() : current_(NULL) {}
			
			explicit rb_tree_const_iterator(const iterator_type *node) : current_(node) {}

			template <typename Iter>
			rb_tree_const_iterator(const rb_tree_const_iterator<Iter>& it) : current_(it.base()) {}

			~rb_tree_iterator() {}

			iterator_type base() const {
				return current_;
			}

			pointer operator->() const {
				return &(operator*());
			}

			reference operator*() const {
				return current_->value;
			}

			// https://stackoverflow.com/questions/12684191/implementing-an-iterator-over-binary-or-arbitrary-tree-using-c-11
            rb_tree_const_iterator& operator++() {
				iterator_type	*tmp;

				if (current_->right_ != NULL) {
					current_ = current_->right_;

					while (current_->left_ != NULL)
						current_ = current_->left_;
				} else {
					tmp = current_->parent_;

					while (current_ == tmp->right_) {
						current_ = tmp;
						tmp = tmp->parent_;
					}
					if (current_->right_ != tmp)
						current_ = tmp;
				}
				return *this;
            }

            rb_tree_const_iterator operator++(int) {
                rb_tree_iterator tmp(*this);

                ++(*this);
                return tmp;
            }

			rb_tree_const_iterator&	operator--(void) {
				iterator_type	*tmp;

				if (current_->left_ != NULL) {
					current_ = current_->left_;

					while (current_->right_ != NULL)
						current_ = current_->right_;
				} else {
					tmp = current_->parent_;

					while (current_ == tmp->left_) {
						current_ = tmp;
						tmp = tmp->parent_;
					}
					if (current_->left_ != tmp)
						current_ = tmp;
				}
				return *this;
			}

			rb_tree_const_iterator operator--(int) {
				rb_tree_iterator tmp(*this);

				--(*this);
				return (tmp);
			}

			bool operator==(const rb_tree_const_iterator & x) const {
				return (m_current == x.m_current);
			}
			bool operator!=(const rb_tree_const_iterator & x) const {
				return (m_current != x.m_current);
			}
		protected:
			iterator_type *current_;
		private:
	};

	template <typename T>
	bool operator==(const rb_tree_const_iterator<T>& lhs, const rb_tree_iterator<T>& rhs) {
		return lhs.base() == rhs.base();
	}

	template <typename T>
	bool operator!=(const rb_tree_const_iterator<T>& lhs, const rb_tree_iterator<T>& rhs) {
		return !(lhs == rhs);
	}

}

#endif