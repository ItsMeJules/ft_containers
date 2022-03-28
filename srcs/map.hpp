#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include "utils/utility.hpp"
# include "iterators/regular_iterator.hpp"

namespace ft {
	template <typename Key, typename T,
		typename Compare = std::less<Key>,
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
			typedef typename ft::regular_iterator<pointer>			iterator;		
			typedef typename ft::regular_iterator<const_pointer>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

            typedef	ptrdiff_t									    difference_type;
            typedef std::size_t									    size_type;
			
			class value_compare : public ft::binary_function<value_type, value_type, bool> {
				public:
					key_compare	comp;

					value_compare(key_compare c = key_compare()) : comp(c) {}

					bool operator()(const value_type & x, const value_type & y) const {
						return comp(x.first, y.first);
					}
			};
		protected:
		private:
	};
}

#endif