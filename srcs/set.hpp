#ifndef SET_HPP
# define SET_HPP

# include <memory>
# include "utils/functional.hpp"
# include "utils/algorithm.hpp"
# include "utils/utility.hpp"
# include "utils/rb_tree.hpp"

namespace ft {
	template <typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> >
	class set {
		public:
			typedef T														key_type;
			typedef T														value_type;
			typedef Compare													value_compare;
			typedef Compare													key_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;		
			typedef typename allocator_type::const_reference				const_reference;	
			typedef typename allocator_type::pointer						pointer;		
			typedef typename allocator_type::const_pointer					const_pointer;

			typedef ft::rb_btree<value_type, value_compare, allocator_type>	btree_type;

			typedef typename btree_type::iterator							iterator;
			typedef typename btree_type::const_iterator						const_iterator;
			typedef typename btree_type::reverse_iterator					reverse_iterator;
			typedef typename btree_type::const_reverse_iterator				const_reverse_iterator;
			typedef typename btree_type::difference_type					difference_type;
			typedef	typename btree_type::size_type							size_type;
		private:
			btree_type tree_;
		
		public:
			explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: tree_(comp, alloc)
			{}
			
			template <class InputIterator>
  			set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: tree_(comp, alloc)
			{
				while (first != last) {
					if (tree_.find(*first) == tree_.end())
						tree_.insert(*first);
					first++;
				}
			}

			set(const set& x) : tree_(btree_type(x.tree_)) {}

			~set() {}

			//ITERATORS
			iterator begin() {
				return tree_.begin();
			}

			const_iterator begin() const {
				return tree_.begin();
			}

			iterator end() {
				return tree_.end();
			}

			const_iterator end() const {
				return tree_.end();
			}

			reverse_iterator rbegin() {
				return tree_.rbegin();
			}

			const_reverse_iterator rbegin() const {
				return tree_.rbegin();
			}

			reverse_iterator rend() {
				return tree_.rend();
			}

			const_reverse_iterator rend() const {
				return tree_.rend();
			}

			// CAPACITY
			bool empty() const {
				return tree_.empty();
			}

			size_type size() const {
				return tree_.size();
			}

			size_type max_size() const {
				return tree_.max_size();
			}

			//MODIFIERS
			ft::pair<iterator, bool> insert(const value_type& val) {
				iterator it = tree_.find(val);

				return (it == tree_.end() ? ft::make_pair(tree_.insert(val), true) : ft::make_pair(it, false));
			}

			iterator insert(iterator position, const value_type& val) {
				iterator it = tree_.find(val);

				return (it == tree_.end() ? tree_.insert(position, val) : it);
			}

			template <class InputIterator>
  			void insert(InputIterator first, InputIterator last) {
				while (first != last) {
					if (tree_.find(*first) == tree_.end())
						tree_.insert(*first);
					first++;
				}
			}

			void erase(iterator position) {
				tree_.erase(position);
			}

			size_type erase(const value_type& val) {
				return tree_.erase(val);
			}

			void erase(iterator first, iterator last) {
				tree_.erase(first, last);
			}

			void swap(set& x) {
				tree_.swap(x.tree_);
			}

			void clear() {
				tree_.clear();
			}

			//OBSERVER
			key_compare	key_comp() const {
				return tree_.get_comparator();
			}

			value_compare value_comp() const {
				return tree_.get_comparator();
			}

			//OPERATIONS
			iterator find(const value_type& val) {
				return tree_.find(val);
			}

			size_type count(const value_type& val) const {
				return (tree_.find(val) != tree_.end() ? 1 : 0);
			}

			iterator lower_bound(const value_type& val) const {
				const_iterator it = begin();

				while (it != end() && tree_.get_comparator()(*it, val))
					it++;
				return iterator(it.base());
			}

			iterator upper_bound(const value_type& val) const {
				const_iterator it = begin();

				while (it != end() && !tree_.get_comparator()(val, *it))
					it++;
				return iterator(it.base());
			}

			ft::pair<iterator, iterator> equal_range(const value_type& val) const {
				return ft::pair<iterator, iterator>(lower_bound(val), upper_bound(val));
			}

			allocator_type get_allocator() const {
				return tree_.get_allocator();
			}
	};

	template<typename T, typename Compare, typename Alloc>
	bool operator==(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		if (lhs.size() == rhs.size())
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		else
			return false;
	}

	template<typename T, typename Compare, typename Alloc>
	bool operator!=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template<typename T, typename Compare, typename Alloc>
	bool operator<(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<typename T, typename Compare, typename Alloc>
	bool operator<=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template<typename T, typename Compare, typename Alloc>
	bool operator>(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return rhs < lhs;
	}

	template<typename T, typename Compare, typename Alloc>
	bool operator>=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template<typename T, typename Compare, typename Alloc>
	void swap(const set<T, Compare, Alloc>& x, const set<T, Compare, Alloc>& y) {
		x.swap(y);
	}
}

#endif