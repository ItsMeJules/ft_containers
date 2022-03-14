#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

/*
    All template and struct was found on cplusplus.com
*/

namespace ft {

    template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator {
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

    template <class Iterator>
    class iterator_traits {
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::iterator_category    iterator_category;
    };

    template <class T>
    class iterator_traits<T*> {
        typedef std::ptrdiff_t              difference_type;
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef random_access_iterator_tag  iterator_category;
    };

    template <class T>
    class iterator_traits<const T*> {
        typedef std::ptrdiff_t              difference_type;
        typedef T                           value_type;
        typedef const T*                          pointer;
        typedef const T&                          reference;
        typedef random_access_iterator_tag  iterator_category;
    };

    template <class Iterator, class Container>
    class regular_iterator :
        public iterator<typename iterator_traits<Iterator>::iterator_category,
                        typename iterator_traits<Iterator>::value_type,
                        typename iterator_traits<Iterator>::difference_type,
                        typename iterator_traits<Iterator>::pointer,
                        typename iterator_traits<Iterator>::reference> {
        private:
        protected:
            Iterator current_;
        public:
            typedef Iterator                                            iterator_type;
            typedef Container                                           container_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer         pointer;
            typedef typename iterator_traits<Iterator>::reference       reference;

        regular_iterator() {}
        explicit regular_iterator(Iterator it) : current_(it) {}
        template <class Iter>
        regular_iterator(const regular_iterator<Iter> &it) : current_(it.base()) {}
        ~regular_iterator() {}

        iterator_type base() const {
            return current_;
        }

        reference operator*() const {
            return *current_;
        }

        regular_iterator operator+(difference_type n) const {
            return regular_iterator(current_ + n);
        }

        regular_iterator& operator++() {
            current_++;
            return *this;
        }

        regular_iterator operator++(int) {
            regular_iterator temp(*this);

            ++(*this);
            return temp;
        }

        regular_iterator &operator+=(difference_type n) {
            current_ += n;
            return *this;
        }

        regular_iterator operator-(difference_type n) const {
            return regular_iterator(current_ - n);
        }

        regular_iterator& operator--() {
            current_--;
            return *this;
        }

        regular_iterator operator--(int) {
            regular_iterator temp(*this);

            --(*this);
            return temp;
        }

        regular_iterator &operator-=(difference_type n) {
            current_ -= n;
            return *this;
        }

        pointer operator->() const {
            return &(operator*());
        }

        reference operator[](difference_type n) const {
            return current_[n];
        }
    };

    //IteratorL and IteratorR to compare const_iterator and non const iterator

    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator==(const regular_iterator<IteratorL, Container> &x, const regular_iterator<IteratorR, Container> &y) {
        return x.base() == y.base();
    }

    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator!=(const regular_iterator<IteratorL, Container> &x, const regular_iterator<IteratorR, Container> &y) {
        return x.base() != y.base();
    }

    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator<(const regular_iterator<IteratorL, Container> &x, const regular_iterator<IteratorR, Container> &y) {
        return x.base() < y.base();
    }

    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator<=(const regular_iterator<IteratorL, Container> &x, const regular_iterator<IteratorR, Container> &y) {
        return x.base() <= y.base();
    }

    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator>(const regular_iterator<IteratorL, Container> &x, const regular_iterator<IteratorR, Container> &y) {
        return x.base() > y.base();
    }

    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator>=(const regular_iterator<IteratorL, Container> &x, const regular_iterator<IteratorR, Container> &y) {
        return x.base() >= y.base();
    }

    template <class Iterator, class Container>
    class reverse_iterator :
        public iterator<typename iterator_traits<Iterator>::iterator_category,
                        typename iterator_traits<Iterator>::value_type,
                        typename iterator_traits<Iterator>::difference_type,
                        typename iterator_traits<Iterator>::pointer,
                        typename iterator_traits<Iterator>::reference> {
        private:
        protected:
            Iterator current_;
        public:
            typedef Iterator                                            iterator_type;
            typedef Container                                           container_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer         pointer;
            typedef typename iterator_traits<Iterator>::reference       reference;

        reverse_iterator() {}
        explicit reverse_iterator(Iterator it) : current_(it) {}
        template <class Iter>
        reverse_iterator(const reverse_iterator<Iter> &it) : current_(it.base()) {}
        ~reverse_iterator() {}

        iterator_type base() const {
            return current_;
        }

        reference operator*() const {
            Iterator it(current_);


            return (*(--it));
        }

        reverse_iterator operator+(difference_type n) const {
            return reverse_iterator(current_ - n);
        }

        reverse_iterator& operator++() {
            current_--;
            return *this;
        }

        reverse_iterator operator++(int) {
            reverse_iterator temp(*this);

            --(*this);
            return temp;
        }

        reverse_iterator &operator+=(difference_type n) {
            current_ -= n;
            return *this;
        }

        reverse_iterator operator-(difference_type n) const {
            return reverse_iterator(current_ + n);
        }

        reverse_iterator& operator--() {
            current_++;
            return *this;
        }

        reverse_iterator operator--(int) {
            reverse_iterator temp(*this);

            ++(*this);
            return temp;
        }

        reverse_iterator &operator-=(difference_type n) {
            current_ += n;
            return *this;
        }

        pointer operator->() const {
            return &(operator*());
        }

        reference operator[](difference_type n) const {
            return current_[-n - 1];
        }
    };

    //IteratorL and IteratorR to compare const_reverse_iterator and non const reverse_iterator

    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator==(const reverse_iterator<IteratorL, Container> &x, const reverse_iterator<IteratorR, Container> &y) {
        return x.base() == y.base();
    }

    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator!=(const reverse_iterator<IteratorL, Container> &x, const reverse_iterator<IteratorR, Container> &y) {
        return x.base() != y.base();
    }

    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator<(const reverse_iterator<IteratorL, Container> &x, const reverse_iterator<IteratorR, Container> &y) {
        return x.base() < y.base();
    }

    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator<=(const reverse_iterator<IteratorL, Container> &x, const reverse_iterator<IteratorR, Container> &y) {
        return x.base() <= y.base();
    }

    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator>(const reverse_iterator<IteratorL, Container> &x, const reverse_iterator<IteratorR, Container> &y) {
        return x.base() > y.base();
    }

    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator>=(const reverse_iterator<IteratorL, Container> &x, const reverse_iterator<IteratorR, Container> &y) {
        return x.base() >= y.base();
    }

}

#endif