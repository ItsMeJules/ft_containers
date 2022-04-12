#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "utils/utility.hpp"
# include "utils/functional.hpp"
# include "utils/rb_tree.hpp"
# include "iterators/regular_iterator.hpp"
# include "iterators/reverse_iterator.hpp"

namespace ft {
	template <typename Key, typename T,
		typename Compare = ft::less<Key>,
		typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;		
			typedef typename allocator_type::const_reference		const_reference;	
			typedef typename allocator_type::pointer				pointer;		
			typedef typename allocator_type::const_pointer			const_pointer;
			
			class value_compare : public ft::binary_function<value_type, value_type, bool> {
				public:
					key_compare	comp;

					value_compare(key_compare c = key_compare()) : comp(c) {}

					bool operator()(const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
					}
			};
		private:
			typedef ft::rb_btree<value_type, value_compare, allocator_type>	tree_type;

			tree_type tree_;
		public:
			typedef typename tree_type::iterator				iterator;
			typedef typename tree_type::const_iterator			const_iterator;
			typedef typename tree_type::reverse_iterator		reverse_iterator;
			typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;
			typedef typename tree_type::difference_type			difference_type;
			typedef	typename tree_type::size_type				size_type;
		
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: tree_(comp, alloc)
			{}

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: tree_(comp, alloc)
			{
				while (first != last) {
					if (tree_.find(*first) == tree_.end())
						tree_.insert(*first);
					first++;
				}
			}
			
			map(const map& src)
				: tree_(tree_type(src.tree_)) 
			{}

			~map() {}

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

			iterator insert(iterator position, const value_type & val) {
				iterator it = tree_.find(val);

				return (it == tree_.end() ? tree_.insert(position, val) : it);
			}

			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last) {
				while (first != last) {
					if (tree_.find(*first) == tree_.end())
						tree_.insert(*first);
					first++;
				}
			}

			void erase(iterator position) {
				tree_.erase(position);
			}

			size_type erase(const key_type& k) {
				return tree_.erase(ft::make_pair(k, mapped_type()));
			}

			void erase(iterator first, iterator last) {
				tree_.erase(first, last);
			}

			void swap(map& x) {
				tree_.swap(x.tree_);
			}

			void clear() {
				tree_.clear();
			}

			//OBSERVER
			key_compare	key_comp() const {
				return tree_.get_comparator().comp;
			}

			value_compare value_comp() const {
				return tree_.get_comparator();
			}

			//OPERATIONS
			iterator find(const key_type& k) {
				return tree_.find(ft::make_pair(k, mapped_type()));
			}

			const_iterator find(const key_type& k) const {
				return tree_.find(ft::make_pair(k, mapped_type()));
			}

			size_type count(const key_type& k) const {
				return (tree_.find(ft::make_pair(k, mapped_type())) != tree_.end() ? 1 : 0);
			}

			iterator lower_bound(const key_type& k) {
				iterator it = begin();

				while (it != end() && tree_.get_comparator()(*it, ft::make_pair(k, mapped_type())))
					it++;
				return it;
			}

			const_iterator lower_bound(const key_type& k) const {
				const_iterator it = begin();

				while (it != end() && tree_.get_comparator()(*it, ft::make_pair(k, mapped_type())))
					it++;
				return it;
			}

			iterator upper_bound(const key_type& k) {
				iterator it = begin();

				while (it != end() && !tree_.get_comparator()(*it, ft::make_pair(k, mapped_type())))
					it++;
				return it;
			}

			const_iterator upper_bound(const key_type& k) const {
				const_iterator it = begin();

				while (it != end() && !tree_.get_comparator()(*it, ft::make_pair(k, mapped_type())))
					it++;
				return it;
			}

			ft::pair<const_iterator, const_iterator> equal_range(const value_type& k) const {
				return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
			}

			ft::pair<iterator, iterator> equal_range(const value_type& k) {
				return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
			}

			//OPERATORS
			map& operator=(const map& x) {
				if (this != &x)
					tree_ = x.tree_;
				return (*this);
			}

			mapped_type& operator[](const key_type& k) {
				return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
			}
			
			allocator_type get_allocator() const {
				return tree_.get_allocator();
			}
	};
}

#endif