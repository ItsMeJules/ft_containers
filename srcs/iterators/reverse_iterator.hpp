#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include <typeinfo>
# include "regular_iterator.hpp"

namespace ft {

    template <class Iterator>
	class reverse_iterator : public regular_iterator<Iterator> {
		private:
		protected:
		public:
			typedef regular_iterator<Iterator>							super_class;
            typedef Iterator                                            iterator_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer         pointer;
            typedef typename iterator_traits<Iterator>::reference       reference;

			reverse_iterator() {}
			explicit reverse_iterator(Iterator it) : super_class::regular_iterator(it) {}
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& it) : super_class::regular_iterator(it.base()) {}
			~reverse_iterator() {}

			reference operator*() const {
				Iterator it = super_class::current_;

				return *(--it);
			}

			super_class operator+(difference_type n) const {
				return reverse_iterator(super_class::current_ - n);
			}

			super_class& operator++() {
				super_class::current_--;
				return *this;
			}

			super_class operator++(int) {
				reverse_iterator temp(*this);

				super_class::current_--;
				return temp;
			}

			super_class& operator+=(difference_type n) {
				super_class::current_ -= n;
				return *this;
			}

			super_class operator-(difference_type n) const {
				return reverse_iterator(super_class::current_ + n);
			}

			super_class& operator--() {
				super_class::current_++;
				return *this;
			}

			super_class operator--(int) {
				reverse_iterator temp(*this);

				++(*this);
				return temp;
			}

			super_class& operator-=(difference_type n) {
				super_class::current_ += n;
				return *this;
			}

			reference operator[](difference_type n) const {
				return super_class::current_[-n - 1];
			}
	};
}

#endif