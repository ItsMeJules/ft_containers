#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include <typeinfo>
# include "regular_iterator.hpp"

namespace ft {

    template <class Iterator>
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
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer         pointer;
            typedef typename iterator_traits<Iterator>::reference       reference;

			reverse_iterator() {}
			explicit reverse_iterator(Iterator it) : current_(it) {}
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& it) : current_(it.base()) {}
			~reverse_iterator() {}

            iterator_type base() const {
                return current_;
            }

            pointer operator->() const {
                return &(operator*());
            }
			
			reference operator*() const {
				Iterator it = current_;

				return *(--it);
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

				current_--;
				return temp;
			}

			reverse_iterator& operator+=(difference_type n) {
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

			reverse_iterator& operator-=(difference_type n) {
				current_ += n;
				return *this;
			}

			reference operator[](difference_type n) const {
				return current_[-n - 1];
			}
	};

	template <typename IteratorL, typename IteratorR>
    bool operator==(const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) {
        return x.base() == y.base();
    }

    template <typename IteratorL, typename IteratorR>
    bool operator!=(const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) {
        return x.base() != y.base();
    }

    template <typename IteratorL, typename IteratorR>
    bool operator<(const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) {
        return x.base() < y.base();
    }

    template <typename IteratorL, typename IteratorR>
    bool operator<=(const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) {
        return x.base() <= y.base();
    }

    template <typename IteratorL, typename IteratorR>
    bool operator>(const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) {
        return x.base() > y.base();
    }

    template <typename IteratorL, typename IteratorR>
    bool operator>=(const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) {
        return x.base() >= y.base();
    }

	template <typename IteratorL, typename IteratorR>
	typename reverse_iterator<IteratorL>::difference_type operator-(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs) {
		return (lhs.base() - rhs.base());
	}

	template <typename Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it) {
		return (reverse_iterator<Iterator>(it.base() + n));
	}
}

#endif