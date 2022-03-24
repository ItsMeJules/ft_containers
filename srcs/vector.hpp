#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "regular_iterator.hpp"
# include "reverse_iterator.hpp"
# include "type_traits.hpp"

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

            explicit vector(const allocator_type& alloc = allocator_type()) : alloc_(alloc) {}
            explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) : alloc_(alloc), size_(n) {
                     for (size_type i = 0; i < n; i++)

                 }

            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
            vector (const vector& x);

            /* ITERATORS */
            iterator begin() {
                return iterator(start_);
            }

            const_iterator begin() const {
                return const_iterator(start_);
            }

            iterator end() {
				return iterator(start_ + size_);
			}

			const_iterator end() const {
				return const_iterator(start_ + size_);
			}

			reverse_iterator rbegin() {
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(end());
			}

			reverse_iterator rend() {
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend() const {
				return const_reverse_iterator(begin());
			}

            /* CAPACITY */
            size_type size() const {
                return size_;
            }

            size_type max_size() const {
                return alloc_.max_size();
            }

            void resize(size_type n, value_type val = value_type()) {
                if (n < size_)
                    erase(end() - (size_ - n), end());
                else if (n > size_)
                    insert(end(), n - size_, val);
            }

            size_type capacity() const {
                return capacity_;
            }

            bool empty() const {
                return size_ == 0;
            }

            void reserve(size_type n) {
                if (capacity_ <= n) {
                    vector<T> tmp(*this);

                    clear();
                    alloc_.deallocate(start_, size_);
                    start_ = alloc_.allocate(n);
                    capacity_ =  n;
                    for (iterator it = tmp.begin(); it != tmp.end(); it++) {
                        alloc_.construct(start_ + size_, *it);
                        size_++;
                    }
                }
            }
            
            /* MODIFIERS */
            template <class InputIterator>
            void assign(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
                for (iterator it = begin(); i != end(); it++)
                    alloc_.destroy(&(*it));

                size_type size = 0;
                InputIterator tmp = first;
                while (tmp != last) {
                    tmp++;
                    size++;
                }
                if (size >= capacity_) {
                    alloc_.deallocate(start_, capacity_);
                    capacity_ = size;
                    pointer_ = alloc_.allocate(size);
                }

                size_ = 0;
                for (InputIterator it = first; it != last; it++)
                    push_back(*it);
            }

            void assign(size_type n, const value_type& val) {
                for (iterator it = begin(); it != end(); it++)
                    alloc_.destroy(&(*it));
                if (n >= capacity_) {
                    alloc_.deallocate(start_, capacity_);
                    capacity_ = n;
                    pointer_ = alloc_.allocate(n);
                }
                size_ = 0;
                for (size_type i = 0; i < n; i++)
                    push_back(val);
            }

            void push_back(const value_type& val) {
                if (capacity_  <= size_) {
                    if (capacity_ == 0)
                        reserve(1);
                    else
                        reserve(capacity_ * 2);
                }
                alloc_.construct(start_ + size_, val);
                size_++;
            }

            void pop_back() {
                size_--;
                alloc_.destroy(start_ + size_);
            }

            void clear() {
                while (size_ != 0)
                    pop_back();
            }

            iterator erase(iterator position) {
                alloc_.destroy(&(*position));
                for (it = position; it != end() - 1; it++) {
                    alloc_.construct(&(*it), (*it) + 1);
                    alloc_.destroy(&(*(it + 1)));
                }
                size_--;
                return position;
            }

            iterator erase(iterator first, iterator last) {
                for (it = first; it != last; last--)
                    erase(it);
                return first;
            }

            iterator	insert(iterator position, const value_type& val) {
				difference_type	diff = position - begin();
				
				if (size_ + 1 > capacity_) {
					if (size_ * 2 > size_ + 1)
						reserve(size_ * 2);
					else
						reserve(size_ + 1);
				}

				iterator iter = end();
				for (; iter != begin() + diff; iter--) {
					alloc_.construct(&(*iter), *(iter - 1));
					alloc_.destroy(&(*(iter - 1)));
				}
				malloc_.construct(&(*iter), val);
				size_++;
				return (iter);
		    }


            void insert(iterator position, size_type n, const value_type& val) {
			    difference_type	diff = position - begin();

				if (!n)
					return ;
				if (size_ + n > capacity_) {
					if (size_ * 2 > size_ + n)
						reserve(size_ * 2);
					else
						reserve(size_ + n);
				}
				while (n--)
					insert(begin() + diff, val);
            }

            template <class InputIterator>
			void	insert(iterator position, InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
                difference_type	diff = position - begin();
				
				difference_type len = 0;
				for (InputIterator it = first; it != last; it++)
					len++;
				if (size_ + len > m_capacity) {
					if (size_ * 2 > size_ + len)
						reserve(size_ * 2);
					else
						reserve(size_ + len);
				}
				for (difference_type i = 0; first != last; first++, i++)
					insert(begin() + diff + i, *first);
            }

        private:
            allocator_type alloc_;
            size_type size_;
            size_type capacity_;
            pointer start_;
        protected:
    };
}

#endif