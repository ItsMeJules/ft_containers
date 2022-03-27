#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "iterator_utils.hpp"

namespace ft {

    template <class Iterator>
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
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer         pointer;
            typedef typename iterator_traits<Iterator>::reference       reference;

            regular_iterator() {}
            explicit regular_iterator(Iterator it) : current_(it) {}
            template <class Iter>
            regular_iterator(const regular_iterator<Iter>& it) : current_(it.base()) {}
            virtual ~regular_iterator() {}

            iterator_type base() const {
                return current_;
            }

            virtual reference operator*() const {
                return *current_;
            }

            pointer operator->() const {
                return &(operator*());
            }

            virtual regular_iterator operator+(difference_type n) const {
                return regular_iterator(current_ + n);
            }

            virtual regular_iterator& operator++() {
                current_++;
                return *this;
            }

            virtual regular_iterator operator++(int) {
                regular_iterator temp(*this);

                ++(*this);
                return temp;
            }

            virtual regular_iterator &operator+=(difference_type n) {
                current_ += n;
                return *this;
            }

            virtual regular_iterator operator-(difference_type n) const {
                return regular_iterator(current_ - n);
            }

            virtual regular_iterator& operator--() {
                current_--;
                return *this;
            }

            virtual regular_iterator operator--(int) {
                regular_iterator temp(*this);

                current_--;
                return temp;
            }

            virtual regular_iterator &operator-=(difference_type n) {
                current_ -= n;
                return *this;
            }

            virtual reference operator[](difference_type n) const {
                return current_[n];
            }
    };

    template <typename IteratorL, typename IteratorR>
    bool operator==(const regular_iterator<IteratorL>& x, const regular_iterator<IteratorR>& y) {
        return x.base() == y.base();
    }

    template <typename IteratorL, typename IteratorR>
    bool operator!=(const regular_iterator<IteratorL>& x, const regular_iterator<IteratorR>& y) {
        return x.base() != y.base();
    }

    template <typename IteratorL, typename IteratorR>
    bool operator<(const regular_iterator<IteratorL>& x, const regular_iterator<IteratorR>& y) {
        return x.base() < y.base();
    }

    template <typename IteratorL, typename IteratorR>
    bool operator<=(const regular_iterator<IteratorL>& x, const regular_iterator<IteratorR>& y) {
        return x.base() <= y.base();
    }

    template <typename IteratorL, typename IteratorR>
    bool operator>(const regular_iterator<IteratorL>& x, const regular_iterator<IteratorR>& y) {
        return x.base() > y.base();
    }

    template <typename IteratorL, typename IteratorR>
    bool operator>=(const regular_iterator<IteratorL>& x, const regular_iterator<IteratorR>& y) {
        return x.base() >= y.base();
    }

	template <typename IteratorL, typename IteratorR>
	typename regular_iterator<IteratorL>::difference_type operator-(const regular_iterator<IteratorL>& lhs, const regular_iterator<IteratorR>& rhs) {
		return (lhs.base() - rhs.base());
	}

	template <typename Iterator>
	regular_iterator<Iterator> operator+(typename regular_iterator<Iterator>::difference_type n, const regular_iterator<Iterator>& it) {
		return (regular_iterator<Iterator>(it.base() + n));
	}
}

#endif