#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "regular_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft {

    template <class T, class Alloc = std::allocator<T>>
    class vector {
        public:
            typedef T                                       	    value_type;
            typedef Alloc											allocator_type;

            typedef typename allocator_type::reference      	    reference;
            typedef typename allocator_type::const_reference	    const_reference;
            typedef typename allocator_type::pointer        	    pointer;
            typedef typename allocator_type::const_pointer  	    const_pointer;

            typedef typename ft::regular_iterator<value_type>   	iterator;
            typedef typename ft::regular_iterator<const value_type>	const_iterator;
            typedef typename ft::reverse_iterator<iterator>   		reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef std::size_t												size_type;
        protected:
        private:
    };
}

#endif