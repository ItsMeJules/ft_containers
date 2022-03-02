#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

namespace ft {

    template <class T, class Alloc = std::allocator<T>>
    class vector {
        public:
            typedef T                           value_type;
            typedef Alloc                       allocator_type;
            typedef typename reference          allocator_type::reference;
            typedef typename const_reference    allocator_type::const_reference;
            typedef typename pointer            allocator_type:pointer;
            typedef typename const_pointer      allocator_type:const_pointer;
            typedef ft::iterator<ft::random_acc, >                
        protected:
        private:
    };
}

#endif