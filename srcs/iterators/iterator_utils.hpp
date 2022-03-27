#ifndef ITERATOR_UTILS_HPP
# define ITERATOR_UTILS_HPP

# include <cstddef>

namespace ft {

    template <typename Category, typename T, typename Distance = std::ptrdiff_t, typename Pointer = T*, typename Reference = T&>
    struct iterator {
        public:
            typedef T         value_type;
            typedef Distance  difference_type;
            typedef Pointer   pointer;
            typedef Reference reference;
            typedef Category  iterator_category;
    };

    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template <typename Iterator>
    class iterator_traits {
        public:
            typedef typename Iterator::difference_type      difference_type;
            typedef typename Iterator::value_type           value_type;
            typedef typename Iterator::pointer              pointer;
            typedef typename Iterator::reference            reference;
            typedef typename Iterator::iterator_category    iterator_category;
    };

    template <typename T>
    class iterator_traits<T*> {
        public:
            typedef std::ptrdiff_t                  difference_type;
            typedef T                               value_type;
            typedef T*                              pointer;
            typedef T&                              reference;
            typedef ft::random_access_iterator_tag  iterator_category;
    };

    template <typename T>
    class iterator_traits<const T*> {
        public:
            typedef std::ptrdiff_t                  difference_type;
            typedef T                               value_type;
            typedef const T*                              pointer;
            typedef const T&                              reference;
            typedef ft::random_access_iterator_tag  iterator_category;
    };

}

#endif